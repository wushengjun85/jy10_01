/****************************************************************************
** Meta object code from reading C++ file 'camera_thread.h'
**
** Created: Sat Aug 20 09:16:55 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "camera_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Camera_thread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Camera_thread[] = {
    "Camera_thread\0\0img\0image_data(QImage*)\0"
};

void Camera_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Camera_thread *_t = static_cast<Camera_thread *>(_o);
        switch (_id) {
        case 0: _t->image_data((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Camera_thread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Camera_thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Camera_thread,
      qt_meta_data_Camera_thread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Camera_thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Camera_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Camera_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Camera_thread))
        return static_cast<void*>(const_cast< Camera_thread*>(this));
    return QThread::qt_metacast(_clname);
}

int Camera_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Camera_thread::image_data(QImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
