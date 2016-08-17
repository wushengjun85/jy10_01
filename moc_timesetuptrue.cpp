/****************************************************************************
** Meta object code from reading C++ file 'timesetuptrue.h'
**
** Created: Wed Aug 17 17:40:05 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "timesetuptrue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timesetuptrue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TimesetupTrue[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      44,   39,   14,   14, 0x08,
      81,   75,   14,   14, 0x08,
     112,   39,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TimesetupTrue[] = {
    "TimesetupTrue\0\0on_pushButton_clicked()\0"
    "date\0on_dateEdit_dateChanged(QDate)\0"
    "timed\0on_timeEdit_timeChanged(QTime)\0"
    "on_dateTimeEdit_dateTimeChanged(QDateTime)\0"
};

void TimesetupTrue::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TimesetupTrue *_t = static_cast<TimesetupTrue *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_dateEdit_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 2: _t->on_timeEdit_timeChanged((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 3: _t->on_dateTimeEdit_dateTimeChanged((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TimesetupTrue::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TimesetupTrue::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TimesetupTrue,
      qt_meta_data_TimesetupTrue, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TimesetupTrue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TimesetupTrue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TimesetupTrue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TimesetupTrue))
        return static_cast<void*>(const_cast< TimesetupTrue*>(this));
    return QDialog::qt_metacast(_clname);
}

int TimesetupTrue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
