/****************************************************************************
** Meta object code from reading C++ file 'dataupdate.h'
**
** Created: Sat Jul 12 16:25:41 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dataupdate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataupdate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataUpdate[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      22,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   11,   11,   11, 0x0a,
      46,   11,   11,   11, 0x0a,
      58,   11,   11,   11, 0x0a,
      70,   11,   11,   11, 0x0a,
      85,   11,   11,   11, 0x0a,
     102,   11,   11,   11, 0x0a,
     109,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DataUpdate[] = {
    "DataUpdate\0\0CloseUp()\0devFinish()\0"
    "DevFinish()\0ApkFinish()\0PkgFinish()\0"
    "DownloadRead()\0DownloadFinish()\0quit()\0"
    "ApkFileWrite(QNetworkReply*)\0"
};

const QMetaObject DataUpdate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataUpdate,
      qt_meta_data_DataUpdate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataUpdate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataUpdate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataUpdate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataUpdate))
        return static_cast<void*>(const_cast< DataUpdate*>(this));
    return QObject::qt_metacast(_clname);
}

int DataUpdate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: CloseUp(); break;
        case 1: devFinish(); break;
        case 2: DevFinish(); break;
        case 3: ApkFinish(); break;
        case 4: PkgFinish(); break;
        case 5: DownloadRead(); break;
        case 6: DownloadFinish(); break;
        case 7: quit(); break;
        case 8: ApkFileWrite((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DataUpdate::CloseUp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DataUpdate::devFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
