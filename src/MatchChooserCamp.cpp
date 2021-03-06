#define DO_DEBUG

#include "MatchChooserCamp.h"

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QRegExp>
//#include <QtWidgets/QMessageBox>
//#include <QtWidgets/QFrame>
#include <QtGui/QMessageBox>
#include <QtGui/QFrame>

#include "defines.h"
#include "Fanta.h"
#include "Repository.h"
#include "singletonQtLogger.h"
#include "httpwindow.h"

MatchChooserCamp::MatchChooserCamp(QWidget *parent) :
		QDialog(parent) {
	ui.setupUi(this);

	QLabel *emptyLabel = new QLabel();

	int i = 0;
	while (i < 28) {
		for (int j = 0; j < 2; ++j) {
			labels[i][j] = new QLabel();
		}

		for (int j = 0; j < 4; ++j) {
			buttons[i][j] = new QRadioButton();
			buttons[i][j]->setFixedHeight(buttons[i][j]->sizeHint().height());
		}

		DEBUG("i: " << i << " (i % 4): " << (i % 4));

		int j;
		int n;
		for (n = 10; n >= 0; --n) {
			if (i >= 4 * n) {
				j = i + n + 1;
				break;
			}
		}

		DEBUG("j: " << j);

		if (i % 4 == 0) {
			QFrame *line = new QFrame(parent);
			line->setObjectName(QString::fromUtf8("line"));
			line->setFrameShape(QFrame::HLine);
			line->setFrameShadow(QFrame::Sunken);

			ui.gridLayout->addWidget(line, i + n, 0, 1, 6);
			DEBUG("i" << (i + n));
		}

		ui.gridLayout->addWidget(labels[i][0], j, 0);
		ui.gridLayout->addWidget(labels[i][1], j, 1);
		ui.gridLayout->addWidget(buttons[i][0], j, 2);
		ui.gridLayout->addWidget(buttons[i][1], j, 3);
		ui.gridLayout->addWidget(buttons[i][2], j, 4);
		ui.gridLayout->addWidget(buttons[i][3], j, 5);

		++i;
	}

	QFrame *line = new QFrame(parent);
	line->setObjectName(QString::fromUtf8("line"));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	ui.gridLayout->addWidget(line, 36, 0, 1, 6);

	QFile *fileDatiCamp = new QFile(THE_REPO->getDownloadPath() + "datiCampionato.txt");
	if (fileDatiCamp->exists()) {
		fileDatiCamp->open(QIODevice::ReadOnly);
		char buf[1024];

		while (!fileDatiCamp->atEnd()) {
			fileDatiCamp->readLine(buf, sizeof(buf));

			QString str = QString::fromLatin1(buf).trimmed();
			QString style;

			if (str.size() == 0) {
				continue; // skip empty lines
			}

			matches.push_back(str);

			QStringList list = str.split(QRegExp("\\/"),
					QString::KeepEmptyParts);

			int i = list.at(0).at(3).digitValue();
			int j = list.at(0).at(2).digitValue();
			int k = list.at(0).at(1).digitValue();

			QString a = list.at(0).at(1);
			QString b = list.at(0).at(2);
			QString c = list.at(0).at(3);

			DEBUG(a.toStdString().c_str() << b.toStdString().c_str() << c.toStdString().c_str());
			DEBUG(str.toStdString().c_str() << " " << str.indexOf(QRegExp("a[0-3][0-6][0-3]\\/\\/\\/\\/\\/")));

			if (
					(str.indexOf(QRegExp("a[0-3][0-6][0-3]\\/\\/\\/\\/\\/")) == -1)
					&&
					(str.indexOf(QRegExp("a[0-3][0-6][0-3]\\/-\\/-\\/-\\/-\\/"))	== -1)
				) {
				style = "background:#FF0000"; // risultato gia' presente
			} else {
				style = "background:#00FF00"; // risultato mancante
			}

			buttons[4 * j + k][i]->setStyleSheet(style);
			if ((list.at(1) != "" && list.at(1) != "-")
					&& (list.at(2) != "" && list.at(2) != "-")) {
				buttons[4 * j + k][i]->setText(list.at(1) + "-" + list.at(2));
			} else {
				buttons[4 * j + k][i]->setText(" - ");
			}
		}
	} else {
		DEBUG(fileDatiCamp->fileName().toStdString().c_str() << " does not exist");

		/* TODO
		 * completare
		 * * * * * * */
	}

	setData();

	DEBUG("Out");
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

			QString str = QString::fromLatin1(buf).trimmed();
			if (str.size() == 0) {
				continue; // skip empty lines
			} else if (str.indexOf(
					QRegExp("\\$longName\\[[0-9]\\].*\\$longName.*")) != -1) {

				DEBUG("str : " << str.toStdString().c_str());

				str.replace(QRegExp("\\$longName"), "");
				str.replace(QRegExp("\\[[0-9]\\]"), "");
				str.replace(QRegExp("="), "");
				str.replace(QRegExp(";"), "");
				str.replace(QRegExp("\\["), "");
				str.replace(QRegExp("\\]"), "");
				str.replace(QRegExp("^\\s+'"), "'");
				str.replace(QRegExp("'\\s+'"), "'");

				QStringList list = str.split("'", QString::SkipEmptyParts);
				for (unsigned int i=0; i<list.size(); i++)
					DEBUG("list.at(" << i << ")" << list.at(i).toStdString().c_str());

				map[list[0]] = list[1];
			}
		}

	} else {
		DEBUG(fileSquadre->fileName().toStdString().c_str() << " does not exist");

		/* TODO
		 * completare
		 * * * * * * */
	}

	std::map<QString, QString> mapRemap;

	QFile *fileCalendario = new QFile(THE_REPO->getDownloadPath() + "calendario.inc");
	if (fileCalendario->exists()) {
		fileCalendario->open(QIODevice::ReadOnly);
		char buf[1024];

		std::vector<QString> lines;
		while (!fileCalendario->atEnd()) {

			fileCalendario->readLine(buf, sizeof(buf));

			QString str = QString::fromLatin1(buf).trimmed();

			if (str.size() == 0) {
				continue; // skip empty lines
			} else if (str.indexOf(
					QRegExp("super.*longName.*super.*longName.*")) != -1) {

				DEBUG("str : " << str.toStdString().c_str());

				str.replace(QRegExp("\\$super"), "");
				str.replace(QRegExp("\\$longName"), "");
				str.replace(QRegExp("\\[[0-9]\\]"), "");
				str.replace(QRegExp("="), "");
				str.replace(QRegExp(";"), "");
				str.replace(QRegExp("\\["), "");
				str.replace(QRegExp("\\]"), "");
				str.replace(QRegExp("'"), "");
				lines.push_back(str);
			} else if (str.indexOf(
					QRegExp("longName.*[A-H].*longName.*[a-h].*")) != -1) {

				DEBUG("str : " << str.toStdString().c_str());

				str.replace(QRegExp("\\$longName"), "");
				str.replace(QRegExp("="), "");
				str.replace(QRegExp(";"), "");
				str.replace(QRegExp("\\["), "");
				str.replace(QRegExp("\\]"), "");
				str.replace(QRegExp("'"), "");

				QStringList list = str.split(" ", QString::SkipEmptyParts);
				mapRemap[list[0].trimmed()] = list[1].trimmed();
			}
		}

		DEBUG("lines.size() : " << lines.size());

		for (int i = 0; i < 28; ++i) {
			DEBUG("lines.at(" << i << ")" << lines.at(i).toStdString().c_str());

			QStringList list = lines.at(i).split(" ", QString::SkipEmptyParts);

			labels[i][0]->setText(map[mapRemap[list[0].trimmed()]]);
			labels[i][1]->setText(map[mapRemap[list[1].trimmed()]]);
		}

	} else {
		DEBUG(fileCalendario->fileName().toStdString().c_str() << " does not exist");

		/* TODO
		 * completare
		 * * * * * * */
	}

	DEBUG("Out");
}

