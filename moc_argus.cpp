/****************************************************************************
** Meta object code from reading C++ file 'argus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "argus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'argus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Argus_t {
    QByteArrayData data[99];
    char stringdata0[1388];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Argus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Argus_t qt_meta_stringdata_Argus = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Argus"
QT_MOC_LITERAL(1, 6, 14), // "sendVideoQueue"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "sendSight"
QT_MOC_LITERAL(4, 32, 7), // "cv::Mat"
QT_MOC_LITERAL(5, 40, 9), // "sendFrame"
QT_MOC_LITERAL(6, 50, 9), // "playVideo"
QT_MOC_LITERAL(7, 60, 10), // "pauseVideo"
QT_MOC_LITERAL(8, 71, 14), // "sendStopSignal"
QT_MOC_LITERAL(9, 86, 11), // "OF_StartROI"
QT_MOC_LITERAL(10, 98, 11), // "OF_StartTOI"
QT_MOC_LITERAL(11, 110, 12), // "OF_CancelROI"
QT_MOC_LITERAL(12, 123, 12), // "OF_CancelTOI"
QT_MOC_LITERAL(13, 136, 10), // "OF_SaveROI"
QT_MOC_LITERAL(14, 147, 10), // "OF_SaveTOI"
QT_MOC_LITERAL(15, 158, 12), // "OF_RemoveROI"
QT_MOC_LITERAL(16, 171, 12), // "OF_RemoveTOI"
QT_MOC_LITERAL(17, 184, 14), // "OF_roiSetColor"
QT_MOC_LITERAL(18, 199, 15), // "OF_setReference"
QT_MOC_LITERAL(19, 215, 14), // "OF_sensChanged"
QT_MOC_LITERAL(20, 230, 14), // "OF_blurChanged"
QT_MOC_LITERAL(21, 245, 10), // "initNow_OF"
QT_MOC_LITERAL(22, 256, 11), // "startNow_OF"
QT_MOC_LITERAL(23, 268, 10), // "resuNow_OF"
QT_MOC_LITERAL(24, 279, 16), // "assignOF_BoxDims"
QT_MOC_LITERAL(25, 296, 16), // "assignOF_TaskDur"
QT_MOC_LITERAL(26, 313, 11), // "PM_StartROI"
QT_MOC_LITERAL(27, 325, 11), // "PM_StartTOI"
QT_MOC_LITERAL(28, 337, 12), // "PM_CancelROI"
QT_MOC_LITERAL(29, 350, 12), // "PM_CancelTOI"
QT_MOC_LITERAL(30, 363, 10), // "PM_SaveROI"
QT_MOC_LITERAL(31, 374, 10), // "PM_SaveTOI"
QT_MOC_LITERAL(32, 385, 12), // "PM_RemoveROI"
QT_MOC_LITERAL(33, 398, 12), // "PM_RemoveTOI"
QT_MOC_LITERAL(34, 411, 14), // "PM_roiSetColor"
QT_MOC_LITERAL(35, 426, 15), // "PM_setReference"
QT_MOC_LITERAL(36, 442, 14), // "PM_sensChanged"
QT_MOC_LITERAL(37, 457, 14), // "PM_blurChanged"
QT_MOC_LITERAL(38, 472, 10), // "initNow_PM"
QT_MOC_LITERAL(39, 483, 11), // "startNow_PM"
QT_MOC_LITERAL(40, 495, 10), // "resuNow_PM"
QT_MOC_LITERAL(41, 506, 16), // "assignPM_BoxDims"
QT_MOC_LITERAL(42, 523, 16), // "assignPM_TaskDur"
QT_MOC_LITERAL(43, 540, 11), // "locateVideo"
QT_MOC_LITERAL(44, 552, 9), // "loadVideo"
QT_MOC_LITERAL(45, 562, 15), // "filePathChanged"
QT_MOC_LITERAL(46, 578, 17), // "blurSliderChanged"
QT_MOC_LITERAL(47, 596, 17), // "sensSliderChanged"
QT_MOC_LITERAL(48, 614, 10), // "eyeClicked"
QT_MOC_LITERAL(49, 625, 12), // "QMouseEvent*"
QT_MOC_LITERAL(50, 638, 2), // "ev"
QT_MOC_LITERAL(51, 641, 8), // "eyeMoved"
QT_MOC_LITERAL(52, 650, 22), // "change_ratNumOpenField"
QT_MOC_LITERAL(53, 673, 14), // "videoPlayPause"
QT_MOC_LITERAL(54, 688, 9), // "videoStop"
QT_MOC_LITERAL(55, 698, 12), // "PM_selectROI"
QT_MOC_LITERAL(56, 711, 12), // "PM_selectTOI"
QT_MOC_LITERAL(57, 724, 10), // "PM_saveROI"
QT_MOC_LITERAL(58, 735, 10), // "PM_saveTOI"
QT_MOC_LITERAL(59, 746, 12), // "PM_removeROI"
QT_MOC_LITERAL(60, 759, 12), // "PM_removeTOI"
QT_MOC_LITERAL(61, 772, 17), // "PM_ColorChanged01"
QT_MOC_LITERAL(62, 790, 17), // "PM_ColorChanged02"
QT_MOC_LITERAL(63, 808, 15), // "PM_InitAnalysis"
QT_MOC_LITERAL(64, 824, 16), // "PM_BeginAnalysis"
QT_MOC_LITERAL(65, 841, 15), // "PM_ResuAnalysis"
QT_MOC_LITERAL(66, 857, 11), // "PM_XChanged"
QT_MOC_LITERAL(67, 869, 11), // "PM_YChanged"
QT_MOC_LITERAL(68, 881, 17), // "PM_taskDurChanged"
QT_MOC_LITERAL(69, 899, 19), // "PM_ignoreDurChanged"
QT_MOC_LITERAL(70, 919, 12), // "OF_selectROI"
QT_MOC_LITERAL(71, 932, 12), // "OF_selectTOI"
QT_MOC_LITERAL(72, 945, 10), // "OF_saveROI"
QT_MOC_LITERAL(73, 956, 10), // "OF_saveTOI"
QT_MOC_LITERAL(74, 967, 12), // "OF_removeROI"
QT_MOC_LITERAL(75, 980, 12), // "OF_removeTOI"
QT_MOC_LITERAL(76, 993, 17), // "OF_ColorChanged01"
QT_MOC_LITERAL(77, 1011, 17), // "OF_ColorChanged02"
QT_MOC_LITERAL(78, 1029, 15), // "OF_InitAnalysis"
QT_MOC_LITERAL(79, 1045, 16), // "OF_BeginAnalysis"
QT_MOC_LITERAL(80, 1062, 15), // "OF_ResuAnalysis"
QT_MOC_LITERAL(81, 1078, 11), // "OF_XChanged"
QT_MOC_LITERAL(82, 1090, 11), // "OF_YChanged"
QT_MOC_LITERAL(83, 1102, 17), // "OF_taskDurChanged"
QT_MOC_LITERAL(84, 1120, 19), // "OF_ignoreDurChanged"
QT_MOC_LITERAL(85, 1140, 17), // "boxUnitChanged_CM"
QT_MOC_LITERAL(86, 1158, 17), // "boxUnitChanged_IN"
QT_MOC_LITERAL(87, 1176, 20), // "qReff_StarterClicked"
QT_MOC_LITERAL(88, 1197, 20), // "qReff_AverageClicked"
QT_MOC_LITERAL(89, 1218, 20), // "qReff_CustomFClicked"
QT_MOC_LITERAL(90, 1239, 21), // "qReff_AssignReference"
QT_MOC_LITERAL(91, 1261, 11), // "videoLoaded"
QT_MOC_LITERAL(92, 1273, 10), // "guiUpdated"
QT_MOC_LITERAL(93, 1284, 16), // "openField_expSet"
QT_MOC_LITERAL(94, 1301, 23), // "OF_TrackerFrameAssigned"
QT_MOC_LITERAL(95, 1325, 12), // "videoStopped"
QT_MOC_LITERAL(96, 1338, 15), // "userReassignTOI"
QT_MOC_LITERAL(97, 1354, 17), // "pingOF_objectLost"
QT_MOC_LITERAL(98, 1372, 15) // "plusMaze_expSet"

    },
    "Argus\0sendVideoQueue\0\0sendSight\0cv::Mat\0"
    "sendFrame\0playVideo\0pauseVideo\0"
    "sendStopSignal\0OF_StartROI\0OF_StartTOI\0"
    "OF_CancelROI\0OF_CancelTOI\0OF_SaveROI\0"
    "OF_SaveTOI\0OF_RemoveROI\0OF_RemoveTOI\0"
    "OF_roiSetColor\0OF_setReference\0"
    "OF_sensChanged\0OF_blurChanged\0initNow_OF\0"
    "startNow_OF\0resuNow_OF\0assignOF_BoxDims\0"
    "assignOF_TaskDur\0PM_StartROI\0PM_StartTOI\0"
    "PM_CancelROI\0PM_CancelTOI\0PM_SaveROI\0"
    "PM_SaveTOI\0PM_RemoveROI\0PM_RemoveTOI\0"
    "PM_roiSetColor\0PM_setReference\0"
    "PM_sensChanged\0PM_blurChanged\0initNow_PM\0"
    "startNow_PM\0resuNow_PM\0assignPM_BoxDims\0"
    "assignPM_TaskDur\0locateVideo\0loadVideo\0"
    "filePathChanged\0blurSliderChanged\0"
    "sensSliderChanged\0eyeClicked\0QMouseEvent*\0"
    "ev\0eyeMoved\0change_ratNumOpenField\0"
    "videoPlayPause\0videoStop\0PM_selectROI\0"
    "PM_selectTOI\0PM_saveROI\0PM_saveTOI\0"
    "PM_removeROI\0PM_removeTOI\0PM_ColorChanged01\0"
    "PM_ColorChanged02\0PM_InitAnalysis\0"
    "PM_BeginAnalysis\0PM_ResuAnalysis\0"
    "PM_XChanged\0PM_YChanged\0PM_taskDurChanged\0"
    "PM_ignoreDurChanged\0OF_selectROI\0"
    "OF_selectTOI\0OF_saveROI\0OF_saveTOI\0"
    "OF_removeROI\0OF_removeTOI\0OF_ColorChanged01\0"
    "OF_ColorChanged02\0OF_InitAnalysis\0"
    "OF_BeginAnalysis\0OF_ResuAnalysis\0"
    "OF_XChanged\0OF_YChanged\0OF_taskDurChanged\0"
    "OF_ignoreDurChanged\0boxUnitChanged_CM\0"
    "boxUnitChanged_IN\0qReff_StarterClicked\0"
    "qReff_AverageClicked\0qReff_CustomFClicked\0"
    "qReff_AssignReference\0videoLoaded\0"
    "guiUpdated\0openField_expSet\0"
    "OF_TrackerFrameAssigned\0videoStopped\0"
    "userReassignTOI\0pingOF_objectLost\0"
    "plusMaze_expSet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Argus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      94,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      40,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  484,    2, 0x06 /* Public */,
       3,    2,  487,    2, 0x06 /* Public */,
       5,    1,  492,    2, 0x06 /* Public */,
       6,    0,  495,    2, 0x06 /* Public */,
       7,    0,  496,    2, 0x06 /* Public */,
       8,    0,  497,    2, 0x06 /* Public */,
       9,    2,  498,    2, 0x06 /* Public */,
      10,    2,  503,    2, 0x06 /* Public */,
      11,    1,  508,    2, 0x06 /* Public */,
      12,    1,  511,    2, 0x06 /* Public */,
      13,    1,  514,    2, 0x06 /* Public */,
      14,    1,  517,    2, 0x06 /* Public */,
      15,    1,  520,    2, 0x06 /* Public */,
      16,    1,  523,    2, 0x06 /* Public */,
      17,    2,  526,    2, 0x06 /* Public */,
      18,    1,  531,    2, 0x06 /* Public */,
      19,    1,  534,    2, 0x06 /* Public */,
      20,    1,  537,    2, 0x06 /* Public */,
      21,    0,  540,    2, 0x06 /* Public */,
      22,    0,  541,    2, 0x06 /* Public */,
      23,    0,  542,    2, 0x06 /* Public */,
      24,    3,  543,    2, 0x06 /* Public */,
      25,    2,  550,    2, 0x06 /* Public */,
      26,    2,  555,    2, 0x06 /* Public */,
      27,    2,  560,    2, 0x06 /* Public */,
      28,    1,  565,    2, 0x06 /* Public */,
      29,    1,  568,    2, 0x06 /* Public */,
      30,    1,  571,    2, 0x06 /* Public */,
      31,    1,  574,    2, 0x06 /* Public */,
      32,    1,  577,    2, 0x06 /* Public */,
      33,    1,  580,    2, 0x06 /* Public */,
      34,    2,  583,    2, 0x06 /* Public */,
      35,    1,  588,    2, 0x06 /* Public */,
      36,    1,  591,    2, 0x06 /* Public */,
      37,    1,  594,    2, 0x06 /* Public */,
      38,    0,  597,    2, 0x06 /* Public */,
      39,    0,  598,    2, 0x06 /* Public */,
      40,    0,  599,    2, 0x06 /* Public */,
      41,    3,  600,    2, 0x06 /* Public */,
      42,    2,  607,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      43,    0,  612,    2, 0x08 /* Private */,
      44,    0,  613,    2, 0x08 /* Private */,
      45,    1,  614,    2, 0x08 /* Private */,
      46,    1,  617,    2, 0x08 /* Private */,
      47,    1,  620,    2, 0x08 /* Private */,
      48,    1,  623,    2, 0x08 /* Private */,
      51,    1,  626,    2, 0x08 /* Private */,
      52,    1,  629,    2, 0x08 /* Private */,
      53,    1,  632,    2, 0x08 /* Private */,
      54,    0,  635,    2, 0x08 /* Private */,
      55,    1,  636,    2, 0x08 /* Private */,
      56,    1,  639,    2, 0x08 /* Private */,
      57,    1,  642,    2, 0x08 /* Private */,
      58,    1,  645,    2, 0x08 /* Private */,
      59,    1,  648,    2, 0x08 /* Private */,
      60,    1,  651,    2, 0x08 /* Private */,
      61,    1,  654,    2, 0x08 /* Private */,
      62,    1,  657,    2, 0x08 /* Private */,
      63,    0,  660,    2, 0x08 /* Private */,
      64,    0,  661,    2, 0x08 /* Private */,
      65,    0,  662,    2, 0x08 /* Private */,
      66,    1,  663,    2, 0x08 /* Private */,
      67,    1,  666,    2, 0x08 /* Private */,
      68,    1,  669,    2, 0x08 /* Private */,
      69,    1,  672,    2, 0x08 /* Private */,
      70,    1,  675,    2, 0x08 /* Private */,
      71,    1,  678,    2, 0x08 /* Private */,
      72,    1,  681,    2, 0x08 /* Private */,
      73,    1,  684,    2, 0x08 /* Private */,
      74,    1,  687,    2, 0x08 /* Private */,
      75,    1,  690,    2, 0x08 /* Private */,
      76,    1,  693,    2, 0x08 /* Private */,
      77,    1,  696,    2, 0x08 /* Private */,
      78,    0,  699,    2, 0x08 /* Private */,
      79,    0,  700,    2, 0x08 /* Private */,
      80,    0,  701,    2, 0x08 /* Private */,
      81,    1,  702,    2, 0x08 /* Private */,
      82,    1,  705,    2, 0x08 /* Private */,
      83,    1,  708,    2, 0x08 /* Private */,
      84,    1,  711,    2, 0x08 /* Private */,
      85,    0,  714,    2, 0x08 /* Private */,
      86,    0,  715,    2, 0x08 /* Private */,
      87,    0,  716,    2, 0x08 /* Private */,
      88,    0,  717,    2, 0x08 /* Private */,
      89,    0,  718,    2, 0x08 /* Private */,
      90,    0,  719,    2, 0x08 /* Private */,
      91,    4,  720,    2, 0x0a /* Public */,
      92,    1,  729,    2, 0x0a /* Public */,
      93,    2,  732,    2, 0x0a /* Public */,
      94,    2,  737,    2, 0x0a /* Public */,
      95,    0,  742,    2, 0x0a /* Public */,
      96,    1,  743,    2, 0x0a /* Public */,
      97,    0,  746,    2, 0x0a /* Public */,
      98,    2,  747,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 49,   50,
    QMetaType::Void, 0x80000000 | 49,   50,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,

       0        // eod
};

