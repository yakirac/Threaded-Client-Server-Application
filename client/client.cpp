#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QtNetwork>
#include "client.h"
#include "registerdialog.h"

Client::Client(QWidget *parent)
    : QDialog(parent), networkSession(0)
{
	 // find out which IP to connect to
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	// use the first non-localhost IPv4 address
	for (int i = 0; i < ipAddressesList.size(); ++i) {
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			ipAddress = ipAddressesList.at(i).toString();
			break;
		}
	}
	// if we did not find one, use IPv4 localhost
	if (ipAddress.isEmpty())
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

	userLabel = new QLabel("Username: ");
	passLabel = new QLabel("Password: ");
	statusLabel = new QLabel();

	userLineEdit = new QLineEdit();
	passLineEdit = new QLineEdit();
	passLineEdit->setEchoMode(QLineEdit::Password);

	registerButton = new QPushButton("Register");
	loginButton = new QPushButton("Login");
	cancelButton = new QPushButton("Cancel");

	buttonBox = new QDialogButtonBox();
	buttonBox->addButton(registerButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(loginButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

	mainLayout = new QGridLayout;
	mainLayout->addWidget(userLabel, 0, 0, 1, 2);
	mainLayout->addWidget(userLineEdit, 1, 0, 1, 5);
	mainLayout->addWidget(passLabel, 2, 0, 1, 2);
	mainLayout->addWidget(passLineEdit, 3, 0, 1, 5);
	mainLayout->addWidget(statusLabel, 4, 0, 3, 4);
	mainLayout->addWidget(buttonBox, 7, 1, 1, 2);

	setLayout(mainLayout);

	tcpSocket = new QTcpSocket(this);

	connect(registerButton, SIGNAL(clicked()), this, SLOT(registerWithServer()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(loginButton, SIGNAL(clicked()), this, SLOT(requestNewConnection()));
	connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendLoginInfo()));
	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(updateLabels()));
	//connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));

	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
		// Get saved network configuration
		QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		settings.endGroup();

		// If the saved network configuration is not currently discovered use the system default
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) !=
			QNetworkConfiguration::Discovered) {
			config = manager.defaultConfiguration();
		}

		networkSession = new QNetworkSession(config, this);
		connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

		statusLabel->setText(tr("Opening network session."));
		networkSession->open();
	}

}

void Client::connectionClosedByServer(){
	statusLabel->setText("Error: Connection closed by server");
}

void Client::requestNewConnection(){
	blockSize = 0;
	tcpSocket->abort();
	if((cLayout.compare("Move") == 0 && !userLineEdit->text().isEmpty())
			|| (cLayout.compare("Locate") == 0 && !userLineEdit->text().isEmpty())){
		tcpSocket->connectToHost(ipAddress, 49209);
	}
	else if(!(userLineEdit->text().isEmpty()) && !(passLineEdit->text().isEmpty())){
		tcpSocket->connectToHost(ipAddress, 49209);
	}else if(!cLayout.compare("Move") == 0 && !cLayout.compare("Locate") == 0){
		statusLabel->setText("Please enter a username and a password");
	}
}

void Client::registerWithServer(){
	RegisterDialog rd(this);
	if(rd.exec()){
		QString name = rd.name();
		QString pass = rd.pass();
		userLineEdit->setText(name);
		passLineEdit->setText(pass);

		disconnect(tcpSocket, SIGNAL(connected()), this, SLOT(sendLoginInfo()));
		requestNewConnection();
		connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendRegistration()));
	}
}

void Client::sendRegistration(){
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	out << quint16(0) << quint8('R') << userLineEdit->text() << passLineEdit->text();

	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));
	tcpSocket->write(block);

	//ui.label->setText(tr("Sending request..."));
	//printf("In sendRegistration. Sending Request...\n");
}

void Client::sendLoginInfo(){
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	out << quint16(0) << quint8('L') << userLineEdit->text() << passLineEdit->text();

	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));
	tcpSocket->write(block);

	//ui.label->setText(tr("Sending request..."));
	//printf("Sending Request...\n");
}

void Client::sendFile(){
	QByteArray block;
	//QFile *file = new QFile(userLineEdit->text());
	//file->open(QIODevice::ReadOnly);
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	QString file = userLineEdit->text();
	if(!userLineEdit->text().isEmpty()){
		//printf("File from edit: %s\n", qPrintable(file));
		out << quint16(0) << quint8('F') << userLineEdit->text();
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		tcpSocket->write(block);
	}else{
		statusLabel->setText("Please choose a file to move to the server");
	}

	//ui.label->setText(tr("Sending request..."));
	//printf("Sending Request...\n");
}

