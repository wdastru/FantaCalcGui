#include "MatchChooserCamp.h"

#include <QFile>
#include <QDebug>
#include <QRegExp>

#include "defines.h"
#include "Repository.h"

MatchChooserCamp::MatchChooserCamp(QWidget *parent) :
		QDialog(parent) {
	ui.setupUi(this);

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 2; ++j) {
			labels[i][j] = new QLabel();
		}

		for (int j = 0; j < 4; ++j) {
			buttons[i][j] = new QRadioButton();
		}
	}

	for (int i = 0; i < 28; ++i) {
		ui.gridLayout->addWidget(labels[i][0], i, 0);
		ui.gridLayout->addWidget(labels[i][1], i, 1);
		ui.gridLayout->addWidget(buttons[i][0], i, 2);
		ui.gridLayout->addWidget(buttons[i][1], i, 3);
		ui.gridLayout->addWidget(buttons[i][2], i, 4);
		ui.gridLayout->addWidget(buttons[i][3], i, 5);
	}

}

MatchChooserCamp::~MatchChooserCamp() {

}

void MatchChooserCamp::setData() {

	std::map<QString, QString> map;

	QFile *fileSquadre = new QFile(THE_REPO->getDownloadPath() + "squadre.inc");
	if (fileSquadre->exists()) {
		fileSquadre->open(QIODevice::ReadOnly);
		char buf[1024];

		std::vector<QString> lines;

		while (!fileSquadre->atEnd()) {
			fileSquadre->readLine(buf, sizeof(buf));

			QString str = QString::fromAscii(buf).trimmed();
			if (str.size() == 0) {
				continue; // skip empty lines
			} else if (str.indexOf(
					QRegExp("\\$longName\\[[0-9]\\].*\\$longName.*")) != -1) {
				str.replace(QRegExp("\\$longName"), "");
				str.replace(QRegExp("\\[[0-9]\\]"), "");
				str.replace(QRegExp("="), "");
				str.replace(QRegExp(";"), "");
				str.replace(QRegExp("\\["), "");
				str.replace(QRegExp("\\]"), "");
				str.replace(QRegExp("^\\s+'"), "'");
				str.replace(QRegExp("'\\s+'"), "'");

				QStringList list = str.split("'", QString::SkipEmptyParts);
				map[list[0]] = list[1];
			}

		}

	} else {
		qDebug() << fileSquadre->fileName() + " does not exist";

		/* TODO
		 * completare
		 * * * * * * */
	}

	QFile *fileCalendario = new QFile(THE_REPO->getDownloadPath() +"calendario.inc");
	if (fileCalendario->exists()) {
		fileCalendario->open(QIODevice::ReadOnly);
		char buf[1024];

		std::vector<QString> lines;
		while (!fileCalendario->atEnd()) {

			fileCalendario->readLine(buf, sizeof(buf));

			QString str = QString::fromAscii(buf).trimmed();
			if (str.size() == 0) {
				continue; // skip empty lines
			} else if (str.indexOf(
					QRegExp("super.*longName.*super.*longName.*")) != -1) {
				str.replace(QRegExp("\\$super"), "");
				str.replace(QRegExp("\\$longName"), "");
				str.replace(QRegExp("\\[[0-9]\\]"), "");
				str.replace(QRegExp("="), "");
				str.replace(QRegExp(";"), "");
				str.replace(QRegExp("\\["), "");
				str.replace(QRegExp("\\]"), "");
				str.replace(QRegExp("'"), "");
				lines.push_back(str);
			}
		}

		for (int i = 0; i < 28; ++i) {
			QStringList list = lines.at(i).split(" ", QString::SkipEmptyParts);

			labels[i][0]->setText(map[list[0].trimmed()]);
			labels[i][1]->setText(map[list[1].trimmed()]);
		}

	} else {
		qDebug() << fileCalendario->fileName() + " does not exist";

		/* TODO
		 * completare
		 * * * * * * */
	}
}

void MatchChooserCamp::quit() {

	chosenMatch = "";

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 7; ++j) {
			for (int k = 0; k < 4; ++k) {
				if (buttons[4*j+k][i]->isChecked()) {
					chosenMatch = "a" + QString::number(k)
							+ QString::number(j) + QString::number(i);
				}
			}
		}

		if (!chosenMatch.isEmpty()) {
			this->close();
		} else {
			return;
		}
	}
}

QString MatchChooserCamp::getChosenMatch() {
	return this->chosenMatch;
}
