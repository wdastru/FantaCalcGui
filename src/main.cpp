
#include <QtGui/QApplication>
#include <QtCore/QObject>
#include "singletonQtLogger.h"
#include "Repository.h"
#include "IniFilePopulator.h"
#include "IniFileManager.h"
#include "Fanta.h"
#include "defines.h"

using namespace std;

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);
	a.setOrganizationName("Eptadone Software");
	a.setApplicationName("FantaCalcGui");
	a.setApplicationVersion("3.2.1");

	THE_REPO; // prima si crea il repository dei dati
	THE_MANAGER; // quindi si legge l'ini file (o lo si crea se non esistente)

	THE_LOGGER; // poi parte l'applicazione
	THE_LOGGER->setVersion(a.applicationVersion());
	THE_LOGGER->setTitle(a.applicationName());

	LOG(INFO,
			QObject::tr("<br>Benvenuti in %1 v%2<br>").arg(
					THE_LOGGER->getTitle()).arg(THE_LOGGER->getVersion()));

	THE_LOGGER->checkForUpdates();

	THE_CONFIGURATOR; // infine il configuratore viene popolato con i dati

	return a.exec();
}
