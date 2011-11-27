/********************************************************************************
** Form generated from reading UI file 'DownloadManager.ui'
**
** Created: Fri 15. Jul 20:34:13 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADMANAGER_H
#define UI_DOWNLOADMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DownloadManagerClass
{
public:
    QPushButton *seenButton;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *DownloadManagerClass)
    {
        if (DownloadManagerClass->objectName().isEmpty())
            DownloadManagerClass->setObjectName(QString::fromUtf8("DownloadManagerClass"));
        DownloadManagerClass->resize(361, 440);
        seenButton = new QPushButton(DownloadManagerClass);
        seenButton->setObjectName(QString::fromUtf8("seenButton"));
        seenButton->setGeometry(QRect(140, 400, 75, 23));
        plainTextEdit = new QPlainTextEdit(DownloadManagerClass);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 20, 321, 361));
        plainTextEdit->setReadOnly(true);

        retranslateUi(DownloadManagerClass);
        QObject::connect(seenButton, SIGNAL(clicked()), DownloadManagerClass, SLOT(close()));

        QMetaObject::connectSlotsByName(DownloadManagerClass);
    } // setupUi

    void retranslateUi(QDialog *DownloadManagerClass)
    {
        DownloadManagerClass->setWindowTitle(QApplication::translate("DownloadManagerClass", "DownloadManager", 0, QApplication::UnicodeUTF8));
        seenButton->setText(QApplication::translate("DownloadManagerClass", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DownloadManagerClass: public Ui_DownloadManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADMANAGER_H
