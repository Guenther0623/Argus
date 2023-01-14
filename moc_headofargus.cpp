/****************************************************************************
** Meta object code from reading C++ file 'headofargus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headofargus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'headofargus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HeadOfArgus_t {
    QByteArrayData data[75];
    char stringdata0[1160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HeadOfArgus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HeadOfArgus_t qt_meta_stringdata_HeadOfArgus = {
    {
QT_MOC_LITERAL(0, 0, 11), // "HeadOfArgus"
QT_MOC_LITERAL(1, 12, 15), // "sendVideoString"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "videoSynced"
QT_MOC_LITERAL(4, 41, 9), // "sendFrame"
QT_MOC_LITERAL(5, 51, 9), // "nextFrame"
QT_MOC_LITERAL(6, 61, 13), // "startVideoNow"
QT_MOC_LITERAL(7, 75, 13), // "pauseVideoNow"
QT_MOC_LITERAL(8, 89, 12), // "stopVideoNow"
QT_MOC_LITERAL(9, 102, 14), // "assignRefImage"
QT_MOC_LITERAL(10, 117, 14), // "roiSelectStart"
QT_MOC_LITERAL(11, 132, 14), // "toiSelectStart"
QT_MOC_LITERAL(12, 147, 13), // "roiSelectSave"
QT_MOC_LITERAL(13, 161, 13), // "toiSelectSave"
QT_MOC_LITERAL(14, 175, 15), // "roiSelectCancel"
QT_MOC_LITERAL(15, 191, 15), // "toiSelectCancel"
QT_MOC_LITERAL(16, 207, 15), // "roiSelectRemove"
QT_MOC_LITERAL(17, 223, 15), // "toiSelectRemove"
QT_MOC_LITERAL(18, 239, 14), // "roiSelectColor"
QT_MOC_LITERAL(19, 254, 13), // "setOF_BoxDims"
QT_MOC_LITERAL(20, 268, 13), // "setOF_TaskDur"
QT_MOC_LITERAL(21, 282, 19), // "sendViewChange_Norm"
QT_MOC_LITERAL(22, 302, 19), // "sendViewChange_Base"
QT_MOC_LITERAL(23, 322, 19), // "sendViewChange_Reff"
QT_MOC_LITERAL(24, 342, 19), // "sendViewChange_Diff"
QT_MOC_LITERAL(25, 362, 19), // "sendViewChange_Subt"
QT_MOC_LITERAL(26, 382, 19), // "signalOF_objectLost"
QT_MOC_LITERAL(27, 402, 11), // "compileData"
QT_MOC_LITERAL(28, 414, 27), // "ping_reguestTOIReassignment"
QT_MOC_LITERAL(29, 442, 19), // "openField_expChange"
QT_MOC_LITERAL(30, 462, 16), // "trackerInfo_Sent"
QT_MOC_LITERAL(31, 479, 10), // "initNow_OF"
QT_MOC_LITERAL(32, 490, 11), // "startNow_OF"
QT_MOC_LITERAL(33, 502, 10), // "resuNow_OF"
QT_MOC_LITERAL(34, 513, 9), // "videoSync"
QT_MOC_LITERAL(35, 523, 10), // "guiUpdated"
QT_MOC_LITERAL(36, 534, 11), // "setRefImage"
QT_MOC_LITERAL(37, 546, 18), // "sensitivityChanged"
QT_MOC_LITERAL(38, 565, 17), // "blurFactorChanged"
QT_MOC_LITERAL(39, 583, 16), // "startROISelector"
QT_MOC_LITERAL(40, 600, 16), // "startTOISelector"
QT_MOC_LITERAL(41, 617, 17), // "cancelROISelector"
QT_MOC_LITERAL(42, 635, 17), // "cancelTOISelector"
QT_MOC_LITERAL(43, 653, 15), // "saveROISelector"
QT_MOC_LITERAL(44, 669, 15), // "saveTOISelector"
QT_MOC_LITERAL(45, 685, 14), // "removeROISaved"
QT_MOC_LITERAL(46, 700, 14), // "removeTOISaved"
QT_MOC_LITERAL(47, 715, 11), // "roiSetColor"
QT_MOC_LITERAL(48, 727, 17), // "receiveOF_BoxDims"
QT_MOC_LITERAL(49, 745, 17), // "receiveOF_TaskDur"
QT_MOC_LITERAL(50, 763, 17), // "pingOF_objectLost"
QT_MOC_LITERAL(51, 781, 15), // "analysisStopped"
QT_MOC_LITERAL(52, 797, 10), // "eyeClicked"
QT_MOC_LITERAL(53, 808, 12), // "QMouseEvent*"
QT_MOC_LITERAL(54, 821, 8), // "eyeMoved"
QT_MOC_LITERAL(55, 830, 18), // "videoSyncCompleted"
QT_MOC_LITERAL(56, 849, 14), // "videoPlayPause"
QT_MOC_LITERAL(57, 864, 9), // "videoStop"
QT_MOC_LITERAL(58, 874, 14), // "qSliderChanged"
QT_MOC_LITERAL(59, 889, 15), // "qSliderReleased"
QT_MOC_LITERAL(60, 905, 14), // "qSpinerChanged"
QT_MOC_LITERAL(61, 920, 11), // "goNextFrame"
QT_MOC_LITERAL(62, 932, 16), // "openField_expSet"
QT_MOC_LITERAL(63, 949, 16), // "trackerInfo_Send"
QT_MOC_LITERAL(64, 966, 18), // "ping_initOpenField"
QT_MOC_LITERAL(65, 985, 19), // "ping_startOpenField"
QT_MOC_LITERAL(66, 1005, 18), // "ping_resuOpenField"
QT_MOC_LITERAL(67, 1024, 16), // "analysisFinished"
QT_MOC_LITERAL(68, 1041, 27), // "sendRequest_TOIReassignment"
QT_MOC_LITERAL(69, 1069, 5), // "bool*"
QT_MOC_LITERAL(70, 1075, 16), // "viewChanged_Norm"
QT_MOC_LITERAL(71, 1092, 16), // "viewChanged_Base"
QT_MOC_LITERAL(72, 1109, 16), // "viewChanged_Reff"
QT_MOC_LITERAL(73, 1126, 16), // "viewChanged_Diff"
QT_MOC_LITERAL(74, 1143, 16) // "viewChanged_Subt"

    },
    "HeadOfArgus\0sendVideoString\0\0videoSynced\0"
    "sendFrame\0nextFrame\0startVideoNow\0"
    "pauseVideoNow\0stopVideoNow\0assignRefImage\0"
    "roiSelectStart\0toiSelectStart\0"
    "roiSelectSave\0toiSelectSave\0roiSelectCancel\0"
    "toiSelectCancel\0roiSelectRemove\0"
    "toiSelectRemove\0roiSelectColor\0"
    "setOF_BoxDims\0setOF_TaskDur\0"
    "sendViewChange_Norm\0sendViewChange_Base\0"
    "sendViewChange_Reff\0sendViewChange_Diff\0"
    "sendViewChange_Subt\0signalOF_objectLost\0"
    "compileData\0ping_reguestTOIReassignment\0"
    "openField_expChange\0trackerInfo_Sent\0"
    "initNow_OF\0startNow_OF\0resuNow_OF\0"
    "videoSync\0guiUpdated\0setRefImage\0"
    "sensitivityChanged\0blurFactorChanged\0"
    "startROISelector\0startTOISelector\0"
    "cancelROISelector\0cancelTOISelector\0"
    "saveROISelector\0saveTOISelector\0"
    "removeROISaved\0removeTOISaved\0roiSetColor\0"
    "receiveOF_BoxDims\0receiveOF_TaskDur\0"
    "pingOF_objectLost\0analysisStopped\0"
    "eyeClicked\0QMouseEvent*\0eyeMoved\0"
    "videoSyncCompleted\0videoPlayPause\0"
    "videoStop\0qSliderChanged\0qSliderReleased\0"
    "qSpinerChanged\0goNextFrame\0openField_expSet\0"
    "trackerInfo_Send\0ping_initOpenField\0"
    "ping_startOpenField\0ping_resuOpenField\0"
    "analysisFinished\0sendRequest_TOIReassignment\0"
    "bool*\0viewChanged_Norm\0viewChanged_Base\0"
    "viewChanged_Reff\0viewChanged_Diff\0"
    "viewChanged_Subt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeadOfArgus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      71,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      32,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  369,    2, 0x06 /* Public */,
       3,    4,  372,    2, 0x06 /* Public */,
       4,    1,  381,    2, 0x06 /* Public */,
       5,    0,  384,    2, 0x06 /* Public */,
       6,    0,  385,    2, 0x06 /* Public */,
       7,    0,  386,    2, 0x06 /* Public */,
       8,    0,  387,    2, 0x06 /* Public */,
       9,    1,  388,    2, 0x06 /* Public */,
      10,    2,  391,    2, 0x06 /* Public */,
      11,    2,  396,    2, 0x06 /* Public */,
      12,    1,  401,    2, 0x06 /* Public */,
      13,    1,  404,    2, 0x06 /* Public */,
      14,    1,  407,    2, 0x06 /* Public */,
      15,    1,  410,    2, 0x06 /* Public */,
      16,    1,  413,    2, 0x06 /* Public */,
      17,    1,  416,    2, 0x06 /* Public */,
      18,    2,  419,    2, 0x06 /* Public */,
      19,    3,  424,    2, 0x06 /* Public */,
      20,    2,  431,    2, 0x06 /* Public */,
      21,    0,  436,    2, 0x06 /* Public */,
      22,    0,  437,    2, 0x06 /* Public */,
      23,    0,  438,    2, 0x06 /* Public */,
      24,    0,  439,    2, 0x06 /* Public */,
      25,    0,  440,    2, 0x06 /* Public */,
      26,    0,  441,    2, 0x06 /* Public */,
      27,    0,  442,    2, 0x06 /* Public */,
      28,    1,  443,    2, 0x06 /* Public */,
      29,    2,  446,    2, 0x06 /* Public */,
      30,    2,  451,    2, 0x06 /* Public */,
      31,    0,  456,    2, 0x06 /* Public */,
      32,    0,  457,    2, 0x06 /* Public */,
      33,    0,  458,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      34,    1,  459,    2, 0x0a /* Public */,
      35,    1,  462,    2, 0x0a /* Public */,
      36,    1,  465,    2, 0x0a /* Public */,
      37,    1,  468,    2, 0x0a /* Public */,
      38,    1,  471,    2, 0x0a /* Public */,
      39,    2,  474,    2, 0x0a /* Public */,
      40,    2,  479,    2, 0x0a /* Public */,
      41,    1,  484,    2, 0x0a /* Public */,
      42,    1,  487,    2, 0x0a /* Public */,
      43,    1,  490,    2, 0x0a /* Public */,
      44,    1,  493,    2, 0x0a /* Public */,
      45,    1,  496,    2, 0x0a /* Public */,
      46,    1,  499,    2, 0x0a /* Public */,
      47,    2,  502,    2, 0x0a /* Public */,
      48,    3,  507,    2, 0x0a /* Public */,
      49,    2,  514,    2, 0x0a /* Public */,
      50,    0,  519,    2, 0x0a /* Public */,
      51,    0,  520,    2, 0x0a /* Public */,
      52,    1,  521,    2, 0x0a /* Public */,
      54,    1,  524,    2, 0x0a /* Public */,
      55,    4,  527,    2, 0x08 /* Private */,
      56,    0,  536,    2, 0x08 /* Private */,
      57,    0,  537,    2, 0x08 /* Private */,
      58,    1,  538,    2, 0x08 /* Private */,
      59,    0,  541,    2, 0x08 /* Private */,
      60,    1,  542,    2, 0x08 /* Private */,
      61,    0,  545,    2, 0x08 /* Private */,
      62,    2,  546,    2, 0x08 /* Private */,
      63,    2,  551,    2, 0x08 /* Private */,
      64,    0,  556,    2, 0x08 /* Private */,
      65,    0,  557,    2, 0x08 /* Private */,
      66,    0,  558,    2, 0x08 /* Private */,
      67,    0,  559,    2, 0x08 /* Private */,
      68,    2,  560,    2, 0x08 /* Private */,
      70,    0,  565,    2, 0x08 /* Private */,
      71,    0,  566,    2, 0x08 /* Private */,
      72,    0,  567,    2, 0x08 /* Private */,
      73,    0,  568,    2, 0x08 /* Private */,
      74,    0,  569,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 53,    2,
    QMetaType::Void, 0x80000000 | 53,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 69,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HeadOfArgus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HeadOfArgus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendVideoString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->videoSynced((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->sendFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->nextFrame(); break;
        case 4: _t->startVideoNow(); break;
        case 5: _t->pauseVideoNow(); break;
        case 6: _t->stopVideoNow(); break;
        case 7: _t->assignRefImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->roiSelectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->toiSelectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->roiSelectSave((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->toiSelectSave((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->roiSelectCancel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->toiSelectCancel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->roiSelectRemove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->toiSelectRemove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->roiSelectColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->setOF_BoxDims((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 18: _t->setOF_TaskDur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->sendViewChange_Norm(); break;
        case 20: _t->sendViewChange_Base(); break;
        case 21: _t->sendViewChange_Reff(); break;
        case 22: _t->sendViewChange_Diff(); break;
        case 23: _t->sendViewChange_Subt(); break;
        case 24: _t->signalOF_objectLost(); break;
        case 25: _t->compileData(); break;
        case 26: _t->ping_reguestTOIReassignment((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->openField_expChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 28: _t->trackerInfo_Sent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: _t->initNow_OF(); break;
        case 30: _t->startNow_OF(); break;
        case 31: _t->resuNow_OF(); break;
        case 32: _t->videoSync((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->guiUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->setRefImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->sensitivityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->blurFactorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->startROISelector((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 38: _t->startTOISelector((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 39: _t->cancelROISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->cancelTOISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->saveROISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->saveTOISelector((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->removeROISaved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->removeTOISaved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->roiSetColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 46: _t->receiveOF_BoxDims((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 47: _t->receiveOF_TaskDur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 48: _t->pingOF_objectLost(); break;
        case 49: _t->analysisStopped(); break;
        case 50: _t->eyeClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 51: _t->eyeMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 52: _t->videoSyncCompleted((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 53: _t->videoPlayPause(); break;
        case 54: _t->videoStop(); break;
        case 55: _t->qSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->qSliderReleased(); break;
        case 57: _t->qSpinerChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 58: _t->goNextFrame(); break;
        case 59: _t->openField_expSet((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 60: _t->trackerInfo_Send((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 61: _t->ping_initOpenField(); break;
        case 62: _t->ping_startOpenField(); break;
        case 63: _t->ping_resuOpenField(); break;
        case 64: _t->analysisFinished(); break;
        case 65: _t->sendRequest_TOIReassignment((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 66: _t->viewChanged_Norm(); break;
        case 67: _t->viewChanged_Base(); break;
        case 68: _t->viewChanged_Reff(); break;
        case 69: _t->viewChanged_Diff(); break;
        case 70: _t->viewChanged_Subt(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HeadOfArgus::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::sendVideoString)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(double , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::videoSynced)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::sendFrame)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::nextFrame)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::startVideoNow)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::pauseVideoNow)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::stopVideoNow)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::assignRefImage)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::roiSelectStart)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::toiSelectStart)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::roiSelectSave)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::toiSelectSave)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::roiSelectCancel)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::toiSelectCancel)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::roiSelectRemove)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::toiSelectRemove)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::roiSelectColor)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(double , double , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::setOF_BoxDims)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::setOF_TaskDur)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::sendViewChange_Norm)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::sendViewChange_Base)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::sendViewChange_Reff)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::sendViewChange_Diff)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::sendViewChange_Subt)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::signalOF_objectLost)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::compileData)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::ping_reguestTOIReassignment)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::openField_expChange)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::trackerInfo_Sent)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::initNow_OF)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::startNow_OF)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (HeadOfArgus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeadOfArgus::resuNow_OF)) {
                *result = 31;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HeadOfArgus::staticMetaObject = { {
    &QGroupBox::staticMetaObject,
    qt_meta_stringdata_HeadOfArgus.data,
    qt_meta_data_HeadOfArgus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HeadOfArgus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeadOfArgus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HeadOfArgus.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int HeadOfArgus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 71)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 71;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 71)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 71;
    }
    return _id;
}

