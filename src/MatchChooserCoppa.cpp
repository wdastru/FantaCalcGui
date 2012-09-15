#include "MatchChooserCoppa.h"

#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QMessageBox>
#include <QFrame>

#include "defines.h"
#include "Fanta.h"
#include "Repository.h"
#include "singletonQtLogger.h"
#include "httpwindow.h"

MatchChooserCoppa::MatchChooserCoppa(QWidget *parent) :
		QDialog(parent) {
	ui.setupUi(this);

	QLabel *emptyLabel = new QLabel();

	int i = 0;
	while (i < 20) {
		for (int j = 0; j < 2; ++j) {
			labels[i][j] = new QLabel();
		}

		buttons[i] = new QRadioButton();

		//qDebug() << QString::number(i) << " " << QString::number(i % 4);

		int j;
		int n;
		for (n = 10; n >= 0; --n) {
			if (i >= 4 * n) {
				j = i + n + 1;
				break;
			}
		}

		//qDebug() << "j" << QString::number(j);

		if (i % 4 == 0) {
			QFrame *line = new QFrame(parent);
			line->setObjectName(QString::fromUtf8("line"));
			line->setFrameShape(QFrame::HLine);
			line->setFrameShadow(QFrame::Sunken);

			ui.gridLayout->addWidget(line, i + n, 0, 1, 3);
			//qDebug() << "i" << QString::number(i + n);
		}

		ui.gridLayout->addWidget(labels[i][0], j, 0);
		ui.gridLayout->addWidget(labels[i][1], j, 1);
		ui.gridLayout->addWidget(buttons[i], j, 2);

		++i;
	}

	QFrame *line = new QFrame(parent);
	line->setObjectName(QString::fromUtf8("line"));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	ui.gridLayout->addWidget(line, 26, 0, 1, 3);

	QFile *fileDatiCoppa = new QFile(THE_REPO->getDownloadPath() +"datiCoppa.txt");
	if (fileDatiCoppa->exists()) {
		fileDatiCoppa->open(QIODevice::ReadOnly);
		char buf[1024];

		int i = 0;
		while (!fileDatiCoppa->atEnd()) {
			fileDatiCoppa->readLine(buf, sizeof(buf));

			QString str = QString::fromAscii(buf).trimmed();
			QString style;

			if (str.size() == 0) {
				continue; // skip empty lines
			}

			matches.push_back(str);

			QStringList list = str.split(QRegExp("\\/"),
					QString::SkipEmptyParts);

			//int i = list.at(0).at(3).digitValue();
			//int j = list.at(0).at(2).digitValue();
			//int k = list.at(0).at(1).digitValue();

			//qDebug() << list.at(0) << " " << str;

			if ((str.indexOf(
					QRegExp(
							"^(gruppi[0-9]{1,2}|semi[0-3]|finali[0-3])\\/-\\/-\\/-\\/-\\/"))
					== -1)
					&& (str.indexOf(
							QRegExp(
									"^(gruppi[0-9]{1,2}|semi[0-3]|finali[0-3])\\/\\/\\/\\/\\/"))
							== -1)) {
				style = "background:#FF0000"; // risultato gia' presente
			} else {
				style = "background:#00FF00"; // risultato mancante
			}

			buttons[i]->setStyleSheet(style);
			++i;
		}
	} else {
		qDebug() << fileDatiCoppa->fileName() + " does not exist";

		/* TODO
		 * completare
		 * * * * * * */
	}

	//qDebug() << "Out of MatchChooserCoppa::MatchChooserCoppa(QWidget *parent)";
}

MatchChooserCoppa::~MatchChooserCoppa() {

}

void MatchChooserCoppa::setData() {

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

	std::map<QString, QString> mapRemap;
	std::vector<QString> lines;

	QFile *fileCalendario = new QFile(THE_REPO->getDownloadPath() +"calendarioCoppa.inc");
	if (fileCalendario->exists()) {
		fileCalendario->open(QIODevice::ReadOnly);
		char buf[1024];

		while (!fileCalendario->atEnd()) {

			fileCalendario->readLine(buf, sizeof(buf));

			QString str = QString::fromAscii(buf).trimmed();

			if (str.size() == 0) {
				continue; // skip empty lines
			} else if (str.indexOf(
					QRegExp("\\$[a-h]Coppa.*\\$longName\\['[a-h]'\\];"))
					!= -1) {
				str.replace(QRegExp("\\$"), "");
				str.replace(QRegExp("Coppa"), "");
				str.replace(QRegExp("longName"), "");
				str.replace(QRegExp("="), "");
				str.replace(QRegExp(";"), "");
				str.replace(QRegExp("\\["), "");
				str.replace(QRegExp("\\]"), "");
				str.replace(QRegExp("'"), "");

				mapRemap[str.split(" ", QString::SkipEmptyParts).at(0).trimmed()] =
						str.split(" ", QString::SkipEmptyParts).at(1).trimmed();

				//qDebug() << str.split(" ", QString::SkipEmptyParts).at(0).trimmed() << " " << str.split(" ", QString::SkipEmptyParts).at(1).trimmed();

			} else if (str.indexOf(
			// $superCoppa[0][0][0] = $aCoppa;	$superCoppa[0][0][1] = $bCoppa;
					QRegExp(
							"^\\$superCoppa\\[0\\]\\[[0-9]{1,2}\\]\\[[0-1]\\]\\s+=\\s+\\$[a-h]Coppa;\\s+\\$superCoppa\\[0\\]\\[[0-9]{1,2}\\]\\[[0-1]\\]\\s+=\\s+\\$[a-h]Coppa;"))
					!= -1) {
				str.replace(QRegExp("\\$"), "");
				str.replace(QRegExp("(Coppa|superCoppa)"), "");
				str.replace(QRegExp("="), "");
				str.replace(QRegExp("[0-9]"), "");
				str.replace(QRegExp(";"), "");
				str.replace(QRegExp("\\["), "");
				str.replace(QRegExp("\\]"), "");
				lines.push_back(str);

				//qDebug() << str;
			}
		}

		for (int i = 0; i < 12; ++i) {

			labels[i][0]->setText(
					map[mapRemap[lines.at(i).split(" ", QString::SkipEmptyParts).at(
							0).trimmed()]]);
			labels[i][1]->setText(
					map[mapRemap[lines.at(i).split(" ", QString::SkipEmptyParts).at(
							1).trimmed()]]);
		}

		for (int i = 12; i < 16; ++i) {
			labels[i][0]->setText("semifinale " + QString::number(i - 11));
			labels[i][1]->setText("semifinale " + QString::number(i - 11));
		}

		for (int i = 16; i < 20; ++i) {
			labels[i][0]->setText("finale " + QString::number(i - 15));
			labels[i][1]->setText("finale " + QString::number(i - 15));
		}

	} else {
		qDebug() << fileCalendario->fileName() + " does not exist";

		/* TODO
		 * completare
		 * * * * * * */
	}

	//qDebug() << "Out of void MatchChooserCoppa::setData().";
}

