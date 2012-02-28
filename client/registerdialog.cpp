#include <QtNetwork>
#include <QMessageBox>
#include "registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	//connect(&tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
	//connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
	//connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(updateLabels()));
	//connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));

	QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
	for(int i = 0; i < ipAddressList.size(); ++i){
		if(ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address()){
			ipAddress = ipAddressList.at(i).toString();
			break;
		}
	}
	if(ipAddress.isEmpty()){
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	}

	//ui.cancelButton->setEnabled(false);
	ui.statusLabel->setText("When you are done typing in a username and password,\n click ok then click register again to register with the server.");
}

void RegisterDialog::connectToServer(){
	tcpSocket.connectToHost(ipAddress, 34);

	//ui.label->setText("Connecting to server...");
	printf("Connecting to server...\n");
	nextBlockSize = 0;
}

void RegisterDialog::sendRequest(){
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	out << quint16(0) << quint8('R') << ui.nameEdit->text() << ui.passEdit->text();

	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));
	tcpSocket.write(block);

	//ui.label->setText(tr("Sending request..."));
	printf("Sending Request...\n");
}

void RegisterDialog::updateLabels(){
	QDataStream in(&tcpSocket);
	in.setVersion(QDataStream::Qt_4_1);

	forever{
		if(nextBlockSize == 0){
			if(tcpSocket.bytesAvailable() < sizeof(quint16)){
				break;
			}
			in >> nextBlockSize;
		}

		if(nextBlockSize == 0xFFFF){
			closeConnection();
			//ui.label->setText(tr("Finished reading from server"));
			break;
		}

		if(tcpSocket.bytesAvailable() < nextBlockSize){
			break;
		}

		QString status;

		in >> status;

		printf("The status from the server is: %s\n", qPrintable(status));

		ui.statusLabel->setText(status);

		nextBlockSize = 0;
		//ui.cancelButton->setEnabled(true);
	}
}

void RegisterDialog::displayError(QAbstractSocket::SocketError socketError){
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(this, tr("Client"),
								 tr("The host was not found. Please check the "
									"host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information(this, tr("Client"),
								 tr("The connection was refused by the peer. "
									"Make sure the fortune server is running, "
									"and check that the host name and port "
									"settings are correct."));
		break;
	default:
		QMessageBox::information(this, tr("Client"),
								 tr("The following error occurred: %1.")
								 .arg(tcpSocket.errorString()));
	}
}

void RegisterDialog::closeConnection(){
	tcpSocket.close();
}

void RegisterDialog::connectionClosedByServer(){
	if(nextBlockSize != 0xFFFF){
		ui.statusLabel->setText("Error: Connection closed by server");
		//printf("Error: Connection closed by server...\n");
		closeConnection();
	}
}
