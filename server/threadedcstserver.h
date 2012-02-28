#ifndef THREADEDCSTSERVER_H
#define THREADEDCSTSERVER_H

#include <QTcpServer>

class ThreadedCSTServer : public QTcpServer
{
	Q_OBJECT
public:
    ThreadedCSTServer(QObject *parent = 0);

private:
    void incomingConnection(int socketId);
};

#endif // THREADEDCSTSERVER_H

