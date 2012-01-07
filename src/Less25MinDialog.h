#ifndef LESS25MINDIALOG_H
#define LESS25MINDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class Less25MinDialog : public QDialog
{
    Q_OBJECT

public:
    Less25MinDialog(QWidget *parent = 0);
    void setPlayer( std::string );
    std::string getAnswer();

private slots:
    void questionMessage();
    void exit();

private:
    std::string Message;
    QLabel *questionLabel;
    QPushButton *questionButton;
    QPushButton *okButton;
    QString openFilesPath;
    std::string player;
    std::string answer;
    void enableOkButton();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif
