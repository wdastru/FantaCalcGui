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
	singletonQtLogger::Inst()->setDebugStatus(IniFileManager::Inst()->getDebugStatus());

	LOG(DEBUG, "In main(): Logger started.<br/>");

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
		// <-- Scegli e scarica i file dalla rete e crea file squadre
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

	FANTA->execute();

	std::string riepilogo = "RIEPILOGO";
	QString match = IniFileManager::Inst()->getRisultatiPath() + "risultato_"
			+ QString::fromStdString(FANTA->getTeamName(0)) + "-"
			+ QString::fromStdString(FANTA->getTeamName(1)) + "_" + QFileInfo(
			FANTA->getFileGazzetta()).fileName();

	singletonQtLogger::Inst()->setLogFileName(match);
	singletonQtLogger::Inst()->saveLogFile();

	 	/*
		string fileOut = "tmp";
		fOut.open( fileOut.c_str() );

		printTitolo2_toFile( match, fOut );
		Fanta->printRiepilogo_toFile( fOut );

		Fanta->printFormationPor2Att_toFile( 0, fOut );
		fOut << endl;
		Fanta->printFormationAtt2Por_toFile( 1, fOut );
		fOut << endl;

		for (unsigned int k = 0; k < 2; k++)
		{
			printTitolo2_toFile( Fanta->getTeamName( k ), fOut );
			Fanta->printPlayersInfo_toFile( k, fOut );
		}

		fOut.close();

		// concatenate tmp and tmp2 in tmp3
		ifstream in1("tmp", ios::in | ios::binary);
		if(!in1)
		{
			cout << "Cannot open tmp.\n";
			remove("tmp");
			remove("tmp2");
			remove("tmp3");
			return EXIT_FAILURE;
		}
		ifstream in2("tmp2", ios::in | ios::binary);
		if(!in2)
		{
			cout << "Cannot open tmp2.\n";
			remove("tmp");
			remove("tmp2");
			remove("tmp3");
			return EXIT_FAILURE;
		}
		ofstream out("tmp3", ios::out | ios::binary);
		if(!out)
		{
			cout << "can't open tmp3";
			remove("tmp");
			remove("tmp2");
			remove("tmp3");
			return EXIT_FAILURE;
		}

		out << in1.rdbuf();
		out << endl << flush;
		out << in2.rdbuf();
		out << endl << " File prodotto con FantaCalcGui.exe " << ver.getVersion() << endl;

		in1.close();
		in2.close();
		out.close();

		OutputFileDialog outputFileDialog;
		outputFileDialog.init("tmp3", fileDialog.getFileNameOutputPath());
		outputFileDialog.setTitle("Risultato");
		outputFileDialog.setFileName("risultato_" + \
				QString::fromStdString(Fanta->getTeamName(0)) + \
				"-" + \
				QString::fromStdString(Fanta->getTeamName(1)));
		outputFileDialog.exec();

		remove("tmp");
		remove("tmp2");
		remove("tmp3");
		*/

	return a.exec();
}
