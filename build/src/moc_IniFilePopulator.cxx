/****************************************************************************
** Meta object code from reading C++ file 'IniFilePopulator.h'
**
** Created: Sun 27. Nov 00:59:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/IniFilePopulator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IniFilePopulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IniFilePopulator[] = {

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
      18,   17,   17,   17, 0x08,
      41,   17,   17,   17, 0x08,
      62,   17,   17,   17, 0x08,
      84,   17,   17,   17, 0x08,
     105,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IniFilePopulator[] = {
    "IniFilePopulator\0\0chooseFormazioniPath()\0"
    "chooseGazzettaPath()\0chooseRisultatiPath()\0"
    "chooseDownloadPath()\0chooseListePath()\0"
};

const QMetaObject IniFilePopulator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IniFilePopulator,
      qt_meta_data_IniFilePopulator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IniFilePopulator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IniFilePopulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IniFilePopulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IniFilePopulator))
        return static_cast<void*>(const_cast< IniFilePopulator*>(this));
    return QDialog::qt_metacast(_clname);
}

int IniFilePopulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: chooseFormazioniPath(); break;
        case 1: chooseGazzettaPath(); break;
        case 2: chooseRisultatiPath(); break;
        case 3: chooseDownloadPath(); break;
        case 4: chooseListePath(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
