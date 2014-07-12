/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Jul 12 17:47:08 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   11,   11,   11, 0x0a,
      37,   11,   11,   11, 0x0a,
      49,   11,   11,   11, 0x0a,
      61,   11,   11,   11, 0x0a,
      72,   11,   11,   11, 0x0a,
      87,   11,   11,   11, 0x0a,
      96,   11,   11,   11, 0x0a,
     109,   11,   11,   11, 0x0a,
     121,  119,   11,   11, 0x0a,
     149,  142,   11,   11, 0x0a,
     173,  142,   11,   11, 0x0a,
     190,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0setMvState()\0OnGengxin()\0"
    "OnWenjian()\0OnBaobiao()\0OnFuwuqi()\0"
    "OnShangchuan()\0OnHelp()\0ScanUsbDev()\0"
    "TimeNow()\0i\0ChangeDevStatus(int)\0"
    "bState\0onlineStateChange(bool)\0"
    "setMvState(bool)\0SetUnUpCount()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setMvState(); break;
        case 1: OnGengxin(); break;
        case 2: OnWenjian(); break;
        case 3: OnBaobiao(); break;
        case 4: OnFuwuqi(); break;
        case 5: OnShangchuan(); break;
        case 6: OnHelp(); break;
        case 7: ScanUsbDev(); break;
        case 8: TimeNow(); break;
        case 9: ChangeDevStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: onlineStateChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: setMvState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: SetUnUpCount(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::setMvState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
