/****************************************************************************
** Meta object code from reading C++ file 'timesetup.h'
**
** Created: Sat Aug 20 09:16:56 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "timesetup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timesetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Timesetup[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      35,   10,   10,   10, 0x08,
      61,   10,   10,   10, 0x08,
      87,   10,   10,   10, 0x08,
     113,   10,   10,   10, 0x08,
     139,   10,   10,   10, 0x08,
     165,   10,   10,   10, 0x08,
     191,   10,   10,   10, 0x08,
     218,   10,   10,   10, 0x08,
     244,   10,   10,   10, 0x08,
     271,   10,   10,   10, 0x08,
     298,   10,   10,   10, 0x08,
     325,   10,   10,   10, 0x08,
     352,   10,   10,   10, 0x08,
     379,   10,   10,   10, 0x08,
     406,   10,   10,   10, 0x08,
     433,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Timesetup[] = {
    "Timesetup\0\0on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_9_clicked()\0"
    "on_pushButton_11_clicked()\0"
    "on_pushButton_8_clicked()\0"
    "on_pushButton_10_clicked()\0"
    "on_pushButton_16_clicked()\0"
    "on_pushButton_18_clicked()\0"
    "on_pushButton_17_clicked()\0"
    "on_pushButton_15_clicked()\0"
    "on_pushButton_14_clicked()\0"
    "on_pushButton_12_clicked()\0"
    "on_pushButton_13_clicked()\0"
};

void Timesetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Timesetup *_t = static_cast<Timesetup *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_pushButton_5_clicked(); break;
        case 3: _t->on_pushButton_4_clicked(); break;
        case 4: _t->on_pushButton_7_clicked(); break;
        case 5: _t->on_pushButton_6_clicked(); break;
        case 6: _t->on_pushButton_9_clicked(); break;
        case 7: _t->on_pushButton_11_clicked(); break;
        case 8: _t->on_pushButton_8_clicked(); break;
        case 9: _t->on_pushButton_10_clicked(); break;
        case 10: _t->on_pushButton_16_clicked(); break;
        case 11: _t->on_pushButton_18_clicked(); break;
        case 12: _t->on_pushButton_17_clicked(); break;
        case 13: _t->on_pushButton_15_clicked(); break;
        case 14: _t->on_pushButton_14_clicked(); break;
        case 15: _t->on_pushButton_12_clicked(); break;
        case 16: _t->on_pushButton_13_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Timesetup::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Timesetup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Timesetup,
      qt_meta_data_Timesetup, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Timesetup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Timesetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Timesetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Timesetup))
        return static_cast<void*>(const_cast< Timesetup*>(this));
    return QDialog::qt_metacast(_clname);
}

int Timesetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
