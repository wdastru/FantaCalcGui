#include "UpdatesChooser.h"
#include "Downloader.h"
#include "defines.h"

#include "QtGui/QFileDialog"
#include "QtCore/QDebug"
#include "QtCore/QUrl"

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

			QObject::connect(radio, SIGNAL(toggled(bool)), this,
					SLOT(enableOkButton()));

			radioButtons.push_back(radio);

			ui.gridLayout->addWidget(radioButtons.at(i), i, 0);
			ui.gridLayout->addWidget(labels.at(i), i, 1);
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
	} else if (updateDownloader.requestAborted()) {
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
