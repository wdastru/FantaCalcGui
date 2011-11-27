/********************************************************************************
** Form generated from reading UI file 'IniFilePopulator.ui'
**
** Created: Sun 27. Nov 00:59:49 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INIFILEPOPULATOR_H
#define UI_INIFILEPOPULATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IniFilePopulatorClass
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QPushButton *formazioniButton;
    QLineEdit *formazioniLineEdit;
    QPushButton *gazzettaButton;
    QLineEdit *gazzettaLineEdit;
    QPushButton *risultatiButton;
    QLineEdit *risultatiLineEdit;
    QPushButton *downloadButton;
    QLineEdit *downloadLineEdit;
    QPushButton *listeButton;
    QLineEdit *listeLineEdit;
    QLineEdit *formazioniUrlLineEdit;
    QLineEdit *gazzettaUrlLineEdit;
    QLabel *label_3;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *debugLabel;
    QCheckBox *trueCheckBox;
    QCheckBox *falseCheckBox;
    QDialogButtonBox *okCancelButtonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *IniFilePopulatorClass)
    {
        if (IniFilePopulatorClass->objectName().isEmpty())
            IniFilePopulatorClass->setObjectName(QString::fromUtf8("IniFilePopulatorClass"));
        IniFilePopulatorClass->resize(400, 420);
        label = new QLabel(IniFilePopulatorClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 10, 281, 51));
        layoutWidget = new QWidget(IniFilePopulatorClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 60, 357, 231));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        formazioniButton = new QPushButton(layoutWidget);
        formazioniButton->setObjectName(QString::fromUtf8("formazioniButton"));

        formLayout->setWidget(0, QFormLayout::LabelRole, formazioniButton);

        formazioniLineEdit = new QLineEdit(layoutWidget);
        formazioniLineEdit->setObjectName(QString::fromUtf8("formazioniLineEdit"));
        formazioniLineEdit->setEnabled(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, formazioniLineEdit);

        gazzettaButton = new QPushButton(layoutWidget);
        gazzettaButton->setObjectName(QString::fromUtf8("gazzettaButton"));

        formLayout->setWidget(1, QFormLayout::LabelRole, gazzettaButton);

        gazzettaLineEdit = new QLineEdit(layoutWidget);
        gazzettaLineEdit->setObjectName(QString::fromUtf8("gazzettaLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, gazzettaLineEdit);

        risultatiButton = new QPushButton(layoutWidget);
        risultatiButton->setObjectName(QString::fromUtf8("risultatiButton"));

        formLayout->setWidget(2, QFormLayout::LabelRole, risultatiButton);

        risultatiLineEdit = new QLineEdit(layoutWidget);
        risultatiLineEdit->setObjectName(QString::fromUtf8("risultatiLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, risultatiLineEdit);

        downloadButton = new QPushButton(layoutWidget);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));

        formLayout->setWidget(3, QFormLayout::LabelRole, downloadButton);

        downloadLineEdit = new QLineEdit(layoutWidget);
        downloadLineEdit->setObjectName(QString::fromUtf8("downloadLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, downloadLineEdit);

        listeButton = new QPushButton(layoutWidget);
        listeButton->setObjectName(QString::fromUtf8("listeButton"));

        formLayout->setWidget(4, QFormLayout::LabelRole, listeButton);

        listeLineEdit = new QLineEdit(layoutWidget);
        listeLineEdit->setObjectName(QString::fromUtf8("listeLineEdit"));
        listeLineEdit->setMinimumSize(QSize(268, 20));

        formLayout->setWidget(4, QFormLayout::FieldRole, listeLineEdit);

        formazioniUrlLineEdit = new QLineEdit(layoutWidget);
        formazioniUrlLineEdit->setObjectName(QString::fromUtf8("formazioniUrlLineEdit"));

        formLayout->setWidget(5, QFormLayout::FieldRole, formazioniUrlLineEdit);

        gazzettaUrlLineEdit = new QLineEdit(layoutWidget);
        gazzettaUrlLineEdit->setObjectName(QString::fromUtf8("gazzettaUrlLineEdit"));

        formLayout->setWidget(6, QFormLayout::FieldRole, gazzettaUrlLineEdit);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_3);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_2);

        horizontalLayoutWidget = new QWidget(IniFilePopulatorClass);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 300, 171, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        debugLabel = new QLabel(horizontalLayoutWidget);
        debugLabel->setObjectName(QString::fromUtf8("debugLabel"));
        debugLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(debugLabel);

        trueCheckBox = new QCheckBox(horizontalLayoutWidget);
        buttonGroup = new QButtonGroup(IniFilePopulatorClass);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(trueCheckBox);
        trueCheckBox->setObjectName(QString::fromUtf8("trueCheckBox"));

        horizontalLayout->addWidget(trueCheckBox);

        falseCheckBox = new QCheckBox(horizontalLayoutWidget);
        buttonGroup->addButton(falseCheckBox);
        falseCheckBox->setObjectName(QString::fromUtf8("falseCheckBox"));

        horizontalLayout->addWidget(falseCheckBox);

        okCancelButtonBox = new QDialogButtonBox(IniFilePopulatorClass);
        okCancelButtonBox->setObjectName(QString::fromUtf8("okCancelButtonBox"));
        okCancelButtonBox->setGeometry(QRect(120, 380, 156, 23));
        okCancelButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(IniFilePopulatorClass);
        QObject::connect(okCancelButtonBox, SIGNAL(accepted()), IniFilePopulatorClass, SLOT(close()));
        QObject::connect(okCancelButtonBox, SIGNAL(rejected()), IniFilePopulatorClass, SLOT(close()));
        QObject::connect(downloadButton, SIGNAL(clicked()), IniFilePopulatorClass, SLOT(chooseDownloadPath()));
        QObject::connect(formazioniButton, SIGNAL(clicked()), IniFilePopulatorClass, SLOT(chooseFormazioniPath()));
        QObject::connect(gazzettaButton, SIGNAL(clicked()), IniFilePopulatorClass, SLOT(chooseGazzettaPath()));
        QObject::connect(listeButton, SIGNAL(clicked()), IniFilePopulatorClass, SLOT(chooseListePath()));
        QObject::connect(risultatiButton, SIGNAL(clicked()), IniFilePopulatorClass, SLOT(chooseRisultatiPath()));

        QMetaObject::connectSlotsByName(IniFilePopulatorClass);
    } // setupUi

    void retranslateUi(QDialog *IniFilePopulatorClass)
    {
        IniFilePopulatorClass->setWindowTitle(QApplication::translate("IniFilePopulatorClass", "IniFilePopulator", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IniFilePopulatorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:24pt; font-weight:600;\">The Populator</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        formazioniButton->setText(QApplication::translate("IniFilePopulatorClass", "Formazioni", 0, QApplication::UnicodeUTF8));
        gazzettaButton->setText(QApplication::translate("IniFilePopulatorClass", "Gazzetta", 0, QApplication::UnicodeUTF8));
        risultatiButton->setText(QApplication::translate("IniFilePopulatorClass", "Risultati", 0, QApplication::UnicodeUTF8));
        downloadButton->setText(QApplication::translate("IniFilePopulatorClass", "Download", 0, QApplication::UnicodeUTF8));
        listeButton->setText(QApplication::translate("IniFilePopulatorClass", "Liste", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("IniFilePopulatorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Gazzetta Url</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IniFilePopulatorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Formazioni Url</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        debugLabel->setText(QApplication::translate("IniFilePopulatorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Debug</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        trueCheckBox->setText(QApplication::translate("IniFilePopulatorClass", "TRUE", 0, QApplication::UnicodeUTF8));
        falseCheckBox->setText(QApplication::translate("IniFilePopulatorClass", "FALSE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IniFilePopulatorClass: public Ui_IniFilePopulatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INIFILEPOPULATOR_H
