/********************************************************************************
** Form generated from reading UI file 'Logger.ui'
**
** Created: Thu 7. Jul 16:37:32 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGGER_H
#define UI_LOGGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoggerClass
{
public:
    QPlainTextEdit *plainTextEdit;
    QPushButton *closeButton;
    QLabel *loggerLabel;
    QPushButton *startButton;

    void setupUi(QDialog *LoggerClass)
    {
        if (LoggerClass->objectName().isEmpty())
            LoggerClass->setObjectName(QString::fromUtf8("LoggerClass"));
        LoggerClass->resize(400, 452);
        plainTextEdit = new QPlainTextEdit(LoggerClass);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 90, 381, 351));
        closeButton = new QPushButton(LoggerClass);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(90, 60, 75, 23));
        loggerLabel = new QLabel(LoggerClass);
        loggerLabel->setObjectName(QString::fromUtf8("loggerLabel"));
        loggerLabel->setGeometry(QRect(20, 10, 361, 41));
        loggerLabel->setFrameShape(QFrame::StyledPanel);
        loggerLabel->setAlignment(Qt::AlignCenter);
        startButton = new QPushButton(LoggerClass);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(230, 60, 75, 23));

        retranslateUi(LoggerClass);
        QObject::connect(closeButton, SIGNAL(clicked()), LoggerClass, SLOT(close()));

        QMetaObject::connectSlotsByName(LoggerClass);
    } // setupUi

    void retranslateUi(QDialog *LoggerClass)
    {
        LoggerClass->setWindowTitle(QApplication::translate("LoggerClass", "Logger", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        closeButton->setWhatsThis(QApplication::translate("LoggerClass", "Close the program.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        closeButton->setText(QApplication::translate("LoggerClass", "Close", 0, QApplication::UnicodeUTF8));
        loggerLabel->setText(QString());
#ifndef QT_NO_WHATSTHIS
        startButton->setWhatsThis(QApplication::translate("LoggerClass", "Start the file dialog.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        startButton->setText(QApplication::translate("LoggerClass", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoggerClass: public Ui_LoggerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGER_H
