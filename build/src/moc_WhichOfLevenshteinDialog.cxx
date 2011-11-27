/****************************************************************************
** Meta object code from reading C++ file 'WhichOfLevenshteinDialog.h'
**
** Created: Sat 19. Nov 22:43:36 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/WhichOfLevenshteinDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WhichOfLevenshteinDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WhichOfLevenshteinDialog[] = {

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
      26,   25,   25,   25, 0x08,
      36,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WhichOfLevenshteinDialog[] = {
    "WhichOfLevenshteinDialog\0\0setItem()\0"
    "exit()\0"
};

const QMetaObject WhichOfLevenshteinDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WhichOfLevenshteinDialog,
      qt_meta_data_WhichOfLevenshteinDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WhichOfLevenshteinDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WhichOfLevenshteinDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WhichOfLevenshteinDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WhichOfLevenshteinDialog))
        return static_cast<void*>(const_cast< WhichOfLevenshteinDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int WhichOfLevenshteinDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setItem(); break;
        case 1: exit(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
