#include "threadedcstserver.h"

#include <QtGui>
#include <QApplication>
#include <QtNetwork>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    ThreadedCSTServer w;
    if(!w.listen(QHostAddress::Any, 49209)){
    	printf("Failed to bind to port");
    	return 1;
    }
    QPushButton quitButton(QObject::tr("Quit"));
    quitButton.setWindowTitle(QObject::tr("TServer"));
    QObject::connect(&quitButton, SIGNAL(clicked()), &a, SLOT(quit()));
    quitButton.show();
    return a.exec();
}

