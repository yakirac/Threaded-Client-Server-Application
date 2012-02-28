/*
 * serverthread.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Yogi
 */

#ifndef SERVERTHREAD_H_
#define SERVERTHREAD_H_

#include <QThread>

class ServerThread : public QThread{
	Q_OBJECT
public:
	ServerThread(QObject *parent, int socketDescriptor);

	void run();

private:
	int socketDescriptor;
};

#endif /* SERVERTHREAD_H_ */