void MatchChooserCamp::quit() {

	DEBUG("");

	chosenMatch = "";
	QString home;
	QString away;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 7; ++j) {

			for (int k = 0; k < 4; ++k) {
				DEBUG("button[" << (4*j+k) << "][" << i << "]");
				if (buttons[4 * j + k][i]->isChecked()) {
					DEBUG("checked");
					chosenMatch = "a" + QString::number(k) + QString::number(j)
							+ QString::number(i);
					home = labels[4 * j + k][0]->text();
					away = labels[4 * j + k][1]->text();
				}
			}
		}
	}

	DEBUG("chosenMatch = " << chosenMatch.toStdString().c_str());

	if (!chosenMatch.isEmpty()) {

		QString message, match, goalHome, goalAway, puntiHome, puntiAway,
				squadraHome, squadraAway;
		
		for (int i = 0; i < matches.size(); ++i) {

			if (matches.at(i).indexOf(chosenMatch) != -1) {
				match = matches.at(i);
				break;
			}
		}

		DEBUG("match = " << match.toStdString().c_str());

		QString title = "ATTENZIONE!!!";
		QStringList items = match.split(QRegExp("\\/"),
				QString::SkipEmptyParts);

		if (items.size() == 1
				|| (items.at(1) == "-" && items.at(2) == "-"
						&& items.at(3) == "-" && items.at(4) == "-")) { // risultato non ancora presente
			message += "I seguenti dati verranno salvati:<br><br>";
		} else { // risultato gia' presente che verrà sostituito
			message += "I dati:<br><br>";
			message += home + " : " + items[1] + " (" + items[3] + ")";
			message += "<br>";
			message += away + " : " + items[2] + " (" + items[4] + ")";
			message += "<br><br>";
			message += "marcatori:<br>";
			for (int i = 5; i < items.size(); ++i) {
				message += items[i] + "<br>";
			}
			message += "<br>";
			message += "verranno sostituiti con :<br><br>";
		}

		squadraHome = QString::fromStdString(FANTA->getTeamName(0));
		squadraAway = QString::fromStdString(FANTA->getTeamName(1));
		goalHome = my::toQString<unsigned int>(FANTA->getGoals(0));
		goalAway = my::toQString<unsigned int>(FANTA->getGoals(1));
		puntiHome = my::toQString<double>(FANTA->getTotal(0));
		puntiAway = my::toQString<double>(FANTA->getTotal(1));

		message += squadraHome + " : " + goalHome + " (" + puntiHome + ")";
		message += "<br>";
		message += squadraAway + " : " + goalAway + " (" + puntiAway + ")";
		message += "<br><br>";
		message += "marcatori:<br>";

		for (int i = 0; i < FANTA->getScorersSize(0); ++i) {
			message += QString::fromStdString(FANTA->getScorer(0, i)) + "<br>";
		}

		for (int i = 0; i < FANTA->getScorersSize(1); ++i) {
			message += QString::fromStdString(FANTA->getScorer(1, i)) + "<br>";
		}

		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, title, message,
				QMessageBox::Yes | QMessageBox::No);

		DEBUG("2");

		if (reply == QMessageBox::Yes) {
			DEBUG("yes");

			QFile *file = new QFile(THE_REPO->getDownloadPath() + "datiCampionato.txt");
			file->open(QIODevice::WriteOnly);
			for (int i = 0; i < matches.size(); ++i) {
				if (matches.at(i).indexOf(chosenMatch) == -1) {
					file->write(matches.at(i).toStdString().c_str());
				} else {
					QString line;

					if (chosenMatch.at(3) == '1' || chosenMatch.at(3) == '3') {
						line += chosenMatch + "/" + goalAway + "/" + goalHome + "/" + puntiAway + "/"	+ puntiHome	+ "/";
					} else if (chosenMatch.at(3) == '0' || chosenMatch.at(3) == '2') {
						line += chosenMatch + "/" + goalHome + "/" + goalAway + "/" + puntiHome + "/"	+ puntiAway	+ "/";
					} else {
						DEBUG("Errore! Risultato non salvato.");
						LOG(ERR, "Errore, risultato della partita non pubblicato.");
						return;
					}

					for (int j = 0; j < FANTA->getScorersSize(0); ++j) {
						line += QString::fromStdString(FANTA->getScorer(0, j))
						+ "/";
					}
					for (int j = 0; j < FANTA->getScorersSize(1); ++j) {
						line += QString::fromStdString(FANTA->getScorer(1, j))
						+ "/";
					}

					file->write(line.toStdString().c_str());

				}
				file->write("\n");
			}
			file->close();

			DEBUG("3");

			QUrl url(THE_REPO->getUrl());
			HttpWindow * httpWindow = new HttpWindow(THE_LOGGER, url,
					"datiCampionato.txt");
			httpWindow->upload(
					THE_REPO->getDownloadPath() + "datiCampionato.txt");

		} else if (reply == QMessageBox::No) {
			DEBUG("No");

			/*
			 * TODO
			 * completare ?
			 * * * * * * * */
		} else {
			LOG(ERR, "In void MatchChooserCamp::quit() --> ???");
			/*
			 * TODO
			 * completare ?
			 * * * * * * * */
		}

		this->close();

	} else {
		DEBUG("Out 1");
		return;
	}

	DEBUG("Out 2");
}

