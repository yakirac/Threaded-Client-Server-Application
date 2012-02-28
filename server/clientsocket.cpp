/*
 * clientsocket.cpp
 *
 *  Created on: Dec 5, 2010
 *      Author: Yogi
 */

#include <QTcpSocket>
#include <QFile>
#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent)
: QTcpSocket(parent)
{
	connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
	connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

	nextBlockSize = 0;
	loadLoginFile();

}
void ClientSocket::readClient(){
	QDataStream in(this);
	in.setVersion(QDataStream::Qt_4_1);

	if(nextBlockSize == 0){
		if(bytesAvailable() < sizeof(quint16)){
			return;
		}
		in >> nextBlockSize;
	}

	if(bytesAvailable() < nextBlockSize){
		return;
	}

	quint8 requestType;
	QString user;
	QString pass;
	QString f;
	QString search;

	in >> requestType;

	if(requestType == 'L'){
		in >> user >> pass;

		//printf("the user name is: %s\n", qPrintable(user));
		//printf("the password is: %s\n", qPrintable(pass));

		generateReply(user, pass);

		//QDataStream out(this);
		//out << quint16(0xFFFF);
		this->disconnectFromHost();
	}else if(requestType == 'R'){
		in >> user >> pass;
		//printf("the user name is: %s\n", qPrintable(user));
		//printf("the password is: %s\n", qPrintable(pass));

		registerClient(user, pass);

		//QDataStream out(this);
		//out << quint16(0xFFFF);
		this->disconnectFromHost();
	}
	else if(requestType == 'F'){
		//printf("Trying to read in QByteArray from client.\n");
		in >> f;
		readFile(f);

		//QDataStream out(this);
		//out << quint16(0xFFFF);
		this->disconnectFromHost();
	}else if(requestType == 'S'){
		printf("Got your search request\n");
		in >> search;
		searchForFile(search);
	}

	//close();

}

void ClientSocket::loadLoginFile(){
	QFile file("userpass.dat");
	file.open(QIODevice::ReadOnly);

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_1);
	in >> loginInfo;
}

void ClientSocket::saveUserPass(){
	QFile file("userpass.dat");
	file.open(QIODevice::WriteOnly);

	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_1);

	out << loginInfo;
}

void ClientSocket::generateReply(const QString &user, const QString &pass){
	//printf("in the generateReply method\n");
	//printf("the user name is: %s\n", qPrintable(user));
	//printf("the password is: %s\n", qPrintable(pass));
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	QString logged;
	if(loginInfo.contains(user)){
		if(loginInfo.value(user).compare(pass) == 0){
			logged = "You have logged in to the server";
			out << quint16(0) << logged;
		}
		else{
			logged = "Your username and password were not correct.\n Please try again or Register.";
			out << quint16(0) << logged;
		}
	}
	else{
		logged = "Your username and password were not correct.\n Please try again or Register.";
		out << quint16(0) << logged;
	}
	out << quint16(0) << logged;
	//printf("sent the logged message to the data stream\n");
	//printf("the message is: %s\n", qPrintable(logged));
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));

	write(block);
	nextBlockSize = 0;

}

void ClientSocket::registerClient(const QString &name, const QString &pass){
	loginInfo.insertMulti(name, pass);
	saveUserPass();

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	QString logged = "You have registered with the server.";

	out << quint16(0) << logged;
	//printf("sent the logged message to the data stream\n");
	//printf("the message is: %s\n", qPrintable(logged));
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));

	write(block);
	nextBlockSize = 0;
}

void ClientSocket::readFile(QString &file){
	//printf("In readFile.\n");
	QString f = file;
	//printf("File: %s\n", qPrintable(f));
	QFile writefile("savesFiles.txt");
	writefile.open(QIODevice::WriteOnly | QIODevice::Append);
//	if(writefile.exists()){
//		printf("this file exists\n");
//		if(!writefile.openMode() == 0x0000){
//			printf("The file is open");
//		}
//	}
	cposition = writefile.pos();
	QTextStream writeOut(&writefile);
	writeOut.device()->seek(cposition);
	writeOut << f << endl;
	cposition = writefile.pos();


	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	QString logged = "We received your file.";

	out << quint16(0) << logged;
	//printf("sent the logged message to the data stream\n");
	//printf("the message is: %s\n", qPrintable(logged));
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));

	write(block);
}

void ClientSocket::searchForFile(QString &text){
	//printf("Searching for file: %s\n", qPrintable(text));
	QFile file("savesFiles.txt");
	file.open(QIODevice::ReadOnly);

	QTextStream readIn(&file);
	while(!readIn.atEnd()){
		QString line = readIn.readLine();
		if(line.contains(text, Qt::CaseInsensitive)){
			printf("Next line: %s\n", qPrintable(line));
			fileList.append(line);
		}
	}

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_1);
	QString logged = "Results coming";

	out << quint16(0) << logged << fileList;
	//printf("sent the logged message to the data stream\n");
	//printf("the message is: %s\n", qPrintable(logged));
	out.device()->seek(0);
	out << quint16(block.size() - sizeof(quint16));

	write(block);
}

