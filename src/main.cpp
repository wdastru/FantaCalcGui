//#include "cstdlib"
//#include "string"
//#include <fstream>

//#include <QtGui/QtGui>
#include <QtGui/QApplication>
//#include <QtCore/QFileInfo>

#include "singletonQtLogger.h"
#include "Repository.h"
//#include "stringModifiers.h"
//#include "toString.h"

//#include "CVersion.h"
//#include "UseTheNetDialog.h"
#include "IniFilePopulator.h"
#include "IniFileManager.h"
//#include "ChooseFileFromAListDialog.h"
//#include "GazzettaFileReader.h"
//#include "FormazioniFileReader.h"
//#include "StringModifier.h"
#include "Fanta.h"
#include "defines.h"

using namespace std;

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);

	QString version = "3.1.0";

	a.setOrganizationName("Eptadone Software");
	a.setApplicationName("FantaCalcGui");
	a.setApplicationVersion(version);
//	a.setWindowIcon(QIcon)

	THE_LOGGER; // prima parte l'applicazione
	THE_LOGGER->setVersion(version);

	LOG(
			INFO,
			"Benvenuti in " + THE_LOGGER->getTitle() + " "
					+ THE_LOGGER->getVersion() + ".");

	THE_REPO; // poi si crea il repository dei dati
	THE_MANAGER; // quindi si legge l'ini file (o lo si crea se non esistente)
	THE_CONFIGURATOR; // infine il configuratore viene popolato con i dati

	return a.exec();
}
