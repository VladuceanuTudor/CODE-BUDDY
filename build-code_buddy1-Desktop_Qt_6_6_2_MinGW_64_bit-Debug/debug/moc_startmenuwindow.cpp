/****************************************************************************
** Meta object code from reading C++ file 'startmenuwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ClientSide/startmenuwindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'startmenuwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSStartMenuWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSStartMenuWindowENDCLASS = QtMocHelpers::stringData(
    "StartMenuWindow",
    "on_pushButton_4_clicked",
    "",
    "on_pushButton_5_clicked",
    "on_pushButton_6_clicked",
    "on_pushButton_clicked",
    "onLessonButtonClicked",
    "buttonText",
    "CLimbaj*",
    "limbaj",
    "printLimbajLessonsMenu"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSStartMenuWindowENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[16];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[24];
    char stringdata5[22];
    char stringdata6[22];
    char stringdata7[11];
    char stringdata8[9];
    char stringdata9[7];
    char stringdata10[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSStartMenuWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSStartMenuWindowENDCLASS_t qt_meta_stringdata_CLASSStartMenuWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "StartMenuWindow"
        QT_MOC_LITERAL(16, 23),  // "on_pushButton_4_clicked"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 23),  // "on_pushButton_5_clicked"
        QT_MOC_LITERAL(65, 23),  // "on_pushButton_6_clicked"
        QT_MOC_LITERAL(89, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(111, 21),  // "onLessonButtonClicked"
        QT_MOC_LITERAL(133, 10),  // "buttonText"
        QT_MOC_LITERAL(144, 8),  // "CLimbaj*"
        QT_MOC_LITERAL(153, 6),  // "limbaj"
        QT_MOC_LITERAL(160, 22)   // "printLimbajLessonsMenu"
    },
    "StartMenuWindow",
    "on_pushButton_4_clicked",
    "",
    "on_pushButton_5_clicked",
    "on_pushButton_6_clicked",
    "on_pushButton_clicked",
    "onLessonButtonClicked",
    "buttonText",
    "CLimbaj*",
    "limbaj",
    "printLimbajLessonsMenu"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSStartMenuWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    2,   54,    2, 0x08,    5 /* Private */,
      10,    1,   59,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject StartMenuWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSStartMenuWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSStartMenuWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSStartMenuWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<StartMenuWindow, std::true_type>,
        // method 'on_pushButton_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_5_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_6_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLessonButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<CLimbaj *, std::false_type>,
        // method 'printLimbajLessonsMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<CLimbaj *, std::false_type>
    >,
    nullptr
} };

void StartMenuWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StartMenuWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_4_clicked(); break;
        case 1: _t->on_pushButton_5_clicked(); break;
        case 2: _t->on_pushButton_6_clicked(); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->onLessonButtonClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<CLimbaj*>>(_a[2]))); break;
        case 5: _t->printLimbajLessonsMenu((*reinterpret_cast< std::add_pointer_t<CLimbaj*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *StartMenuWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StartMenuWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSStartMenuWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int StartMenuWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
