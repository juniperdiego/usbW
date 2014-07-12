/****************************************************************************
** Meta object code from reading C++ file 'baobiao.h'
**
** Created: Sat Jul 12 11:04:36 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "baobiao.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baobiao.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_baobiao[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      20,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_baobiao[] = {
    "baobiao\0\0OnReturn()\0OnSearchData()\0"
};

const QMetaObject baobiao::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_baobiao,
      qt_meta_data_baobiao, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &baobiao::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *baobiao::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *baobiao::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_baobiao))
        return static_cast<void*>(const_cast< baobiao*>(this));
    return QWidget::qt_metacast(_clname);
}

int baobiao::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnReturn(); break;
        case 1: OnSearchData(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
