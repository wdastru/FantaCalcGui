/*
 * FormazioniFileReader.cpp
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "FormazioniFileReader.h"

FormazioniFileReader::FormazioniFileReader(QString _fileFormazioni) {
	this->fileFormazioni = _fileFormazioni;
}
FormazioniFileReader::~FormazioniFileReader() {
	// TODO Auto-generated destructor stub
}
void FormazioniFileReader::setPlayers(
		std::vector<std::vector<std::string> > & _allThePlayers) {
	this->allThePlayers = _allThePlayers;
}
unsigned int FormazioniFileReader::execute() {
	std::ifstream fSqua(this->fileFormazioni.toStdString().c_str());
	if (!fSqua) {
		LOG(
				FATAL,
				"In FormazioniFileReader::execute() --> il file gazzetta  : "
						+ this->fileFormazioni + " non esiste!");
	}

	std::string line;

	// --> lettura file Squadre
	for (unsigned int k = 0; k < 2; k++) // k indice delle squadre
	{
		while (!fSqua.eof()) {
			bool gdv = false;
			bool gdp = false;

			getline(fSqua, line);

			if (line.size() == 0) // salta le righe nulle
			{
				continue;
			} else if (line.find("###***###", 0) != std::string::npos) {
				/*
				 *  ###***### serve per separare le due squadre nel file di input
				 *  se trovato passa alla prossima squadra o esce dal loop for
				 */

				LOG(
						DEBUG,
						"In FormazioniFileReader::execute() --> separatore : "
								+ QString::fromStdString(line));
				break;
			} else if (line.find("#", 0) != std::string::npos) {
				// # indica linee di commento
				LOG(
						DEBUG,
						"In FormazioniFileReader::execute() --> commento : "
								+ QString::fromStdString(line));
				continue;
			} else if (line.find("nome squadra", 0) != std::string::npos) {
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
			} else if (line.find("modulo", 0) != std::string::npos) {
				LOG(
						DEBUG,
						"In FormazioniFileReader::execute() --> "
								+ QString::fromStdString(line));

				unsigned int xx;
				xx = FANTA->setModulo(line, k);
				if (xx == EXIT_FAILURE) {
					LOG(
							ERROR,
							"Modulo non consentito!<br>Controllare il file di input."
									+ QString::fromStdString(
											FANTA->getModuloSquadra(k)));
					//goto restart;
				} else {
					continue;
				}
			} else if (line.find("in casa", 0) != std::string::npos) {
				FANTA->setAtHome(k);
				LOG(DEBUG, "In FormazioniFileReader::execute() --> in casa");
				continue;
			} else {
				// --> sostituzione ����� ed eliminazione caratteri "non-lettera"
				STR_MOD->modifyAccents(line);
				STR_MOD->onlyLettersBegin(line);
				STR_MOD->onlyLettersEnd(line);
				// <-- sostituzione ����� ed eliminazione caratteri "non-lettera"
				STR_MOD->toUpperCase(line);

				if (line.size() <= 1) // evitare le righe con un solo carattere rimasto
					continue;

				//				LOG(
				//						DEBUG,
				//						"In FormazioniFileReader::execute() --> "
				//								+ QString::fromStdString(
				//										STR_MOD->leftString(line, 15)));

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

				vector<string> v_Found; // vettore con tutti i giocatori trovati che contengono il nome cercato
				v_Found.clear(); // es.: con Toni si trovano TONI, ANTONIOLI, ...

				vector<string> v_WhichOfThese;
				vector<string> v_WhichOfTheseLevenshtein;
				v_WhichOfThese.clear();
				v_WhichOfTheseLevenshtein.clear();

				unsigned int xx = line[0]; // xx e' il valore ASCII della prima lettera del cognome
				for (unsigned int j = 0; j
						< this->allThePlayers[xx - 65].size(); j++) {
					string tempStrGazz = this->allThePlayers[xx - 65].at(j);

					size_t found = STR_MOD->msk(tempStrGazz, DELIM,
							ColNomeCognome).find(line, 0);
					// cerca nella riga della Gazzetta il nome del giocatore

					if (found != string::npos) // se vero il giocatore e' stato trovato
						v_Found.push_back(this->allThePlayers[xx - 65].at(j)); // aggiungi al vettore con tutti i giocatori trovati
				}

				unsigned int answer = 0;
				bool wasALeven = false;
				bool wasAThese = false;

				if (v_Found.size() > 1) {
					wasAThese = true;
					for (unsigned int j = 0; j < v_Found.size(); j++) {
						string tmpRuolo = STR_MOD->msk(v_Found.at(j), DELIM,
								ColRuolo);
						if (tmpRuolo == "P")
							tmpRuolo = "Portiere";
						else if (tmpRuolo == "D")
							tmpRuolo = "Difensore";
						else if (tmpRuolo == "C")
							tmpRuolo = "Centrocampista";
						else if (tmpRuolo == "A")
							tmpRuolo = "Attaccante";

						string tmpStr = "";
						tmpStr += ('[' + my::toString<unsigned int>(j + 1)
								+ ']');
						tmpStr += " ";
						tmpStr += STR_MOD->msk(v_Found.at(j), DELIM,
								ColNomeCognome);
						tmpStr += " - ";
						tmpStr += tmpRuolo;
						tmpStr += " - ";
						tmpStr
								+= STR_MOD->msk(v_Found.at(j), DELIM,
										ColSquadra);

						v_WhichOfThese.push_back(tmpStr);
					}

					WhichOfTheseDialog whichOfTheseDialog;
					whichOfTheseDialog.setListOfThese(v_WhichOfThese);
					whichOfTheseDialog.exec();

					answer = whichOfTheseDialog.chosenThese;
					answer--;
				} else if (v_Found.size() == 0) {
					wasALeven = true;
					vector<string> Levenshteins; // possibili giocatori
					Levenshteins.clear();

					for (size_t ii = 0; ii < 26; ii++) {
						for (size_t jj = 0; jj < this->allThePlayers[ii].size(); jj++) {
							// Threshold
							if (STR_MOD->msk(this->allThePlayers[ii].at(jj),
									DELIM, ColNomeCognome) != "TnotF!") {
								if (FANTA->LevenshteinDistance(
										line,
										STR_MOD->onlySurname(
												STR_MOD->msk(
														this->allThePlayers[ii].at(
																jj), DELIM,
														ColNomeCognome))) < 3)
									Levenshteins.push_back(
											this->allThePlayers[ii].at(jj));
							} else {
								LOG(
										ERROR,
										"Il file della Gazzetta non sembra essere valido !<br/>Controllare il file di input.");
								return FORMFILEREAD_BAD_GAZ_FILE;
							}
						}
					}

					if (Levenshteins.size() == 0) {
						LOG(
								ERROR,
								QString::fromStdString(line)
										+ "<br>Giocatore non trovato!<br>Controllare il file di input.");
						//goto restart;
					}

					for (unsigned int j = 0; j < Levenshteins.size(); j++) {
						string tmpRuolo = STR_MOD->msk(Levenshteins.at(j),
								DELIM, ColRuolo);
						if (tmpRuolo == "P")
							tmpRuolo = "Portiere";
						else if (tmpRuolo == "D")
							tmpRuolo = "Difensore";
						else if (tmpRuolo == "C")
							tmpRuolo = "Centrocampista";
						else if (tmpRuolo == "A")
							tmpRuolo = "Attaccante";

						string tmpStr = "";
						tmpStr += ('[' + my::toString<unsigned int>(j + 1)
								+ ']');
						tmpStr += " ";
						tmpStr += STR_MOD->msk(Levenshteins.at(j), DELIM,
								ColNomeCognome);
						tmpStr += " - ";
						tmpStr += tmpRuolo;
						tmpStr += " - ";
						tmpStr += STR_MOD->msk(Levenshteins.at(j), DELIM,
								ColSquadra);

						v_WhichOfTheseLevenshtein.push_back(tmpStr);
					}

					WhichOfLevenshteinDialog whichOfLevenshteinDialog;
					whichOfLevenshteinDialog.setListOfLevenshtein(
							v_WhichOfTheseLevenshtein);
					whichOfLevenshteinDialog.exec();

					v_Found.push_back(
							Levenshteins.at(
									whichOfLevenshteinDialog.chosenLevenshtein
											- 1));
				}

				if (line.size() > 1) // se rimane solo un carattere "non-lettera" va avanti senza aggiungere nulla
				{
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

					switch (FANTA->addPlayer(v_Found.at(answer), k)) {
					case 0:
						break;

					case 1:
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
						return FORMFILEREAD_REPEATED;
						break;

					case 2:
						LOG(
								ERROR,
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(answer), DELIM,
												ColNomeCognome)) + " ( "
										+ QString::fromStdString(
												STR_MOD->msk(
														v_Found.at(answer),
														DELIM, ColSquadra))
										+ "<br>Giocatore indicato con goal decisivo vittoria senza che abbia segnato !!!<br/>Controllare il file di input.");
						return FORMFILEREAD_GDV_NO_GOAL;
						break;

					case 3:
						LOG(
								ERROR,
								QString::fromStdString(
										STR_MOD->msk(v_Found.at(answer), DELIM,
												ColNomeCognome)) + " ( "
										+ QString::fromStdString(
												STR_MOD->msk(
														v_Found.at(answer),
														DELIM, ColSquadra))
										+ "<br>Giocatore indicato con goal decisivo pareggio senza che abbia segnato !!!<br/>Controllare il file di input.<br>");
						return FORMFILEREAD_GDP_NO_GOAL;
						break;

					default:
						break;
					}

					//					if (wasAThese || wasALeven) {
					//						LOG(
					//								DEBUG,
					//								"In FormazioniFileReader::execute() --> "
					//										+ QString::fromStdString(
					//												STR_MOD->msk(
					//														v_Found.at(answer),
					//														DELIM, ColNomeCognome))
					//										+ " ( " + QString::fromStdString(
					//										STR_MOD->msk(v_Found.at(answer), DELIM,
					//												ColSquadra)) + " ) trovato.");
					//					} else {
					//						LOG(
					//								DEBUG,
					//								"In FormazioniFileReader::execute() --> "
					//										+ QString::fromStdString(line)
					//										+ " trovato.");
					//					}
					LOG(
							DEBUG,
							"In FormazioniFileReader::execute() --> "
									+ QString::fromStdString(
											STR_MOD->msk(v_Found.at(answer),
													DELIM, ColNomeCognome))
									+ " ( " + QString::fromStdString(
									STR_MOD->msk(v_Found.at(answer), DELIM,
											ColSquadra)) + " ) trovato.");

				} else {
					;
				}
			}
		}
	}
	// <-- lettura file Squadre
	return FORMFILEREAD_OK;
}
//void FormazioniFileReader::printTitolo2(std::string str) {
//	QString tmp = "";
//	LOG(TOFILE, "\n +");
//	for (unsigned int i = 0; i < str.size() + 6; i++) {
//		tmp += "-";
//	}
//	LOG(TOFILE, tmp + "+\n" + " | +");
//
//	tmp = "";
//	for (unsigned int i = 0; i < str.size() + 2; i++) {
//		tmp += "-";
//	}
//	LOG(TOFILE, tmp + "+ |\n");
//
//	LOG(TOFILE, " | | " + QString::fromStdString(str) + " | |\n");
//
//	LOG(TOFILE, " | +");
//	for (unsigned int i = 0; i < str.size() + 2; i++)
//		LOG(TOFILE, "-");
//	LOG(TOFILE, "+ |\n");
//
//	LOG(TOFILE, " +");
//	for (unsigned int i = 0; i < str.size() + 6; i++)
//		LOG(TOFILE, "-");
//	LOG(TOFILE, "+\n\n");
//}
//void FormazioniFileReader::printTitolo3(std::string str) {
//	LOG(TOFILE, "\n!!!! " + QString::fromStdString(str) + " !!!!\n");
//}
