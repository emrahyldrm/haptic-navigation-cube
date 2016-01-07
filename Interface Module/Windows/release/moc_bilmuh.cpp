/****************************************************************************
** Meta object code from reading C++ file 'bilmuh.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bilmuh.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bilmuh.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BilMuh_t {
    QByteArrayData data[23];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BilMuh_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BilMuh_t qt_meta_stringdata_BilMuh = {
    {
QT_MOC_LITERAL(0, 0, 6), // "BilMuh"
QT_MOC_LITERAL(1, 7, 19), // "progressSetLocation"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "loc"
QT_MOC_LITERAL(4, 32, 16), // "onProcessChanged"
QT_MOC_LITERAL(5, 49, 4), // "info"
QT_MOC_LITERAL(6, 54, 22), // "onProgressShortestPath"
QT_MOC_LITERAL(7, 77, 5), // "info1"
QT_MOC_LITERAL(8, 83, 5), // "char*"
QT_MOC_LITERAL(9, 89, 11), // "pressKantin"
QT_MOC_LITERAL(10, 101, 8), // "pressLab"
QT_MOC_LITERAL(11, 110, 8), // "pressZ11"
QT_MOC_LITERAL(12, 119, 8), // "pressZ06"
QT_MOC_LITERAL(13, 128, 12), // "pressRobotik"
QT_MOC_LITERAL(14, 141, 8), // "pressZ02"
QT_MOC_LITERAL(15, 150, 8), // "pressZ04"
QT_MOC_LITERAL(16, 159, 8), // "pressZ05"
QT_MOC_LITERAL(17, 168, 8), // "pressZ10"
QT_MOC_LITERAL(18, 177, 13), // "pressMikroLab"
QT_MOC_LITERAL(19, 191, 13), // "pressDevreLab"
QT_MOC_LITERAL(20, 205, 8), // "pressZ23"
QT_MOC_LITERAL(21, 214, 10), // "pressGiris"
QT_MOC_LITERAL(22, 225, 5) // "reset"

    },
    "BilMuh\0progressSetLocation\0\0loc\0"
    "onProcessChanged\0info\0onProgressShortestPath\0"
    "info1\0char*\0pressKantin\0pressLab\0"
    "pressZ11\0pressZ06\0pressRobotik\0pressZ02\0"
    "pressZ04\0pressZ05\0pressZ10\0pressMikroLab\0"
    "pressDevreLab\0pressZ23\0pressGiris\0"
    "reset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BilMuh[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  102,    2, 0x0a /* Public */,
       6,    2,  105,    2, 0x0a /* Public */,
       9,    0,  110,    2, 0x0a /* Public */,
      10,    0,  111,    2, 0x0a /* Public */,
      11,    0,  112,    2, 0x0a /* Public */,
      12,    0,  113,    2, 0x0a /* Public */,
      13,    0,  114,    2, 0x0a /* Public */,
      14,    0,  115,    2, 0x0a /* Public */,
      15,    0,  116,    2, 0x0a /* Public */,
      16,    0,  117,    2, 0x0a /* Public */,
      17,    0,  118,    2, 0x0a /* Public */,
      18,    0,  119,    2, 0x0a /* Public */,
      19,    0,  120,    2, 0x0a /* Public */,
      20,    0,  121,    2, 0x0a /* Public */,
      21,    0,  122,    2, 0x0a /* Public */,
      22,    0,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    7,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BilMuh::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BilMuh *_t = static_cast<BilMuh *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->progressSetLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onProcessChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onProgressShortestPath((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 3: _t->pressKantin(); break;
        case 4: _t->pressLab(); break;
        case 5: _t->pressZ11(); break;
        case 6: _t->pressZ06(); break;
        case 7: _t->pressRobotik(); break;
        case 8: _t->pressZ02(); break;
        case 9: _t->pressZ04(); break;
        case 10: _t->pressZ05(); break;
        case 11: _t->pressZ10(); break;
        case 12: _t->pressMikroLab(); break;
        case 13: _t->pressDevreLab(); break;
        case 14: _t->pressZ23(); break;
        case 15: _t->pressGiris(); break;
        case 16: _t->reset(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BilMuh::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BilMuh::progressSetLocation)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject BilMuh::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BilMuh.data,
      qt_meta_data_BilMuh,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BilMuh::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BilMuh::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BilMuh.stringdata0))
        return static_cast<void*>(const_cast< BilMuh*>(this));
    return QDialog::qt_metacast(_clname);
}

int BilMuh::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void BilMuh::progressSetLocation(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
