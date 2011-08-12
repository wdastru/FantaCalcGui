#include <QtGui>

#include "WhichOfLevenshteinDialog.h"
#include <sstream>

//extern std::string msk (std::string, std::string, size_t);

WhichOfLevenshteinDialog::WhichOfLevenshteinDialog(QWidget *parent)
        : QDialog(parent)
{
    int frameStyle = QFrame::Sunken | QFrame::Panel;

    itemLabel = new QLabel;
    itemLabel->setFrameStyle(frameStyle);
    QPushButton *itemButton = new QPushButton(tr("Possibili sostituti"));

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

    setWindowTitle(tr("Nessun giocatore trovato !"));
}
void WhichOfLevenshteinDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
void WhichOfLevenshteinDialog::setItem()
{
    QStringList items;

    for (size_t i = 0; i < WhichOfLevenshteinDialog::ListOfLevenshtein.size(); i++)
        items << tr( WhichOfLevenshteinDialog::ListOfLevenshtein.at( i ).c_str() );

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Scegli"),
                                         tr("Quale di questi?"), items, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        itemLabel->setText(item);
        std::ostringstream oss;
        oss << item.toAscii().constData();
        this->chosenLevenshtein = atoi( msk( oss.str(), "[]", 0 ).c_str() );
        this->enableOkButton();
        this->enableQuitButton();
    }
}
void WhichOfLevenshteinDialog::enableOkButton()
{
    if (!this->itemLabel->text().isEmpty())
        this->okButton->setEnabled(true);
}
void WhichOfLevenshteinDialog::enableQuitButton()
{
    if (!this->itemLabel->text().isEmpty())
        this->abortButton->setEnabled(true);
}
void WhichOfLevenshteinDialog::exit()
{
    remove("tmp");
    remove("tmp2");
    remove("tmp3");
    exit();
}
void WhichOfLevenshteinDialog::setListOfLevenshtein( std::vector < std::string > list)
{
    WhichOfLevenshteinDialog::ListOfLevenshtein = list;
}
