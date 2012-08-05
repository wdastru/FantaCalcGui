#include "FileFormazioniReader.h"
#include "singletonQtLogger.h"
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtGui/QMessageBox>
#include <QtGui>
#include "Fanta.h"
#include "Repository.h"
#include "WhichOfLevenshteinDialog.h"
#include "WhichOfTheseDialog.h"

FileFormazioniReader::FileFormazioniReader(QString _fileFormazioni,
		QWidget *parent) :
		QDialog(parent) {
	this->fileFormazioni = _fileFormazioni;

	//QString a = "pippo";
	//QString b = "pluto";
	//QString c = "cicci";
    //
	//QStringList items;
    //
	//items.push_back(a);
	//items.push_back(b);
	//items.push_back(c);
    //
	//bool ok;
	//QString item = QInputDialog::getItem(this, tr("Scegli"),
	//		"Gugu non trovato. Giocatori con nome simile:", items, 0,
	//		false, &ok);
}
FileFormazioniReader::~FileFormazioniReader() {
}
void FileFormazioniReader::setPlayers(
		std::vector<std::vector<std::string> > _allThePlayers) {
	this->allThePlayers = _allThePlayers;
}
unsigned int FileFormazioniReader::execute() {

	LOG(DEBUG, "<br/> =============================");
	LOG(DEBUG,      " === Lettura file di input ===");
	LOG(DEBUG,      " =============================");
	//qDebug() << In FileFormazioniReader::execute().";

	std::ifstream fSqua(this->fileFormazioni.toStdString().c_str());
	if (!fSqua) {
		qDebug() << "In FileFormazioniReader::execute()  -> il file formazioni  : " + this->fileFormazioni + " non esiste o non e' leggibile!";
		LOG(FATAL, "Il file formazioni  : " + this->fileFormazioni + " non esiste o non e' leggibile!");
		return FORMFILEREAD_NO_FORM_FILE;
	} else {
		//qDebug() << "In FileFormazioniReader::execute()  -> file formazioni  : " + this->fileFormazioni;
	}

	std::string line;

	for (unsigned int k = 0; k < 2; k++) // k indice delle squadre
	{
		while (!fSqua.eof()) {
			bool gdv = false;
			bool gdp = false;

			getline(fSqua, line);

			if (line.size() == 0) // salta le righe nulle
			{
				continue;
			} else if (line.find("###***###", 0) != std::string::npos) { // separatore
				/*
				 *  ###***### serve per separare le due squadre nel file di input
				 *  se trovato passa alla prossima squadra o esce dal loop for
				 */
				//qDebug() << "In FileFormazioniReader::execute()  -> separatore : " + QString::fromStdString(line);

				LOG(DEBUG, "<br>    ---------------------------------");

				break;
			} else if (line.find("#", 0) != std::string::npos) {// # indica linee di commento
				//qDebug() << "In FileFormazioniReader::execute()  -> commento : " + QString::fromStdString(line);
				continue;
			} else if (line.find("nome squadra", 0) != std::string::npos) { // nome squadra
				/*
				 * lettura del nome della squadra a partire dalla fine di "nome squadra"
				 */
				line = line.substr(line.find("nome squadra") + 12);
				STR_MOD->onlyLettersAndNumbersBegin(line);
				STR_MOD->onlyLettersAndNumbersEnd(line);
				STR_MOD->removeNotAllowedChars(line);
				if (line.size() == 0)
					line = "Squadra" + my::toString<unsigned int>(k + 1);
				FANTA->setTeamName(line, k);

				//LOG(INFO, "<br/>&nbsp;&nbsp;==== "
				//				+ QString::fromStdString(FANTA->getTeamName(k)).toUpper()
				//				+ " ====<br/><br/>");

				LOG(DEBUG, "<br>    nome squadra : "
								+ QString::fromStdString(line));

				continue;
			} else if (line.find("modulo", 0) != std::string::npos) { // modulo
				LOG(DEBUG, \
						+ "    " \
						+ QString::fromStdString(line));

				unsigned int xx;
				xx = FANTA->setModulo(line, k);
				if (xx == EXIT_FAILURE) {
					LOG(
							ERROR,
							"In FileFormazioniReader::execute()  -> Modulo non consentito!<br/>Controllare il file di input."
									+ QString::fromStdString(
											FANTA->getModuloSquadra(k)));
					//goto restart;
				} else {
					continue;
				}
			} else if (line.find("in casa", 0) != std::string::npos) { // in casa
				FANTA->setAtHome(k);
				LOG(DEBUG, "    in casa");
				continue;
			} else { // riga "buona"
				//  -> sostituzione lettere accentate ed eliminazione caratteri "non-lettera"
				STR_MOD->modifyAccents(line);
				STR_MOD->onlyLettersBegin(line);
				STR_MOD->onlyLettersEnd(line);
				// <-- sostituzione lettere accentate ed eliminazione caratteri "non-lettera"
				STR_MOD->toUpperCase(line);

				if (line.size() <= 1) // evitare le righe con un solo carattere rimasto
					continue;

				size_t i = 0;
				while (STR_MOD->msk(line, " ", i) != "TnotF!") {
					i++;
				} // trova l'ultimo token
				i--;

				if (STR_MOD->msk(line, " ", i) == "GDV") {
					gdv = true;
					line.erase(line.size() - 4, 4);// toglie gdv
				} else if (STR_MOD->msk(line, " ", i) == "GDP") {
					gdp = true;
					line.erase(line.size() - 4, 4);// toglie gdp
				}

				/*
				 *  v_Found: vettore con tutti i giocatori trovati che contengono
				 *  il nome cercato es.: con Anto si trovano ANTONIOLI, ANTONINI, ...
				 */
				vector<string> v_Found;
				v_Found.clear();

				/*
				 *  v_WhichOfThese: vettore con tutte le corrispondenze
				 *  contenenti la string cercata.
				 *  es.: per ANTO si trovano ANTONIOLI, ANTONINI
				 */
				vector<string> v_WhichOfThese;
				v_WhichOfThese.clear();

				/*
				 *  v_WhichOfTheseLevenshtein: vettore contenente le possibili
				 *  corrispondenze nel caso la stringa cercata non sia stata
				 *  trovata.
				 */
				vector<string> v_WhichOfTheseLevenshtein;
				v_WhichOfTheseLevenshtein.clear();

				unsigned int xx = line[0]; // xx e' il valore ASCII della prima lettera del cognome
				for (unsigned int j = 0; j
						< this->allThePlayers[xx - 65].size(); j++) {
					string tempStrGazz = this->allThePlayers[xx - 65].at(j);

					// cerca nella riga della Gazzetta il nome del giocatore
					size_t found = STR_MOD->msk(tempStrGazz, DELIM,
							ColNomeCognome).find(line, 0);

					if (found != string::npos) { // se vero il giocatore e' stato trovato
						// aggiungi al vettore con tutti i giocatori trovati
						v_Found.push_back(this->allThePlayers[xx - 65].at(j));
					}
				}

				if (v_Found.size() > 1) {
					LOG(DEBUG, "<br>    " \
							+ QString::fromStdString(line) \
							+ " : trovate " \
							+ my::toQString<size_t>(v_Found.size()) \
							+ " corrispondenze");
					//qDebug() << "In FileFormazioniReader::execute()  -> " \
						+ QString::fromStdString(line) \
						+ " : v_Found.size = " \
						+ my::toQString<size_t>(v_Found.size());

					std::vector<std::string> temp;
					temp.clear();

					do { // while (v_Found.size() > 1)

						for (unsigned int j = 0; j < v_Found.size(); j++) {

							LOG(DEBUG, "      " \
									+ QString::fromStdString(this->prepareStringToPresent(v_Found.at(j), j)) \
									+ " : ");

							if (FANTA->LevenshteinDistance(
									line,
									STR_MOD->onlySurname(
											STR_MOD->msk(v_Found.at(j), DELIM,
													ColNomeCognome))) == 0) { // corrispondenza esatta
								LOG(DEBUG, "    Trovata corrispondenza esatta : " \
									+ QString::fromStdString(line));

								temp.push_back(v_Found.at(j)); // aggiungi corrispondenza esatta						}
							}
						}

						if (temp.size() > 1) { // piu' di una corrispondenza esatta (!!!)
							for (unsigned int j = 0; j < temp.size(); j++) {
								std::string tmpStr =
										this->prepareStringToPresent(
												temp.at(j), j);
								v_WhichOfThese.push_back(tmpStr);
							}

							WhichOfTheseDialog whichOfTheseDialog;
							whichOfTheseDialog.setListOfThese(v_WhichOfThese);
							whichOfTheseDialog.exec();

							v_Found.clear();
							v_Found.push_back(
									temp.at(whichOfTheseDialog.chosenThese - 1));

						} else if (temp.size() == 1) {
							//qDebug() << "In FileFormazioniReader::execute()  -> found : TRUE.";
							v_Found = temp;
						} else { // nessuna corrispondenza esatta

							for (unsigned int j = 0; j < v_Found.size(); j++) {
								std::string tmpStr =
										this->prepareStringToPresent(
												v_Found.at(j), j);
								v_WhichOfThese.push_back(tmpStr);
							}

							WhichOfTheseDialog whichOfTheseDialog;
							whichOfTheseDialog.setListOfThese(v_WhichOfThese);
							whichOfTheseDialog.exec();

							std::string temp = v_Found.at(
									whichOfTheseDialog.chosenThese - 1);
							v_Found.clear();
							v_Found.push_back(temp);

							LOG(INFO, "    scelto " \
								+ QString::fromStdString(STR_MOD->msk(v_Found.at(0), DELIM, ColNomeCognome)));
						}

					} while (v_Found.size() > 1);

				}

				if (v_Found.size() == 0) {
					/*
					 *  Non sono stati trovati giocatori che contengono
					 *  la string di ricerca.
					 *  Ora si prova a cercare delle corrispondenze con
					 *  la distanza di Levensthein
					 */

					vector<string> Levenshteins; // possibili giocatori
					Levenshteins = this->findLevenstheins(line);

					LOG(DEBUG, "");
					LOG(WARN, QObject::tr("    non trovato %1.").arg(QString::fromStdString(line)));

					if (Levenshteins.empty()) {
						LOG(ERROR,
								"ATTENZIONE !!! Nessun giocatore trovato.<br/>");
					} else {
						LOG(DEBUG, "    trovati " \
							+ my::toQString<signed int>(Levenshteins.size()) \
							+ " possibili sostituti:");

						for (unsigned int j = 0; j < Levenshteins.size(); j++) {
							std::string tmpStr = this->prepareStringToPresent(
									Levenshteins.at(j), j);
							v_WhichOfTheseLevenshtein.push_back(tmpStr);

							LOG(DEBUG, "      "\
								+ QString::fromStdString(tmpStr));
						}

						WhichOfLevenshteinDialog whichOfLevenshteinDialog;
						whichOfLevenshteinDialog.setPlayer(
								QString::fromStdString(line));
						whichOfLevenshteinDialog.setListOfLevenshtein(
								v_WhichOfTheseLevenshtein);
						whichOfLevenshteinDialog.exec();

						/*
						 * TODO
						 *
						 * usare QInputDialog::getItem(this, tr("Scegli"),
						 * this->player + " non trovato. Giocatori con nome simile:", items,
						 * 0, false, &ok); ?
						 *
						 * Eliminare WhichOfLevenshteinDialog?
						 * Si deve modificare FileFormazioniReader xche'
						 * QInputDialog::getItem(this, ... richiede this
						 * e FileFormazioniReader non e' un QWidget
						 *
						 * * * * * * * * * * * * * * * * * * * * * * */

						//code :

						//unsigned int chosenLevenshtein;
						//QStringList items;
						//for (size_t i = 0; i < v_WhichOfTheseLevenshtein.size(); i++) {
						//	items << tr(v_WhichOfTheseLevenshtein.at(i).c_str());
						//}
						//bool ok;
						//QString msg = QString::fromStdString(line) \
						//		+ " non trovato. Giocatori con nome simile:";
						//QString item = QInputDialog::getItem(this, tr("Scegli"),
						//			msg, items,
						//			0, false, &ok);
						//if (ok && !item.isEmpty()) {
						//	itemLabel->setText(item);
						//	std::ostringstream oss;
						//	oss << item.toAscii().constData();
						//	chosenLevenshtein = atoi(STR_MOD->msk(oss.str(), "[]", 0).c_str());
						//} else {
						//	/*
						//	 * TODO
						//	 * handle exception
						//	 * * * * * * * * * * */
						//}
                        //
						//v_Found.push_back(Levenshteins.at(chosenLevenshtein	- 1));


						v_Found.push_back(
								Levenshteins.at(
										whichOfLevenshteinDialog.chosenLevenshtein
										- 1));

						LOG(INFO, "    scelto "
								+ QString::fromStdString(STR_MOD->msk(v_Found.at(0), DELIM, ColNomeCognome)));

					}
				}

				if (v_Found.size() == 1) {

					/*
					 * riempi i dati mancanti (stringhe nulle) con '-'
					 *
					 * * * * * * * * * * * * * * * * */
					size_t i = 0;
					while (STR_MOD->msk(v_Found.at(0), DELIM, i) != "TnotF!") {
						i++;
					} // trova l'ultimo token
					i--;

					if (i < 14) { // non sono presenti tutti i dati (o meglio sono stringhe nulle)

						QString toAdd;
						for (unsigned int j = i; j<14; j++) {
							toAdd += "\t-";
						}
						toAdd += "\t";

						unsigned int index = QString::fromStdString(v_Found.at(0)).indexOf("\t\t");
						v_Found.at(0) = v_Found.at(0).substr(0, index) + toAdd.toStdString();
					}
					/* * * * * * * * * * * * * * * * */

					QMessageBox msgBox;
					msgBox.setStandardButtons(QMessageBox::Ok);
					msgBox.setDefaultButton(QMessageBox::Ok);
					msgBox.setIcon(QMessageBox::Information);
					msgBox.setFont(THE_REPO->fontVariableWidthSmall);
					msgBox.setWindowTitle("ATTENZIONE !!!");

					/*
					 *  aggiungo le due colonne mancanti
					 *  nel file della Gazzetta : GDV e GDP
					 *
					 * * * * * * * * * * * * * * * * * * * */
					if (gdv) {
						v_Found.at(0) += "1\t0";
					} else if (gdp) {
						v_Found.at(0) += "0\t1";
					} else {
						v_Found.at(0) += "0\t0";
					}

					//qDebug() << "In FileFormazioniReader::execute()  -> before switch : v_Found.at(0) = " \
									+ QString::fromStdString(v_Found.at(0)) \
									+ " (squadra " \
									+ my::toQString<unsigned int>(k) + ")";

					//qDebug() << "In FileFormazioniReader::execute()  -> FANTA->Team[" \
									+ my::toQString<unsigned int>(k) \
									+ "].size() = " \
									+ my::toQString<unsigned int>( \
											FANTA->Team[k].size());

					switch (FANTA->addPlayer(v_Found.at(0), k)) {
					case PLAYER_OK:

						LOG(DEBUG, ""); // blank line in log file only
						LOG(INFO, "    trovato " \
							+ QString::fromStdString(STR_MOD->msk(v_Found.at(0), DELIM,ColNomeCognome)) \
							+ " ( " \
							+ QString::fromStdString(STR_MOD->msk(v_Found.at(0), DELIM,ColSquadra)) \
							+ " ).");
						LOG(DEBUG, "      [" \
							+ QString::fromStdString(v_Found.at(0)).replace("\t", " ") \
							+ "]");

						if (STR_MOD->msk(v_Found.at(0), DELIM,ColGoalDecVitt) == "1") {
							LOG(DEBUG, "      - goal decisivo vittoria.");
						} else if (STR_MOD->msk(v_Found.at(0), DELIM,ColGoalDecPar) == "1") {
							LOG(DEBUG, "      - goal decisivo pareggio.");
						}

						break;

					case PLAYER_REPEATED:
						LOG(ERROR, \
							QObject::tr("<br>    ATTENZIONE !!!  -> %1 ( %2 ) ripetuto.<br/>    Controllare il file di input.").arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColNomeCognome))).arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColSquadra))).replace( \
								QString(" "), QString("&nbsp;")));

						msgBox.setInformativeText( \
								QObject::tr("%1 ( %2 ) ripetuto.<br>Controllare il file di input.").arg( \
									QString::fromStdString( \
											STR_MOD->msk(v_Found.at(0), \
													DELIM, ColNomeCognome))).arg( \
									QString::fromStdString( \
											STR_MOD->msk(v_Found.at(0), \
													DELIM, ColSquadra))).replace( \
									QString(" "), QString("&nbsp;")));
						msgBox.exec();

						return FORMFILEREAD_REPEATED;
						break;

					case PLAYER_GDV_NOT_PLAYED:
						LOG(ERROR, \
							QObject::tr("<br/>    ATTENZIONE !!!  -> %1 ( %2 ).<br/>    Giocatore indicato con GDV senza che abbia giocato !!!<br/>    Controllare il file di input.").arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColNomeCognome))).arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColSquadra))));

						msgBox.setInformativeText( \
								QObject::tr( \
										"%1 ( %2 )<br>Giocatore indicato con GDV senza che abbia giocato !!!<br>Controllare il file di input").arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColNomeCognome))).arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColSquadra))));
						msgBox.exec();

						return FORMFILEREAD_GDV_NOT_PLAYED;
						break;

					case PLAYER_GDP_NOT_PLAYED:
						LOG(ERROR, \
							QObject::tr("<br/>    ATTENZIONE !!!  -> %1 ( %2 ).<br/>    Giocatore indicato con GDP senza che abbia giocato !!!<br/>    Controllare il file di input.").arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColNomeCognome))).arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColSquadra))));

						msgBox.setInformativeText( \
								QObject::tr( \
										"%1 ( %2 )<br>Giocatore indicato con GDP senza che abbia giocato !!!<br>Controllare il file di input").arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColNomeCognome))).arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColSquadra))));
						msgBox.exec();

						return FORMFILEREAD_GDP_NOT_PLAYED;
						break;

					case PLAYER_GDV_NO_GOAL:
						LOG(ERROR, \
							QObject::tr("<br/>    ATTENZIONE !!!  -> %1 ( %2 ).<br/>    Giocatore indicato con GDV senza che abbia segnato !!!<br/>    Controllare il file di input.").arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColNomeCognome))).arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColSquadra))));

						msgBox.setInformativeText( \
								QObject::tr( \
										"%1 ( %2 )<br>Giocatore indicato con GDV senza che abbia segnato !!!<br>Controllare il file di input").arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColNomeCognome))).arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColSquadra))));
						msgBox.exec();

						return FORMFILEREAD_GDV_NO_GOAL;
						break;

					case PLAYER_GDP_NO_GOAL:
						LOG(ERROR, \
							QObject::tr("<br/>    ATTENZIONE !!!  -> %1 ( %2 ).<br/>    Giocatore indicato con GDP senza che abbia segnato !!!<br/>    Controllare il file di input.").arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColNomeCognome))).arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColSquadra))));

						msgBox.setInformativeText( \
								QObject::tr( \
										"%1 ( %2 )<br>Giocatore indicato con GDP senza che abbia segnato !!!<br>Controllare il file di input").arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColNomeCognome))).arg( \
										QString::fromStdString( \
												STR_MOD->msk(v_Found.at(0), \
														DELIM, ColSquadra))));
						msgBox.exec();

						return FORMFILEREAD_GDP_NO_GOAL;
						break;

					case PLAYER_ERROR:
						LOG(ERROR, \
								"<br>    ATTENZIONE !!!  -> PLAYER ERROR.<br/>    Controllare il file di input.");

						msgBox.setInformativeText( \
								QObject::tr( \
										"PLAYER ERROR<br>Controllare il file di input."));
						msgBox.exec();

						break;

					default:
						qDebug() << "In FileFormazioniReader::execute()  -> switch : default.";
						break;
					}

				}
			}
		}
	}
	return FORMFILEREAD_OK;
}
std::vector<std::string> FileFormazioniReader::findLevenstheins(
		std::string line) {
	/*
	 *  loop per cercare corrispondenze;
	 *  se non viene trovato nulla si ripete
	 *  con un valore di distance piu' grande
	 */

	std::vector<std::string> Levenshteins;

	for (unsigned int distance = 1;; distance++) { // loop infinito: fino a trovare qualcosa
		Levenshteins.clear();
		for (size_t ii = 0; ii < 26; ii++) { // giocatori della squadra
			for (size_t jj = 0; jj < this->allThePlayers[ii].size(); jj++) { // giocatori della Gazzetta
				if (STR_MOD->msk(this->allThePlayers[ii].at(jj), DELIM,
						ColNomeCognome) != "TnotF!") {

					if (FANTA->LevenshteinDistance(
							line,
							STR_MOD->onlySurname(
									STR_MOD->msk(
											this->allThePlayers[ii].at(jj),
											DELIM, ColNomeCognome)))
							<= distance) {
						Levenshteins.push_back(this->allThePlayers[ii].at(jj));
					}
				} else {
					LOG(
							ERROR,
							"In FileFormazioniReader::findLevenstheins(line)  -> il file della Gazzetta non sembra essere valido !");
					//return FORMFILEREAD_BAD_GAZ_FILE;
				}
			}
		}

		//qDebug() << "In FileFormazioniReader::findLevenstheins(line)  -> distance : " \
						+ my::toQString<signed int>(distance) \
						+ " - line size : " \
						+ my::toQString<size_t>(line.size()) + " - trovati : " \
						+ my::toQString<signed int>(Levenshteins.size());

		if (Levenshteins.size() <= 1) {
			continue;
		} else
			break;
	}

	return Levenshteins;
}
std::string FileFormazioniReader::prepareStringToPresent(std::string str,
		signed int j) {
	string tmpRuolo = STR_MOD->msk(str, DELIM, ColRuolo);
	if (tmpRuolo == "P")
		tmpRuolo = "Portiere";
	else if (tmpRuolo == "D")
		tmpRuolo = "Difensore";
	else if (tmpRuolo == "C")
		tmpRuolo = "Centrocampista";
	else if (tmpRuolo == "A")
		tmpRuolo = "Attaccante";

	string tmpStr = "";
	tmpStr += ('[' + my::toString<unsigned int>(j + 1) + ']');
	tmpStr += " ";
	tmpStr += STR_MOD->msk(str, DELIM, ColNomeCognome);
	tmpStr += " - ";
	tmpStr += tmpRuolo;
	tmpStr += " - ";
	tmpStr += STR_MOD->msk(str, DELIM, ColSquadra);

	return tmpStr;
}
void FileFormazioniReader::init() {
	;
}