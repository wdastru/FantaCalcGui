#ifndef MATCHCHOOSERCAMP_H
#define MATCHCHOOSERCAMP_H

#include <QtGui/QDialog>
#include <QLabel>
#include <QRadioButton>

#include "ui_MatchChooserCamp.h"

class MatchChooserCamp: public QDialog {
Q_OBJECT

public:
	MatchChooserCamp(QWidget *parent = 0);
	~MatchChooserCamp();
	void setData();
	QString getChosenMatch();

private slots:
	void quit();
	void deleteResult();

private:
	Ui::MatchChooserCampClass ui;

	QLabel *labels[28][2];
	QRadioButton *buttons[28][4];
	QString chosenMatch;
	std::vector<QString> matches;
};

#endif // MATCHCHOOSER_H
