/****************************************************************************
** Meta object code from reading C++ file 'ChooseFileFromAListDialog.h'
**
** Created: Sun 27. Nov 14:29:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ChooseFileFromAListDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChooseFileFromAListDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChooseFileFromAListDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x08,
      44,   26,   26,   26, 0x08,
      51,   26,   26,   26, 0x08,
      61,   26,   26,   26, 0x08,
      71,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ChooseFileFromAListDialog[] = {
    "ChooseFileFromAListDialog\0\0enableOkButton()\0"
    "quit()\0toggle1()\0toggle2()\0execute()\0"
};

const QMetaObject ChooseFileFromAListDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ChooseFileFromAListDialog,
      qt_meta_data_ChooseFileFromAListDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChooseFileFromAListDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChooseFileFromAListDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChooseFileFromAListDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChooseFileFromAListDialog))
        return static_cast<void*>(const_cast< ChooseFileFromAListDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ChooseFileFromAListDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enableOkButton(); break;
        case 1: quit(); break;
        case 2: toggle1(); break;
        case 3: toggle2(); break;
        case 4: execute(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE