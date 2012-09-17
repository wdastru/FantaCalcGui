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
			//buttons[i][j]->setStyleSheet("background:#FF0000;");
		}

		ui.gridLayout->addWidget(labels[i][0], i, 0);
		ui.gridLayout->addWidget(labels[i][1], i, 1);
		ui.gridLayout->addWidget(buttons[i][0], i, 2);
		ui.gridLayout->addWidget(buttons[i][1], i, 3);
		ui.gridLayout->addWidget(buttons[i][2], i, 4);
		ui.gridLayout->addWidget(buttons[i][3], i, 5);
	}

	QFile *fileDatiCamp = new QFile(THE_REPO->getDownloadPath() +"datiCampionato.txt");
	if (fileDatiCamp->exists()) {
		fileDatiCamp->open(QIODevice::ReadOnly);
		char buf[1024];

		while (!fileDatiCamp->atEnd()) {
			fileDatiCamp->readLine(buf, sizeof(buf));

			QString str = QString::fromAscii(buf).trimmed();
			QString style;

			if (str.size() == 0) {
				continue; // skip empty lines
			}

			QStringList list = str.split(QRegExp("\/"), QString::SkipEmptyParts);

			int i = list.at(0).at(3).digitValue();
			int j = list.at(0).at(2).digitValue();
			int k = list.at(0).at(1).digitValue();

			//qDebug() << list.at(0).at(1) << list.at(0).at(2) << list.at(0).at(3);
			//qDebug() << str << " " << str.indexOf(QRegExp("a[0-3][0-6][0-3]\/\/\/\/\/"));

			if (str.indexOf(QRegExp("a[0-3][0-6][0-3]\/\/\/\/\/")) == -1) {
				style = "background:#FF0000"; // risultato gia' presente
			} else {
				style = "background:#00FF00"; // risultato mancante
			}

			buttons[4*j+k][i]->setStyleSheet(style);

		}
	} else {
		qDebug() << fileDatiCamp->fileName() + " does not exist";

		/* TODO
		 * completare
		 * * * * * * */
	}
	qDebug() << "Out of MatchChooserCamp::MatchChooserCamp(QWidget *parent)";
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

				//qDebug() << str;

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

	//qDebug() << "In void MatchChooserCamp::setData() 3";

}

void MatchChooserCamp::quit() {

	chosenMatch = "";

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 7; ++j) {
			for (int k = 0; k < 4; ++k) {

				//qDebug() << "button[" << 4*j+k << "][" << i << "]";
				if (buttons[4 * j + k][i]->isChecked()) {
					//qDebug() << "checked";
					chosenMatch = "a" + QString::number(k) + QString::number(j)
							+ QString::number(i);
				}
			}
		}
	}

	//qDebug() << "In void MatchChooserCamp::quit(). chosenMatch = " << chosenMatch;

	if (!chosenMatch.isEmpty()) {
		this->close();
	} else {
		return;
	}
}

QString MatchChooserCamp::getChosenMatch() {
	return this->chosenMatch;
}
