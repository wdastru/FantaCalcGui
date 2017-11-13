
#define DO_DEBUG

#include "RinviateDialog.h"
#include "defines.h"

#include <QtCore/QDebug>

RinviateDialog* RinviateDialog::pInstance = NULL;

RinviateDialog* RinviateDialog::Inst() {
	if (pInstance == NULL) {
		pInstance = new RinviateDialog();
	}
	return pInstance;
}

std::vector<std::string> RinviateDialog::partiteRinviate() {

	std::vector<std::string> squadreRinviate;
	int i = 0;
	while (i < 20) {

		if (checkBox[i]->isChecked()) {
			squadreRinviate.push_back(checkBox[i]->text().toStdString());
		}

		++i;
	}

	return squadreRinviate;
}

RinviateDialog::RinviateDialog(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);

	std::string squadreSerieA[20];
	squadreSerieA[0] = "ATALANTA";
	squadreSerieA[1] = "BENEVENTO";
	squadreSerieA[2] = "BOLOGNA";
	squadreSerieA[3] = "CAGLIARI";
	squadreSerieA[4] = "CHIEVO";
	squadreSerieA[5] = "CROTONE";
	squadreSerieA[6] = "FIORENTINA";
	squadreSerieA[7] = "GENOA";
	squadreSerieA[8] = "INTER";
	squadreSerieA[9] = "JUVENTUS";
	squadreSerieA[10] = "LAZIO";
	squadreSerieA[11] = "MILAN";
	squadreSerieA[12] = "NAPOLI";
	squadreSerieA[13] = "ROMA";
	squadreSerieA[14] = "SAMPDORIA";
	squadreSerieA[15] = "SASSUOLO";
	squadreSerieA[16] = "SPAL";
	squadreSerieA[17] = "TORINO";
	squadreSerieA[18] = "UDINESE";
	squadreSerieA[19] = "VERONA";

	int i = 0;
	while (i < 20) {
		checkBox[i] = new QCheckBox();
		checkBox[i]->setText(
					QApplication::translate("RinviateDialogClass", squadreSerieA[i].c_str(), 0,
							QApplication::UnicodeUTF8));

		QObject::connect(checkBox[i], SIGNAL(toggled(bool)), this, SLOT(enableOkButton()));

		//DEBUG("i: " << i << " int(i / 4): " << int(i / 4));
		//DEBUG("i: " << i << " (i % 4)   : " << (i % 4));

		ui.gridLayout->addWidget(checkBox[i], int(i / 4), (i % 4));
		++i;
	}

	this->setWindowTitle("FantaCalcGui - Rinviate");
}
RinviateDialog::~RinviateDialog() {

}
void RinviateDialog::enableOkButton() {

	int i = 0;
	while (i < 20) {

		if (checkBox[i]->isChecked()) {
			if (ui.okButton->isEnabled()) {
				ui.okButton->setEnabled(false);
			} else {
				ui.okButton->setEnabled(true);
			}
		}

		++i;
	}

	if (ui.okButton->isEnabled()) {
		DEBUG("enableOkButton abilitato");
	} else {
		DEBUG("enableOkButton disabilitato");
	}
}


void RinviateDialog::quit() {
	DEBUG("");
	this->close();
}
