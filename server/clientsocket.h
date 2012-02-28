/*
 * clientsocket.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Yogi
 */

#ifndef CLIENTSOCKET_H_
#define CLIENTSOCKET_H_

#include <QTcpSocket>

class ClientSocket : public QTcpSocket
{
	Q_OBJECT
public:
	ClientSocket(QObject *parent = 0);

private slots:
	void readClient();

private:
	void generateReply(const QString &name, const QString &pass);
	void registerClient(const QString &name, const QString &pass);
	void readFile(QString &file);
	void loadLoginFile();
	void saveUserPass();
	void searchForFile(QString &text);
	quint16 nextBlockSize;
	qint64 cposition;
	QMap<QString, QString> loginInfo;
	QList<QString> fileList;
};

#endif /* CLIENTSOCKET_H_ */

