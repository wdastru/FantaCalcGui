#include "Less25MinDialog.h"
#include "Repository.h"
#include "defines.h"

using namespace std;

Less25MinDialog::Less25MinDialog(QWidget *parent) :
	QDialog(parent) {

	this->setFont(THE_REPO->fontVariableWidthSmall);

	int frameStyle = QFrame::Sunken | QFrame::Panel;

	questionLabel = new QLabel;
	questionLabel->setFrameStyle(frameStyle);
	questionButton = new QPushButton(tr("Ha giocato almeno 25' ?"));

	okButton = new QPushButton(tr("&Ok"));
	okButton->setDefault(true);
	okButton->setEnabled(false);

	/*
	 buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
	 buttonBox->setEnabled(false);
	 */

	connect(questionButton, SIGNAL(clicked()), this, SLOT(questionMessage()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	//connect(buttonBox, SIGNAL(rejected()), this, SLOT(exit()));

	QGridLayout *layout = new QGridLayout;
	layout->setColumnStretch(1, 1);
	layout->setColumnMinimumWidth(1, 300);
	layout->addWidget(questionButton, 0, 0);
	layout->addWidget(questionLabel, 0, 1);
	layout->addWidget(okButton, 1, 0);
	setLayout(layout);

	setWindowTitle(tr("Giocatore sceso in campo ma senza voto"));
}
void Less25MinDialog::enableOkButton() {
	if (!this->questionLabel->text().isEmpty())
		this->okButton->setEnabled(true);
}
void Less25MinDialog::closeEvent(QCloseEvent *event) {
	event->ignore();
}
void Less25MinDialog::questionMessage() {

	QMessageBox msgBox;
	msgBox.setWindowTitle("Ha giocato almeno 25' ?");
	msgBox.setInformativeText(Less25MinDialog::Message.c_str());
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setFont(THE_REPO->fontVariableWidthSmall);
	int reply = msgBox.exec();

	//	QMessageBox::StandardButton reply;
//	reply = QMessageBox::question(this, tr("Ha giocato almeno 25' ?"),
//			tr(Less25MinDialog::Message.c_str()),
//			QMessageBox::Yes | QMessageBox::No);

	std::string tmp;

	switch (reply) {
	   case QMessageBox::Yes:
		   tmp = Less25MinDialog::player + " ha giocato più di 25'";
		   		questionLabel->setText(tr(tmp.c_str()));
		   		questionLabel->setStyleSheet("font: 10pt 'Candara';");
		   		Less25MinDialog::answer = "Yes";
	       break;
	   case QMessageBox::No:
		   tmp = Less25MinDialog::player
		   				+ " non ha giocato più di 25'";
		   		questionLabel->setText(tr(tmp.c_str()));
		   		questionLabel->setStyleSheet("font: 10pt 'Candara';");
		   		Less25MinDialog::answer = "No";
	       break;
	   default:
	       // should never be reached
	       break;
	 }


	//	if (reply == QMessageBox::Yes) {
	//		std::string tmp = Less25MinDialog::player + " ha giocato più di 25'";
	//		questionLabel->setText(tr(tmp.c_str()));
	//		questionLabel->setStyleSheet("font: 10pt 'Candara';");
	//		Less25MinDialog::answer = "Yes";
	//	} else if (reply == QMessageBox::No) {
	//		std::string tmp = Less25MinDialog::player
	//				+ " non ha giocato più di 25'";
	//		questionLabel->setText(tr(tmp.c_str()));
	//		questionLabel->setStyleSheet("font: 10pt 'Candara';");
	//		Less25MinDialog::answer = "No";
	//	}

	this->enableOkButton();
}
void Less25MinDialog::setPlayer(std::string player) {
	Less25MinDialog::player = player;
	Less25MinDialog::Message
			= "Il giocatore \n\n" + player
					+ " \n\nha giocato, ma non e\' stato giudicato. \nHa giocato piu\' di 25\' ?";
}
std::string Less25MinDialog::getAnswer() {
	return Less25MinDialog::answer;
}
void Less25MinDialog::exit() {
	exit();
}
