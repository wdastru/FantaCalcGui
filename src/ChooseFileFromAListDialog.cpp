#include "ChooseFileFromAListDialog.h"

#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QMainWindow>
#include <QtCore/QTime>
#include <QTabWidget>
#include <QtCore/QRect>
#include <QPalette>
#include <QtCore/QString>

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "defines.h"
#include "singletonQtLogger.h"
#include "IniFileManager.h"
#include "Repository.h"
#include "Downloader.h"
#include "toString.h"
#include "tokenize.h"

ChooseFileFromAListDialog::ChooseFileFromAListDialog(QString _fileFormazioni,
		QString _fileGazzetta, QWidget *parent) :
	QDialog(parent) {

	LOG(DEBUG, "In ChooseFileFromAListDialog constructor.");

	this->resize(630, 0);
	this->setMinimumSize(630, 0);

	Tabs = new QTabWidget(this);
	Tabs->setObjectName(QString::fromUtf8("Tabs"));

	formazioniTab = new QWidget();
	formazioniTab->setObjectName(QString::fromUtf8("formazioniTab"));
	QScrollArea *scrollAreaFormazioni = new QScrollArea(formazioniTab);
	Tabs->addTab(formazioniTab, QString());
	gazzettaTab = new QWidget();
	gazzettaTab->setObjectName(QString::fromUtf8("gazzettaTab"));
	QScrollArea *scrollAreaGazzetta = new QScrollArea(gazzettaTab);
	Tabs->addTab(gazzettaTab, QString());
	Tabs->setTabText(Tabs->indexOf(formazioniTab), "Formazioni");
	Tabs->setTabText(Tabs->indexOf(gazzettaTab), "Files Gazzetta");
	Tabs->setCurrentIndex(0);

	cancelClicked = false;
	QVBoxLayout * vboxLabelsFormazioni = new QVBoxLayout;
	QVBoxLayout * vboxHome = new QVBoxLayout;
	QVBoxLayout * vboxAway = new QVBoxLayout;
	QVBoxLayout * vboxNeutro1 = new QVBoxLayout;
	QVBoxLayout * vboxNeutro2 = new QVBoxLayout;
	QHBoxLayout * hboxButtons = new QHBoxLayout;
	QGridLayout * gridGazzettaLayout = new QGridLayout;

	FilesBox = new QGroupBox(tr("Files"));
	HomeAwayBox = new QGroupBox(tr("Andata-Ritorno"));
	CampoNeutroBox = new QGroupBox(tr("Campo Neutro"));

	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);

	sizePolicy.setHeightForWidth(HomeAwayBox->sizePolicy().hasHeightForWidth());
	HomeAwayBox->setSizePolicy(sizePolicy);

	sizePolicy.setHeightForWidth(
			CampoNeutroBox->sizePolicy().hasHeightForWidth());
	CampoNeutroBox->setSizePolicy(sizePolicy);

	groupBoxLabelsFormazioni = new QGroupBox("File");
	groupBoxHome = new QGroupBox("Casa");
	groupBoxAway = new QGroupBox("Fuori");
	groupBoxNeutro1 = new QGroupBox("Neutro");
	groupBoxNeutro2 = new QGroupBox("Neutro");
	groupBoxGazzetta = new QGroupBox("Files Gazzetta");
	LOG(
			DEBUG,
			"In ChooseFileFromAListDialog::ChooseFileFromAListDialog(...) --> fileFormazioni : "
					+ _fileFormazioni);

	QFile *file1 = new QFile(_fileFormazioni);

	QString time = QTime::currentTime().toString("hh:mm:ss.zzz");

	/*
	 * creazione di tre GroupBox:
	 * FilesBox
	 * HomeAwayBox
	 * CampoNeutroBoxs
	 *
	 */

	if (file1->exists()) {
		file1->open(QIODevice::ReadOnly);
		char buf[1024];

		int i = 0;

		/*
		 * creazione dei singoli radio buttons e labels
		 * e assegnazione degli stessi a:
		 * std::vector<QRadioButton *> home;
		 * std::vector<QRadioButton *> away;
		 * std::vector<QRadioButton *> neutro1;
		 * std::vector<QRadioButton *> neutro2;
		 * std::vector<QLabel *> labelFormazioni;
		 *
		 */

		while (!file1->atEnd()) {
			file1->readLine(buf, sizeof(buf));
			if (QString::fromAscii(buf).trimmed().size() == 0)
				continue; // skip empty lines

			QLabel * tmpLabel = new QLabel(QString::fromAscii(buf).trimmed());
			tmpLabel->setMaximumHeight(20);
			tmpLabel->setFont(THE_REPO->fontVariableWidthSmall);
			labelFormazioni.push_back(tmpLabel);

			QRadioButton * tmpButton1 = new QRadioButton();
			QRadioButton * tmpButton2 = new QRadioButton();
			QRadioButton * tmpButton3 = new QRadioButton();
			QRadioButton * tmpButton4 = new QRadioButton();
			tmpButton1->setMaximumHeight(20);
			tmpButton2->setMaximumHeight(20);
			tmpButton3->setMaximumHeight(20);
			tmpButton4->setMaximumHeight(20);
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
			vboxLabelsFormazioni->addWidget(labelFormazioni.at(i));
			vboxHome->addWidget(home.at(i));
			vboxAway->addWidget(away.at(i));
			vboxNeutro1->addWidget(neutro1.at(i));
			vboxNeutro2->addWidget(neutro2.at(i));

			i++;
		}

		this->nFiles = i;

		groupBoxLabelsFormazioni->setLayout(vboxLabelsFormazioni);
		groupBoxHome->setLayout(vboxHome);
		groupBoxAway->setLayout(vboxAway);
		groupBoxNeutro1->setLayout(vboxNeutro1);
		groupBoxNeutro2->setLayout(vboxNeutro2);
		/**/
		int max_size;
		(groupBoxLabelsFormazioni->sizeHint().height()
				> groupBoxHome->sizeHint().height()) ? max_size
				= groupBoxLabelsFormazioni->sizeHint().height() : max_size
				= groupBoxHome->sizeHint().height();
		(max_size > groupBoxAway->sizeHint().height()) ? max_size = max_size
				: max_size = groupBoxAway->sizeHint().height();
		(max_size > groupBoxNeutro1->sizeHint().height()) ? max_size = max_size
				: max_size = groupBoxNeutro1->sizeHint().height();
		(max_size > groupBoxNeutro2->sizeHint().height()) ? max_size = max_size
				: max_size = groupBoxNeutro2->sizeHint().height();

		groupBoxLabelsFormazioni->setFixedHeight(max_size);
		groupBoxHome->setFixedHeight(max_size);
		groupBoxAway->setFixedHeight(max_size);
		groupBoxNeutro1->setFixedHeight(max_size);
		groupBoxNeutro2->setFixedHeight(max_size);
		/**/

		QHBoxLayout * hboxRadio1 = new QHBoxLayout;
		hboxRadio1->addWidget(groupBoxHome);
		hboxRadio1->addWidget(groupBoxAway);
		HomeAwayBox->setCheckable(true);
		HomeAwayBox->setChecked(true);
		HomeAwayBox->setLayout(hboxRadio1);

		QHBoxLayout * hboxRadio2 = new QHBoxLayout;
		hboxRadio2->addWidget(groupBoxNeutro1);
		hboxRadio2->addWidget(groupBoxNeutro2);
		CampoNeutroBox->setCheckable(true);
		CampoNeutroBox->setChecked(false);
		CampoNeutroBox->setLayout(hboxRadio2);

		QHBoxLayout * hboxLabels = new QHBoxLayout;
		hboxLabels->addWidget(groupBoxLabelsFormazioni);
		FilesBox->setLayout(hboxLabels);

		file1->close();
	} else {
		LOG(
				FATAL,
				"In ChooseFileFromAListDialog constructor: Il file "
						+ _fileFormazioni + " non esiste.");
	} // fine GroupBox : FilesBox, HomeAwayBox e CampoNeutroBox


	time = QTime::currentTime().toString("hh:mm:ss.zzz");

	LOG(
			DEBUG,
			"In ChooseFileFromAListDialog::ChooseFileFromAListDialog(...) --> fileGazzetta : "
					+ _fileGazzetta);

	QFile *file2 = new QFile(_fileGazzetta);
	if (file2->exists()) {
		file2->open(QIODevice::ReadOnly);
		char buf[1024];

		int i = 0;
		std::vector<QString> lines;
		while (!file2->atEnd()) {
			file2->readLine(buf, sizeof(buf));
			if (QString::fromAscii(buf).trimmed().size() == 0)
				continue; // skip empty lines
			lines.push_back(QString::fromAscii(buf).trimmed());
			i++;
		}

		int rows = 15;
		int rowCounter = 0;
		for (unsigned int i = 0; i < lines.size(); i++) {
			QLabel * tmpLabel = new QLabel(lines.at(i));
			tmpLabel->setFont(THE_REPO->fontVariableWidthSmall);
			QRadioButton * tmpButton = new QRadioButton("");
			labelGazzetta.push_back(tmpLabel);
			gaz.push_back(tmpButton);
			connect(gaz.at(i), SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));
			gridGazzettaLayout->addWidget(labelGazzetta.at(i), rowCounter,
					2 * int(i / rows));
			gridGazzettaLayout->addWidget(gaz.at(i), rowCounter,
					2 * int(i / rows) + 1);
			if (rowCounter >= rows - 1)
				rowCounter = 0;
			else
				rowCounter++;
		}

		this->nGazFiles = lines.size();

		groupBoxGazzetta->setLayout(gridGazzettaLayout);

		file2->close();
	} else {
		LOG(
				FATAL,
				"In ChooseFileFromAListDialog constructor: Il file "
						+ _fileGazzetta + " non esiste.");
	}

	okButton = new QPushButton(tr("Ok"));
	cancelButton = new QPushButton(tr("Cancel"));

	okButton->setEnabled(false);
	okButton->setDefault(true);

	connect(HomeAwayBox, SIGNAL(toggled(bool)), this, SLOT(toggle1())); // da lasciare dopo HomeAwayBox->setChecked(true); altrimenti lancia toggle2()
	connect(CampoNeutroBox, SIGNAL(toggled(bool)), this, SLOT(toggle2()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(execute()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(quit()));

	hboxButtons->addWidget(okButton);
	hboxButtons->addWidget(cancelButton);

	QHBoxLayout *hBoxFormazioni = new QHBoxLayout;
	hBoxFormazioni->addWidget(FilesBox);
	hBoxFormazioni->addWidget(HomeAwayBox);
	hBoxFormazioni->addWidget(CampoNeutroBox);

	QHBoxLayout *hBoxGazzetta = new QHBoxLayout;
	hBoxGazzetta->addWidget(groupBoxGazzetta);

	QVBoxLayout * vboxFormazioni = new QVBoxLayout;
	vboxFormazioni->addLayout(hBoxFormazioni);
	QVBoxLayout * vboxGazzetta = new QVBoxLayout;
	vboxGazzetta->addLayout(hBoxGazzetta);

	containerBoxFormazioni = new QGroupBox(formazioniTab);
	containerBoxFormazioni->setLayout(vboxFormazioni);
	containerBoxFormazioni->setFlat(true);
	containerBoxGazzetta = new QGroupBox(gazzettaTab);
	containerBoxGazzetta->setLayout(vboxGazzetta);
	containerBoxGazzetta->setFlat(true);
	scrollAreaFormazioni->setWidget(containerBoxFormazioni);
	scrollAreaGazzetta->setWidget(containerBoxGazzetta);

	/*
	 * set Dimensions
	 */
	scrollAreaFormazioni->setFixedHeight(400);
	scrollAreaGazzetta->setFixedHeight(400);

	LOG(
			DEBUG,
			"In ChooseFileFromAListDialog::ChooseFileFromAListDialog(...) --> FilesBox->size().width() : "
					+ my::toQString<int>(FilesBox->size().width()));
	LOG(
			DEBUG,
			"In ChooseFileFromAListDialog::ChooseFileFromAListDialog(...) --> HomeAwayBox->size().width() : "
					+ my::toQString<int>(HomeAwayBox->size().width()));
	LOG(
			DEBUG,
			"In ChooseFileFromAListDialog::ChooseFileFromAListDialog(...) --> CampoNeutroBox->size().width() : "
					+ my::toQString<int>(CampoNeutroBox->size().width()));

	int width_formazioni = FilesBox->size().width()
			+ HomeAwayBox->size().width() + CampoNeutroBox->size().width() + 51;
	int width_gazzetta = groupBoxGazzetta->size().width() + 33;

	scrollAreaFormazioni->setMinimumWidth(
			std::max(width_formazioni, width_gazzetta));
	scrollAreaGazzetta->setMinimumWidth(
			std::max(width_formazioni, width_gazzetta));

	/*
	 * lo stile delle scrollArea serve inspiegabilmente per permettere
	 * alla colonna dei nomi dei file di allargarsi senza tagliare
	 * i nomi stessi
	 */
	scrollAreaFormazioni->setStyleSheet("border-color: rgb(245, 245, 245);");
	scrollAreaGazzetta->setStyleSheet("border-color: rgb(245, 245, 245);");

	formazioniTab->setFixedHeight(scrollAreaFormazioni->size().height());
	gazzettaTab->setFixedHeight(scrollAreaGazzetta->size().height());

	Tabs->setMinimumHeight(
			std::max(formazioniTab->size().height(),
					gazzettaTab->size().height()) + 26);

	QVBoxLayout *vbox2 = new QVBoxLayout;
	vbox2->addWidget(Tabs);
	vbox2->addLayout(hboxButtons);

	setLayout(vbox2);
	setFont(THE_REPO->fontVariableWidthSmall);
	setWindowTitle(tr("Choose Files"));
}
void ChooseFileFromAListDialog::quit() {
	LOG(DEBUG, "In void ChooseFileFromAListDialog::quit().");

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
void ChooseFileFromAListDialog::enableOkButton() {
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

	if (this->HomeAwayBox->isChecked() && homeIsChecked && awayIsChecked
			&& gazIsChecked)
		this->okButton->setEnabled(true);
	else if (this->CampoNeutroBox->isChecked() && neutro1IsChecked
			&& neutro2IsChecked && gazIsChecked)
		this->okButton->setEnabled(true);
	else
		this->okButton->setEnabled(false);
}
QString ChooseFileFromAListDialog::getGazFile() {
	for (int i = 0; i < this->nGazFiles; i++) {
		if (this->gaz.at(i)->isChecked())
			return this->labelGazzetta.at(i)->text();
	}
	return "";
}
QString ChooseFileFromAListDialog::getHomeFile() {
	if (this->HomeAwayBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->home.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	} else if (this->CampoNeutroBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->neutro1.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	}
	return QString::null;
}
QString ChooseFileFromAListDialog::getAwayFile() {
	if (this->HomeAwayBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->away.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	} else if (this->CampoNeutroBox->isChecked()) {
		for (int i = 0; i < this->nFiles; i++) {
			if (this->neutro2.at(i)->isChecked())
				return this->labelFormazioni.at(i)->text();
		}
	}
	return QString::null;
}
int ChooseFileFromAListDialog::groupBoxChecked() {
	if (this->HomeAwayBox->isChecked())
		return HOMEAWAY_BOX_IS_CHECKED;
	else if (this->CampoNeutroBox->isChecked())
		return NEUTRO_BOX_IS_CHECKED;
	else
		return NO_BOX_IS_CHECKED;
}
void ChooseFileFromAListDialog::toggle1() {
	if (this->HomeAwayBox->isChecked())
		this->CampoNeutroBox->setChecked(false);
	else
		this->CampoNeutroBox->setChecked(true);

	this->enableOkButton();
}
void ChooseFileFromAListDialog::toggle2() {
	if (this->CampoNeutroBox->isChecked())
		this->HomeAwayBox->setChecked(false);
	else
		this->HomeAwayBox->setChecked(true);

	this->enableOkButton();
}
void ChooseFileFromAListDialog::setFileFormazioni(QString _fileFormazioni) {
	this->fileFormazioni = _fileFormazioni;
}
QString ChooseFileFromAListDialog::getFileFormazioni(void) {
	return this->fileFormazioni;
}
QString ChooseFileFromAListDialog::getFileGazzetta(void) {
	return this->fileGazzetta;
}
void ChooseFileFromAListDialog::setFileGazzetta(QString _fileGazzetta) {
	this->fileGazzetta = _fileGazzetta;
}
void ChooseFileFromAListDialog::doDownload() {
	LOG(DEBUG,
			"In ChooseFileFromAListDialog::doDownload() --> Network will be accessed.");

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	urls->push_back(
			QUrl::fromLocalFile(
					THE_REPO->getFormazioniUrl() + this->getHomeFile()));
	urls->push_back(
			QUrl::fromLocalFile(
					THE_REPO->getFormazioniUrl() + this->getAwayFile()));
	urls->push_back(
			QUrl::fromLocalFile(THE_REPO->getGazzettaUrl() + this->getGazFile()));

	std::vector<QString> * savePaths = new std::vector<QString>;
	savePaths->push_back(
			THE_REPO->getDownloadPath() + '/' + this->getHomeFile());
	savePaths->push_back(
			THE_REPO->getDownloadPath() + '/' + this->getAwayFile());
	savePaths->push_back(THE_REPO->getGazzettaPath() + '/' + this->getGazFile());

	Downloader filesDownloader(THE_LOGGER, urls, savePaths);
	filesDownloader.show();
	filesDownloader.exec();

	if (filesDownloader.requestSucceded()) {
		this->downloadSuccess = true;
		LOG(
				DEBUG,
				"In ChooseFileFromAListDialog::doDownload() --> the download of files succeded.");
	} else {
		this->downloadSuccess = false;
		LOG(DEBUG,
				"In ChooseFileFromAListDialog::doDownload() --> the download of files failed.");
	}
	return;
}
bool ChooseFileFromAListDialog::createFileSquadreFromWebFiles() {
	LOG(DEBUG, "In ChooseFileFromAListDialog::createFileSquadreFromWebFiles().");

	if (this->downloadSuccess) {

		LOG(
				DEBUG,
				"In ChooseFileFromAListDialog::createFileSquadreFromWebFiles() --> download was successful.");

		QFile fHome(THE_REPO->getDownloadPath() + "/" + this->getHomeFile());
		QFile fAway(THE_REPO->getDownloadPath() + "/" + this->getAwayFile());

		fHome.open(QIODevice::ReadOnly);
		fAway.open(QIODevice::ReadOnly);

		if (!fHome.isReadable())
			LOG(
					FATAL,
					"In void ChooseFileFromAListDialog::createFileSquadreFromWebFiles() --> il file : "
							+ fHome.fileName() + " non è apribile.");

		else if (!fAway.isReadable())
			LOG(
					FATAL,
					"In void ChooseFileFromAListDialog::createFileSquadreFromWebFiles() --> il file : "
							+ fHome.fileName() + " non è apribile.");

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
			LOG(
					FATAL,
					"In : void ChooseFileFromAListDialog::createFileSquadreFromWebFiles() --> il file "
							+ fileOut + " non è apribile in scrittura.");
			this->close();
			return EXIT_FAILURE;
		}

		unsigned int ruolo[4] = { 3, 8, 8, 6 };
		QString str = "nome squadra : " + FIfHome.baseName().split("_").at(0)
				+ "\n";

		QString line = QString::fromAscii(fHome.readLine(1024)); // Ia riga : modulo tipo
		unsigned int modulo[4];
		str += "modulo : " + line + "\n";

		std::vector<std::string> vect;
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			modulo[i] = atoi(vect.at(i).c_str());

		vect.clear();
		line = QString::fromAscii(fHome.readLine(1024)); // IIa riga titolari
		unsigned int titolari[4];
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			titolari[i] = atoi(vect.at(i).c_str());

		vect.clear();
		line = QString::fromAscii(fHome.readLine(1024));
		unsigned int riserve[4];
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			riserve[i] = atoi(vect.at(i).c_str());

		if (!this->CampoNeutroBox->isChecked())
			str += "in casa\n\n";

		unsigned int lineReadCounter = 0;

		for (unsigned int i = 0; i < titolari[0]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[0]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == ruolo[0])) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[1]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[1]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1]))) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[2]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[2]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2]))) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[3]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[3]; i++) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2] + ruolo[3]))) {
			line = QString::fromAscii(fHome.readLine(1024));
			lineReadCounter++;
		}

		str += "\n###***###\n\n";

		str += "nome squadra : " + FIfAway.baseName().split("_").at(0) + "\n";

		line = QString::fromAscii(fAway.readLine(1024));
		str += "modulo : " + line + "\n";
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			modulo[i] = atoi(vect.at(i).c_str());

		vect.clear();
		line = QString::fromAscii(fAway.readLine(1024));
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			titolari[i] = atoi(vect.at(i).c_str());

		vect.clear();
		line = QString::fromAscii(fAway.readLine(1024));
		vect = tokenize(line.toStdString(), " -");
		for (unsigned int i = 0; i < vect.size(); i++)
			riserve[i] = atoi(vect.at(i).c_str());

		lineReadCounter = 0;

		for (unsigned int i = 0; i < titolari[0]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[0]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == ruolo[0])) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[1]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[1]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1]))) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[2]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[2]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2]))) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
		}

		for (unsigned int i = 0; i < titolari[3]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		for (unsigned int i = 0; i < riserve[3]; i++) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
			str += line;
		}

		while (!(lineReadCounter == (ruolo[0] + ruolo[1] + ruolo[2] + ruolo[3]))) {
			line = QString::fromAscii(fAway.readLine(1024));
			lineReadCounter++;
		}

		fOut.write(str.toAscii());

		LOG(
				DEBUG,
				"In ChooseFileFromAListDialog::createFileSquadreFromWebFiles() --> <br>"
						+ str);

		fHome.close();
		fAway.close();
		fOut.close();
		return EXIT_SUCCESS;
	} else {
		LOG(
				DEBUG,
				"In ChooseFileFromAListDialog::createFileSquadreFromWebFiles() --> download was not successful.");
		return EXIT_FAILURE;
	}
}
void ChooseFileFromAListDialog::execute() {
	LOG(DEBUG, "In void ChooseFileFromAListDialog::execute().");
	this->doDownload();
	if (this->downloadSuccess) {
		this->createFileSquadreFromWebFiles();
		this->fileGazzetta = THE_REPO->getGazzettaPath() + "/"
				+ this->getGazFile();
		this->accept();
	} else {
		LOG(
				DEBUG,
				"In void ChooseFileFromAListDialog::execute() --> download of file was not successful.");
		/* TODO
		 * completare
		 */
	}
}
bool ChooseFileFromAListDialog::wasCancelClicked() {
	return this->cancelClicked;
}
bool ChooseFileFromAListDialog::isFinished() {
	return this->hasFinished;
}
void ChooseFileFromAListDialog::closeEvent(QCloseEvent *event) {
	this->quit();
}