void Client::sendSearchInfo(){
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	//if(!userLineEdit->text().isEmpty()){
		out << quint16(0) << quint8('S') << userLineEdit->text();
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		tcpSocket->write(block);
	//}else{
	//	statusLabel->setText("Please enter a file to search for");
	//}

	//ui.label->setText(tr("Sending request..."));
	//printf("Sending Request...\n");
}


void Client::updateLabels(){
	QDataStream in(tcpSocket);
	in.setVersion(QDataStream::Qt_4_0);

	if (blockSize == 0) {
		if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
			return;

		in >> blockSize;
	}

	if (tcpSocket->bytesAvailable() < blockSize)
		return;


	QString status;
	in >> status;

	message = status;
	//statusLabel->setText(status);
	//printf("Status: %s\n", qPrintable(status));
	if(status.compare("You have logged in to the server") == 0){
		createMenuLayout();
	}else if(status.compare("We received your file.") == 0){
		//printf("got it");
		statusLabel->setText(status);
	}else if(status.compare("You have registered with the server.") == 0){
		createMenuLayout();
	}else if(status.compare("Results coming") == 0){
		in >> fileList;
		if(fileList.isEmpty()){
			//printf("The file list is empty");
			statusLabel->setText("No files were found");
		}
		for(int i = 0; i < fileList.size(); ++i){
			new QListWidgetItem(fileList.at(i), resultList);
		}
	}else{
		statusLabel->setText(status);
	}
}

void Client::browseForFile(){
	QString file = QFileDialog::getOpenFileName(this,
			                               tr("Find Files"));
	QFileInfo f(file);
	file = f.fileName();

	if (!file.isEmpty()) {
		userLineEdit->setText(file);
	}
}

void Client::sessionOpened(){
	// Save the used configuration
	QNetworkConfiguration config = networkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice)
		id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
	else
		id = config.identifier();

	QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
	settings.beginGroup(QLatin1String("QtNetwork"));
	settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
	settings.endGroup();

	statusLabel->setText(tr("This examples requires that you run the "
							"Fortune Server example as well."));
}

void Client::displayError(QAbstractSocket::SocketError socketError){
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
								 .arg(tcpSocket->errorString()));
	}
}

void Client::reloadMenu(){
	if(cLayout.compare("Move") == 0){
		delete userLabel;
		delete userLineEdit;
		delete statusLabel;
		delete browseButton;
		delete menuButton;
		delete moveFilesButton;
		delete cancelButton;
		delete buttonBox;

		statusLabel = new QLabel();
		userLabel = new QLabel("Move Files");
		passLabel = new QLabel("Locate Files");

		moveButton = new QPushButton("Move");
		locateButton = new QPushButton("Locate");
		cancelButton = new QPushButton("Cancel");

		mainLayout->addWidget(statusLabel, 0, 4, 1, 1);
		mainLayout->addWidget(userLabel, 1, 4, 1, 1);
		mainLayout->addWidget(moveButton, 2, 4, 1, 1);
		mainLayout->addWidget(passLabel, 3, 4, 1, 1);
		mainLayout->addWidget(locateButton, 4, 4, 1, 1);
		mainLayout->addWidget(cancelButton, 5, 4, 1, 1);

		setLayout(mainLayout);

		connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
		connect(moveButton, SIGNAL(clicked()), this, SLOT(createMoveLayout()));
		connect(locateButton, SIGNAL(clicked()), this, SLOT(createLocateLayout()));
	}
	else if (cLayout.compare("Locate") == 0){
		delete userLineEdit;
		delete searchButton;
		delete userLabel;
		delete resultList;
		delete statusLabel;
		delete menuButton;
		delete openButton;
		delete cancelButton;
		delete buttonBox;

		statusLabel = new QLabel();
		userLabel = new QLabel("Move Files");
		passLabel = new QLabel("Locate Files");

		moveButton = new QPushButton("Move");
		locateButton = new QPushButton("Locate");
		cancelButton = new QPushButton("Cancel");

		mainLayout->addWidget(statusLabel, 0, 4, 1, 1);
		mainLayout->addWidget(userLabel, 1, 4, 1, 1);
		mainLayout->addWidget(moveButton, 2, 4, 1, 1);
		mainLayout->addWidget(passLabel, 3, 4, 1, 1);
		mainLayout->addWidget(locateButton, 4, 4, 1, 1);
		mainLayout->addWidget(cancelButton, 5, 4, 1, 1);

		setLayout(mainLayout);

		connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
		connect(moveButton, SIGNAL(clicked()), this, SLOT(createMoveLayout()));
		connect(locateButton, SIGNAL(clicked()), this, SLOT(createLocateLayout()));
	}
}

