#include "cstdlib"
#include "string"
#include <fstream>

#include <QtGui/QtGui>
#include <QtGui/QApplication>
#include <QtCore/QFileInfo>

#include "singletonQtLogger.h"
#include "defines.h"
#include "stringModifiers.h"
#include "toString.h"

#include "CVersion.h"
#include "UseTheNetDialog.h"
#include "IniFileManager.h"
#include "ChooseFileFromAListDialog.h"
#include "GazzettaFileReader.h"
#include "FormazioniFileReader.h"
#include "StringModifier.h"
#include "Fanta.h"

using namespace std;

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	CVersion version;
	QString loggerTitle = "FantaCalcGui v" + version.getVersion();

	singletonQtLogger::Inst()->setTitle(loggerTitle);
	singletonQtLogger::Inst()->setDebugStatus(
			IniFileManager::Inst()->getDebugStatus());

	LOG(DEBUG, "In main() -> Logger started.");

	LOG(
			DEBUG,
			"In main() -> contenuto iniFile ("
					+ IniFileManager::Inst()->getIniFilePath() + "):<br />"
					+ IniFileManager::Inst()->showIniFile());

	UseTheNetDialog * useTheNetDialog = new UseTheNetDialog(THE_LOGGER);
	useTheNetDialog->setQuestion(
			"<span style='font-size:8pt; font-weight:600; color:#ff0000;'>Si vuole usare la rete per scaricare i files?</span><br /><br /><span style='font-size:8pt; font-weight:200; color:#000000;'>se s&iacute;, assicurarsi di essere connessi.</span>");
	do
		useTheNetDialog->exec();
	while (!useTheNetDialog->hasFinished);

	useTheNetDialog->close();

	if (!useTheNetDialog->hasBeenAborted) {
		QString fileGazzetta;
		QString fileFormazioni;

		ChooseFileFromAListDialog * chooseFileFromAListDialog = NULL;
		/*
		 *  --> Controllo dell'input dell'utente a UseTheNetDialog
		 */
		if (useTheNetDialog->getYesClicked()) {
			if (useTheNetDialog->getDownloadSuccess()) {
				/*
				 * --> Scegli, scarica i file dalla rete e crea file squadre
				 */
				chooseFileFromAListDialog = new ChooseFileFromAListDialog(
						IniFileManager::Inst()->getListaFormazioni(),
						IniFileManager::Inst()->getListaGazFiles(), THE_LOGGER);
				chooseFileFromAListDialog->exec();
				fileGazzetta = chooseFileFromAListDialog->getFileGazzetta();
				fileFormazioni = chooseFileFromAListDialog->getFileFormazioni();
				// <-- Scegli e scarica i file dalla rete e crea file squadre
			} else {
				LOG(FATAL, "In main() --> the net was used but the download failed.");
				return EXIT_FAILURE;
			}
		} else if (useTheNetDialog->getNoClicked()) {
			fileGazzetta = useTheNetDialog->getNoNetGazzettaFile();
			fileFormazioni = useTheNetDialog->getNoNetSquadreFile();
		} else if (useTheNetDialog->hasBeenAborted) {
			LOG(DEBUG, "In main() --> useTheNetDialog aborted.");
		} else {
			LOG(FATAL, "In main() --> Caso strano, che si fa?");
		}
		// <-- fine controllo dell'input dell'utente a UseTheNetDialog

		/*
		 * --> lettura file Gazzetta e Formazioni
		 */
		GazzettaFileReader * gazzettaFileReader = new GazzettaFileReader(
				fileGazzetta);

		FormazioniFileReader * formazioniFileReader = new FormazioniFileReader(
				fileFormazioni);
		formazioniFileReader->setPlayers(gazzettaFileReader->getOutput());
		formazioniFileReader->execute();
				// <-- lettura file Gazzetta e Formazioni
		//		FANTA->execute();
		//
		//		QString match = IniFileManager::Inst()->getRisultatiPath()
		//				+ "risultato_" + QString::fromStdString(FANTA->getTeamName(0))
		//				+ "-" + QString::fromStdString(FANTA->getTeamName(1)) + "_"
		//				+ QFileInfo(FANTA->getFileGazzetta()).fileName();
		//
		//		FANTA->printTitolo(
		//				FANTA->getTeamName(0) + " - " + FANTA->getTeamName(1));
		//		FANTA->printRiepilogo();
		//		FANTA->printFormations();

		//		singletonQtLogger::Inst()->setLogFileName(match);
	} else
		return a.exec();
}
