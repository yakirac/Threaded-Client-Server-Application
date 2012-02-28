#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>


class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);

private slots:
	void requestNewConnection();
	void registerWithServer();
    void browseForFile();
    void connectionClosedByServer();
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();
    void sendLoginInfo();
    void sendRegistration();
    void sendSearchInfo();
    void updateLabels();
    void reloadMenu();
    void printStatus();
    void createMoveLayout();
    void createLocateLayout();
    void sendFile();

private:
    void createMenuLayout();
	void closeConnection();
	void addItems();
    QLabel *userLabel;
	QLabel *passLabel;
	QLineEdit *userLineEdit;
	QLineEdit *passLineEdit;
	QLabel *statusLabel;
	QPushButton *loginButton;
	QPushButton *cancelButton;
	QPushButton *registerButton;
	QPushButton *moveButton;
	QPushButton *locateButton;
	QPushButton *menuButton;
	QPushButton *moveFilesButton;
	QPushButton *browseButton;
	QPushButton *searchButton;
	QPushButton *openButton;
	QListWidget *resultList;


	QComboBox *comboBox;

	QDialogButtonBox *buttonBox;

	QGridLayout *mainLayout;

	QTcpSocket *tcpSocket;
	QString ipAddress;
	quint16 blockSize;

	QNetworkSession *networkSession;

	QString cLayout;
	QString message;
	QList<QString> fileList;

};

#endif // CLIENT_H

