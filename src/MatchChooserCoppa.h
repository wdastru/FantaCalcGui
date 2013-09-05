#ifndef MATCHCHOOSERCOPPA_H
#define MATCHCHOOSERCOPPA_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>

#include "ui_MatchChooserCoppa.h"

class MatchChooserCoppa: public QDialog {
Q_OBJECT

public:
	MatchChooserCoppa(QWidget *parent = 0);
	~MatchChooserCoppa();
	void setData();
	QString getChosenMatch();

private slots:
	void quit();
	void deleteResult();


private:
	Ui::MatchChooserCoppaClass ui;

	QLabel *labels[20][2];
	QRadioButton *buttons[20];
	QString chosenMatch;
	std::vector<QString> matches;
};

#endif // MATCHCHOOSER_H
