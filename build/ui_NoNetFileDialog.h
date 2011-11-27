/********************************************************************************
** Form generated from reading UI file 'NoNetFileDialog.ui'
**
** Created: Sat 19. Nov 22:43:42 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NONETFILEDIALOG_H
#define UI_NONETFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoNetFileDialogClass
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *openFileNameGazzettaButton;
    QPushButton *openFileNameSquadreButton;
    QPushButton *noFileButton;
    QLineEdit *fileSquadreLineEdit;
    QLineEdit *fileGazzettaLineEdit;
    QLineEdit *newFileLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *NoNetFileDialogClass)
    {
        if (NoNetFileDialogClass->objectName().isEmpty())
            NoNetFileDialogClass->setObjectName(QString::fromUtf8("NoNetFileDialogClass"));
        NoNetFileDialogClass->resize(400, 155);
        layoutWidget = new QWidget(NoNetFileDialogClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 11, 361, 83));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        openFileNameGazzettaButton = new QPushButton(layoutWidget);
        openFileNameGazzettaButton->setObjectName(QString::fromUtf8("openFileNameGazzettaButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openFileNameGazzettaButton->sizePolicy().hasHeightForWidth());
        openFileNameGazzettaButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(openFileNameGazzettaButton, 1, 0, 1, 1);

        openFileNameSquadreButton = new QPushButton(layoutWidget);
        openFileNameSquadreButton->setObjectName(QString::fromUtf8("openFileNameSquadreButton"));
        sizePolicy.setHeightForWidth(openFileNameSquadreButton->sizePolicy().hasHeightForWidth());
        openFileNameSquadreButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(openFileNameSquadreButton, 0, 0, 1, 1);

        noFileButton = new QPushButton(layoutWidget);
        noFileButton->setObjectName(QString::fromUtf8("noFileButton"));
        sizePolicy.setHeightForWidth(noFileButton->sizePolicy().hasHeightForWidth());
        noFileButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(noFileButton, 2, 0, 1, 1);

        fileSquadreLineEdit = new QLineEdit(layoutWidget);
        fileSquadreLineEdit->setObjectName(QString::fromUtf8("fileSquadreLineEdit"));

        gridLayout->addWidget(fileSquadreLineEdit, 0, 1, 1, 1);

        fileGazzettaLineEdit = new QLineEdit(layoutWidget);
        fileGazzettaLineEdit->setObjectName(QString::fromUtf8("fileGazzettaLineEdit"));

        gridLayout->addWidget(fileGazzettaLineEdit, 1, 1, 1, 1);

        newFileLineEdit = new QLineEdit(layoutWidget);
        newFileLineEdit->setObjectName(QString::fromUtf8("newFileLineEdit"));

        gridLayout->addWidget(newFileLineEdit, 2, 1, 1, 1);

        okButton = new QPushButton(NoNetFileDialogClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(230, 120, 75, 23));
        cancelButton = new QPushButton(NoNetFileDialogClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(310, 120, 75, 23));

        retranslateUi(NoNetFileDialogClass);
        QObject::connect(noFileButton, SIGNAL(clicked()), NoNetFileDialogClass, SLOT(createEmptyFile()));
        QObject::connect(openFileNameGazzettaButton, SIGNAL(clicked()), NoNetFileDialogClass, SLOT(setOpenFileNameGazzetta()));
        QObject::connect(openFileNameSquadreButton, SIGNAL(clicked()), NoNetFileDialogClass, SLOT(setOpenFileNameSquadre()));
        QObject::connect(okButton, SIGNAL(clicked()), NoNetFileDialogClass, SLOT(okClicked()));
        QObject::connect(cancelButton, SIGNAL(clicked()), NoNetFileDialogClass, SLOT(cancelClicked()));

        QMetaObject::connectSlotsByName(NoNetFileDialogClass);
    } // setupUi

    void retranslateUi(QDialog *NoNetFileDialogClass)
    {
        NoNetFileDialogClass->setWindowTitle(QApplication::translate("NoNetFileDialogClass", "NoNetFileDialog", 0, QApplication::UnicodeUTF8));
        openFileNameGazzettaButton->setText(QApplication::translate("NoNetFileDialogClass", "File Gazzetta", 0, QApplication::UnicodeUTF8));
        openFileNameSquadreButton->setText(QApplication::translate("NoNetFileDialogClass", "File Squadre", 0, QApplication::UnicodeUTF8));
        noFileButton->setText(QApplication::translate("NoNetFileDialogClass", "Nuovo File", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("NoNetFileDialogClass", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("NoNetFileDialogClass", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NoNetFileDialogClass: public Ui_NoNetFileDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NONETFILEDIALOG_H
