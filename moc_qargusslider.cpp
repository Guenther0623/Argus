/****************************************************************************
** Meta object code from reading C++ file 'qargusslider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qargusslider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qargusslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QArgusSlider_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QArgusSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QArgusSlider_t qt_meta_stringdata_QArgusSlider = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QArgusSlider"
QT_MOC_LITERAL(1, 13, 12), // "valueChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "sliderReleased"
QT_MOC_LITERAL(4, 42, 18), // "sliderValueChanged"
QT_MOC_LITERAL(5, 61, 17), // "sliderWasReleased"
QT_MOC_LITERAL(6, 79, 11), // "retractFive"
QT_MOC_LITERAL(7, 91, 10), // "retractOne"
QT_MOC_LITERAL(8, 102, 9), // "returnOne"
QT_MOC_LITERAL(9, 112, 10), // "returnFive"
QT_MOC_LITERAL(10, 123, 9) // "addMarker"

    },
    "QArgusSlider\0valueChanged\0\0sliderReleased\0"
    "sliderValueChanged\0sliderWasReleased\0"
    "retractFive\0retractOne\0returnOne\0"
    "returnFive\0addMarker"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QArgusSlider[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   63,    2, 0x08 /* Private */,
       5,    0,   66,    2, 0x08 /* Private */,
       6,    0,   67,    2, 0x0a /* Public */,
       7,    0,   68,    2, 0x0a /* Public */,
       8,    0,   69,    2, 0x0a /* Public */,
       9,    0,   70,    2, 0x0a /* Public */,
      10,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QArgusSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QArgusSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sliderReleased(); break;
        case 2: _t->sliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sliderWasReleased(); break;
        case 4: _t->retractFive(); break;
        case 5: _t->retractOne(); break;
        case 6: _t->returnOne(); break;
        case 7: _t->returnFive(); break;
        case 8: _t->addMarker(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QArgusSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QArgusSlider::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QArgusSlider::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QArgusSlider::sliderReleased)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QArgusSlider::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_QArgusSlider.data,
    qt_meta_data_QArgusSlider,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QArgusSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QArgusSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QArgusSlider.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QArgusSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QArgusSlider::valueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QArgusSlider::sliderReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
