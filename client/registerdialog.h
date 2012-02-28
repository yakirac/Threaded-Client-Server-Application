#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QtGui/QDialog>
#include <QTcpSocket>
#include "ui_registerdialog.h"


class RegisterDialog : public QDialog
{
    Q_OBJECT

public: QString name(){
    	return ui.nameEdit->text();
    }
public: QString pass(){
    	return ui.passEdit->text();
    }

public:
    RegisterDialog(QWidget *parent = 0);

private slots:
	void connectToServer();
	void sendRequest();
	void updateLabels();
	void displayError(QAbstractSocket::SocketError socketError);
	void connectionClosedByServer();

private:
    Ui::RegisterDialogClass ui;
    void closeConnection();
    QTcpSocket tcpSocket;
	quint16 nextBlockSize;
	QString ipAddress;
};

#endif // REGISTERDIALOG_H
