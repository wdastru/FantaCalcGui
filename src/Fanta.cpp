/*
 * Fanta.cpp
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#define DO_DEBUG

#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include <QtCore/QObject>

#include "Fanta.h"
#include "defines.h"
#include "singletonQtLogger.h"
#include "StringModifier.h"
#include "Repository.h"

Fanta * Fanta::Inst() {
	if (pInstance == NULL) {
		pInstance = new Fanta();
	}
	return pInstance;
}
Fanta * Fanta::Refresh() {
	if (pInstance != NULL)
		delete pInstance;

	return pInstance = new Fanta();
}

Fanta * Fanta::pInstance = NULL;

Fanta::Fanta() {
	this->initialize();
}
Fanta::~Fanta() {
}
void Fanta::initialize() {

	DEBUG("");

	for (size_t k = 0; k < 2; k++) {
		for (size_t j = 0; j < 4; j++) {
			Fanta::modulo[k][j] = 0;
			Fanta::inCampo[k][j] = 0;
		}

		Fanta::modulo[k][0] = 1;
		Fanta::atHome[k] = 0;
		Fanta::Total[k] = 0.0;
		Fanta::modifier[k] = 0;
		Fanta::defenseMean[k] = 0.0;
		Fanta::defenders[k] = 0;
		Fanta::sfide[k] = 0;
		Fanta::goals[k] = 0;
		Fanta::sostituzioni[k] = 0;
		Fanta::Team[k].clear();
	}

	Fanta::longerNameLength = 0;

	Fanta::NonHaGiocato.Cognome = "---";
	Fanta::NonHaGiocato.Cognome_Sost = "---";
	Fanta::NonHaGiocato.Squadra = "---";
	Fanta::NonHaGiocato.Squadra_Sost = "---";
	Fanta::NonHaGiocato.Ruolo = -1;
	Fanta::NonHaGiocato.VotoGazzetta = 0.0;
	Fanta::NonHaGiocato.FantaVotoGazzetta = 3.0;
	Fanta::NonHaGiocato.FantaVoto = 3.0;
	Fanta::NonHaGiocato.GoalFatti = 0.0;
	Fanta::NonHaGiocato.Autoreti = -0.0;
	Fanta::NonHaGiocato.GoalSubiti = 0.0;
	Fanta::NonHaGiocato.GoalDecVitt = 0;
	Fanta::NonHaGiocato.GoalDecPar = 0;
	Fanta::NonHaGiocato.Assist = 0;
	Fanta::NonHaGiocato.Amm = -0;
	Fanta::NonHaGiocato.Esp = -0;
	Fanta::NonHaGiocato.daSostituire = 0;
	Fanta::NonHaGiocato.RigoreParato = 0;
	Fanta::NonHaGiocato.RigoreSbagliato = 0;

	Fanta::fakePlayer.Cognome = "fake";
	Fanta::fakePlayer.Cognome_Sost = "---";
	Fanta::fakePlayer.Squadra = "---";
	Fanta::fakePlayer.Squadra_Sost = "---";
	Fanta::fakePlayer.Ruolo = -1;
	Fanta::fakePlayer.VotoGazzetta = 0.0;
	Fanta::fakePlayer.FantaVotoGazzetta = 3.0;
	Fanta::fakePlayer.FantaVoto = 3.0;
	Fanta::fakePlayer.GoalFatti = 0.0;
	Fanta::fakePlayer.Autoreti = -0.0;
	Fanta::fakePlayer.GoalSubiti = 0.0;
	Fanta::fakePlayer.GoalDecVitt = 0;
	Fanta::fakePlayer.GoalDecPar = 0;
	Fanta::fakePlayer.Assist = 0;
	Fanta::fakePlayer.Amm = 0;
	Fanta::fakePlayer.Esp = 0;
	Fanta::fakePlayer.daSostituire = 0;
	Fanta::fakePlayer.RigoreParato = 0;
	Fanta::fakePlayer.RigoreSbagliato = 0;

	for (int j = 0; j < 4; j++) {
		Fanta::modifierValues[0][j] = j + 1;
	}

	for (size_t i = 1; i < 5; i++) {
		for (size_t j = 0; j < 4; j++) {
			Fanta::modifierValues[i][j] = std::max(
					Fanta::modifierValues[i - 1][j] - 1, 0);
		}
	}

	for (size_t i = 5; i < 9; i++) {
		for (size_t j = 0; j < 4; j++) {
			Fanta::modifierValues[i][j] = -1 * Fanta::modifierValues[8 - i][j];
		}
	}

	for (size_t i = 1; i < 9; i++) {
		Fanta::modifierVoti[i] = 5.0f + 0.25f * (i - 1);
		Fanta::modifierValues[i][4] = Fanta::modifierValues[i][3];
	}

	Fanta::modifierVoti[0] = 0.0;
	Fanta::modifierVoti[9] = 10.0;

}
void Fanta::setTeamName(const std::string str, unsigned int k) {
	if (this->teamName.size() < 2) {
		this->teamName.push_back(str);
		this->longerNameLength = std::max(this->longerNameLength, str.size());
	} else {
		LOG(
				WARN,
				"Tentativo di aggiungere piu' di due nomi di squadra in setTeamName(const std::string str, unsigned int k)");
		DEBUG("Tried to add more than 2 team names!");
		exit(1);
	}
}
std::string Fanta::getTeamName(unsigned int i) {
	return this->teamName.at(i);
}
unsigned int Fanta::setModulo(std::string & str, size_t k) {
	unsigned int xx = 0;

	for (size_t i = 1; i < 4; i++) {
		this->modulo[k][i] = atoi(STR_MOD->STR_MOD->msk(str, " :-", i).c_str()); // lettura del modulo di gioco
		xx += this->modulo[k][i];
	}

	if (xx != 10 || this->modulo[k][1] < 3 || this->modulo[k][1] > 5
			|| this->modulo[k][2] < 3 || this->modulo[k][2] > 5
			|| this->modulo[k][3] < 1 || this->modulo[k][3] > 3)
		return EXIT_FAILURE;

	else
		return EXIT_SUCCESS;
}
std::string Fanta::getModuloSquadra(size_t k) const {
	return my::toString(this->getModulo(k, 1)) + " - " + my::toString(
			this->getModulo(k, 2)) + " - "
			+ my::toString(this->getModulo(k, 3));
}
unsigned int Fanta::getModulo(size_t k, size_t i) const {
	return this->modulo[k][i];
}
void Fanta::setAtHome(unsigned int k) {
	this->atHome[k] = 2;
}
unsigned int Fanta::addPlayer(std::string & str, unsigned int k) {
	try {
		DEBUG("str : " << str.c_str());

		Fanta::player tmpPlayer;

		DEBUG("ColCognome            : " << STR_MOD->msk(str, DELIM, ColCognome).c_str());
//		DEBUG("ColNome_Sost          : " << STR_MOD->msk(str, DELIM, ColCognome_Sost).c_str());
		DEBUG("ColSquadra            : " << STR_MOD->msk(str, DELIM, ColSquadra).c_str());
//		DEBUG("ColSquadra_Sost       : " << STR_MOD->msk(str, DELIM, ColSquadra_Sost).c_str());
		DEBUG("ColRuolo              : " << STR_MOD->msk(str, DELIM, ColRuolo).c_str());
		DEBUG("ColRuolo2             : " << STR_MOD->msk(str, DELIM, ColRuolo2).c_str());
//		DEBUG("ColFantaVoto          : " << STR_MOD->msk(str, DELIM, ColFantaVoto).c_str());
		DEBUG("ColFantaVotoGazzetta  : " << STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta).c_str());
		DEBUG("ColVotoGazzetta       : " << STR_MOD->msk(str, DELIM, ColVotoGazzetta).c_str());
		DEBUG("ColGoalFatti          : " << STR_MOD->msk(str, DELIM, ColGoalFatti).c_str());
		DEBUG("ColGoalSubiti         : " << STR_MOD->msk(str, DELIM, ColGoalSubiti).c_str());
		DEBUG("ColAutoreti           : " << STR_MOD->msk(str, DELIM, ColAutoreti).c_str());
//		DEBUG("ColRigoreParato       : " << STR_MOD->msk(str, DELIM, ColRigoreParato).c_str());
//		DEBUG("ColRigoreSbagliato    : " << STR_MOD->msk(str, DELIM, ColRigoreSbagliato).c_str());
		DEBUG("ColGoalDecVitt        : " << STR_MOD->msk(str, DELIM, ColGoalDecVitt).c_str());
		DEBUG("ColGoalDecPar         : " << STR_MOD->msk(str, DELIM, ColGoalDecPar).c_str());
		DEBUG("ColAssist             : " << STR_MOD->msk(str, DELIM, ColAssist).c_str());
		DEBUG("ColAmm                : " << STR_MOD->msk(str, DELIM, ColAmm).c_str());
		DEBUG("ColEsp                : " << STR_MOD->msk(str, DELIM, ColEsp).c_str());
//		DEBUG("ColdaSostituire       : " << STR_MOD->msk(str, DELIM, ColdaSostituire).c_str());

		// nome
		tmpPlayer.Cognome = STR_MOD->msk(str, DELIM, ColCognome);

		// squadra
		tmpPlayer.Squadra = STR_MOD->msk(str, DELIM, ColSquadra);

		// goal e rigori
		if (STR_MOD->msk(str, DELIM, ColRuolo) == "P") {
			tmpPlayer.Ruolo = 0;
			tmpPlayer.GoalSubiti = fabs(
					atof(STR_MOD->msk(str, DELIM, ColGoalSubiti).c_str()));
			tmpPlayer.GoalFatti = 0;
			tmpPlayer.RigoreParato = fabs(
					atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
			tmpPlayer.RigoreSbagliato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "D") {
			tmpPlayer.Ruolo = 1;
			tmpPlayer.GoalFatti = atof(
					STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3;
			tmpPlayer.GoalSubiti = 0;
			tmpPlayer.RigoreSbagliato = fabs(
					atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
			tmpPlayer.RigoreParato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "C") {
			tmpPlayer.Ruolo = 2;
			tmpPlayer.GoalFatti = atof(
					STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3;
			tmpPlayer.GoalSubiti = 0;
			tmpPlayer.RigoreSbagliato = fabs(
					atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
			tmpPlayer.RigoreParato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "A") {
			tmpPlayer.Ruolo = 3;
			tmpPlayer.GoalFatti = atof(
					STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3;
			tmpPlayer.GoalSubiti = 0;
			tmpPlayer.RigoreSbagliato = fabs(
					atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
			tmpPlayer.RigoreParato = 0;
		}

		DEBUG(str.c_str());
		DEBUG("_" << STR_MOD->msk(str, DELIM, ColVotoGazzetta).c_str() << "_");
		DEBUG("_" << STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta).c_str() << "_");

		// fantavoto
		if (STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta) == "-")
		{
			tmpPlayer.FantaVotoGazzetta = 0.0;
		} else {
			tmpPlayer.FantaVotoGazzetta = atof(
					STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta).c_str());
		}

		// voto gazzetta
		if (STR_MOD->msk(str, DELIM, ColVotoGazzetta) == "-") {
			tmpPlayer.VotoGazzetta = 0.0;
		} else if (STR_MOD->msk(str, DELIM, ColVotoGazzetta) == "S.V.") {
			tmpPlayer.VotoGazzetta = -1;
		} else {
			tmpPlayer.VotoGazzetta = atof(
					STR_MOD->msk(str, DELIM, ColVotoGazzetta).c_str());
		}

		DEBUG("VotoGazzetta = _" << tmpPlayer.VotoGazzetta << "_");
		DEBUG("FantaVotoGazzetta = _" << tmpPlayer.FantaVotoGazzetta << "_");

		// --> goal decisivi
		tmpPlayer.GoalDecVitt = atoi(
				STR_MOD->msk(str, DELIM, ColGoalDecVitt).c_str());
		tmpPlayer.GoalDecPar = atoi(
						STR_MOD->msk(str, DELIM, ColGoalDecPar).c_str());

		DEBUG("GoalDecVitt = #" << tmpPlayer.GoalDecVitt << "#");
		DEBUG("GoalDecPar = #" << tmpPlayer.GoalDecPar << "#");

		if (tmpPlayer.GoalDecVitt != 0) {
			if (tmpPlayer.FantaVotoGazzetta == 0) {
				DEBUG("PLAYER_GDV_NOT_PLAYED");
				Fanta::Team[k].push_back(this->fakePlayer);
				return PLAYER_GDV_NOT_PLAYED;
			} else if (tmpPlayer.GoalFatti == 0) {
				DEBUG("PLAYER_GDV_NO_GOAL");
				Fanta::Team[k].push_back(this->fakePlayer);
				return PLAYER_GDV_NO_GOAL;
			}
		} else if (tmpPlayer.GoalDecPar != 0) {
			if (tmpPlayer.FantaVotoGazzetta == 0) {
				DEBUG("PLAYER_GDP_NOT_PLAYED");
				Fanta::Team[k].push_back(this->fakePlayer);
				return PLAYER_GDP_NOT_PLAYED;
			} else if (tmpPlayer.GoalFatti == 0) {
				DEBUG("PLAYER_GDP_NO_GOAL");
				Fanta::Team[k].push_back(this->fakePlayer);
				return PLAYER_GDP_NO_GOAL;
			}
		}
		// <-- goal decisivi

		tmpPlayer.Assist = atoi(STR_MOD->msk(str, DELIM, ColAssist).c_str());
		tmpPlayer.Autoreti = abs(
				atoi(STR_MOD->msk(str, DELIM, ColAutoreti).c_str()) / 2);
		tmpPlayer.Amm = abs(
				int(atof(STR_MOD->msk(str, DELIM, ColAmm).c_str()) / 0.5));
		tmpPlayer.Esp = abs(atoi(STR_MOD->msk(str, DELIM, ColEsp).c_str()));

		tmpPlayer.daSostituire = 0;

		for (size_t kk = 0; kk < 2; kk++) {
			for (size_t i = 0; i < Team[kk].size(); i++) {
				if (tmpPlayer.Cognome == Fanta::Team[kk].at(i).Cognome
						&& tmpPlayer.Ruolo == Fanta::Team[kk].at(i).Ruolo) {
					Fanta::Team[k].push_back(this->fakePlayer);
					return PLAYER_REPEATED;
				}
			}
		}

		Fanta::Team[k].push_back(tmpPlayer);
		return PLAYER_OK;
	} catch (...) {
		Fanta::Team[k].push_back(this->fakePlayer);
		return PLAYER_ERROR;
	}
}
unsigned int Fanta::LevenshteinDistance(const std::string& s1,
		const std::string& s2) {

	const unsigned int cost_del = 1;
	const unsigned int cost_ins = 1;
	const unsigned int cost_sub = 1;

	unsigned int n1 = s1.length();
	unsigned int n2 = s2.length();

	unsigned int* p = new unsigned int[n2 + 1];
	unsigned int* q = new unsigned int[n2 + 1];
	unsigned int* r;

	p[0] = 0;
	for (unsigned int j = 1; j <= n2; ++j)
		p[j] = p[j - 1] + cost_ins;

	for (unsigned int i = 1; i <= n1; ++i) {
		q[0] = p[0] + cost_del;
		for (unsigned int j = 1; j <= n2; ++j) {
			unsigned int d_del = p[j] + cost_del;
			unsigned int d_ins = q[j - 1] + cost_ins;
			unsigned int d_sub = p[j - 1] + (s1[i - 1] == s2[j - 1] ? 0
					: cost_sub);
			q[j] = std::min(std::min(d_del, d_ins), d_sub);
		}
		r = p;
		p = q;
		q = r;
	}

	unsigned int tmp = p[n2];
	delete[] p;
	delete[] q;

	return tmp;
}
void Fanta::execute() {

	DEBUG("");

	try {
		this->checkGiocatoSenzaVoto();
	} catch (...) {
		LOG(ERR, "Exception caught in checkGiocatoSenzaVoto().");
		DEBUG("exception caught in checkGiocatoSenzaVoto().");
	}

	try {
		this->checkNonHaGiocato();
	} catch (...) {
		LOG(ERR, "Exception caught in checkNonHaGiocato().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->orderByRuolo();
	} catch (...) {
		LOG(ERR, "In void Fanta::execute() --> exception caught in orderByRuolo().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->fillWithNonHaGiocato();
	} catch (...) {
		LOG(ERR, "Exception caught in fillWithNonHaGiocato().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->substitutions();
	} catch (...) {
		LOG(ERR, "Exception caught in substitutions().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->calculateFantaVoto();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateFantaVoto().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->calculateDefenseMean();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateDefenseMean().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->calculateDefenseModifier();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateDefenseModifier().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->calculateSfide();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateSfide().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->calculateTotal();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateTotal().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->calculateGoals();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateGoals().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	try {
		this->calculateScorers();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateScorers().");
		DEBUG("exception caught in checkNonHaGiocato().");
	}

	return;
}
void Fanta::checkGiocatoSenzaVoto() {

	LOG(DBG, "<br/> ============================");
	LOG(DBG,      " === Giocatori senza voto ===");
	LOG(DBG,      " ============================<br/><br/>");
		DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < this->Team[k].size(); j++) { // loop sui giocatori
			DEBUG( this->Team[k].at(j).Cognome.c_str());

			if (this->Team[k].at(j).VotoGazzetta == -1) { // se S.V.

				if (this->Team[k].at(j).Ruolo == 0) { // se e' un portiere

					DEBUG("Giocato senza voto --> " << this->Team[k].at(j).Cognome.c_str() << " - portiere.");

					this->Team[k].at(j).VotoGazzetta = 6.0; // il portiere non si sostituisce se ha giocato (ma non ha preso voto),
					this->Team[k].at(j).FantaVotoGazzetta
							= this->Team[k].at(j).VotoGazzetta
									- this->Team[k].at(j).Esp - 0.5
									* this->Team[k].at(j).Amm - 2
									* this->Team[k].at(j).Autoreti
									+ this->Team[k].at(j).Assist
									- this->Team[k].at(j).GoalSubiti; // subiti x un portiere !

					LOG(
							DBG,
							" -> "
									+ QString::fromStdString(
											this->Team[k].at(j).Cognome) + " ("
									+ QString::fromStdString(
											this->Team[k].at(j).Squadra)
									+ ", portiere) senza voto ma ha giocato. Fantavoto :  "
									+ QString::fromStdString(
											my::toString<float>(
													this->Team[k].at(j).FantaVotoGazzetta)));

				} else if (this->Team[k].at(j).Ruolo > 0) { //se non e' un portiere

					DEBUG("Giocato senza voto --> " << this->Team[k].at(j).Cognome.c_str() << " - non portiere.");

					QString answer;

					try {

						answer
								= this->questionMessage(
										QString::fromStdString(
												this->Team[k].at(j).Cognome));

						DEBUG("piu' di 25 minuti ? " << this->Team[k].at(j).Cognome.c_str() << " " << answer.toStdString().c_str());

					} catch (...) {
						LOG(FATAL,
								"Exception caught in Fanta::checkGiocatoSenzaVoto()!");
					}

					if (answer == "Yes") { // giocato piu' di 25'

						/* TODO
						 * controllare il regolamento
						 * riguardante i giocatori
						 * senza voto
						 */
						this->Team[k].at(j).VotoGazzetta = 6.0;
						this->Team[k].at(j).FantaVotoGazzetta
								= this->Team[k].at(j).VotoGazzetta
										- this->Team[k].at(j).Esp - 0.5
										* this->Team[k].at(j).Amm - 2
										* this->Team[k].at(j).Autoreti
										+ this->Team[k].at(j).Assist + 3
										* this->Team[k].at(j).GoalFatti;

						if (this->Team[k].at(j).FantaVotoGazzetta == 6.0) { // no Bonus/Malus
							this->Team[k].at(j).VotoGazzetta = 5.5;
							this->Team[k].at(j).FantaVotoGazzetta = 5.5;

							LOG(DBG, \
									" -> " \
										+ QString::fromStdString(this->Team[k].at(j).Cognome) \
										+ " (" \
										+ QString::fromStdString(this->Team[k].at(j).Squadra) \
										+ ") ha giocato 25'.");
						}

					} else if (answer == "No") { // giocato meno di 25' --> sostituire

						DEBUG("da sostituire.");

						this->Team[k].at(j).daSostituire = 1; // viene marcato per l'eliminazione

						LOG(DBG, \
								" -> " \
										+ QString::fromStdString(this->Team[k].at(j).Cognome) \
										+ " (" \
										+ QString::fromStdString(this->Team[k].at(j).Squadra) \
										+ ") non ha giocato 25' : verra' effettuata una sostituzione.");

					} else {
						/* TODO
						 * IMPOSSIBILE?
						 * answer is neither Yes or No !!!!!!
						 * * * * * * * * * * * * * * * * * * * */
					}
				} else { // da sostituire

					DEBUG("da sostituire.");

					this->Team[k].at(j).daSostituire = 1; // viene marcato per l'eliminazione

					LOG(DBG, \
							" -> " \
							+ QString::fromStdString(this->Team[k].at(j).Cognome) \
							+ " (" \
							+ QString::fromStdString(this->Team[k].at(j).Squadra) \
							+ ") non ha giocato 25' : verra' effettuata una sostituzione.");
				}

				continue;
			} // se S.V.
		} // loop giocatori
	} // loop squadre
}
QString Fanta::questionMessage(QString playerName) {

	DEBUG("");

	QString title = "Ha giocato almeno 25' ?";

	QString
			message =
					"Il giocatore \n" + playerName
							+ " \nha giocato, ma non e\' stato giudicato. \nHa giocato piu\' di 25\' ?";

	QString answer;

	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(THE_LOGGER, title, message,
			QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes) {
		answer = "Yes";
		DEBUG("returning " << answer.toStdString().c_str() << ".");
	} else if (reply == QMessageBox::No) {
		answer = "No";
		DEBUG("returning " << answer.toStdString().c_str() << ".");
	} else {
		answer = "Error";
		LOG(ERR, "In Fanta::questionMessage() --> returning " + answer + ".");
	}

	return answer;
}
void Fanta::checkNonHaGiocato() {

	LOG(DBG, "<br/> =======================================");
	LOG(DBG,      " === Giocatori che non hanno giocato ===");
	LOG(DBG,      " =======================================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DBG, \
				"<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)) + " :");

		for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
		{
			if (this->Team[k].at(j).VotoGazzetta == 0) {
				if (this->Team[k].at(j).FantaVotoGazzetta == 0) {

					this->Team[k].at(j).daSostituire = 1; // viene marcato per l'eliminazione

					LOG(DBG, \
							"      " \
							+ QString::fromStdString(this->Team[k].at(j).Cognome) \
							+ " (" \
							+ QString::fromStdString(this->Team[k].at(j).Squadra) \
							+ ").");
				} else {
					// ma ha ricevuto voto dalla Gazzetta (caso di partite sospese ??? )
					this->Team[k].at(j).VotoGazzetta
							= this->Team[k].at(j).FantaVotoGazzetta;
					LOG(DBG, \
							"      " \
							+ QString::fromStdString(this->Team[k].at(j).Cognome) \
							+ " (" \
							+ QString::fromStdString(this->Team[k].at(j).Squadra) \
							+ ") non ha giocato, ma ha ricevuto voto(" \
							+ QString::fromStdString(my::toString<float>(this->Team[k].at(j).FantaVotoGazzetta)) \
							+ ").");
				}
			} else {
				//LOG(DBG, \
						" -> " \
						+ QString::fromStdString(this->Team[k].at(j).Cognome) \
						+ " (" \
						+ QString::fromStdString(this->Team[k].at(j).Squadra) \
						+ ") fantavoto : " \
						+ QString::fromStdString(my::toString<float>(this->Team[k].at(j).FantaVotoGazzetta)) \
						+ ".");
			}
		}
	}
}
void Fanta::orderByRuolo() {

	DEBUG("");

	try {
		for (unsigned int k = 0; k < 2; k++)// loop sulle squadre
		{
			try {
				for (signed int i = 0; i < 4; i++) // loop sui ruoli
				{

					for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
					{
						if (this->Team[k].at(j).Ruolo == i) {
							Fanta::teamOrderedByRuolo[k][i].push_back(
									this->Team[k].at(j));
							DEBUG(i << " " << this->Team[k].at(j).Cognome.c_str());
						}
					}
				}
			} catch (...) {
				LOG(FATAL,
						"Exception caught in ruoli loop.");
			}
		}
	} catch (...) {
		LOG(FATAL,
				"Exception caught in squadre loop.");
	}
}
void Fanta::fillWithNonHaGiocato() {

	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			for (size_t j = Fanta::teamOrderedByRuolo[k][i].size(); j
					< modulo[k][i] + 2; j++) {
				Fanta::teamOrderedByRuolo[k][i].push_back(Fanta::NonHaGiocato);
				DEBUG("Squadra " << this->getTeamName(k).c_str() << " : aggiunto un Fanta::NonHaGiocato");
				//LOG(DBG, \
						QString::fromStdString(this->getTeamName(k)) \
								+ " : aggiunto un Fanta::NonHaGiocato");
			}
		}
	}
}
void Fanta::substitutions() {

	LOG(DBG, "<br/> ====================");
	LOG(DBG,      " === Sostituzioni ===");
	LOG(DBG,      " ====================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size(); j++) // loop sui tutti i giocatori
			{
				if (this->teamOrderedByRuolo[k][i].at(j).daSostituire == 1) {
					Fanta::player tmpPlayer = Fanta::NonHaGiocato;
					tmpPlayer.Cognome_Sost
							= this->teamOrderedByRuolo[k][i].at(j).Cognome;
					tmpPlayer.Squadra_Sost = this->teamOrderedByRuolo[k][i].at(
							j).Squadra;
					this->teamOrderedByRuolo[k][i].at(j) = tmpPlayer;
				}
			}
		}
	}

	/*
	 *  sposta i 'NON HA GIOCATO' al fondo dei giocatori in campo
	 */
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t xx = Fanta::modulo[k][i] - 1;

			for (size_t j = 0; j < xx; j++) {
				for (size_t t = 0; t < xx - j; t++) {
					if (Fanta::teamOrderedByRuolo[k][i].at(t).Cognome == "---")
						swap(Fanta::teamOrderedByRuolo[k][i].at(t),
								Fanta::teamOrderedByRuolo[k][i].at(t + 1));
				}
			}
		}
	}

	/*
	 *  se il primo panchinaro non ha giocato lo swappa con il secondo;
	 *  se anch'esso non ha giocato non serve a nulla, se ha giocato lo porta in prima posizione
	 */

	for (size_t k = 0; k < 2; k++) // squadre
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			if (Fanta::teamOrderedByRuolo[k][i].at(Fanta::modulo[k][i]).Cognome
					== "---")
				swap(
						Fanta::teamOrderedByRuolo[k][i].at(Fanta::modulo[k][i]),
						Fanta::teamOrderedByRuolo[k][i].at(
								Fanta::modulo[k][i] + 1));
		}
	}

	unsigned int a[7] = { 0, 3, 2, 1, 3, 2, 1 }; // ordine delle sostituzioni

	for (size_t k = 0; k < 2; k++) {

		LOG(DBG, "<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)) \
				+ " :");

		for (size_t t = 0; t < 3; t++) { // ripetere il loop sottostante per esaurire tutte le sostituzioni
			for (size_t i = 0; i < 7; i++) { // loop sulla dimensione di a[]
				unsigned int w = Fanta::modulo[k][a[i]];

				for (size_t j = 0; j < w; j++) // loop sui giocatori
				{
					if (Fanta::teamOrderedByRuolo[k][a[i]].at(j).Cognome == "---"
							&& sostituzioni[k] < 3) {

						for (size_t x = w; x
								< Fanta::teamOrderedByRuolo[k][a[i]].size(); x++) {
							if (Fanta::teamOrderedByRuolo[k][a[i]].at(x).Cognome
									!= "---") {
								sostituzioni[k]++;

								LOG(DBG, \
										"      " \
										+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][a[i]].at(x).Cognome) \
										+ " (" \
										+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][a[i]].at(x).Squadra) \
										+ ") al posto di " \
										+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][a[i]].at(j).Cognome_Sost) \
										+ " (" \
										+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][a[i]].at(j).Squadra_Sost) \
										+ ").");

								swap(
										Fanta::teamOrderedByRuolo[k][a[i]].at(x),
										Fanta::teamOrderedByRuolo[k][a[i]].at(j));

								goto label;
								// serve per poter uscire da due loop contemporaneamente
							}
						}
					}
				}
				label: ; // solo una sostituzione per ruolo ( per volta )
			}
		}
	}

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			Fanta::teamOrderedByRuolo[k][i].resize(Fanta::modulo[k][i]);
		}
	}

	//for (size_t k = 0; k < 2; k++) // squadra
	//{
	//	for (size_t i = 0; i < 4; i++) // ruolo
	//	{
	//		for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size(); j++) {
	//			DEBUG(this->getTeamName(k).c_str() << " : " << \
	//					this->teamOrderedByRuolo[k][i].at(j).Ruolo << " " << \
	//					this->teamOrderedByRuolo[k][i].at(j).Cognome.c_str() + ".");
	//		}
	//	}
	//}
}
void Fanta::calculateFantaVoto() {

	LOG(DBG, "<br/> =================");
	LOG(DBG,      " === Fantavoti ===");
	LOG(DBG,      " =================");
	DEBUG("");

	int longerName = 0;

	for (size_t k = 0; k < 2; k++) { // squadra
		for (size_t i = 0; i < 4; i++) { // ruolo
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto =
						Fanta::teamOrderedByRuolo[k][i].at(j).FantaVotoGazzetta
						+ Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecVitt
						+ Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecPar * 0.5;

				(this->teamOrderedByRuolo[k][i].at(j).Cognome.size() > longerName) \
						? \
						longerName=this->teamOrderedByRuolo[k][i].at(j).Cognome.size() \
						: \
						longerName;

				j++;
			}
		}
	}

	int counter;
	for (size_t k = 0; k < 2; k++) { // squadra
		LOG(DBG,
				"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");

		counter = 1;

		for (size_t i = 0; i < 4; i++) { // ruolo

			size_t j = 0;

			while (j < Fanta::modulo[k][i]) {
				LOG(DBG, "      [" \
						+ STR_MOD->rightQString(my::toQString<int>(counter++), 2) \
						+ "] " \
						+ QString::fromStdString(STR_MOD->leftString(this->teamOrderedByRuolo[k][i].at(j).Cognome, longerName)) \
						+ " : " \
						+ my::toQString<float>(this->teamOrderedByRuolo[k][i].at(j).FantaVoto));

				j++;
			}
		}
	}

}
void Fanta::calculateDefenseMean() {

	LOG(DBG, "<br/> ====================");
	LOG(DBG,      " === Media difesa ===");
	LOG(DBG,      " ====================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DBG, \
				"<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)) + " :");

		size_t j = 0;
		while (j < Fanta::modulo[k][1]) {
			if (Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta != 0) {
				Fanta::defenseMean[k] +=
						Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta;
				Fanta::defenders[k]++;

				LOG(DBG, "      [" \
						+ my::toQString<size_t>(j + 1) \
						+ "] " \
						+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][1].at(j).Cognome) \
						+ " (" \
						+ my::toQString<float>(Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta) \
						+ ")");
			}
			j++;
		}
		Fanta::defenseMean[k] /= Fanta::defenders[k];

		LOG(DBG, "      media = " \
				+ my::toQString<double>(Fanta::defenseMean[k]));
	}
}
void Fanta::calculateDefenseModifier() {

	LOG(DBG, "<br/> =================================");
	LOG(DBG,      " === Modificatore della difesa ===");
	LOG(DBG,      " =================================");
	DEBUG("");

	for (size_t i = 0; i < 9; i++) {
		if (Fanta::defenseMean[0] >= Fanta::modifierVoti[i]
				&& Fanta::defenseMean[0] < Fanta::modifierVoti[i + 1])
			Fanta::modifier[1] = Fanta::modifierValues[i][Fanta::defenders[0]
					- 1];

		if (Fanta::defenseMean[1] >= Fanta::modifierVoti[i]
				&& Fanta::defenseMean[1] < Fanta::modifierVoti[i + 1])
			Fanta::modifier[0] = Fanta::modifierValues[i][Fanta::defenders[1]
					- 1];
	}

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DBG, "<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)) \
				+ "<br>      modificatore : " \
				+ my::toQString<signed int>(Fanta::modifier[k]));
	}
}
void Fanta::calculateSfide() {

	LOG(DBG, "<br/> =====================");
	LOG(DBG,      " === Calcolo sfide ===");
	LOG(DBG,      " =====================<br>");
	DEBUG("");

	QString winner, loser, team;
	int longerName = max(this->getTeamName(0).size(), this->getTeamName(1).size());

	QString def0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][1].at(0).Cognome) \
				+ " (" \
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta) \
				+ ", " \
				+ QString::fromStdString(this->getTeamName(0)) \
				+ ")";

	QString cen0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][2].at(0).Cognome) \
				+ " (" \
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta) \
				+ ", " \
				+ QString::fromStdString(this->getTeamName(0)) \
				+ ")";

	QString att0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][3].at(0).Cognome) \
				+ " (" \
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta) \
				+ ", " \
				+ QString::fromStdString(this->getTeamName(0)) \
				+ ")";

	QString def1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][1].at(0).Cognome) \
				+ " (" \
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta) \
				+ ", " \
				+ QString::fromStdString(this->getTeamName(1)) \
				+ ")";

	QString cen1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][2].at(0).Cognome) \
				+ " (" \
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta) \
				+ ", " \
				+ QString::fromStdString(this->getTeamName(1)) \
				+ ")";

	QString att1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][3].at(0).Cognome) \
				+ " (" \
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta) \
				+ ", " \
				+ QString::fromStdString(this->getTeamName(1)) \
				+ ")";

	/*
	 *  difensori - attaccanti
	 */

	if (Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(0)), longerName);
		winner = def0;
		loser = att1;

	} else if (Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(1)), longerName);
		winner = att1;
		loser = def0;

	} else {

		team = STR_MOD->leftQString("---", longerName);
		winner = def0;
		loser = att1;

	}

	LOG	(DBG, "    [1] " \
			+ team \
			+ " : "
			+ winner \
			+ " - " \
			+ loser);

	/*
	 *  centrocampisti - centrocampisti
	 */

	if (Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(0)), longerName);
		winner = cen0;
		loser = cen1;

	} else if (Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(1)), longerName);
		winner = cen1;
		loser = cen0;

	} else {

		team = STR_MOD->leftQString("---", longerName);
		winner = cen0;
		loser = cen1;

	}

	LOG	(DBG, "    [2] " \
			+ team \
			+ " : "
			+ winner \
			+ " - " \
			+ loser);

	/*
	 *  attaccanti - difensori
	 */

	if (Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(0)), longerName);
		winner = att0;
		loser = def1;

	} else if (Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(1)), longerName);
		winner = def1;
		loser = att0;

	} else {

		team = STR_MOD->leftQString("---", longerName);
		winner = att0;
		loser = def1;

	}

	LOG	(DBG, "    [3] " \
			+ team \
			+ " : "
			+ winner \
			+ " - " \
			+ loser);

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DBG, \
				"<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)));
		LOG(DBG, \
				+ "      sfide = " + my::toQString<unsigned int>(Fanta::sfide[k]));
	}
}
void Fanta::calculateTotal() {

	LOG(DBG, "<br/> =========================");
	LOG(DBG,      " === Calcolo punteggio ===");
	LOG(DBG,      " =========================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		QString message;

		LOG(DBG, \
				"<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)));


		Fanta::Total[k] += Fanta::atHome[k];
		message = "      " \
				+ my::toQString<double>(Fanta::Total[k]) \
				+ " (" \
				+ my::toQString<unsigned int>(Fanta::atHome[k]) \
				+ ", in casa)";


		LOG(DBG, message);

		Fanta::Total[k] += Fanta::modifier[k];
		message = "      " \
				+ my::toQString<double>(Fanta::Total[k]) \
				+ " (" \
				+ my::toQString<signed int>(Fanta::modifier[k]) \
				+ ", modificatore difesa)";

		LOG(DBG, message);

		Fanta::Total[k] += Fanta::sfide[k];
		message = "      " \
				+ my::toQString<double>(Fanta::Total[k]) \
				+ " (" \
				+ my::toQString<unsigned int>(Fanta::sfide[k]) \
				+ ", sfide)";

		LOG(DBG, message);

		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::Total[k]
						+= Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto;

				message = "      " \
						+ my::toQString<double>(Fanta::Total[k]) \
						+ " (" \
						+ my::toQString<float>(Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto) \
						+ ", " \
						+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][i].at(j).Cognome) \
						+ ")";

				LOG(DBG, message);

				j++;
			}
		}

		message = "<br>    Totale : "
				+ my::toQString<double>(Fanta::Total[k]);

		LOG(DBG, message);
	}
}
void Fanta::calculateGoals() {

	LOG(DBG, "<br/> =====================");
	LOG(DBG,      " === Calcolo goals ===");
	LOG(DBG,      " =====================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) {

		for (size_t i = 0;; i++) {
			if (Fanta::Total[k] >= (6 * i))
				continue;

			if (i > 11) {
				Fanta::goals[k] = i - 11;
			} else {
				Fanta::goals[k] = 0;
			}

			break;
		}
	}

	if (Fanta::Total[0] < 66 && Fanta::Total[1] < 66) {

		if (Fanta::Total[0] >= Fanta::Total[1] + 6) {
			Fanta::goals[0] = 1;
		} else if (Fanta::Total[1] >= Fanta::Total[0] + 6) {
			Fanta::goals[1] = 1;
		}

		LOG(DBG, \
				"<br>      Entrambe le due squadre hanno totalizzato meno di 66 punti");

		for (size_t k = 0; k < 2; k++) {
			LOG(DBG, "      " \
				+ STR_MOD->leftQString(QString::fromStdString(this->getTeamName(k)), FANTA->longerNameLength) \
				+ " : " \
				+ my::toQString<double>(Fanta::Total[k]) \
				+ " --> " \
				+ my::toQString<signed int>(Fanta::goals[k]) \
				+ " goals");
		}
	}

	if (Fanta::goals[0] < 0 || Fanta::goals[1] < 0) {

		LOG(DBG, "");
		for (size_t k = 0; k < 2; k++) {
			if (Fanta::goals[k] < 0) {
				LOG(DBG, \
						"      " \
						+ STR_MOD->leftQString(QString::fromStdString(this->getTeamName(k)), FANTA->longerNameLength) \
						+ " ha totalizzato un numero negativo di goals (" \
						+ my::toQString<signed int>(Fanta::goals[k]) + " --> 0)");

				Fanta::goals[k] = 0;

			}
		}
	}


	for (size_t k = 0; k < 2; k++) {
		LOG(DBG, "<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)));
		LOG(DBG, "      goals : " \
				+ my::toQString<signed int>(Fanta::goals[k]));
	}

}
void Fanta::calculateScorers() {

	LOG(DBG, "<br/> =================");
	LOG(DBG,      " === Marcatori ===");
	LOG(DBG,      " =================");
	DEBUG("");

	vector<Fanta::player> tmpVector[2];

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				// preparing a single vector
				tmpVector[k].push_back(Fanta::teamOrderedByRuolo[k][i].at(j));
				j++;
			}
		}
	}

	for (size_t k = 0; k < 2; k++) // squadra
	{

		LOG(DBG, \
				"<br> -> " \
				+ QString::fromStdString(this->getTeamName(k)));

		if (Fanta::goals[k] == 0) {
			LOG(DBG, \
					"      ---");
			continue;
		}

		do {
			Fanta::bSort(tmpVector[k]);
			Fanta::scorers[k].push_back(tmpVector[k].at(0).Cognome);

			LOG(DBG, \
					"      " \
					+ QString::fromStdString(tmpVector[k].at(0).Cognome) \
					+ " (" + my::toQString<float>(tmpVector[k].at(0).FantaVoto) \
					+ ")");

			tmpVector[k].at(0).FantaVoto -= 3.0;
		} while (Fanta::scorers[k].size() < Fanta::goals[k]);
	}
}
void Fanta::bSort(std::vector<Fanta::player> & vect) {
	size_t xx = vect.size() - 1;

	// sorting with bubble-sort algorithm
	for (size_t j = 0; j < xx; j++) {
		for (size_t i = 0; i < xx - j; i++) {
			if (vect.at(i).FantaVoto < vect.at(i + 1).FantaVoto) // ordina per FantaVoto
				swap(vect.at(i), vect.at(i + 1));
			else if (vect.at(i).FantaVoto == vect.at(i + 1).FantaVoto) {
				if (vect.at(i).VotoGazzetta < vect.at(i + 1).VotoGazzetta) // poi per Voto
					swap(vect.at(i), vect.at(i + 1));
				else if (vect.at(i).VotoGazzetta == vect.at(i + 1).VotoGazzetta) {
					if (vect.at(i).Ruolo < vect.at(i + 1).Ruolo) // poi per Ruolo
						swap(vect.at(i), vect.at(i + 1));
				}
			}
		}
	}
}
QString Fanta::getFileGazzetta() {
	return this->fileGazzetta;
}
void Fanta::printRiepilogo() {

	FANTA->longerNameLength = (FANTA->getTeamName(0).size()
			>= FANTA->getTeamName(1).size()) ? FANTA->getTeamName(0).size()
			: FANTA->getTeamName(1).size();

	QString team_A =
			QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)).replace(QString(" "),
					QString("&nbsp;"));

	QString team_B =
			QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)).replace(QString(" "),
					QString("&nbsp;"));

	QString output = "<br/> --- Modulo ---<br/><br/>   " + team_A + " : "
			+ QString::fromStdString(FANTA->getModuloSquadra(0));

	output += "<br/>   " + team_B + " : " + QString::fromStdString(
			FANTA->getModuloSquadra(1));

	output += "<br/><br/> --- Fattore Campo ---<br/><br/>   " + team_A + " : "
			+ my::toQString<unsigned int>(FANTA->atHome[0]);

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->atHome[1]);

	output += "<br/><br/> --- Ammonizioni ---<br/><br/>   " + team_A + " : "
			+ my::toQString<unsigned int>(FANTA->getAmmonizioniTot(0));
	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->getAmmonizioniTot(1));

	output += "<br/><br/> --- Espulsioni ---<br/><br/>   " + team_A + " : "
			+ my::toQString<unsigned int>(FANTA->getEspulsioniTot(0));

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->getEspulsioniTot(1));

	output += "<br/><br/> --- Goal decisivi vittoria ---<br/><br/>   " + team_A
			+ " : " + my::toQString<unsigned int>(FANTA->getGoalDecVittTot(0));

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->getGoalDecVittTot(1));

	output += "<br/><br/> --- Goal decisivi pareggio ---<br/><br/>   " + team_A
			+ " : " + my::toQString<unsigned int>(FANTA->getGoalDecParTot(0));

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->getGoalDecParTot(1));

	output += "<br/><br/> --- Assist ---<br/><br/>   " + team_A + " : "
			+ my::toQString<unsigned int>(FANTA->getAssistTot(0));

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->getAssistTot(1));

	output += "<br/><br/> --- Sostituzioni ---<br/><br/>   " + team_A + " : "
			+ my::toQString<unsigned int>(FANTA->sostituzioni[0]);

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->sostituzioni[1]);

	output += "<br/><br/> --- Sfide ---<br/><br/>   " + team_A + " : "
			+ my::toQString<unsigned int>(FANTA->sfide[0]);

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
			FANTA->sfide[1]);

	output += "<br/><br/> Dettaglio :<br/>";

	output += "<br/>   |";

	output
			+= "<br/>   | Dif " + team_A + " : "
					+ QString::fromStdString(
							STR_MOD->leftString(
									my::toString<float>(
											FANTA->teamOrderedByRuolo[0][1].at(
													0).VotoGazzetta), 3))
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[0][1].at(0).Cognome);

	output
			+= "<br/>   | Att " + team_B + " : "
					+ QString::fromStdString(
							STR_MOD->leftString(
									my::toString<float>(
											FANTA->teamOrderedByRuolo[1][3].at(
													0).VotoGazzetta), 3))
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[1][3].at(0).Cognome);

	output += "<br/>   |";

	output
			+= "<br/>   | Cen " + team_A + " : "
					+ QString::fromStdString(
							STR_MOD->leftString(
									my::toString<float>(
											FANTA->teamOrderedByRuolo[0][2].at(
													0).VotoGazzetta), 3))
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[0][2].at(0).Cognome);

	output
			+= "<br/>   | Cen " + team_B + " : "
					+ QString::fromStdString(
							STR_MOD->leftString(
									my::toString<float>(
											FANTA->teamOrderedByRuolo[1][2].at(
													0).VotoGazzetta), 3))
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[1][2].at(0).Cognome);

	output += "<br/>   |";

	output
			+= "<br/>   | Att " + team_A + " : "
					+ QString::fromStdString(
							STR_MOD->leftString(
									my::toString<float>(
											FANTA->teamOrderedByRuolo[0][3].at(
													0).VotoGazzetta), 3))
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[0][3].at(0).Cognome);

	output
			+= "<br/>   | Dif " + team_B + " : "
					+ QString::fromStdString(
							STR_MOD->leftString(
									my::toString<float>(
											FANTA->teamOrderedByRuolo[1][1].at(
													0).VotoGazzetta), 3))
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[1][1].at(0).Cognome);

	output += "<br/>   |";
	output += "<br/>   +---------------------------------------------><br/>";

	output += "<br/> --- Media Difesa ---<br/><br/>";

	for (size_t i = 0; i < 2; i++) {
		QString string = "   " + QString::fromStdString(
				STR_MOD->leftString(FANTA->getTeamName(i),
						FANTA->longerNameLength)).replace(QString(" "),
				QString("&nbsp;")) + " : " + my::toQString<double>(
				FANTA->defenseMean[i]) + " ( " + my::toQString<unsigned int>(
				FANTA->defenders[i]) + " )";

		output += string + "<br/>";
	}

	output += "<br/> --- Modificatore ---<br/><br/>";

	for (size_t i = 0; i < 2; i++) {
		QString string = "   " + QString::fromStdString(
				STR_MOD->leftString(FANTA->getTeamName(i),
						FANTA->longerNameLength)).replace(QString(" "),
				QString("&nbsp;")) + " : " + my::toQString<signed int>(
				FANTA->modifier[i]);

		output += string + "<br/>";
	}

	output += "<br/> --- Risultato e marcatori ---<br/><br/>";

	unsigned int longestTotalLenght =
			(my::toString<double>(FANTA->Total[0]).size() >= my::toString<
					double>(FANTA->Total[1]).size()) ? my::toString<double>(
					FANTA->Total[0]).size() : my::toString<double>(
					FANTA->Total[1]).size();

	for (size_t i = 0; i < 2; i++) {
		QString string = "   " + QString::fromStdString(
				STR_MOD->leftString(FANTA->getTeamName(i),
						FANTA->longerNameLength)).replace(QString(" "),
				QString("&nbsp;")) + " : " + my::toQString<signed int>(
				FANTA->goals[i]) + " ( " + QString::fromStdString(
				STR_MOD->leftString(my::toString<double>(FANTA->Total[i]),
						longestTotalLenght)) + " ";

		if (FANTA->goals[i] > 0)
			string += ": ";

		for (size_t j = 0; j < FANTA->scorers[i].size(); j++) {
			string += QString::fromStdString(
					STR_MOD->onlySurname(FANTA->scorers[i].at(j)));
			if (j < (FANTA->scorers[i].size() - 1))
				string += ", ";
			else
				string += " ";
		}

		output += string + ")<br/>";
	}
	output += "<br/>";

	LOG(INFO, output.replace(QString(" "), QString("&nbsp;")));
}
void Fanta::printTitolo(std::string str, std::string where) {
	QString tmp = "<br/>   +";
	for (unsigned int i = 0; i < str.size() + 6; i++) {
		tmp += "-";
	}
	tmp += "+<br/>";

	tmp += "   | +";
	for (unsigned int i = 0; i < str.size() + 2; i++) {
		tmp += "-";
	}
	tmp += "+ |<br/>";

	tmp += "   | |";
	for (unsigned int i = 0; i < str.size() + 2; i++) {
		tmp += " ";
	}
	tmp += "| |<br/>";

	tmp += "   | | " + QString::fromStdString(str) + " | |<br/>";

	tmp += "   | |";
	for (unsigned int i = 0; i < str.size() + 2; i++) {
		tmp += " ";
	}
	tmp += "| |<br/>";

	tmp += "   | +";
	for (unsigned int i = 0; i < str.size() + 2; i++)
		tmp += "-";
	tmp += "+ |<br/>";

	tmp += "   +";
	for (unsigned int i = 0; i < str.size() + 6; i++)
		tmp += "-";
	tmp += "+<br/>";

	if (where == DBG) {
		LOG(DBG, tmp.replace(QString(" "), QString("&nbsp;")));
	} else if (where == INFO) {
		LOG(INFO, tmp.replace(QString(" "), QString("&nbsp;")));
	}

}
void Fanta::printPlayersInfo() {
	for (size_t k = 0; k < 2; k++) // squadre
	{

		FANTA->printTitolo(FANTA->teamName.at(k), DBG);

		QString tmp = "";

		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < FANTA->modulo[k][i]) {
				tmp += QObject::tr("<br/><br/>   ==== %1 ====").arg(
						QString::fromStdString(
								FANTA->teamOrderedByRuolo[k][i].at(j).Cognome));

				tmp += "<br/><br/>";

				tmp += STR_MOD->rightQString("Voto :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).VotoGazzetta),
								5);
				tmp += STR_MOD->rightQString("Fantavoto :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).FantaVoto),
								5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Goal fatti :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).GoalFatti),
								5);
				tmp += STR_MOD->rightQString("Goal subiti :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).GoalSubiti),
								5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Goal dec vitt :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).GoalDecVitt),
								5);
				tmp += STR_MOD->rightQString("Goal dec par :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).GoalDecPar),
								5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Ammonizioni :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).Amm),
								5);
				tmp += STR_MOD->rightQString("Espulsioni :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).Esp),
								5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Assist :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<unsigned int>(
										FANTA->teamOrderedByRuolo[k][i].at(j).Assist),
								5);
				tmp += STR_MOD->rightQString("Autoreti :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<float>(
										FANTA->teamOrderedByRuolo[k][i].at(j).Autoreti),
								5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Rigore parato :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<unsigned int>(
										FANTA->teamOrderedByRuolo[k][i].at(j).RigoreParato),
								5);
				tmp += STR_MOD->rightQString("Rigore sbagliato :", 20);
				tmp
						+= STR_MOD->rightQString(
								my::toQString<unsigned int>(
										FANTA->teamOrderedByRuolo[k][i].at(j).RigoreSbagliato),
								5);
				tmp += "<br/>";

				j++;
			}
		}

		LOG(DBG, tmp.replace(QString(" "), QString("&nbsp;")));
	}
}
unsigned int Fanta::getAmmonizioniTot(unsigned int k) const {
	unsigned int amm = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < this->modulo[k][i]) {
			amm += this->teamOrderedByRuolo[k][i].at(j).Amm;
			j++;
		}
	}

	return amm;
}
unsigned int Fanta::getEspulsioniTot(unsigned int k) const {
	unsigned int esp = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][i]) {
			esp += Fanta::teamOrderedByRuolo[k][i].at(j).Esp;
			j++;
		}
	}

	return esp;
}
unsigned int Fanta::getGoalDecVittTot(unsigned int k) const {
	unsigned int GDVT = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][i]) {
			GDVT += Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecVitt;
			j++;
		}
	}

	return GDVT;
}
unsigned int Fanta::getGoalDecParTot(unsigned int k) const {
	unsigned int GDPT = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][i]) {
			GDPT += Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecPar;
			j++;
		}
	}

	return GDPT;
}
unsigned int Fanta::getSubstitutions(unsigned int k) const {
	return Fanta::sostituzioni[k];
}
unsigned int Fanta::getAssistTot(unsigned int k) const {
	unsigned int AssTot = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][i]) {
			AssTot += Fanta::teamOrderedByRuolo[k][i].at(j).Assist;
			j++;
		}
	}

	return AssTot;

}
void Fanta::printFormations() {
	QString output = "";

	QString bordi =
					"<p> |                                                                                |</p>";

	QString fondo =
					"<p> +------------------------------+------------------+------------------------------+</p>";

	QString
			area =
					"<p> |                              |__________________|                              |</p>";

	QString
			area_sotto =
					area
							+ "<p> |                                      \\__/                                      |</p>"
							+ bordi;

	QString
			area_sopra =
					"<p> |                                       __                                       |</p><p> |                               _______/__\\_______                               |</p><p> |                              |                  |                              |</p>";

	QString
			separatore =
					"<p> |                                       ___                                      |</p><p> |                                      /   \\                                     |</p><p> |-------------------------------------(--o--)------------------------------------|</p><p> |                                      \\___/                                     |</p><p> |                                                                                |</p>";

	bordi = bordi.replace(" ", "&nbsp;");
	fondo = fondo.replace(" ", "&nbsp;");
	area = area.replace(" ", "&nbsp;");
	area_sotto = area_sotto.replace(" ", "&nbsp;");
	area_sopra = area_sopra.replace(" ", "&nbsp;");
	separatore = separatore.replace(" ", "&nbsp;");





	output += fondo;

	/*
	 *  squadra in casa    : por --> att
	 *  squadra fuori casa :                   att --> por
	 */
	unsigned int a[2][4] = { { 0, 1, 2, 3 }, { 3, 2, 1, 0 } };

	for (size_t k = 0; k < 2; k++) // squadre
	{
		for (size_t j = 0; j < 4; j++) // ruoli
		{
			QString tmpString = "<p> |";

			/*
			 *  nomi giocatori
			 */
			for (size_t i = 0; i < Fanta::modulo[k][a[k][j]]; i++) { // giocatori
				if (Fanta::modulo[k][a[k][j]] == 3) {
					tmpString
							+= QString::fromStdString(STR_MOD->centerString(
									STR_MOD->onlySurname(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).Cognome), 26));
				} else if (a[k][j] == 0) { // portiere
					if (k == 1) {
						output += area_sopra;
					}

					tmpString
							+= QString::fromStdString("                              |"
									+ STR_MOD->centerString(
											STR_MOD->onlySurname(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).Cognome), 18)
									+ "|                              |");
				} else {
					tmpString
							+= QString::fromStdString(STR_MOD->centerString(
									STR_MOD->onlySurname(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).Cognome),
									80 / Fanta::modulo[k][a[k][j]]));
				}
			}

			if (Fanta::modulo[k][a[k][j]] == 3) {
				output += tmpString + "  |</p>";
			} else if (a[k][j] == 0) {
				output += tmpString + "</p>";
			} else {
				output += tmpString + "|</p>";
			}

			tmpString = "";

			if (a[k][j] != 0)
				tmpString += "<p> |";

			/*
			 *  voti giocatori
			 */
			for (size_t i = 0; i < Fanta::modulo[k][a[k][j]]; i++) { // giocatori
				if (Fanta::modulo[k][a[k][j]] == 3) {
					tmpString
							+= QString::fromStdString(STR_MOD->centerString(
									(my::toString(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).FantaVoto) + " ("

											+ my::toString(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).VotoGazzetta)
											+ ")"), 26));
				} else if (a[k][j] == 0) { // portiere
					tmpString
							+= QString::fromStdString("<p> |                              |"
									+ STR_MOD->centerString(
											(my::toString(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).FantaVoto)
													+ " ("

													+ my::toString(
															Fanta::teamOrderedByRuolo[k][a[k][j]].at(
																	i).VotoGazzetta)
													+ ")"), 18)
									+ "|                              |");

					if (k == 0) {
						tmpString += "</p>" + area_sotto;
					}
				} else {
					tmpString
							+= QString::fromStdString(STR_MOD->centerString(
									(my::toString(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).FantaVoto) + " ("

											+ my::toString(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).VotoGazzetta)
											+ ")"),
									80 / Fanta::modulo[k][a[k][j]]));
				}
			}

			if (Fanta::modulo[k][a[k][j]] == 3) {
				output += tmpString + "  |</p>" + bordi;
			} else if (a[k][j] == 0) {
				output += tmpString;
			} else {
				output += tmpString + "|</p>" + bordi;
			}

			tmpString = "";
		}

		if (k == 0) {
			output += separatore + bordi;
		}
	}

	output += "</p>" + fondo;
	output = output.replace(" ", "&nbsp;");
	LOG(INFO, output);
}
unsigned int Fanta::getGoals(unsigned int k) const {
	return Fanta::goals[k];
}
double Fanta::getTotal(unsigned int k) const {
	return Fanta::Total[k];
}
std::string Fanta::getScorer(unsigned int k, unsigned int i) const {
	return Fanta::scorers[k].at(i);
}
unsigned int Fanta::getScorersSize(unsigned int k) const {
	return Fanta::scorers[k].size();
}
