/********************************************************************************
** Form generated from reading UI file 'UseTheNetDialog.ui'
**
** Created: Sun 27. Nov 00:59:47 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USETHENETDIALOG_H
#define UI_USETHENETDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UseTheNetDialogClass
{
public:
    QLabel *UseTheNetDialogLabel;
    QPushButton *yesButton;
    QPushButton *noButton;
    QPushButton *abortButton;
    QPushButton *configButton;

    void setupUi(QDialog *UseTheNetDialogClass)
    {
        if (UseTheNetDialogClass->objectName().isEmpty())
            UseTheNetDialogClass->setObjectName(QString::fromUtf8("UseTheNetDialogClass"));
        UseTheNetDialogClass->resize(332, 185);
        UseTheNetDialogClass->setMouseTracking(false);
        UseTheNetDialogLabel = new QLabel(UseTheNetDialogClass);
        UseTheNetDialogLabel->setObjectName(QString::fromUtf8("UseTheNetDialogLabel"));
        UseTheNetDialogLabel->setGeometry(QRect(20, 20, 261, 51));
        yesButton = new QPushButton(UseTheNetDialogClass);
        yesButton->setObjectName(QString::fromUtf8("yesButton"));
        yesButton->setGeometry(QRect(90, 110, 75, 23));
        noButton = new QPushButton(UseTheNetDialogClass);
        noButton->setObjectName(QString::fromUtf8("noButton"));
        noButton->setGeometry(QRect(170, 110, 75, 23));
        abortButton = new QPushButton(UseTheNetDialogClass);
        abortButton->setObjectName(QString::fromUtf8("abortButton"));
        abortButton->setGeometry(QRect(90, 140, 75, 23));
        configButton = new QPushButton(UseTheNetDialogClass);
        configButton->setObjectName(QString::fromUtf8("configButton"));
        configButton->setGeometry(QRect(170, 140, 75, 23));

        retranslateUi(UseTheNetDialogClass);
        QObject::connect(yesButton, SIGNAL(clicked()), UseTheNetDialogClass, SLOT(yesClicked()));
        QObject::connect(noButton, SIGNAL(clicked()), UseTheNetDialogClass, SLOT(noClicked()));
        QObject::connect(abortButton, SIGNAL(clicked()), UseTheNetDialogClass, SLOT(abortClicked()));
        QObject::connect(configButton, SIGNAL(clicked()), UseTheNetDialogClass, SLOT(configClicked()));

        QMetaObject::connectSlotsByName(UseTheNetDialogClass);
    } // setupUi

    void retranslateUi(QDialog *UseTheNetDialogClass)
    {
        UseTheNetDialogClass->setWindowTitle(QApplication::translate("UseTheNetDialogClass", "Vuoi usare la rete?", 0, QApplication::UnicodeUTF8));
        UseTheNetDialogLabel->setText(QApplication::translate("UseTheNetDialogClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#000000;\">&nbsp;</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        yesButton->setText(QApplication::translate("UseTheNetDialogClass", "Yes", 0, QApplication::UnicodeUTF8));
        noButton->setText(QApplication::translate("UseTheNetDialogClass", "No", 0, QApplication::UnicodeUTF8));
        abortButton->setText(QApplication::translate("UseTheNetDialogClass", "Abort", 0, QApplication::UnicodeUTF8));
        configButton->setText(QApplication::translate("UseTheNetDialogClass", "Configure", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UseTheNetDialogClass: public Ui_UseTheNetDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USETHENETDIALOG_H
