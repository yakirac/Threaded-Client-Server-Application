TEMPLATE = app
TARGET = TCST
QT += core \
    gui \
    network
HEADERS += client.h \
    registerdialog.h
SOURCES += client.cpp \
    registerdialog.cpp \
    main.cpp
FORMS += registerdialog.ui \
    tcst.ui
RESOURCES += 
