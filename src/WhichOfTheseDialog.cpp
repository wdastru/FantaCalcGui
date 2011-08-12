#include <QtGui>

#include "WhichOfTheseDialog.h"
#include "toString.h"
#include "StringModifier.h"
#include "defines.h"
#include <sstream>

using namespace std;

extern std::string msk (std::string, std::string, size_t);

WhichOfTheseDialog::WhichOfTheseDialog(QWidget *parent)
        : QDialog(parent)
{
    int frameStyle = QFrame::Sunken | QFrame::Panel;

    itemLabel = new QLabel;
    itemLabel->setFrameStyle(frameStyle);

    QPushButton *itemButton = new QPushButton(tr("Quale di questi ?"));

    okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    okButton->setEnabled(false);

    abortButton = new QPushButton(tr("&Quit"));
    abortButton->setCheckable(true);
    abortButton->setAutoDefault(false);
    abortButton->setEnabled(false);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(abortButton, QDialogButtonBox::RejectRole);

    connect(itemButton, SIGNAL(clicked()), this, SLOT(setItem()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(exit()));

    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 300);
    layout->addWidget(itemButton, 0, 0);
    layout->addWidget(itemLabel, 0, 1);
    layout->addWidget(buttonBox, 1, 0);
    setLayout(layout);

    setWindowTitle(tr("Più giocatori trovati !"));
}
void WhichOfTheseDialog::enableOkButton()
{
    if (!WhichOfTheseDialog::itemLabel->text().isEmpty())
        WhichOfTheseDialog::okButton->setEnabled(true);
}
void WhichOfTheseDialog::enableQuitButton()
{
    if (!WhichOfTheseDialog::itemLabel->text().isEmpty())
        WhichOfTheseDialog::abortButton->setEnabled(true);
}
void WhichOfTheseDialog::setItem()
{
    WhichOfTheseDialog::chosenThese = -1;

    QStringList items;

    for (size_t i = 0; i < WhichOfTheseDialog::ListOfThese.size(); i++)
        items << tr( WhichOfTheseDialog::ListOfThese.at( i ).c_str() );

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Scegli"),
                                         tr("Quale di questi?"), items, 0, false, &ok);

    if (ok && !item.isEmpty())
    {
        std::ostringstream oss;
        oss << item.toAscii().constData();
        itemLabel->setText(item);
        this->chosenThese = atoi(STR_MOD->msk( oss.str(), "[]", 0 ).c_str() );
        this->enableOkButton();
        this->enableQuitButton();
    }
}
void WhichOfTheseDialog::exit()
{
    exit();
}
void WhichOfTheseDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
void WhichOfTheseDialog::setListOfThese( std::vector < std::string > list)
{
    WhichOfTheseDialog::ListOfThese = list;
}
