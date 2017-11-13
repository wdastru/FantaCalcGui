
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
RinviateDialog::RinviateDialog(QWidget *parent) :
	QDialog(parent) {
	ui.setupUi(this);
	this->setWindowTitle("FantaCalcGui - Rinviate");
}
RinviateDialog::~RinviateDialog() {

}
void RinviateDialog::enableOkButton() {



	ui.okButton->setEnabled(true);
	ui.okButton->setEnabled(false);

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
