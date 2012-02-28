/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created: Fri Dec 10 19:13:13 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Client[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      31,    7,    7,    7, 0x08,
      52,    7,    7,    7, 0x08,
      68,    7,    7,    7, 0x08,
     107,   95,    7,    7, 0x08,
     150,    7,    7,    7, 0x08,
     166,    7,    7,    7, 0x08,
     182,    7,    7,    7, 0x08,
     201,    7,    7,    7, 0x08,
     218,    7,    7,    7, 0x08,
     233,    7,    7,    7, 0x08,
     246,    7,    7,    7, 0x08,
     260,    7,    7,    7, 0x08,
     279,    7,    7,    7, 0x08,
     300,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Client[] = {
    "Client\0\0requestNewConnection()\0"
    "registerWithServer()\0browseForFile()\0"
    "connectionClosedByServer()\0socketError\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "sessionOpened()\0sendLoginInfo()\0"
    "sendRegistration()\0sendSearchInfo()\0"
    "updateLabels()\0reloadMenu()\0printStatus()\0"
    "createMoveLayout()\0createLocateLayout()\0"
    "sendFile()\0"
};

const QMetaObject Client::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Client,
      qt_meta_data_Client, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Client))
        return static_cast<void*>(const_cast< Client*>(this));
    return QDialog::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: requestNewConnection(); break;
        case 1: registerWithServer(); break;
        case 2: browseForFile(); break;
        case 3: connectionClosedByServer(); break;
        case 4: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: sessionOpened(); break;
        case 6: sendLoginInfo(); break;
        case 7: sendRegistration(); break;
        case 8: sendSearchInfo(); break;
        case 9: updateLabels(); break;
        case 10: reloadMenu(); break;
        case 11: printStatus(); break;
        case 12: createMoveLayout(); break;
        case 13: createLocateLayout(); break;
        case 14: sendFile(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
