/*
 * FormazioniFileReader.cpp
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "singletonQtLogger.h"
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include "FormazioniFileReader.h"
#include "Fanta.h"

FormazioniFileReader::FormazioniFileReader(QString _fileFormazioni) {
	this->fileFormazioni = _fileFormazioni;
}
FormazioniFileReader::~FormazioniFileReader() {
}
void FormazioniFileReader::setPlayers(
		std::vector<std::vector<std::string> > _allThePlayers) {
	this->allThePlayers = _allThePlayers;
}
unsigned int FormazioniFileReader::execute() {
	//qDebug() << In FormazioniFileReader::execute().";

	std::ifstream fSqua(this->fileFormazioni.toStdString().c_str());
	if (!fSqua) {
		qDebug() << "In FormazioniFileReader::execute()  -> il file formazioni  : " + this->fileFormazioni + " non esiste o non e' leggibile!";
		LOG(FATAL, "Il file formazioni  : " + this->fileFormazioni + " non esiste o non e' leggibile!");
		return FORMFILEREAD_NO_FORM_FILE;
	} else {
		//qDebug() << "In FormazioniFileReader::execute()  -> file formazioni  : " + this->fileFormazioni;
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
				//qDebug() << "In FormazioniFileReader::execute()  -> separatore : " + QString::fromStdString(line);
				break;
			} else if (line.find("#", 0) != std::string::npos) {// # indica linee di commento
				//qDebug() << "In FormazioniFileReader::execute()  -> commento : " + QString::fromStdString(line);
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

				LOG(INFO, "<br/>&nbsp;&nbsp;==== "
								+ QString::fromStdString(FANTA->getTeamName(k)).toUpper()
								+ " ====<br/><br/>");

				LOG(DEBUG, "nome squadra : "
								+ QString::fromStdString(line));

				continue;
			} else if (line.find("modulo", 0) != std::string::npos) { // modulo
				LOG(DEBUG, QString::fromStdString(line));

				unsigned int xx;
				xx = FANTA->setModulo(line, k);
				if (xx == EXIT_FAILURE) {
					LOG(
							ERROR,
							"In FormazioniFileReader::execute()  -> Modulo non consentito!<br/>Controllare il file di input."
									+ QString::fromStdString(
											FANTA->getModuloSquadra(k)));
					//goto restart;
				} else {
					continue;
				}
			} else if (line.find("in casa", 0) != std::string::npos) { // in casa
				FANTA->setAtHome(k);
				LOG(DEBUG, "In casa");
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
					LOG(DEBUG, QString::fromStdString(line) + " : trovate " + my::toQString<size_t>(v_Found.size()) + " corrispondenze");
					//qDebug() << "In FormazioniFileReader::execute()  -> " \
						+ QString::fromStdString(line) \
						+ " : v_Found.size = " \
						+ my::toQString<size_t>(v_Found.size());

					std::vector<std::string> temp;
					temp.clear();

					do { // while (v_Found.size() > 1)

						for (unsigned int j = 0; j < v_Found.size(); j++) {

							LOG(DEBUG, QString::fromStdString(this->prepareStringToPresent(v_Found.at(j), j)) \
								+ " : ");

							if (FANTA->LevenshteinDistance(
									line,
									STR_MOD->onlySurname(
											STR_MOD->msk(v_Found.at(j), DELIM,
													ColNomeCognome))) == 0) { // corrispondenza esatta
								LOG(DEBUG, "Trovata corrispondenza esatta : " \
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
							//qDebug() << "In FormazioniFileReader::execute()  -> found : TRUE.";
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
					LOG(WARN, QObject::tr(" -> non trovato %1.").arg(QString::fromStdString(line)));

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

						v_Found.push_back(
								Levenshteins.at(
										whichOfLevenshteinDialog.chosenLevenshtein
												- 1));

						LOG(DEBUG, ""); // blank line in log file only
						LOG(INFO, "    scelto " \
							+ QString::fromStdString(STR_MOD->msk(v_Found.at(0), DELIM,ColNomeCognome)));
					}
				}

				if (v_Found.size() == 1) {
					/*
					 *  aggiungo le due colonne mancanti
					 *  nel file della Gazzetta : GDV e GDP
					 */
					if (gdv) {
						v_Found.at(0) += "1\t0";
					} else if (gdp) {
						v_Found.at(0) += "0\t1";
					} else {
						v_Found.at(0) += "0\t0";
					}

					//qDebug() << "In FormazioniFileReader::execute()  -> before switch : v_Found.at(0) = " \
									+ QString::fromStdString(v_Found.at(0)) \
									+ " (squadra " \
									+ my::toQString<unsigned int>(k) + ")";

					//qDebug() << "In FormazioniFileReader::execute()  -> FANTA->Team[" \
									+ my::toQString<unsigned int>(k) \
									+ "].size() = " \
									+ my::toQString<unsigned int>( \
											FANTA->Team[k].size());

					switch (FANTA->addPlayer(v_Found.at(0), k)) {
					case PLAYER_OK:

						LOG(DEBUG, ""); // blank line in log file only
						LOG(INFO, " -> trovato " \
							+ QString::fromStdString(STR_MOD->msk(v_Found.at(0), DELIM,ColNomeCognome)) \
							+ " ( " \
							+ QString::fromStdString(STR_MOD->msk(v_Found.at(0), DELIM,ColSquadra)) \
							+ " ).");
						LOG(DEBUG, "    [" \
							+ QString::fromStdString(v_Found.at(0)).replace("\t", " ") \
							+ "]");

						if (STR_MOD->msk(v_Found.at(0), DELIM,ColGoalDecVitt) == "1") {
							LOG(DEBUG, "    goal decisivo vittoria.");
						} else if (STR_MOD->msk(v_Found.at(0), DELIM,ColGoalDecPar) == "1") {
							LOG(DEBUG, "    goal decisivo pareggio.");
						}

						break;

					case PLAYER_REPEATED:
						LOG(ERROR, \
							QObject::tr("ATTENZIONE !!!  -> %1 ( %2 ) ripetuto.<br/>Controllare il file di input.").arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColNomeCognome))).arg( \
								QString::fromStdString( \
										STR_MOD->msk(v_Found.at(0), \
												DELIM, ColSquadra))).replace( \
								QString(" "), QString("&nbsp;")));

						return FORMFILEREAD_REPEATED;
						break;

					case PLAYER_GDV_NO_GOAL:
						LOG(ERROR,
							QObject::tr("ATTENZIONE !!!  -> %1 ( %2 ).<br/>Giocatore indicato con GDV senza che abbia segnato !!!<br/>Controllare il file di input.").arg(
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(0),
												DELIM, ColNomeCognome))).arg(
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(0),
												DELIM, ColSquadra))));

						return FORMFILEREAD_GDV_NO_GOAL;
						break;

					case PLAYER_GDP_NO_GOAL:
						LOG(ERROR,
							QObject::tr("ATTENZIONE !!!  -> %1 ( %2 ).<br/>Giocatore indicato con GDP senza che abbia segnato !!!<br/>Controllare il file di input.").arg(
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(0),
												DELIM, ColNomeCognome))).arg(
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(0),
												DELIM, ColSquadra))));

						return FORMFILEREAD_GDP_NO_GOAL;
						break;

					case PLAYER_ERROR:
						LOG(ERROR,
								"ATTENZIONE !!!  -> PLAYER ERROR.<br/>Controllare il file di input.");
						break;

					default:
						qDebug() << "In FormazioniFileReader::execute()  -> switch : default.";
						break;
					}

				}
			}
		}
	}
	return FORMFILEREAD_OK;
}
std::vector<std::string> FormazioniFileReader::findLevenstheins(
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
							"In FormazioniFileReader::findLevenstheins(line)  -> il file della Gazzetta non sembra essere valido !");
					//return FORMFILEREAD_BAD_GAZ_FILE;
				}
			}
		}

		//qDebug() << "In FormazioniFileReader::findLevenstheins(line)  -> distance : " \
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
std::string FormazioniFileReader::prepareStringToPresent(std::string str,
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
void FormazioniFileReader::init() {
	;
}
