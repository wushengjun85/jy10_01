/****************************************************************************
** Meta object code from reading C++ file 'work.h'
**
** Created: Wed Aug 17 17:40:06 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "work.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'work.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Work[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,    5,    5,    5, 0x08,
      50,    5,    5,    5, 0x08,
      76,    5,    5,    5, 0x08,
     106,  102,    5,    5, 0x08,
     128,    5,    5,    5, 0x08,
     143,    5,    5,    5, 0x08,
     157,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Work[] = {
    "Work\0\0camerastartsignal()\0"
    "on_pushButton_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_2_clicked()\0img\0"
    "show_picture(QImage*)\0start_thread()\0"
    "stop_thread()\0on_pushButton_3_clicked()\0"
};

void Work::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Work *_t = static_cast<Work *>(_o);
        switch (_id) {
        case 0: _t->camerastartsignal(); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_pushButton_4_clicked(); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        case 4: _t->show_picture((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 5: _t->start_thread(); break;
        case 6: _t->stop_thread(); break;
        case 7: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Work::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Work::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Work,
      qt_meta_data_Work, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Work::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Work::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Work::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Work))
        return static_cast<void*>(const_cast< Work*>(this));
    return QDialog::qt_metacast(_clname);
}

int Work::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Work::camerastartsignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
