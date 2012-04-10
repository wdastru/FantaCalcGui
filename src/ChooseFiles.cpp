#include "ChooseFiles.h"

#include <QtCore/QDebug>

#include "defines.h"
#include "singletonQtLogger.h"
#include "Repository.h"

ChooseFiles::ChooseFiles(QString _fileFormazioni, QString _fileGazzetta,
		QWidget *parent) :
	QWidget(parent) {
	ui.setupUi(this);
	this->height = 14;
	setupFormazioniTab(_fileFormazioni);
	setupGazzettaTab(_fileGazzetta);
}

ChooseFiles::~ChooseFiles() {

}

void ChooseFiles::setupGazzettaTab(QString _fileGazzetta) {
	QFile *fileGazzetta = new QFile(_fileGazzetta);

	if (fileGazzetta->exists()) {
		fileGazzetta->open(QIODevice::ReadOnly);
		char buf[1024];

		int i = 0;
		std::vector < QString > lines;
		while (!fileGazzetta->atEnd()) {
			fileGazzetta->readLine(buf, sizeof(buf));
			if (QString::fromAscii(buf).trimmed().size() == 0)
				continue; // skip empty lines
			lines.push_back(QString::fromAscii(buf).trimmed());
			i++;
		}

		qDebug() << "In ChooseFiles::ChooseFiles(...) --> lines.size() = "
				+ QString::number(lines.size());

		int rows = 10;
		int rowCounter = 0;
		for (unsigned int i = 0; i < lines.size(); i++) {
			QLabel * tmpLabel = new QLabel(lines.at(i));
			tmpLabel->setFont(THE_REPO->fontVariableWidthSmall);
			tmpLabel->setFixedHeight(this->height);
			tmpLabel->setFixedWidth(tmpLabel->sizeHint().width() + 20);

			QRadioButton * tmpButton = new QRadioButton("");
			tmpButton->setFixedHeight(this->height);
			tmpButton->setFixedWidth(tmpButton->sizeHint().width() * 1.5);

			labelGazzetta.push_back(tmpLabel);
			gaz.push_back(tmpButton);
			connect(gaz.at(i), SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));
			ui.gridGazzettaLayout->addWidget(gaz.at(i), rowCounter,
					2 * int(i / rows));
			ui.gridGazzettaLayout->addWidget(labelGazzetta.at(i), rowCounter,
					2 * int(i / rows) + 1);
			if (rowCounter >= rows - 1)
				rowCounter = 0;
			else
				rowCounter++;
		}

		this->nGazFiles = lines.size();

		fileGazzetta->close();
	} else {
		LOG(
				FATAL,
				"In ChooseFiles constructor: Il file " + _fileGazzetta
						+ " non esiste.");
	}
}

