/****************************************************************************
** Meta object code from reading C++ file 'mindofargus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mindofargus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mindofargus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MindOfArgus_t {
    QByteArrayData data[51];
    char stringdata0[719];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MindOfArgus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MindOfArgus_t qt_meta_stringdata_MindOfArgus = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MindOfArgus"
QT_MOC_LITERAL(1, 12, 9), // "sendSight"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 31, 11), // "videoSynced"
QT_MOC_LITERAL(5, 43, 9), // "updateGUI"
QT_MOC_LITERAL(6, 53, 19), // "openField_expChange"
QT_MOC_LITERAL(7, 73, 17), // "trackerInfo_Frame"
QT_MOC_LITERAL(8, 91, 12), // "trackersLost"
QT_MOC_LITERAL(9, 104, 5), // "bool*"
QT_MOC_LITERAL(10, 110, 13), // "objectWasLost"
QT_MOC_LITERAL(11, 124, 17), // "pong_endOpenField"
QT_MOC_LITERAL(12, 142, 23), // "request_TOIReassignment"
QT_MOC_LITERAL(13, 166, 16), // "viewChanged_Norm"
QT_MOC_LITERAL(14, 183, 16), // "viewChanged_Base"
QT_MOC_LITERAL(15, 200, 16), // "viewChanged_Reff"
QT_MOC_LITERAL(16, 217, 16), // "viewChanged_Diff"
QT_MOC_LITERAL(17, 234, 16), // "viewChanged_Subt"
QT_MOC_LITERAL(18, 251, 18), // "sensitivityChanged"
QT_MOC_LITERAL(19, 270, 17), // "blurFactorChanged"
QT_MOC_LITERAL(20, 288, 9), // "videoSync"
QT_MOC_LITERAL(21, 298, 12), // "frameChanged"
QT_MOC_LITERAL(22, 311, 10), // "startVideo"
QT_MOC_LITERAL(23, 322, 10), // "pauseVideo"
QT_MOC_LITERAL(24, 333, 9), // "stopVideo"
QT_MOC_LITERAL(25, 343, 13), // "playVideoLoop"
QT_MOC_LITERAL(26, 357, 14), // "pauseVideoLoop"
QT_MOC_LITERAL(27, 372, 16), // "startROISelector"
QT_MOC_LITERAL(28, 389, 15), // "saveROISelector"
QT_MOC_LITERAL(29, 405, 17), // "cancelROISelector"
QT_MOC_LITERAL(30, 423, 14), // "removeROISaved"
QT_MOC_LITERAL(31, 438, 11), // "roiSetColor"
QT_MOC_LITERAL(32, 450, 16), // "startTOISelector"
QT_MOC_LITERAL(33, 467, 15), // "saveTOISelector"
QT_MOC_LITERAL(34, 483, 17), // "cancelTOISelector"
QT_MOC_LITERAL(35, 501, 14), // "removeTOISaved"
QT_MOC_LITERAL(36, 516, 17), // "receiveOF_BoxDims"
QT_MOC_LITERAL(37, 534, 17), // "receiveOF_TaskDur"
QT_MOC_LITERAL(38, 552, 17), // "receivePM_BoxDims"
QT_MOC_LITERAL(39, 570, 17), // "receivePM_TaskDur"
QT_MOC_LITERAL(40, 588, 11), // "setRefImage"
QT_MOC_LITERAL(41, 600, 19), // "ping_startOpenField"
QT_MOC_LITERAL(42, 620, 18), // "ping_startPlusMaze"
QT_MOC_LITERAL(43, 639, 10), // "exp_initOF"
QT_MOC_LITERAL(44, 650, 11), // "exp_startOF"
QT_MOC_LITERAL(45, 662, 10), // "exp_resuOF"
QT_MOC_LITERAL(46, 673, 10), // "eyeClicked"
QT_MOC_LITERAL(47, 684, 12), // "QMouseEvent*"
QT_MOC_LITERAL(48, 697, 2), // "ev"
QT_MOC_LITERAL(49, 700, 8), // "eyeMoved"
QT_MOC_LITERAL(50, 709, 9) // "nextFrame"

    },
    "MindOfArgus\0sendSight\0\0cv::Mat\0"
    "videoSynced\0updateGUI\0openField_expChange\0"
    "trackerInfo_Frame\0trackersLost\0bool*\0"
    "objectWasLost\0pong_endOpenField\0"
    "request_TOIReassignment\0viewChanged_Norm\0"
    "viewChanged_Base\0viewChanged_Reff\0"
    "viewChanged_Diff\0viewChanged_Subt\0"
    "sensitivityChanged\0blurFactorChanged\0"
    "videoSync\0frameChanged\0startVideo\0"
    "pauseVideo\0stopVideo\0playVideoLoop\0"
    "pauseVideoLoop\0startROISelector\0"
    "saveROISelector\0cancelROISelector\0"
    "removeROISaved\0roiSetColor\0startTOISelector\0"
    "saveTOISelector\0cancelTOISelector\0"
    "removeTOISaved\0receiveOF_BoxDims\0"
    "receiveOF_TaskDur\0receivePM_BoxDims\0"
    "receivePM_TaskDur\0setRefImage\0"
    "ping_startOpenField\0ping_startPlusMaze\0"
    "exp_initOF\0exp_startOF\0exp_resuOF\0"
    "eyeClicked\0QMouseEvent*\0ev\0eyeMoved\0"
    "nextFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MindOfArgus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  239,    2, 0x06 /* Public */,
       4,    4,  244,    2, 0x06 /* Public */,
       5,    1,  253,    2, 0x06 /* Public */,
       6,    2,  256,    2, 0x06 /* Public */,
       7,    2,  261,    2, 0x06 /* Public */,
       8,    1,  266,    2, 0x06 /* Public */,
      10,    0,  269,    2, 0x06 /* Public */,
      11,    0,  270,    2, 0x06 /* Public */,
      12,    2,  271,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  276,    2, 0x0a /* Public */,
      14,    0,  277,    2, 0x0a /* Public */,
      15,    0,  278,    2, 0x0a /* Public */,
      16,    0,  279,    2, 0x0a /* Public */,
      17,    0,  280,    2, 0x0a /* Public */,
      18,    1,  281,    2, 0x0a /* Public */,
      19,    1,  284,    2, 0x0a /* Public */,
      20,    1,  287,    2, 0x0a /* Public */,
      21,    1,  290,    2, 0x0a /* Public */,
      22,    0,  293,    2, 0x0a /* Public */,
      23,    0,  294,    2, 0x0a /* Public */,
      24,    0,  295,    2, 0x0a /* Public */,
      25,    0,  296,    2, 0x0a /* Public */,
      26,    0,  297,    2, 0x0a /* Public */,
      27,    2,  298,    2, 0x0a /* Public */,
      28,    1,  303,    2, 0x0a /* Public */,
      29,    1,  306,    2, 0x0a /* Public */,
      30,    1,  309,    2, 0x0a /* Public */,
      31,    2,  312,    2, 0x0a /* Public */,
      32,    2,  317,    2, 0x0a /* Public */,
      33,    1,  322,    2, 0x0a /* Public */,
      34,    1,  325,    2, 0x0a /* Public */,
      35,    1,  328,    2, 0x0a /* Public */,
      36,    3,  331,    2, 0x0a /* Public */,
      37,    2,  338,    2, 0x0a /* Public */,
      38,    3,  343,    2, 0x0a /* Public */,
      39,    2,  350,    2, 0x0a /* Public */,
      40,    1,  355,    2, 0x0a /* Public */,
      41,    0,  358,    2, 0x0a /* Public */,
      42,    0,  359,    2, 0x0a /* Public */,
      43,    0,  360,    2, 0x0a /* Public */,
      44,    0,  361,    2, 0x0a /* Public */,
      45,    0,  362,    2, 0x0a /* Public */,
      46,    1,  363,    2, 0x0a /* Public */,
      49,    1,  366,    2, 0x0a /* Public */,
      50,    0,  369,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 47,   48,
    QMetaType::Void, 0x80000000 | 47,   48,
    QMetaType::Void,

       0        // eod
};

