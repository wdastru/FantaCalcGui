#include "UpdatesChooser.h"

UpdatesChooser::UpdatesChooser(QList<QHash<QString, QString> >& resources,
		QWidget *parent) :
		QDialog(parent) {
	ui.setupUi(this);

	chosenUpdate = -1;

	this->setWindowTitle("Scegli l'update che fa per te ...");

	for (int i = 0; i < resources.size(); ++i) {
		if (resources.at(i)["status"] == "new") {
			QLabel *label = new QLabel(
					resources.at(i)["file"] + " ("
							+ resources.at(i)["description"] + ")");
			labels.push_back(label);
			QRadioButton *radio = new QRadioButton();

			QObject::connect(radio, SIGNAL(toggled(bool)), this, SLOT(enableOkButton()));

			radioButtons.push_back(radio);

			ui.gridLayout->addWidget(radioButtons.at(i), i, 0);
			ui.gridLayout->addWidget(labels.at(i), i, 1);
		}
	}
}

UpdatesChooser::~UpdatesChooser() {

}

void UpdatesChooser::checkRadioButtons() {
	for (int i = 0; i < radioButtons.size(); ++i) {
		if (radioButtons.at(i)->isChecked()) {
			chosenUpdate = i;
		}
	}
	this->close();
}

int UpdatesChooser::getUpdate() {
	return chosenUpdate;
}

void UpdatesChooser::enableOkButton(){
	ui.okButton->setEnabled(true);
}
