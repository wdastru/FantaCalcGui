#include "cstdlib"
#include "string"
#include <fstream>

#include <QtGui/QtGui>
#include <QtGui/QApplication>

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
	singletonQtLogger::Inst()->setDebugStatus(TRUE);

	LOG(DEBUG, "In main(): Logger started.");

	LOG(
			DEBUG,
			"Contenuto iniFile (" + IniFileManager::Inst()->getIniFilePath()
					+ "):<br /><br />" + IniFileManager::Inst()->showIniFile());

	QDir qdir(IniFileManager::Inst()->getWorkDir());
	qdir.mkdir("formazioni");
	qdir.mkdir("download");
	qdir.mkdir("gazzetta");
	qdir.mkdir("risultati");
	qdir.mkdir("liste");

	UseTheNetDialog * useTheNetDialog = new UseTheNetDialog(THE_LOGGER);
	useTheNetDialog->setQuestion(
			"<span style='font-size:8pt; font-weight:600; color:#ff0000;'>Si vuole usare la rete per scaricare i files?</span><br /><br /><span style='font-size:8pt; font-weight:200; color:#000000;'>se s&iacute;, assicurarsi di essere connessi.</span>");
	do
		useTheNetDialog->exec();
	while (!useTheNetDialog->hasFinished);

	useTheNetDialog->close();

	QString fileGazzetta;
	QString fileFormazioni;

	ChooseFileFromAListDialog * chooseFileFromAListDialog = NULL;
	/*
	 *  --> Controllo dell'input dell'utente a UseTheNetDialog
	 */
	if (useTheNetDialog->getYesClicked()
			&& useTheNetDialog->getDownloadSuccess()) {
		/*
		 * --> Scegli, scarica i file dalla rete e crea file squadre
		 */
		chooseFileFromAListDialog = new ChooseFileFromAListDialog(
				IniFileManager::Inst()->getListaFormazioni(),
				IniFileManager::Inst()->getListaGazFiles(), THE_LOGGER);
		chooseFileFromAListDialog->exec();
		fileGazzetta = chooseFileFromAListDialog->getFileGazzetta();
		fileFormazioni = chooseFileFromAListDialog->getFileFormazioni();
		// <-- scegli e scarica i file dalla rete
	} else if (useTheNetDialog->getNoClicked()) {
		fileGazzetta = useTheNetDialog->getNoNetGazzettaFile();
		fileFormazioni = useTheNetDialog->getNoNetSquadreFile();
	} else if (useTheNetDialog->hasBeenAborted) {
		LOG(DEBUG, "In main --> useTheNetDialog aborted.");
	} else {
		LOG(FATAL, "In main --> Caso strano, che si f&aacute;?");
	}
	// <-- fine controllo dell'input dell'utente a UseTheNetDialog

	/*
	 * --> lettura file Gazzetta e Formazioni
	 */
	GazzettaFileReader * gazzettaFileReader = new GazzettaFileReader(
			fileGazzetta);
	//	std::vector<std::vector<std::string> > allThePlayers =
	//			gazzettaFileReader->getOutput();

	FormazioniFileReader * formazioniFileReader = new FormazioniFileReader(
			fileFormazioni);
	formazioniFileReader->setPlayers(gazzettaFileReader->getOutput());
	formazioniFileReader->execute();
	// <-- lettura file Gazzetta e Formazioni


	return a.exec();
}