void MindOfArgus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MindOfArgus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSight((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->videoSynced((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->updateGUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->openField_expChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->trackerInfo_Frame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->trackersLost((*reinterpret_cast< bool*(*)>(_a[1]))); break;
        case 6: _t->objectWasLost(); break;
        case 7: _t->pong_endOpenField(); break;
        case 8: _t->request_TOIReassignment((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 9: _t->viewChanged_Norm(); break;
        case 10: _t->viewChanged_Base(); break;
        case 11: _t->viewChanged_Reff(); break;
        case 12: _t->viewChanged_Diff(); break;
        case 13: _t->viewChanged_Subt(); break;
        case 14: _t->sensitivityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->blurFactorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->videoSync((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->startVideo(); break;
        case 19: _t->pauseVideo(); break;
        case 20: _t->stopVideo(); break;
        case 21: _t->playVideoLoop(); break;
        case 22: _t->pauseVideoLoop(); break;
        case 23: _t->startROISelector((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 24: _t->saveROISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->cancelROISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->removeROISaved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->roiSetColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 28: _t->startTOISelector((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: _t->saveTOISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->cancelTOISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->removeTOISaved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->receiveOF_BoxDims((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 33: _t->receiveOF_TaskDur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 34: _t->receivePM_BoxDims((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 35: _t->receivePM_TaskDur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 36: _t->setRefImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->ping_startOpenField(); break;
        case 38: _t->ping_startPlusMaze(); break;
        case 39: _t->exp_initOF(); break;
        case 40: _t->exp_startOF(); break;
        case 41: _t->exp_resuOF(); break;
        case 42: _t->eyeClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 43: _t->eyeMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 44: _t->nextFrame(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MindOfArgus::*)(cv::Mat , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::sendSight)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)(double , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::videoSynced)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::updateGUI)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::openField_expChange)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::trackerInfo_Frame)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)(bool * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::trackersLost)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::objectWasLost)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::pong_endOpenField)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MindOfArgus::*)(int , bool * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MindOfArgus::request_TOIReassignment)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MindOfArgus::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MindOfArgus.data,
    qt_meta_data_MindOfArgus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MindOfArgus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MindOfArgus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MindOfArgus.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MindOfArgus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 45;
    }
    return _id;
}

// SIGNAL 0
void MindOfArgus::sendSight(cv::Mat _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MindOfArgus::videoSynced(double _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MindOfArgus::updateGUI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MindOfArgus::openField_expChange(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MindOfArgus::trackerInfo_Frame(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MindOfArgus::trackersLost(bool * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MindOfArgus::objectWasLost()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MindOfArgus::pong_endOpenField()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MindOfArgus::request_TOIReassignment(int _t1, bool * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