void MatchChooserCamp::deleteResult() {

	DEBUG("");

	chosenMatch = "";
	QString home;
	QString away;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 7; ++j) {
			for (int k = 0; k < 4; ++k) {

				DEBUG("button[" << (4*j+k) << "][" << i << "]");
				if (buttons[4 * j + k][i]->isChecked()) {
					DEBUG("checked");
					chosenMatch = "a" + QString::number(k) + QString::number(j)
							+ QString::number(i);
					home = labels[4 * j + k][0]->text();
					away = labels[4 * j + k][1]->text();
				}
			}
		}
	}

	DEBUG("chosenMatch = " << chosenMatch.toStdString().c_str());

	if (!chosenMatch.isEmpty()) {

		QString message, match, goalHome, goalAway, puntiHome, puntiAway,
				squadraHome, squadraAway;
		bool ritorno;

		for (int i = 0; i < matches.size(); ++i) {

			if (matches.at(i).indexOf(chosenMatch) != -1) {
				match = matches.at(i);
				break;
			}
		}

		DEBUG("match = " << match.toStdString().c_str());

		QString title = "ATTENZIONE!!!";

		QStringList items = match.split(QRegExp("\\/"), QString::SkipEmptyParts);

		if (items.size() == 1
				|| (items.at(1) == "-" && items.at(2) == "-"
						&& items.at(3) == "-" && items.at(4) == "-")) { // risultato non ancora presente
			message += "I seguenti dati verranno eliminati:<br><br>";
		} else { // risultato gia' presente che verrà sostituito
			message += "I dati:<br><br>";
			message += home + " : " + items[1] + " (" + items[3] + ")";
			message += "<br>";
			message += away + " : " + items[2] + " (" + items[4] + ")";
			message += "<br><br>";
			message += "marcatori:<br>";
			for (int i = 5; i < items.size(); ++i) {
				message += items[i] + "<br>";
			}
			message += "<br>";
			message += "verranno eliminati.<br><br>";
		}

		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, title, message,
				QMessageBox::Yes | QMessageBox::No);

		DEBUG("2");

		if (reply == QMessageBox::Yes) {
			DEBUG("yes");

			QFile *file = new QFile(THE_REPO->getDownloadPath() + "datiCampionato.txt");
			file->open(QIODevice::WriteOnly);
			for (int i = 0; i < matches.size(); ++i) {

				if (matches.at(i).indexOf(chosenMatch) == -1) {
					file->write(matches.at(i).toStdString().c_str());
				} else {
					QString line(chosenMatch + "/////");
					file->write(line.toStdString().c_str());
				}

				file->write("\n");
			}

			file->close();

			DEBUG("3");

			QUrl url(THE_REPO->getUrl());
			HttpWindow * httpWindow = new HttpWindow(THE_LOGGER, url,
					"datiCampionato.txt");
			httpWindow->upload(
					THE_REPO->getDownloadPath() + "datiCampionato.txt");

		} else if (reply == QMessageBox::No) {
			DEBUG("No");

			/*
			 * TODO
			 * completare ?
			 * * * * * * * */
		} else {
			LOG(ERR, "In void MatchChooserCamp::quit() --> ???");
			/*
			 * TODO
			 * completare ?
			 * * * * * * * */
		}

		this->close();

	} else {
		DEBUG("Out");
		return;
	}

	DEBUG("Out");
}

QString MatchChooserCamp::getChosenMatch() {
	return this->chosenMatch;
}
