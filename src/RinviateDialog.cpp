
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
	squadreSerieA[1] = "BOLOGNA";
	squadreSerieA[2] = "BRESCIA";
	squadreSerieA[3] = "CAGLIARI";
	squadreSerieA[4] = "FIORENTINA";
	squadreSerieA[5] = "GENOA";
	squadreSerieA[6] = "INTER";
	squadreSerieA[7] = "JUVENTUS";
	squadreSerieA[8] = "LAZIO";
	squadreSerieA[9] = "LECCE";
	squadreSerieA[10] = "MILAN";
	squadreSerieA[11] = "NAPOLI";
	squadreSerieA[12] = "PARMA";
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

	DEBUG("");

	bool enable = true;
	int i = 0;
	while (i < 20) {

		if (checkBox[i]->isChecked())
			enable = enable?false:true;

		++i;
	}

	if (enable) {
		DEBUG("enableOkButton abilitato");
		ui.okButton->setEnabled(true);
	} else {
		DEBUG("enableOkButton disabilitato");
		ui.okButton->setEnabled(false);
	}
}


void RinviateDialog::quit() {
	DEBUG("");
	this->close();
}
