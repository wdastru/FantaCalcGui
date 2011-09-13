#include "IniFilePopulator.h"

IniFilePopulator::IniFilePopulator(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);
}

IniFilePopulator::~IniFilePopulator() {

}

void IniFilePopulator::getDir() {

	LOG(DEBUG, "In IniFilePopulator::getDir()");

	QFileDialog::Options options = QFileDialog::DontResolveSymlinks
			| QFileDialog::ShowDirsOnly;
	options |= QFileDialog::DontUseNativeDialog;

	QString directory = QFileDialog::getExistingDirectory(this,
			"QFileDialog::getExistingDirectory()", ui.formazioniLineEdit->text(),
			options);

	if (!directory.isEmpty())
		this->ui.formazioniLineEdit->setText(directory);
}

