#include <QtGui/QApplication>

#include "singletonQtLogger.h"
#include "Repository.h"

#include "IniFilePopulator.h"
#include "IniFileManager.h"

#include "Fanta.h"
#include "defines.h"

using namespace std;

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QString version = "3.1.0";
	a.setOrganizationName("Eptadone Software");
	a.setApplicationName("FantaCalcGui");
	a.setApplicationVersion(version);

	THE_MANAGER; // lettura dell'ini file (o lo si crea se non esistente)
	THE_LOGGER->setVersion(version); // prima parte l'applicazione

	LOG(
			INFO,
			"Benvenuti in " + THE_LOGGER->getTitle() + " v"
					+ THE_LOGGER->getVersion() + ".");

	THE_LOGGER->checkForUpdates();

	THE_REPO; // repository dei dati
	THE_CONFIGURATOR; // il configuratore viene popolato con i dati

	return a.exec();
}
