#ifndef UPDATESCHOOSER_H
#define UPDATESCHOOSER_H

//#include <QtWidgets/QDialog>
//#include <QtWidgets/QLabel>
//#include <QtWidgets/QRadioButton>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>

#include "ui_UpdatesChooser.h"

#include "Repository.h"

class UpdatesChooser: public QDialog {
	Q_OBJECT

	friend class Repository;

	public:
		UpdatesChooser(QList<QHash<QString, QString> >&, QWidget *parent = 0);
		~UpdatesChooser();

	private slots:
		void checkRadioButtons();
		void enableOkButton();
		void setExistingDirectory();

	private:
		Ui::UpdatesChooserClass ui;
		std::vector<QRadioButton *> radioButtons;
		std::vector<QLabel *> labels;
		int chosenUpdate;
		QList<QHash<QString, QString> > *pResources;

};

#endif // UPDATESCHOOSER_H
