#ifndef UPDATESCHOOSER_H
#define UPDATESCHOOSER_H

#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include "ui_UpdatesChooser.h"

class UpdatesChooser : public QDialog
{
    Q_OBJECT

public:
    UpdatesChooser(QList<QHash<QString, QString> >&, QWidget *parent = 0);
    ~UpdatesChooser();
    int getUpdate();

private slots:
	void checkRadioButtons();
	void enableOkButton();

private:
    Ui::UpdatesChooserClass ui;
    std::vector<QRadioButton *> radioButtons;
    std::vector<QLabel *> labels;
    int chosenUpdate;

};

#endif // UPDATESCHOOSER_H
