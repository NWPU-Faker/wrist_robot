/****************************************************************************
** Meta object code from reading C++ file 'frmnavbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../navbutton/frmnavbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmnavbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmNavButton_t {
    QByteArrayData data[10];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmNavButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmNavButton_t qt_meta_stringdata_frmNavButton = {
    {
QT_MOC_LITERAL(0, 0, 12), // "frmNavButton"
QT_MOC_LITERAL(1, 13, 8), // "initForm"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "buttonClick1"
QT_MOC_LITERAL(4, 36, 12), // "buttonClick2"
QT_MOC_LITERAL(5, 49, 12), // "buttonClick3"
QT_MOC_LITERAL(6, 62, 12), // "buttonClick4"
QT_MOC_LITERAL(7, 75, 12), // "buttonClick5"
QT_MOC_LITERAL(8, 88, 12), // "buttonClick6"
QT_MOC_LITERAL(9, 101, 12) // "buttonClick7"

    },
    "frmNavButton\0initForm\0\0buttonClick1\0"
    "buttonClick2\0buttonClick3\0buttonClick4\0"
    "buttonClick5\0buttonClick6\0buttonClick7"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmNavButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void frmNavButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmNavButton *_t = static_cast<frmNavButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initForm(); break;
        case 1: _t->buttonClick1(); break;
        case 2: _t->buttonClick2(); break;
        case 3: _t->buttonClick3(); break;
        case 4: _t->buttonClick4(); break;
        case 5: _t->buttonClick5(); break;
        case 6: _t->buttonClick6(); break;
        case 7: _t->buttonClick7(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject frmNavButton::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_frmNavButton.data,
      qt_meta_data_frmNavButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *frmNavButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmNavButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frmNavButton.stringdata0))
        return static_cast<void*>(const_cast< frmNavButton*>(this));
    return QWidget::qt_metacast(_clname);
}

int frmNavButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
