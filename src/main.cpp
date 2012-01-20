
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
	QString version = "v3.0.1";
	a.setOrganizationName("Eptadone Software");
	a.setApplicationName("FantaCalcGui");
	a.setApplicationVersion(version);

	THE_LOGGER->setVersion(version); // prima parte l'applicazione

	LOG(
			INFO,
			"Benvenuti in " + THE_LOGGER->getTitle() + " "
					+ THE_LOGGER->getVersion() + ".");

	THE_REPO; // poi si crea il repository dei dati
	THE_MANAGER; // quindi si legge l'ini file (o lo si crea se non esistente)
	THE_CONFIGURATOR; // infine il configuratore viene popolato con i dati

	return a.exec();
}
