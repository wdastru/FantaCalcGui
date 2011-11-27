/****************************************************************************
** Meta object code from reading C++ file 'Less25MinDialog.h'
**
** Created: Sat 19. Nov 22:43:35 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Less25MinDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Less25MinDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Less25MinDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      35,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Less25MinDialog[] = {
    "Less25MinDialog\0\0questionMessage()\0"
    "exit()\0"
};

const QMetaObject Less25MinDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Less25MinDialog,
      qt_meta_data_Less25MinDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Less25MinDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Less25MinDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Less25MinDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Less25MinDialog))
        return static_cast<void*>(const_cast< Less25MinDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Less25MinDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: questionMessage(); break;
        case 1: exit(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