void Argus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Argus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendVideoQueue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendSight((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sendFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->playVideo(); break;
        case 4: _t->pauseVideo(); break;
        case 5: _t->sendStopSignal(); break;
        case 6: _t->OF_StartROI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->OF_StartTOI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->OF_CancelROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->OF_CancelTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->OF_SaveROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->OF_SaveTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->OF_RemoveROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->OF_RemoveTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->OF_roiSetColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->OF_setReference((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->OF_sensChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->OF_blurChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->initNow_OF(); break;
        case 19: _t->startNow_OF(); break;
        case 20: _t->resuNow_OF(); break;
        case 21: _t->assignOF_BoxDims((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 22: _t->assignOF_TaskDur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 23: _t->PM_StartROI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 24: _t->PM_StartTOI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 25: _t->PM_CancelROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->PM_CancelTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->PM_SaveROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->PM_SaveTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->PM_RemoveROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->PM_RemoveTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->PM_roiSetColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 32: _t->PM_setReference((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->PM_sensChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->PM_blurChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->initNow_PM(); break;
        case 36: _t->startNow_PM(); break;
        case 37: _t->resuNow_PM(); break;
        case 38: _t->assignPM_BoxDims((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 39: _t->assignPM_TaskDur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 40: _t->locateVideo(); break;
        case 41: _t->loadVideo(); break;
        case 42: _t->filePathChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 43: _t->blurSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->sensSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->eyeClicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 46: _t->eyeMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 47: _t->change_ratNumOpenField((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->videoPlayPause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: _t->videoStop(); break;
        case 50: _t->PM_selectROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->PM_selectTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->PM_saveROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->PM_saveTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->PM_removeROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->PM_removeTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->PM_ColorChanged01((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 57: _t->PM_ColorChanged02((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 58: _t->PM_InitAnalysis(); break;
        case 59: _t->PM_BeginAnalysis(); break;
        case 60: _t->PM_ResuAnalysis(); break;
        case 61: _t->PM_XChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 62: _t->PM_YChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 63: _t->PM_taskDurChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 64: _t->PM_ignoreDurChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 65: _t->OF_selectROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 66: _t->OF_selectTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->OF_saveROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 68: _t->OF_saveTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 69: _t->OF_removeROI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 70: _t->OF_removeTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 71: _t->OF_ColorChanged01((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 72: _t->OF_ColorChanged02((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 73: _t->OF_InitAnalysis(); break;
        case 74: _t->OF_BeginAnalysis(); break;
        case 75: _t->OF_ResuAnalysis(); break;
        case 76: _t->OF_XChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 77: _t->OF_YChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 78: _t->OF_taskDurChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 79: _t->OF_ignoreDurChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 80: _t->boxUnitChanged_CM(); break;
        case 81: _t->boxUnitChanged_IN(); break;
        case 82: _t->qReff_StarterClicked(); break;
        case 83: _t->qReff_AverageClicked(); break;
        case 84: _t->qReff_CustomFClicked(); break;
        case 85: _t->qReff_AssignReference(); break;
        case 86: _t->videoLoaded((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 87: _t->guiUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 88: _t->openField_expSet((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 89: _t->OF_TrackerFrameAssigned((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 90: _t->videoStopped(); break;
        case 91: _t->userReassignTOI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 92: _t->pingOF_objectLost(); break;
        case 93: _t->plusMaze_expSet((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Argus::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::sendVideoQueue)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Argus::*)(cv::Mat , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::sendSight)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::sendFrame)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::playVideo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::pauseVideo)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::sendStopSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_StartROI)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_StartTOI)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_CancelROI)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_CancelTOI)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_SaveROI)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_SaveTOI)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_RemoveROI)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_RemoveTOI)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_roiSetColor)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_setReference)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_sensChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::OF_blurChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::initNow_OF)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::startNow_OF)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::resuNow_OF)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (Argus::*)(double , double , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::assignOF_BoxDims)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::assignOF_TaskDur)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_StartROI)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_StartTOI)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_CancelROI)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_CancelTOI)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_SaveROI)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_SaveTOI)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_RemoveROI)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_RemoveTOI)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_roiSetColor)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_setReference)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_sensChanged)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::PM_blurChanged)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::initNow_PM)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::startNow_PM)) {
                *result = 36;
                return;
            }
        }
        {
            using _t = void (Argus::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::resuNow_PM)) {
                *result = 37;
                return;
            }
        }
        {
            using _t = void (Argus::*)(double , double , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::assignPM_BoxDims)) {
                *result = 38;
                return;
            }
        }
        {
            using _t = void (Argus::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Argus::assignPM_TaskDur)) {
                *result = 39;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Argus::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Argus.data,
    qt_meta_data_Argus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Argus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Argus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Argus.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Argus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 94)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 94;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 94)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 94;
    }
    return _id;
}

