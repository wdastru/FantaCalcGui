#ifndef WHICHOFTHESEDIALOG_H
#define WHICHOFTHESEDIALOG_H

#include <QDialog>
#include <QtCore/QObject>

class QLabel;
class QErrorMessage;

class WhichOfTheseDialog : public QDialog
{
    Q_OBJECT

public:
    WhichOfTheseDialog(QWidget *parent = 0);
    void setListOfThese( std::vector < std::string > );
    std::vector < std::string > ListOfThese;
    int chosenThese;

private slots:
    void setItem();
    void exit();

private:
    std::string Message;
    QLabel *itemLabel;
    QPushButton *okButton;
    QPushButton *abortButton;
    void enableOkButton();
    void enableQuitButton();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif
