#ifndef WHICHOFLEVENSHTEINDIALOG_H
#define WHICHOFLEVENSHTEINDIALOG_H

#include <QtGui/QDialog>

#include "defines.h"
#include "StringModifier.h"
#include "singletonQtLogger.h"

class QLabel;
class QErrorMessage;

class WhichOfLevenshteinDialog : public QDialog
{
    Q_OBJECT

public:
    WhichOfLevenshteinDialog(QWidget *parent = 0);
    void setListOfLevenshtein( std::vector < std::string > );
    void setPlayer(QString);
    std::vector < std::string > ListOfLevenshtein;
    unsigned int chosenLevenshtein;

private slots:
    void setItem();
    void exit();

private:
    QLabel *itemLabel;
    QPushButton *okButton;
    QPushButton *abortButton;
    void enableOkButton();
    void enableQuitButton();
    QString player;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif
