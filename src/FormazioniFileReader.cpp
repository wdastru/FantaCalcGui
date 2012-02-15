/*
 * FormazioniFileReader.cpp
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "singletonQtLogger.h"
#include <QDebug>
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
	LOG(DEBUG, "In FormazioniFileReader::execute().");

	std::ifstream fSqua(this->fileFormazioni.toStdString().c_str());
	if (!fSqua) {
		LOG(
				FATAL,
				"In FormazioniFileReader::execute() --> il file formazioni  : "
						+ this->fileFormazioni
						+ " non esiste o non и leggibile!");
		return FORMFILEREAD_NO_FORM_FILE;
	} else {
		LOG(
				DEBUG,
				"In FormazioniFileReader::execute() --> file formazioni  : "
						+ this->fileFormazioni);
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

				LOG(
						DEBUG,
						"In FormazioniFileReader::execute() --> separatore : "
								+ QString::fromStdString(line));
				break;
			} else if (line.find("#", 0) != std::string::npos) {// # indica linee di commento
				LOG(
						DEBUG,
						"In FormazioniFileReader::execute() --> commento : "
								+ QString::fromStdString(line));
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

				LOG(
						DEBUG,
						"In FormazioniFileReader::execute() --> nome squadra : "
								+ QString::fromStdString(line));

				continue;
			} else if (line.find("modulo", 0) != std::string::npos) { // modulo
				LOG(
						DEBUG,
						"In FormazioniFileReader::execute() --> "
								+ QString::fromStdString(line));

				unsigned int xx;
				xx = FANTA->setModulo(line, k);
				if (xx == EXIT_FAILURE) {
					LOG(
							ERROR,
							"In FormazioniFileReader::execute() --> Modulo non consentito!<br>Controllare il file di input."
									+ QString::fromStdString(
											FANTA->getModuloSquadra(k)));
					//goto restart;
				} else {
					continue;
				}
			} else if (line.find("in casa", 0) != std::string::npos) { // in casa
				FANTA->setAtHome(k);
				LOG(DEBUG, "In FormazioniFileReader::execute() --> in casa");
				continue;
			} else { // riga "buona"
				// --> sostituzione тащим ed eliminazione caratteri "non-lettera"
				STR_MOD->modifyAccents(line);
				STR_MOD->onlyLettersBegin(line);
				STR_MOD->onlyLettersEnd(line);
				// <-- sostituzione тащим ed eliminazione caratteri "non-lettera"
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

				if (v_Found.size() != 1) {
					LOG(
							DEBUG,
							"In FormazioniFileReader::execute() --> "
									+ QString::fromStdString(line)
									+ " : v_Found.size = " + my::toQString<
									size_t>(v_Found.size()));
				}

				unsigned int answer = 0;
				bool found = FALSE;

				if (v_Found.size() > 1) {

					for (unsigned int j = 0; j < v_Found.size(); j++) {

						std::string temp = v_Found.at(j);

						LOG(
								DEBUG,
								"In FormazioniFileReader::execute() --> "
										+ QString::fromStdString(
												this->prepareStringToPresent(
														v_Found.at(j), j)));

						if (FANTA->LevenshteinDistance(
								line,
								STR_MOD->onlySurname(
										STR_MOD->msk(v_Found.at(j), DELIM,
												ColNomeCognome))) == 0) { // corrispondenza esatta
							LOG(
									DEBUG,
									"In FormazioniFileReader::execute() --> trovata corrispondenza esatta : "
											+ QString::fromStdString(line));
							found = TRUE;
							//answer = j;

							v_Found.clear();
							v_Found.push_back(temp); // adesso v_Found.size() vale 1
						}
					}

					if (!found) {
						for (unsigned int j = 0; j < v_Found.size(); j++) {
							std::string tmpStr = this->prepareStringToPresent(
									v_Found.at(j), j);
							v_WhichOfThese.push_back(tmpStr);
						}

						WhichOfTheseDialog whichOfTheseDialog;
						whichOfTheseDialog.setListOfThese(v_WhichOfThese);
						whichOfTheseDialog.exec();

						answer = whichOfTheseDialog.chosenThese;
						answer--;
					} else {
						LOG(DEBUG,
								"In FormazioniFileReader::execute() --> found : TRUE. ");
					}

				}

				if (v_Found.size() == 0) {
					/*
					 *  Non sono stati trovati giocatori che contengono
					 *  la string di ricerca.
					 *  Ora si prova a cercare delle corrispondenze con
					 *  la distanza di Levensthein
					 */LOG(
							DEBUG,
							"In FormazioniFileReader::execute() --> giocatore non trovato : "
									+ QString::fromStdString(line));

					vector<string> Levenshteins; // possibili giocatori
					Levenshteins = this->findLevenstheins(line);

					if (Levenshteins.empty()) {
						LOG(
								ERROR,
								"In FormazioniFileReader::execute() --> "
										+ QString::fromStdString(line)
										+ " : nessun giocatore trovato.<br/>");
					} else {
						LOG(
								DEBUG,
								"In FormazioniFileReader::execute() --> trovati "
										+ my::toQString<signed int>(
												Levenshteins.size())
										+ " possibili sostituti.");

						for (unsigned int j = 0; j < Levenshteins.size(); j++) {
							std::string tmpStr = this->prepareStringToPresent(
									Levenshteins.at(j), j);
							v_WhichOfTheseLevenshtein.push_back(tmpStr);

							LOG(
									DEBUG,
									"In FormazioniFileReader::execute() --> "
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
					}
				}

				if (v_Found.size() == 1) {
					/*
					 *  aggiungo le due colonne mancanti
					 *  nel file della Gazzetta : GDV e GDP
					 */
					if (gdv) {
						v_Found.at(answer) += "\t1\t0";
					} else if (gdp) {
						v_Found.at(answer) += "\t0\t1";
					} else {
						v_Found.at(answer) += "\t0\t0";
					}

					LOG(
							DEBUG,
							"In FormazioniFileReader::execute() --> before switch : v_Found.at("
									+ my::toQString<unsigned int>(answer)
									+ ") = " + QString::fromStdString(
									v_Found.at(answer)) + " (squadra "
									+ my::toQString<unsigned int>(k) + ")");

					/**/

					LOG(
							DEBUG,
							"In FormazioniFileReader::execute() --> FANTA->Team["
									+ my::toQString<unsigned int>(k)
									+ "].size() = "
									+ my::toQString<unsigned int>(
											FANTA->Team[k].size()));

					switch (FANTA->addPlayer(v_Found.at(answer), k)) {
					case 0:
						LOG(
								DEBUG,
								"In FormazioniFileReader::execute() --> switch : FANTA->addPlayer( ... ) returned PLAYER_OK.");
						break;

					case 1:
						LOG(
								DEBUG,
								"In FormazioniFileReader::execute() --> switch : FANTA->addPlayer( ... ) returned PLAYER_REPEATED.");
						LOG(
								ERROR,
								"In FormazioniFileReader::execute() --> "
										+ QString::fromStdString(
												STR_MOD->msk(
														v_Found.at(answer),
														DELIM, ColNomeCognome))
										+ " ( " + QString::fromStdString(
										STR_MOD->msk(v_Found.at(answer), DELIM,
												ColSquadra))
										+ ") ripetuto !!! Controllare il file di input.");

						//						throw(QString::fromStdString(
						//								STR_MOD->msk(v_Found.at(answer), DELIM,
						//										ColNomeCognome)));

						return FORMFILEREAD_REPEATED;
						break;

					case 2:
						LOG(
								DEBUG,
								"In FormazioniFileReader::execute() --> switch : FANTA->addPlayer( ... ) returned PLAYER_GDV_NO_GOAL.");
						LOG(
								ERROR,
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(answer), DELIM,
												ColNomeCognome)) + " ( "
										+ QString::fromStdString(
												STR_MOD->msk(
														v_Found.at(answer),
														DELIM, ColSquadra))
										+ " )<br>Giocatore indicato con goal decisivo vittoria senza che abbia segnato !!! Controllare il file di input.");
						return FORMFILEREAD_GDV_NO_GOAL;
						break;

					case 3:
						LOG(
								DEBUG,
								"In FormazioniFileReader::execute() --> switch : FANTA->addPlayer( ... ) returned PLAYER_GDP_NO_GOAL.");
						LOG(
								ERROR,
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(answer), DELIM,
												ColNomeCognome)) + " ( "
										+ QString::fromStdString(
												STR_MOD->msk(
														v_Found.at(answer),
														DELIM, ColSquadra))
										+ " )<br>Giocatore indicato con goal decisivo pareggio senza che abbia segnato !!! Controllare il file di input.");
						return FORMFILEREAD_GDP_NO_GOAL;
						break;

					case 99:
						LOG(
								ERROR,
								"In FormazioniFileReader::execute() --> switch : FANTA->addPlayer( ... ) returned PLAYER_ERROR.");
						break;

					default:
						LOG(ERROR,
								"In FormazioniFileReader::execute() --> switch : default.");
						break;
					}

					LOG(
							DEBUG,
							"In FormazioniFileReader::execute() --> "
									+ QString::fromStdString(
											STR_MOD->msk(v_Found.at(answer),
													DELIM, ColNomeCognome))
									+ " ( " + QString::fromStdString(
									STR_MOD->msk(v_Found.at(answer), DELIM,
											ColSquadra)) + " ) trovato.");

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
							"In FormazioniFileReader::findLevenstheins(line) --> il file della Gazzetta non sembra essere valido !");
					//return FORMFILEREAD_BAD_GAZ_FILE;
				}
			}
		}

		LOG(
				DEBUG,
				"In FormazioniFileReader::findLevenstheins(line) --> distance : "
						+ my::toQString<signed int>(distance)
						+ " - line size : "
						+ my::toQString<size_t>(line.size()) + " - trovati : "
						+ my::toQString<signed int>(Levenshteins.size()));

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