// SIGNAL 0
void HeadOfArgus::sendVideoString(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HeadOfArgus::videoSynced(double _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HeadOfArgus::sendFrame(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void HeadOfArgus::nextFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void HeadOfArgus::startVideoNow()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void HeadOfArgus::pauseVideoNow()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void HeadOfArgus::stopVideoNow()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void HeadOfArgus::assignRefImage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void HeadOfArgus::roiSelectStart(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void HeadOfArgus::toiSelectStart(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void HeadOfArgus::roiSelectSave(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void HeadOfArgus::toiSelectSave(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void HeadOfArgus::roiSelectCancel(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void HeadOfArgus::toiSelectCancel(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void HeadOfArgus::roiSelectRemove(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void HeadOfArgus::toiSelectRemove(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void HeadOfArgus::roiSelectColor(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void HeadOfArgus::setOF_BoxDims(double _t1, double _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void HeadOfArgus::setOF_TaskDur(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void HeadOfArgus::sendViewChange_Norm()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void HeadOfArgus::sendViewChange_Base()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void HeadOfArgus::sendViewChange_Reff()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void HeadOfArgus::sendViewChange_Diff()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void HeadOfArgus::sendViewChange_Subt()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void HeadOfArgus::signalOF_objectLost()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void HeadOfArgus::compileData()
{
    QMetaObject::activate(this, &staticMetaObject, 25, nullptr);
}

// SIGNAL 26
void HeadOfArgus::ping_reguestTOIReassignment(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void HeadOfArgus::openField_expChange(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void HeadOfArgus::trackerInfo_Sent(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void HeadOfArgus::initNow_OF()
{
    QMetaObject::activate(this, &staticMetaObject, 29, nullptr);
}

// SIGNAL 30
void HeadOfArgus::startNow_OF()
{
    QMetaObject::activate(this, &staticMetaObject, 30, nullptr);
}

// SIGNAL 31
void HeadOfArgus::resuNow_OF()
{
    QMetaObject::activate(this, &staticMetaObject, 31, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