// SIGNAL 0
void Argus::sendVideoQueue(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Argus::sendSight(cv::Mat _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Argus::sendFrame(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Argus::playVideo()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Argus::pauseVideo()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Argus::sendStopSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Argus::OF_StartROI(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Argus::OF_StartTOI(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Argus::OF_CancelROI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Argus::OF_CancelTOI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Argus::OF_SaveROI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Argus::OF_SaveTOI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Argus::OF_RemoveROI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Argus::OF_RemoveTOI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Argus::OF_roiSetColor(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Argus::OF_setReference(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void Argus::OF_sensChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void Argus::OF_blurChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void Argus::initNow_OF()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void Argus::startNow_OF()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void Argus::resuNow_OF()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void Argus::assignOF_BoxDims(double _t1, double _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void Argus::assignOF_TaskDur(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void Argus::PM_StartROI(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void Argus::PM_StartTOI(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void Argus::PM_CancelROI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void Argus::PM_CancelTOI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void Argus::PM_SaveROI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void Argus::PM_SaveTOI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void Argus::PM_RemoveROI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void Argus::PM_RemoveTOI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void Argus::PM_roiSetColor(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void Argus::PM_setReference(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void Argus::PM_sensChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void Argus::PM_blurChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void Argus::initNow_PM()
{
    QMetaObject::activate(this, &staticMetaObject, 35, nullptr);
}

// SIGNAL 36
void Argus::startNow_PM()
{
    QMetaObject::activate(this, &staticMetaObject, 36, nullptr);
}

// SIGNAL 37
void Argus::resuNow_PM()
{
    QMetaObject::activate(this, &staticMetaObject, 37, nullptr);
}

// SIGNAL 38
void Argus::assignPM_BoxDims(double _t1, double _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 38, _a);
}

// SIGNAL 39
void Argus::assignPM_TaskDur(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
