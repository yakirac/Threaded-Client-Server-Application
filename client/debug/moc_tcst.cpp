/****************************************************************************
** Meta object code from reading C++ file 'tcst.h'
**
** Created: Thu Dec 9 19:18:44 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tcst.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcst.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TCST[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      23,    5,    5,    5, 0x08,
      47,    5,    5,    5, 0x08,
      67,    5,    5,    5, 0x08,
      83,    5,    5,    5, 0x08,
     101,    5,    5,    5, 0x08,
     115,    5,    5,    5, 0x08,
     126,    5,    5,    5, 0x08,
     141,    5,    5,    5, 0x08,
     167,  155,    5,    5, 0x08,
     210,    5,    5,    5, 0x08,
     237,    5,    5,    5, 0x08,
     253,    5,    5,    5, 0x08,
     266,    5,    5,    5, 0x08,
     287,    5,    5,    5, 0x08,
     301,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TCST[] = {
    "TCST\0\0button1Clicked()\0registerButtonClicked()\0"
    "browseForLocation()\0browseForFile()\0"
    "connectToServer()\0sendRequest()\0"
    "sendFile()\0updateLabels()\0confirmFile()\0"
    "socketError\0displayError(QAbstractSocket::SocketError)\0"
    "connectionClosedByServer()\0sessionOpened()\0"
    "reloadMenu()\0registerWithServer()\0"
    "printStatus()\0reconnect()\0"
};

const QMetaObject TCST::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TCST,
      qt_meta_data_TCST, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TCST::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TCST::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TCST::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TCST))
        return static_cast<void*>(const_cast< TCST*>(this));
    return QDialog::qt_metacast(_clname);
}

int TCST::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: button1Clicked(); break;
        case 1: registerButtonClicked(); break;
        case 2: browseForLocation(); break;
        case 3: browseForFile(); break;
        case 4: connectToServer(); break;
        case 5: sendRequest(); break;
        case 6: sendFile(); break;
        case 7: updateLabels(); break;
        case 8: confirmFile(); break;
        case 9: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 10: connectionClosedByServer(); break;
        case 11: sessionOpened(); break;
        case 12: reloadMenu(); break;
        case 13: registerWithServer(); break;
        case 14: printStatus(); break;
        case 15: reconnect(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
