/*
 * serverthread.cpp
 *
 *  Created on: Dec 5, 2010
 *      Author: Yogi
 */

#include "serverthread.h"
#include "clientsocket.h"

ServerThread::ServerThread(QObject *parent, int socketDescriptor)
: QThread(parent), socketDescriptor(socketDescriptor)
{


}

void ServerThread::run(){
	ClientSocket *socket = new ClientSocket(this);
	socket->setSocketDescriptor(socketDescriptor);

	this->exec();

	this->exit(0);
}
