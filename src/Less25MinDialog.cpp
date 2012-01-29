#include <QtGui/QMessageBox>
#include <QtGui/QGridLayout>
#include <QtGui/QCloseEvent>

#include "singletonQtLogger.h"
#include "Less25MinDialog.h"
#include "Repository.h"
#include "defines.h"

using namespace std;

Less25MinDialog::Less25MinDialog(QWidget *parent) :
	QDialog(parent) {

	LOG(DEBUG, "In Less25MinDialog::Less25MinDialog(...).");

	this->setFont(THE_REPO->fontVariableWidthSmall);

	int frameStyle = QFrame::Sunken | QFrame::Panel;

	questionLabel = new QLabel;
	questionLabel->setFrameStyle(frameStyle);
	questionButton = new QPushButton(tr("Ha giocato almeno 25' ?"));

	okButton = new QPushButton(tr("&Ok"));
	okButton->setDefault(true);
	okButton->setEnabled(false);

	connect(questionButton, SIGNAL(clicked()), this, SLOT(questionMessage()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(quit()));

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
//void Less25MinDialog::closeEvent(QCloseEvent *event) {
//	event->ignore();
//}
void Less25MinDialog::questionMessage() {

	LOG(DEBUG, "In Less25MinDialog::questionMessage().");

	QMessageBox msgBox;
	msgBox.setWindowTitle("Ha giocato almeno 25' ?");
	msgBox.setInformativeText(Less25MinDialog::Message.c_str());
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setFont(THE_REPO->fontVariableWidthSmall);

	std::string tmp;

	switch (msgBox.exec()) {
	case QMessageBox::Yes:
		LOG(DEBUG, "In Less25MinDialog::questionMessage() --> case Yes.");
		tmp = this->player + " ha giocato più di 25'";
		this->questionLabel->setText(tr(tmp.c_str()));
		this->questionLabel->setFont(THE_REPO->fontVariableWidthSmall);
		this->answer = "Yes";
		break;
	case QMessageBox::No:
		LOG(DEBUG, "In Less25MinDialog::questionMessage() --> case No.");
		tmp = this->player + " non ha giocato più di 25'";
		this->questionLabel->setText(tr(tmp.c_str()));
		this->questionLabel->setFont(THE_REPO->fontVariableWidthSmall);
		this->answer = "No";
		break;
	default:
		// should never be reached
		LOG(ERROR, "In Less25MinDialog::questionMessage() --> case Default.");
		break;
	}

	this->enableOkButton();
}
void Less25MinDialog::setPlayer(std::string _player) {

	LOG(
			DEBUG,
			"In Less25MinDialog::setPlayer(...) --> player : "
					+ QString::fromStdString(_player));

	this->player = _player;
	this->Message
			= "Il giocatore \n\n" + this->player
					+ " \n\nha giocato, ma non e\' stato giudicato. \nHa giocato piu\' di 25\' ?";
}
std::string Less25MinDialog::getAnswer() {

	LOG(
			DEBUG,
			"In Less25MinDialog::getAnswer() --> player : "
					+ QString::fromStdString(this->player));

	return this->answer;
}
void Less25MinDialog::quit() {
	LOG(DEBUG, "In Less25MinDialog::quit().");

	try {
		this->close();
	} catch (...) {
		LOG(FATAL, "In Less25MinDialog::quit() --> exception caught in close()!");
	}

}
