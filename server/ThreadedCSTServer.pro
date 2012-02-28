TEMPLATE = app
TARGET = ThreadedCSTServer
QT += core \
    gui \
    xml \
    xmlpatterns \
    network
HEADERS += clientsocket.h \
    serverthread.h \
    threadedcstserver.h
SOURCES += clientsocket.cpp \
    serverthread.cpp \
    main.cpp \
    threadedcstserver.cpp
FORMS += 
RESOURCES += server.qrc
