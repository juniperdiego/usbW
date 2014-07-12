/****************************************************************************
** Meta object code from reading C++ file 'gengxin.h'
**
** Created: Sat Jul 12 17:47:07 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gengxin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gengxin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Gengxin[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      16,    8,    8,    8, 0x08,
      25,    8,    8,    8, 0x08,
      36,    8,    8,    8, 0x08,
      45,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Gengxin[] = {
    "Gengxin\0\0OnOk()\0UpDone()\0OnCancle()\0"
    "OnTerm()\0updateVersion()\0"
};

const QMetaObject Gengxin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Gengxin,
      qt_meta_data_Gengxin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Gengxin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Gengxin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Gengxin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gengxin))
        return static_cast<void*>(const_cast< Gengxin*>(this));
    return QDialog::qt_metacast(_clname);
}

int Gengxin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnOk(); break;
        case 1: UpDone(); break;
        case 2: OnCancle(); break;
        case 3: OnTerm(); break;
        case 4: updateVersion(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
