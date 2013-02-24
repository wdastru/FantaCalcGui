#include "UpdatesChooser.h"
#include "Downloader.h"
#include "defines.h"
#ifdef _WIN32
#include "windows.h"
#include "shellapi.h"
#endif

#include "QtGui/QFileDialog"
#include "QtCore/QDebug"
#include "QtCore/QUrl"
#include "QtGui/QMessageBox"
#include "QtCore/QRegExp"

UpdatesChooser::UpdatesChooser(QList<QHash<QString, QString> >& resources,
		QWidget *parent) :
		QDialog(parent) {
	ui.setupUi(this);

	pResources = &resources;
	chosenUpdate = -1;

	this->setWindowTitle("Scegli l'update che fa per te ...");

	for (int i = 0; i < resources.size(); ++i) {
		if (resources.at(i)["status"] == "new") {
			QLabel *label = new QLabel(
					resources.at(i)["file"] + " ("
							+ resources.at(i)["description"] + ")");
			labels.push_back(label);
			QRadioButton *radio = new QRadioButton();
			radio->setFixedWidth(radio->sizeHint().width() * 1.5);
			radio->setText(resources.at(i)["file"] + " ("
							+ resources.at(i)["description"] + ")");

			QObject::connect(radio, SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));

			radioButtons.push_back(radio);

			ui.gridLayout->addWidget(radioButtons.at(i), i, 0);
			//ui.gridLayout->addWidget(labels.at(i), i, 1);
		}
	}

	ui.dirLabel->setText(THE_REPO->getDownloadPath());

	connect(ui.setDir, SIGNAL(clicked()), this, SLOT(setExistingDirectory()));
}

UpdatesChooser::~UpdatesChooser() {

}

void UpdatesChooser::checkRadioButtons() {
	for (int i = 0; i < radioButtons.size(); ++i) {
		if (radioButtons.at(i)->isChecked()) {
			chosenUpdate = i;
			break;
		}
	}

	std::vector<QUrl> * urls = new std::vector<QUrl>;
	QString url = THE_REPO->getUrl() + "download/" + pResources->at(chosenUpdate)["file"];
	urls->push_back(QUrl::fromLocalFile(url));

	//qDebug() << url;

	std::vector<QString> *savePaths = new std::vector<QString>;
	QString savePath = ui.dirLabel->text() + "/"
			+ pResources->at(chosenUpdate)["file"];
	savePaths->push_back(savePath);

	//qDebug() << savePath;

	Downloader updateDownloader(THE_LOGGER, urls, savePaths, true);

	if (updateDownloader.requestSucceded()) { // download succeded
		LOG(DBG,
		"Download of "
		+ pResources->at(chosenUpdate)["file"]
		+ " succeded.");

		//qDebug() << "In void UpdatesChooser::checkRadioButtons() --> answered Yes";
		//qDebug() << "In void UpdatesChooser::checkRadioButtons() --> search for .exe returned " << url.indexOf(QRegExp("\\.exe$"), 0);

		if (url.indexOf(QRegExp("\\.exe$"), 0) != -1) { // urls is an .exe file
			QString title = "Domanda";
			QString message = "Installo la nuova versione ?\nIl programma verra' terminato.";

#ifdef _WIN32
#endif // _WIN32
#ifdef __APPLE__
			message += "\n(richiede wine).";
#endif // __APPLE__
#ifdef __linux__
			message += "\n(richiede wine).";
#endif // __linux__
			QString answer;

			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, title, message,
					QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes) {

#ifdef _WIN32
				std::string command = "\"" + savePath.toStdString() + "\"";
				ShellExecute(NULL, "open", command.c_str(), NULL, NULL, SW_SHOWNORMAL);
#endif // _WIN32
#ifdef __APPLE__
				std::string command = "wine " + savePath.toStdString() + " &";
				int retVal = system(command.c_str());
#endif // __APPLE__
#ifdef __linux__
				std::string command = "wine " + savePath.toStdString() + " &";
				int retVal = system(command.c_str());
#endif // __linux__
				exit(0);

			} else if (reply == QMessageBox::No) {
				this->close();
				return;
			} else {
				LOG(ERR, "In void UpdatesChooser::checkRadioButtons() --> error");
			}
		} else if (url.indexOf(QRegExp("\\.zip$"), 0) != -1) { // urls is a .zip file

#ifdef __APPLE__
#else
			QString title = "Domanda";
			QString message = "Aprire la cartella di destinazione ?";
			QString answer;

			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, title, message,
					QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes) {

#ifdef _WIN32
				ShellExecute(NULL, "open", "explorer.exe", ui.dirLabel->text().toStdString().c_str(), NULL, SW_SHOWNORMAL);
#endif // _WIN32
#ifdef __linux__
				std::string command = "nautilus " + ui.dirLabel->text().toStdString() + " &";
				int retVal = system(command.c_str());
#endif // __linux_
			} else if (reply == QMessageBox::No) {
				this->close();
				return;
			} else {
				LOG(ERR, "In void UpdatesChooser::checkRadioButtons() --> error");
			}
#endif // __APPLE__
		}
	}
	else if (updateDownloader.requestAborted()) {
		LOG(WARN,
				pResources->at(chosenUpdate)["file"]
				+ " download aborted.");

	} else {
		LOG(ERR,
				pResources->at(chosenUpdate)["file"]
				+ " download failed.");

	}

	this->close();
}

void UpdatesChooser::enableOkButton() {
	ui.okButton->setEnabled(true);
}

void UpdatesChooser::setExistingDirectory() {
	QFileDialog::Options options = QFileDialog::DontResolveSymlinks
			| QFileDialog::ShowDirsOnly;
	QString directory = QFileDialog::getExistingDirectory(this,
			tr("QFileDialog::getExistingDirectory()"), ui.dirLabel->text(),
			options);
	if (!directory.isEmpty())
		ui.dirLabel->setText(directory);
}