void Client::printStatus(){
	printf("You are connected again\n");
	//statusLabel->setText("You are connected");
}

void Client::createMenuLayout(){
	delete userLabel;
	delete userLineEdit;
	delete passLabel;
	delete passLineEdit;
	delete statusLabel;
	delete registerButton;
	delete loginButton;
	delete cancelButton;
	delete buttonBox;

	statusLabel = new QLabel(message);
	userLabel = new QLabel("Move Files");
	passLabel = new QLabel("Locate Files");

	moveButton = new QPushButton("Move");
	locateButton = new QPushButton("Locate");
	cancelButton = new QPushButton("Cancel");

	mainLayout->addWidget(statusLabel, 0, 4, 1, 1);
	mainLayout->addWidget(userLabel, 1, 4, 1, 1);
	mainLayout->addWidget(moveButton, 2, 4, 1, 1);
	mainLayout->addWidget(passLabel, 3, 4, 1, 1);
	mainLayout->addWidget(locateButton, 4, 4, 1, 1);
	mainLayout->addWidget(cancelButton, 5, 4, 1, 1);

	setLayout(mainLayout);

	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(moveButton, SIGNAL(clicked()), this, SLOT(createMoveLayout()));
	connect(locateButton, SIGNAL(clicked()), this, SLOT(createLocateLayout()));

}

void Client::createMoveLayout(){
	delete statusLabel;
	delete userLabel;
	delete moveButton;
	delete passLabel;
	delete locateButton;
	delete cancelButton;

	disconnect(tcpSocket, SIGNAL(connected()), this, SLOT(sendLoginInfo()));
	if(cLayout.compare("Locate") == 0){
		disconnect(tcpSocket, SIGNAL(connected()), this, SLOT(sendSearchInfo()));
	}


	userLabel = new QLabel("File to move:");
	userLineEdit = new QLineEdit();
	browseButton = new QPushButton("Browse");
	statusLabel = new QLabel();
	menuButton = new QPushButton("Menu");
	moveFilesButton = new QPushButton("Move Files");
	cancelButton = new QPushButton("Cancel");

	buttonBox = new QDialogButtonBox;
	buttonBox->addButton(menuButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(moveFilesButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

	mainLayout->addWidget(userLabel, 0, 0, 1, 1);
	mainLayout->addWidget(userLineEdit, 1, 0, 1, 4);
	mainLayout->addWidget(browseButton, 1, 4, 1, 1);
	mainLayout->addWidget(statusLabel, 2, 1, 1, 4);
	mainLayout->addWidget(buttonBox, 3, 1, 1, 3);

	setLayout(mainLayout);

	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(moveFilesButton, SIGNAL(clicked()), this, SLOT(requestNewConnection()));
	connect(menuButton, SIGNAL(clicked()), this, SLOT(reloadMenu()));
	connect(browseButton, SIGNAL(clicked()), this, SLOT(browseForFile()));
	connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendFile()));
	cLayout = "Move";

}

void Client::createLocateLayout(){
	delete statusLabel;
	delete userLabel;
	delete moveButton;
	delete passLabel;
	delete locateButton;
	delete cancelButton;

	disconnect(tcpSocket, SIGNAL(connected()), this, SLOT(sendLoginInfo()));
	if(cLayout.compare("Move") == 0){
		disconnect(tcpSocket, SIGNAL(connected()), this, SLOT(sendFile()));
	}

	userLineEdit = new QLineEdit();
	searchButton = new QPushButton("Search");
	userLabel = new QLabel("Results");
	resultList = new QListWidget();
	statusLabel = new QLabel();
	menuButton = new QPushButton("Menu");
	openButton = new QPushButton("Open");
	cancelButton = new QPushButton("Cancel");

	buttonBox = new QDialogButtonBox;
	buttonBox->addButton(menuButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(openButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

	mainLayout->addWidget(userLineEdit, 0, 0, 1, 3);
	mainLayout->addWidget(searchButton, 0, 3, 1, 1);
	mainLayout->addWidget(userLabel, 1, 0, 1, 1);
	mainLayout->addWidget(resultList, 2, 0, 3, 3);
	mainLayout->addWidget(statusLabel, 5, 1, 1, 3);
	mainLayout->addWidget(buttonBox, 6, 1, 1, 3);

	setLayout(mainLayout);

	connect(searchButton, SIGNAL(clicked()), this, SLOT(requestNewConnection()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(menuButton, SIGNAL(clicked()), this, SLOT(reloadMenu()));
	connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendSearchInfo()));
	cLayout = "Locate";
}


