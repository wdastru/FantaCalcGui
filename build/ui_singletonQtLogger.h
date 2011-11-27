/********************************************************************************
** Form generated from reading UI file 'singletonQtLogger.ui'
**
** Created: Sun 27. Nov 14:28:47 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLETONQTLOGGER_H
#define UI_SINGLETONQTLOGGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_singletonQtLoggerClass
{
public:
    QPlainTextEdit *plainTextEdit;
    QLabel *titleLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *exitButton;
    QPushButton *onlineButton;
    QPushButton *offlineButton;
    QPushButton *configButton;
    QLabel *versionLabel;

    void setupUi(QWidget *singletonQtLoggerClass)
    {
        if (singletonQtLoggerClass->objectName().isEmpty())
            singletonQtLoggerClass->setObjectName(QString::fromUtf8("singletonQtLoggerClass"));
        singletonQtLoggerClass->resize(682, 413);
        plainTextEdit = new QPlainTextEdit(singletonQtLoggerClass);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 40, 661, 331));
        titleLabel = new QLabel(singletonQtLoggerClass);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 10, 681, 31));
        QFont font;
        font.setStrikeOut(false);
        font.setKerning(false);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        layoutWidget = new QWidget(singletonQtLoggerClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 380, 320, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        exitButton = new QPushButton(layoutWidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        horizontalLayout->addWidget(exitButton);

        onlineButton = new QPushButton(layoutWidget);
        onlineButton->setObjectName(QString::fromUtf8("onlineButton"));

        horizontalLayout->addWidget(onlineButton);

        offlineButton = new QPushButton(layoutWidget);
        offlineButton->setObjectName(QString::fromUtf8("offlineButton"));

        horizontalLayout->addWidget(offlineButton);

        configButton = new QPushButton(layoutWidget);
        configButton->setObjectName(QString::fromUtf8("configButton"));

        horizontalLayout->addWidget(configButton);

        versionLabel = new QLabel(singletonQtLoggerClass);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setGeometry(QRect(540, 380, 131, 21));

        retranslateUi(singletonQtLoggerClass);
        QObject::connect(exitButton, SIGNAL(clicked()), singletonQtLoggerClass, SLOT(saveLogAndClose()));
        QObject::connect(onlineButton, SIGNAL(clicked()), singletonQtLoggerClass, SLOT(onlineClicked()));
        QObject::connect(offlineButton, SIGNAL(clicked()), singletonQtLoggerClass, SLOT(offlineClicked()));
        QObject::connect(configButton, SIGNAL(clicked()), singletonQtLoggerClass, SLOT(configClicked()));

        QMetaObject::connectSlotsByName(singletonQtLoggerClass);
    } // setupUi

    void retranslateUi(QWidget *singletonQtLoggerClass)
    {
        singletonQtLoggerClass->setWindowTitle(QApplication::translate("singletonQtLoggerClass", "Logger", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("singletonQtLoggerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#0000ff;\">TITOLO</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("singletonQtLoggerClass", "Exit", 0, QApplication::UnicodeUTF8));
        onlineButton->setText(QApplication::translate("singletonQtLoggerClass", "Online", 0, QApplication::UnicodeUTF8));
        offlineButton->setText(QApplication::translate("singletonQtLoggerClass", "Offline", 0, QApplication::UnicodeUTF8));
        configButton->setText(QApplication::translate("singletonQtLoggerClass", "Configure", 0, QApplication::UnicodeUTF8));
        versionLabel->setText(QApplication::translate("singletonQtLoggerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">version</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class singletonQtLoggerClass: public Ui_singletonQtLoggerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLETONQTLOGGER_H
