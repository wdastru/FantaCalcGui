/****************************************************************************
** Meta object code from reading C++ file 'httpwindow.h'
**
** Created: Sun 27. Nov 14:28:58 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/httpwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HttpWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      48,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
     100,   79,   11,   11, 0x08,
     138,   11,   11,   11, 0x08,
     163,  161,   11,   11, 0x08,
     222,   11,   11,   11, 0x08,
     244,  236,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HttpWindow[] = {
    "HttpWindow\0\0downloadAllFiles()\0"
    "cancelDownload()\0httpFinished()\0"
    "httpReadyRead()\0bytesRead,totalBytes\0"
    "updateDataReadProgress(qint64,qint64)\0"
    "enableDownloadButton()\0,\0"
    "slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)\0"
    "closeDialog()\0,errors\0"
    "sslErrors(QNetworkReply*,QList<QSslError>)\0"
};

const QMetaObject HttpWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_HttpWindow,
      qt_meta_data_HttpWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HttpWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HttpWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HttpWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HttpWindow))
        return static_cast<void*>(const_cast< HttpWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int HttpWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: downloadAllFiles(); break;
        case 1: cancelDownload(); break;
        case 2: httpFinished(); break;
        case 3: httpReadyRead(); break;
        case 4: updateDataReadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: enableDownloadButton(); break;
        case 6: slotAuthenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 7: closeDialog(); break;
        case 8: sslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< const QList<QSslError>(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