void MatchChooserCoppa::quit() {

	//qDebug() << "In void MatchChooserCoppa::quit().";

	QString ids[20];
	for (int i = 0; i < 12; ++i) {
		ids[i] = "gruppi" + QString::number(i);
	}
	for (int i = 12; i < 16; ++i) {
		ids[i] = "semi" + QString::number(i);
	}
	for (int i = 16; i < 20; ++i) {
		ids[i] = "finali" + QString::number(i);
	}

	chosenMatch = "";
	QString home;
	QString away;

	for (int i = 0; i < 20; ++i) {
		if (buttons[i]->isChecked()) {
			chosenMatch = QString::number(i);
			home = labels[i][0]->text();
			away = labels[i][1]->text();
		}
	}

	//qDebug() << "In void MatchChooserCoppa::quit(). chosenMatch = " << chosenMatch;

	if (!chosenMatch.isEmpty()) {

		QString message;
		QString match;

		//qDebug() << "chosenMatch.toInt() : " << chosenMatch.toInt();

		match = matches.at(chosenMatch.toInt());

		//qDebug() << "In void MatchChooserCoppa::quit(). match = " << match;

		QString title = "ATTENZIONE!!!";

		QStringList items = match.split(QRegExp("\\/"), QString::SkipEmptyParts);

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

		message += QString::fromStdString(FANTA->getTeamName(0)) + " : " + my::toQString<unsigned int>(FANTA->getGoals(0)) + " (" + my::toQString<double>(FANTA->getTotal(0)) + ")";
		message += "<br>";
		message += QString::fromStdString(FANTA->getTeamName(1)) + " : " + my::toQString<unsigned int>(FANTA->getGoals(1)) + " (" + my::toQString<double>(FANTA->getTotal(1)) + ")";
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

		//qDebug() << "In void MatchChooserCoppa::quit(). 2";

		if (reply == QMessageBox::Yes) {
			//qDebug() << "In void MatchChooserCoppa::quit() --> yes";

			QFile *file = new QFile(THE_REPO->getDownloadPath() +"datiCoppa.txt");
			file->open(QIODevice::WriteOnly);
			for (int i = 0; i < matches.size(); ++i) {
				if (i != chosenMatch.toInt()) {
					file->write(matches.at(i).toStdString().c_str());
				} else {
					QString line;
					line += ids[chosenMatch.toInt()];
					line += "/";
					line += my::toQString<unsigned int>(FANTA->getGoals(0)) + "/" + my::toQString<unsigned int>(FANTA->getGoals(1)) + "/" ;
					line += my::toQString<double>(FANTA->getTotal(0)) + "/" + my::toQString<double>(FANTA->getTotal(1)) + "/";
					for (int j = 0; j < FANTA->getScorersSize(0); ++j) {
						line += QString::fromStdString(FANTA->getScorer(0, j)) + "/";
					}
					for (int j = 0; j < FANTA->getScorersSize(1); ++j) {
						line += QString::fromStdString(FANTA->getScorer(1, j)) + "/";
					}

					file->write(line.toStdString().c_str());

				}
				file->write("\n");
			}
			file->close();

			//qDebug() << "In void MatchChooserCoppa::quit(). 3";

			QUrl url(
					"http://localhost/www.cim.unito.it/website/private/fantacalcio/777/");
			HttpWindow * httpWindow = new HttpWindow(THE_LOGGER, url, "datiCoppa.txt");
			httpWindow->upload(THE_REPO->getDownloadPath() + "datiCoppa.txt");

		} else if (reply == QMessageBox::No) {
				//qDebug() << "In void MatchChooserCoppa::quit() --> No";

				/*
				 * TODO
				 * completare ?
				 * * * * * * * */
			} else {
				LOG(ERROR, "In void MatchChooserCoppa::quit() --> ???");
				/*
				 * TODO
				 * completare ?
				 * * * * * * * */
			}

		this->close();

	} else {
		//qDebug() << "Out of void MatchChooserCoppa::quit(). 1";
		return;
	}

	//qDebug() << "Out of void MatchChooserCoppa::quit(). 2";
}

QString MatchChooserCoppa::getChosenMatch() {
	return this->chosenMatch;
}
