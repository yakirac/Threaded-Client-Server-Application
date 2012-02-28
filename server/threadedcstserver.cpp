#include "threadedcstserver.h"
#include "clientsocket.h"
#include "serverthread.h"

ThreadedCSTServer::ThreadedCSTServer(QObject *parent)
    : QTcpServer(parent)
{

}

void ThreadedCSTServer::incomingConnection(int socketId){
	//ClientSocket *socket = new ClientSocket(this);
	//socket->setSocketDescriptor(socketId);
	ServerThread *thread = new ServerThread(this, socketId);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

