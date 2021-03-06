#define DO_DEBUG

#include "ChooseFiles.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtCore/QString>
#include <QtCore/QFileInfo>

#include <sstream>

#include "defines.h"
#include "singletonQtLogger.h"
#include "Repository.h"
#include "Downloader.h"
#include "tokenize.h"

ChooseFiles::ChooseFiles(QString _fileFormazioni, QString _fileGazzetta,
		QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);
	this->setFont(THE_REPO->fontVariableWidthSmall);
	this->setWindowTitle("FantaCalcGui - Scegli i file online");
	this->height = 14;
	this->cancelClicked = FALSE;
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
			if (QString::fromLatin1(buf).trimmed().size() == 0)
				continue; // skip empty lines
			lines.push_back(QString::fromLatin1(buf).trimmed());
			i++;
		}

		//for (unsigned int i=0; i<lines.size(); i++) {
		//	DEBUG("lines.at(" << i << ") = " << lines.at(i).toStdString().c_str());
		//}

		int rows = 10;
		int rowCounter = 0;
		for (unsigned int i = 0; i < lines.size(); i++) {
			QLabel * tmpLabel = new QLabel(lines.at(i));
			//tmpLabel->setFont(THE_REPO->fontVariableWidthSmall);
			tmpLabel->setFixedHeight(this->height);
			tmpLabel->setFixedWidth(tmpLabel->sizeHint().width() + 20);

			QRadioButton * tmpButton = new QRadioButton("");
			tmpButton->setFixedHeight(this->height);
			tmpButton->setFixedWidth(tmpButton->sizeHint().width() * 1.5);

			labelGazzetta.push_back(tmpLabel);
			gaz.push_back(tmpButton);
			connect(gaz.at(i), SIGNAL(toggled(bool)), this, SLOT(enableOkButton()));
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
		DEBUG("Il file " << _fileGazzetta.toStdString().c_str() << " non esiste.");
		LOG(FATAL, "In ChooseFiles constructor: Il file " + _fileGazzetta + " non esiste.");
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
			if (QString::fromLatin1(buf).trimmed().size() == 0)
				continue; // skip empty lines

			QLabel * tmpLabel = new QLabel(QString::fromLatin1(buf).trimmed());

			tmpLabel->setFixedHeight(this->height);

			//DEBUG("file(" << i << ") = " << QString::fromLatin1(buf).trimmed().toStdString().c_str());

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

void ChooseFiles::on_HomeAwayBox_toggled(bool) {
	if (ui.HomeAwayBox->isChecked())
		ui.CampoNeutroBox->setChecked(false);
	else
		ui.CampoNeutroBox->setChecked(true);

	this->enableOkButton();
}

void ChooseFiles::on_CampoNeutroBox_toggled(bool) {
	if (ui.CampoNeutroBox->isChecked())
		ui.HomeAwayBox->setChecked(false);
	else
		ui.HomeAwayBox->setChecked(true);

	this->enableOkButton();
}

void ChooseFiles::on_okButton_clicked() {
	DEBUG("");

	this->doDownload();
	if (this->downloadSuccess) {
		DEBUG("downloadSuccess is true.");
		this->createFileSquadreFromWebFiles();
		this->fileGazzetta = THE_REPO->getGazzettaPath() + "/"
				+ this->getGazFile();
		this->accept();
	} else {
		if (!this->filesDownloader->wasCancelClicked()) {
			DEBUG("downloadSuccess is false.");
			/* TODO
			 * completare ?
			 * * * * * * * * */
		}
	}

	//this->close();
}

void ChooseFiles::on_cancelButton_clicked() {
	DEBUG("");

	for (int i = 0; i < this->nFiles; i++) {
		home.at(i)->setChecked(false);
		away.at(i)->setChecked(false);
		neutro1.at(i)->setChecked(false);
		neutro2.at(i)->setChecked(false);
	}
	for (int i = 0; i < this->nGazFiles; i++)
		gaz.at(i)->setChecked(false);

	this->cancelClicked = TRUE;
	this->close();
}

void ChooseFiles::enableOkButton() {
	bool homeIsChecked = false;
	bool awayIsChecked = false;
	bool neutro1IsChecked = false;
	bool neutro2IsChecked = false;
	bool gazIsChecked = false;

	for (int i = 0; i < this->nFiles; i++) {
		homeIsChecked = homeIsChecked || home.at(i)->isChecked();
		awayIsChecked = awayIsChecked || away.at(i)->isChecked();
		neutro1IsChecked = neutro1IsChecked || neutro1.at(i)->isChecked();
		neutro2IsChecked = neutro2IsChecked || neutro2.at(i)->isChecked();
	}

	for (int i = 0; i < this->nGazFiles; i++)
		gazIsChecked = gazIsChecked || gaz.at(i)->isChecked();

	if (gazIsChecked) {
		ui.okButton->setEnabled(true);
	} else {
		ui.okButton->setEnabled(false);
	}

	if (ui.HomeAwayBox->isChecked() && homeIsChecked && awayIsChecked
			&& gazIsChecked)
		ui.okButton->setEnabled(true);
	else if (ui.CampoNeutroBox->isChecked() && neutro1IsChecked
			&& neutro2IsChecked && gazIsChecked)
		ui.okButton->setEnabled(true);
	else
		ui.okButton->setEnabled(false);

	if (ui.okButton->isEnabled()) {
		DEBUG("enableOkButton abilitato");
	} else {
		DEBUG("enableOkButton disabilitato");
	}
}

bool ChooseFiles::wasCancelClicked() {
	return this->cancelClicked;
}

QString ChooseFiles::getFileGazzetta(void) {
	return this->fileGazzetta;
}

QString ChooseFiles::getFileFormazioni(void) {
	return this->fileFormazioni;
}

void ChooseFiles::doDownload() {
	DEBUG("Network will be accessed.");

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	urls->push_back(
			QUrl::fromLocalFile(
					THE_REPO->getFormazioniUrl() + this->getHomeFile()));
	urls->push_back(
			QUrl::fromLocalFile(
					THE_REPO->getFormazioniUrl() + this->getAwayFile()));
	urls->push_back(
			QUrl::fromLocalFile(
					THE_REPO->getGazzettaUrl() + this->getGazFile()));

	std::vector<QString> * savePaths = new std::vector<QString>;
	savePaths->push_back(
			THE_REPO->getDownloadPath() + this->getHomeFile());
	savePaths->push_back(
			THE_REPO->getDownloadPath() + this->getAwayFile());
	savePaths->push_back(
			THE_REPO->getGazzettaPath() + this->getGazFile());

	this->filesDownloader = new Downloader(THE_LOGGER, urls, savePaths);
	this->filesDownloader->show();
	this->filesDownloader->exec();

	if (this->filesDownloader->requestSucceded()) {
		DEBUG("request succeded.");
		this->downloadSuccess = true;
	} else {
		if (!this->filesDownloader->wasCancelClicked()) {
			LOG(ERR, "The download of files failed.");
			DEBUG("request not succeded.");
		}

		this->downloadSuccess = false;
	}
	return;
}

QString ChooseFiles::getGazFile() {
	for (int i = 0; i < this->nGazFiles; i++) {
		if (this->gaz.at(i)->isChecked())
			return this->labelGazzetta.at(i)->text();
	}
	return QString::null;
}

QString ChooseFiles::getHomeFile() {
	if (this->ui.HomeAwayBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->home.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	} else if (this->ui.CampoNeutroBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->neutro1.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	}
	return QString::null;
}

QString ChooseFiles::getAwayFile() {
	if (this->ui.HomeAwayBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->away.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	} else if (this->ui.CampoNeutroBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->neutro2.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	}
	return QString::null;
}

bool ChooseFiles::createFileSquadreFromWebFiles() {
	DEBUG("");

	if (this->downloadSuccess) {

		DEBUG("download was successful.");

		QFile fHome(THE_REPO->getDownloadPath() + "/" + this->getHomeFile());
		QFile fAway(THE_REPO->getDownloadPath() + "/" + this->getAwayFile());

		fHome.open(QIODevice::ReadOnly);
		fAway.open(QIODevice::ReadOnly);

		if (!fHome.isReadable()) {
			LOG(FATAL, "Il file : " + fHome.fileName() + " non e' apribile.");
			DEBUG("il file : " << fHome.fileName().toStdString().c_str() << " non e' apribile.");
		} else if (!fAway.isReadable()) {
			LOG(FATAL, "Il file : " + fAway.fileName() + " non e' apribile.");
			DEBUG("il file : " << fAway.fileName().toStdString().c_str() << " non e' apribile.");
		}

		QFileInfo FIfHome(fHome);
		QFileInfo FIfAway(fAway);

		QFile fGaz(this->getGazFile());
		QFileInfo FIfGaz(fGaz);

		QString fileOut = THE_REPO->getFormazioniPath() + '/'
				+ FIfHome.baseName().split("_").at(0) + "_"
				+ FIfAway.baseName().split("_").at(0) + "_" + FIfGaz.baseName()
				+ ".txt";

		this->fileFormazioni = fileOut;

		QFile fOut(fileOut);
		fOut.open(QIODevice::WriteOnly);

		if (!fOut.isWritable()) {
			DEBUG("il file " << fileOut.toStdString().c_str() << " non e' apribile in scrittura.");
			LOG(FATAL, "Il file " + fileOut + " non e' apribile in scrittura.");
			this->close();
			return EXIT_FAILURE;
		}

		unsigned int ruolo[4] = { 3, 8, 8, 6 };
		QString str = "nome squadra : " + FIfHome.baseName().split("_").at(0)
				+ "\n";

		QString line = QString::fromLatin1(fHome.readLine(1024)); // Ia riga : modulo tipo
		unsigned int modulo[4];
		str += "modulo : " + line + "\n";

		std::vector < std::string > vect;
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			modulo[i] = atoi(vect.at(i).c_str());

		vect.clear();
		line = QString::fromLatin1(fHome.readLine(1024)); // IIa riga titolari
		unsigned int titolari[4];
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++) {
			titolari[i] = atoi(vect.at(i).c_str());
			DEBUG("titolari[" << i << "]" << " = " << vect.at(i).c_str());
		}

		vect.clear();
		line = QString::fromLatin1(fHome.readLine(1024));
		unsigned int riserve[4];
		vect = tokenize(line.toStdString(), " -");
		vect.at(0) = QString::number(3 - titolari[0]).toStdString();
		vect.at(1) = QString::number(8 - titolari[1]).toStdString();
		vect.at(2) = QString::number(8 - titolari[2]).toStdString();
		vect.at(3) = QString::number(6 - titolari[3]).toStdString();
		for (unsigned int i = 0; i < vect.size(); i++) {
			riserve[i] = atoi(vect.at(i).c_str());
			DEBUG("riserve[" << i << "]" << " = " << vect.at(i).c_str());
		}

		if (!ui.CampoNeutroBox->isChecked())
			str += "in casa\n\n";

		unsigned int lineReadCounter = 0;

		for (unsigned int i = 0; i < titolari[0]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[0]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == ruolo[0])) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[1]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[1]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1]))) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[2]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[2]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2]))) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[3]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[3]; i++) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2] + ruolo[3]))) {
			line = QString::fromLatin1(fHome.readLine(1024));
			lineReadCounter++;
		}

		str += "\n###***###\n\n";

		str += "nome squadra : " + FIfAway.baseName().split("_").at(0) + "\n";

		line = QString::fromLatin1(fAway.readLine(1024));
		str += "modulo : " + line + "\n";
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			modulo[i] = atoi(vect.at(i).c_str());

		vect.clear();
		line = QString::fromLatin1(fAway.readLine(1024));
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++) {
			titolari[i] = atoi(vect.at(i).c_str());
			DEBUG("titolari[" << i << "]" << " = " << vect.at(i).c_str());
		}

		vect.clear();
		line = QString::fromLatin1(fAway.readLine(1024));
		vect = tokenize(line.toStdString(), " -");
		vect.at(0) = QString::number(3 - titolari[0]).toStdString();
		vect.at(1) = QString::number(8 - titolari[1]).toStdString();
		vect.at(2) = QString::number(8 - titolari[2]).toStdString();
		vect.at(3) = QString::number(6 - titolari[3]).toStdString();
		for (unsigned int i = 0; i < vect.size(); i++) {
			riserve[i] = atoi(vect.at(i).c_str());
			DEBUG("riserve[" << i << "]" << " = " << vect.at(i).c_str());
		}

		lineReadCounter = 0;

		for (unsigned int i = 0; i < titolari[0]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[0]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == ruolo[0])) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[1]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[1]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1]))) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[2]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[2]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2]))) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[3]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[3]; i++) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2] + ruolo[3]))) {
			line = QString::fromLatin1(fAway.readLine(1024));
			lineReadCounter++;
		}

		fOut.write(str.toLatin1());

		LOG(DEB, QObject::tr("<br> ====================="));
		LOG(DEB,     QObject::tr(" === File di input ==="));
		LOG(DEB,     QObject::tr(" =====================<br>"));

		std::istringstream iss(str.toStdString().c_str());
		std::string x;
		const int Limit = 255;
		char input[Limit];

		while(!iss.eof()) {
			iss.getline(input, Limit);
			x = std::string(input);
			LOG(DEB, QObject::tr("    %1").arg(QString::fromStdString(x)));
		}

		fHome.close();
		fAway.close();
		fOut.close();
		DEBUG("Out");

		return EXIT_SUCCESS;
	} else {
		DEBUG("download was not successful.");
		LOG(ERR, "Download was not successful.");
		return EXIT_FAILURE;
	}
}