void ChooseFiles::setupFormazioniTab(QString _fileFormazioni) {
	QFile *fileFormazioni = new QFile(_fileFormazioni);

	if (fileFormazioni->exists()) {
		fileFormazioni->open(QIODevice::ReadOnly);
		char buf[1024];

		int i = 0;
		int maxWidth = 0;

		while (!fileFormazioni->atEnd()) {
			fileFormazioni->readLine(buf, sizeof(buf));
			if (QString::fromAscii(buf).trimmed().size() == 0)
				continue; // skip empty lines

			QLabel * tmpLabel = new QLabel(QString::fromAscii(buf).trimmed());

			tmpLabel->setFixedHeight(this->height);
			tmpLabel->setFont(THE_REPO->fontVariableWidthSmall);

			QRadioButton * tmpButton1 = new QRadioButton();
			QRadioButton * tmpButton2 = new QRadioButton();
			QRadioButton * tmpButton3 = new QRadioButton();
			QRadioButton * tmpButton4 = new QRadioButton();
			tmpButton1->setFixedHeight(this->height);
			tmpButton2->setFixedHeight(this->height);
			tmpButton3->setFixedHeight(this->height);
			tmpButton4->setFixedHeight(this->height);
			tmpButton1->setFixedWidth(tmpButton1->sizeHint().width() * 1.5);
			tmpButton2->setFixedWidth(tmpButton2->sizeHint().width() * 1.5);
			tmpButton3->setFixedWidth(tmpButton3->sizeHint().width() * 1.5);
			tmpButton4->setFixedWidth(tmpButton4->sizeHint().width() * 1.5);

			labelFormazioni.push_back(tmpLabel);
			home.push_back(tmpButton1);
			away.push_back(tmpButton2);
			neutro1.push_back(tmpButton3);
			neutro2.push_back(tmpButton4);
			connect(home.at(i), SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));
			connect(away.at(i), SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));
			connect(neutro1.at(i), SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));
			connect(neutro2.at(i), SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));

			ui.vBoxLabelsFormazioni->addWidget(labelFormazioni.at(i));
			ui.vBoxHome->addWidget(home.at(i));
			ui.vBoxAway->addWidget(away.at(i));
			ui.vBoxNeutro1->addWidget(neutro1.at(i));
			ui.vBoxNeutro2->addWidget(neutro2.at(i));

			i++;
		}

		this->nFiles = i;

		ui.HomeAwayBox->setFixedWidth(120);
		ui.CampoNeutroBox->setFixedWidth(120);

		fileFormazioni->close();
	} else {
		LOG(
				FATAL,
				"In ChooseFiles constructor: Il file " + _fileFormazioni
						+ " non esiste.");
	}
}

void ChooseFiles::on_okButton_clicked() {
	LOG(DEBUG, "In void ChooseFiles::on_okButton_clicked().");
	//this->doDownload();
	//if (this->downloadSuccess) {
	//	this->createFileSquadreFromWebFiles();
	//	this->fileGazzetta = THE_REPO->getGazzettaPath() + "/"
	//			+ this->getGazFile();
	//	this->accept();
	//} else {
	//	LOG(DEBUG,
	//			"In void ChooseFiles::execute() --> download of file was not successful.");
	//	/* TODO
	//	 * completare
	//	 */
	//}

	this->close();
}

void ChooseFiles::on_cancelButton_clicked() {
	qDebug() << "In void ChooseFiles::on_okButton_clicked()";

	//for (int i = 0; i < this->nFiles; i++) {
	//	home.at(i)->setChecked(false);
	//	away.at(i)->setChecked(false);
	//	neutro1.at(i)->setChecked(false);
	//	neutro2.at(i)->setChecked(false);
	//}
	for (int i = 0; i < this->nGazFiles; i++)
		gaz.at(i)->setChecked(false);

	this->cancelClicked = TRUE;
	this->close();
}

void ChooseFiles::enableOkButton() {
	qDebug() << "In void ChooseFiles::enableOkButton()";

	//bool homeIsChecked = false;
	//bool awayIsChecked = false;
	//bool neutro1IsChecked = false;
	//bool neutro2IsChecked = false;
	bool gazIsChecked = false;

	//for (int i = 0; i < this->nFiles; i++) {
	//	homeIsChecked = homeIsChecked || home.at(i)->isChecked();
	//	awayIsChecked = awayIsChecked || away.at(i)->isChecked();
	//	neutro1IsChecked = neutro1IsChecked || neutro1.at(i)->isChecked();
	//	neutro2IsChecked = neutro2IsChecked || neutro2.at(i)->isChecked();
	//}

	for (int i = 0; i < this->nGazFiles; i++)
		gazIsChecked = gazIsChecked || gaz.at(i)->isChecked();

	if (gazIsChecked) {
		ui.okButton->setEnabled(true);
	} else {
		ui.okButton->setEnabled(false);
	}

	//if (this->HomeAwayBox->isChecked() && homeIsChecked && awayIsChecked
	//		&& gazIsChecked)
	//	this->okButton->setEnabled(true);
	//else if (this->CampoNeutroBox->isChecked() && neutro1IsChecked
	//		&& neutro2IsChecked && gazIsChecked)
	//	this->okButton->setEnabled(true);
	//else
	//	this->okButton->setEnabled(false);
}
