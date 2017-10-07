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
			Fanta::distanza[k][j] = 0;
			Fanta::disponibili[k][j] = 0;
		}

		for (size_t j = 0; j < 10; j++) {
			Fanta::ruoloDaSostituire[k][j] = -1;
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

	Fanta::rosa[0] = 3;
	Fanta::rosa[1] = 8;
	Fanta::rosa[2] = 8;
	Fanta::rosa[3] = 6;

	Fanta::moduli[0][0] = 1;
	Fanta::moduli[0][1] = 5;
	Fanta::moduli[0][2] = 4;
	Fanta::moduli[0][3] = 1;
	Fanta::moduli[1][0] = 1;
	Fanta::moduli[1][1] = 4;
	Fanta::moduli[1][2] = 5;
	Fanta::moduli[1][3] = 1;
	Fanta::moduli[2][0] = 1;
	Fanta::moduli[2][1] = 5;
	Fanta::moduli[2][2] = 3;
	Fanta::moduli[2][3] = 2;
	Fanta::moduli[3][0] = 1;
	Fanta::moduli[3][1] = 4;
	Fanta::moduli[3][2] = 4;
	Fanta::moduli[3][3] = 2;
	Fanta::moduli[4][0] = 1;
	Fanta::moduli[4][1] = 3;
	Fanta::moduli[4][2] = 5;
	Fanta::moduli[4][3] = 2;
	Fanta::moduli[5][0] = 1;
	Fanta::moduli[5][1] = 4;
	Fanta::moduli[5][2] = 3;
	Fanta::moduli[5][3] = 3;
	Fanta::moduli[6][0] = 1;
	Fanta::moduli[6][1] = 3;
	Fanta::moduli[6][2] = 4;
	Fanta::moduli[6][3] = 3;

	Fanta::labelModuli[0] = "1-5-4-1";
	Fanta::labelModuli[1] = "1-4-5-1";
	Fanta::labelModuli[2] = "1-5-3-2";
	Fanta::labelModuli[3] = "1-4-4-2";
	Fanta::labelModuli[4] = "1-3-5-2";
	Fanta::labelModuli[5] = "1-4-3-3";
	Fanta::labelModuli[6] = "1-3-4-3";

	for (size_t i = 0; i < 7; i++) {
		Fanta::scoreModuli[i] = 0;
		Fanta::moduloPossibile[i] = true;
	}

	Fanta::NonHaGiocato.Cognome = "---";
	Fanta::NonHaGiocato.Cognome_Sost = "---";
	Fanta::NonHaGiocato.Squadra = "---";
	Fanta::NonHaGiocato.Squadra_Sost = "---";
	Fanta::NonHaGiocato.Ruolo2 = -1;
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
	Fanta::fakePlayer.Ruolo2 = -1;
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
	return my::toString(this->getModulo(k, 1)) + " - "
			+ my::toString(this->getModulo(k, 2)) + " - "
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
		//DEBUG("str : " << str.c_str());

		Fanta::player tmpPlayer;

		//DEBUG("ColCognome            : " << STR_MOD->msk(str, DELIM, ColCognome).c_str());
//		//DEBUG("ColNome_Sost          : " << STR_MOD->msk(str, DELIM, ColCognome_Sost).c_str());
		//DEBUG("ColSquadra            : " << STR_MOD->msk(str, DELIM, ColSquadra).c_str());
//		//DEBUG("ColSquadra_Sost       : " << STR_MOD->msk(str, DELIM, ColSquadra_Sost).c_str());
		//DEBUG("ColRuolo              : " << STR_MOD->msk(str, DELIM, ColRuolo).c_str());
		//DEBUG("ColRuolo2             : " << STR_MOD->msk(str, DELIM, ColRuolo2).c_str());
//		//DEBUG("ColFantaVoto          : " << STR_MOD->msk(str, DELIM, ColFantaVoto).c_str());
		//DEBUG("ColFantaVotoGazzetta  : " << STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta).c_str());
		//DEBUG("ColVotoGazzetta       : " << STR_MOD->msk(str, DELIM, ColVotoGazzetta).c_str());
		//DEBUG("ColGoalFatti          : " << STR_MOD->msk(str, DELIM, ColGoalFatti).c_str());
		//DEBUG("ColGoalSubiti         : " << STR_MOD->msk(str, DELIM, ColGoalSubiti).c_str());
		//DEBUG("ColAutoreti           : " << STR_MOD->msk(str, DELIM, ColAutoreti).c_str());
//		//DEBUG("ColRigoreParato       : " << STR_MOD->msk(str, DELIM, ColRigoreParato).c_str());
//		//DEBUG("ColRigoreSbagliato    : " << STR_MOD->msk(str, DELIM, ColRigoreSbagliato).c_str());
		//DEBUG("ColGoalDecVitt        : " << STR_MOD->msk(str, DELIM, ColGoalDecVitt).c_str());
		//DEBUG("ColGoalDecPar         : " << STR_MOD->msk(str, DELIM, ColGoalDecPar).c_str());
		//DEBUG("ColAssist             : " << STR_MOD->msk(str, DELIM, ColAssist).c_str());
		//DEBUG("ColAmm                : " << STR_MOD->msk(str, DELIM, ColAmm).c_str());
		//DEBUG("ColEsp                : " << STR_MOD->msk(str, DELIM, ColEsp).c_str());
//		//DEBUG("ColdaSostituire       : " << STR_MOD->msk(str, DELIM, ColdaSostituire).c_str());

		// nome
		tmpPlayer.Cognome = STR_MOD->msk(str, DELIM, ColCognome);

		// squadra
		tmpPlayer.Squadra = STR_MOD->msk(str, DELIM, ColSquadra);

		// goal e rigori
		if (STR_MOD->msk(str, DELIM, ColRuolo2) == "P") {
			tmpPlayer.Ruolo = 0;
			tmpPlayer.Ruolo2 = 0;
			tmpPlayer.GoalSubiti = fabs(
			atof(STR_MOD->msk(str, DELIM, ColGoalSubiti).c_str()));
			tmpPlayer.GoalFatti = 0;
			tmpPlayer.RigoreParato = fabs(
			atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
			tmpPlayer.RigoreSbagliato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo2) == "D") {
			tmpPlayer.Ruolo = 1;
			tmpPlayer.Ruolo2 = 1;
			tmpPlayer.GoalFatti = atof(
			STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 4.5;
			tmpPlayer.GoalSubiti = 0;
			tmpPlayer.RigoreSbagliato = fabs(
			atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			tmpPlayer.RigoreParato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo2) == "C") {
			tmpPlayer.Ruolo2 = 2;
			if (STR_MOD->msk(str, DELIM, ColRuolo) == "T") {
				tmpPlayer.Ruolo = 4;
				tmpPlayer.GoalFatti = atof(
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3.5;
				tmpPlayer.RigoreSbagliato = fabs(
				atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "C") {
				tmpPlayer.Ruolo = 2;
				tmpPlayer.GoalFatti = atof(
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 4;
				tmpPlayer.RigoreSbagliato = fabs(
				atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			} else {
				/*
				 * TODO
				 */
			}
			tmpPlayer.GoalSubiti = 0;
			tmpPlayer.RigoreParato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo2) == "A") {
			tmpPlayer.Ruolo2 = 3;
			if (STR_MOD->msk(str, DELIM, ColRuolo) == "T") {
				tmpPlayer.Ruolo = 4;
				tmpPlayer.GoalFatti = atof(
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3.5;
				tmpPlayer.RigoreSbagliato = fabs(
				atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "A") {
				tmpPlayer.Ruolo = 3;
				tmpPlayer.GoalFatti = atof(
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3;
				tmpPlayer.RigoreSbagliato = fabs(
				atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			} else {
				/*
				 * TODO
				 */
			}
			tmpPlayer.GoalSubiti = 0;
			tmpPlayer.RigoreParato = 0;
		}

		//DEBUG(str.c_str());
		//DEBUG("_" << STR_MOD->msk(str, DELIM, ColVotoGazzetta).c_str() << "_");
		//DEBUG("_" << STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta).c_str() << "_");

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

		//DEBUG("VotoGazzetta = _" << tmpPlayer.VotoGazzetta << "_");
		//DEBUG("FantaVotoGazzetta = _" << tmpPlayer.FantaVotoGazzetta << "_");

		// --> goal decisivi
		tmpPlayer.GoalDecVitt = atoi(
		STR_MOD->msk(str, DELIM, ColGoalDecVitt).c_str());
		tmpPlayer.GoalDecPar = atoi(
		STR_MOD->msk(str, DELIM, ColGoalDecPar).c_str());

		//DEBUG("GoalDecVitt = #" << tmpPlayer.GoalDecVitt << "#");
		//DEBUG("GoalDecPar = #" << tmpPlayer.GoalDecPar << "#");

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
		tmpPlayer.Autoreti = abs(atoi(STR_MOD->msk(str, DELIM, ColAutoreti).c_str()) / 2);
		tmpPlayer.Amm = abs(int(atof(STR_MOD->msk(str, DELIM, ColAmm).c_str()) / 0.5));
		tmpPlayer.Esp = abs(atoi(STR_MOD->msk(str, DELIM, ColEsp).c_str()));

		tmpPlayer.daSostituire = 0;

		for (size_t kk = 0; kk < 2; kk++) {
			for (size_t i = 0; i < Team[kk].size(); i++) {
				if (tmpPlayer.Cognome == Fanta::Team[kk].at(i).Cognome
						&& tmpPlayer.Ruolo2 == Fanta::Team[kk].at(i).Ruolo2) {
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
			unsigned int d_sub = p[j - 1]
					+ (s1[i - 1] == s2[j - 1] ? 0 : cost_sub);
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
		LOG(ERR, "Exception caught in orderByRuolo().");
		DEBUG("exception caught in orderByRuolo().");
	}

	try {
		this->fillWithNonHaGiocato();
	} catch (...) {
		LOG(ERR, "Exception caught in fillWithNonHaGiocato().");
		DEBUG("exception caught in fillWithNonHaGiocato().");
	}

	try {
		this->substitutions();
	} catch (...) {
		LOG(ERR, "Exception caught in substitutions().");
		DEBUG("exception caught in substitutions().");
	}

	try {
		this->calculateFantaVoto();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateFantaVoto().");
		DEBUG("exception caught in calculateFantaVoto().");
	}

	try {
		this->calculateDefenseMean();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateDefenseMean().");
		DEBUG("exception caught in calculateDefenseMean().");
	}

	try {
		this->calculateDefenseModifier();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateDefenseModifier().");
		DEBUG("exception caught in calculateDefenseModifier().");
	}

	try {
		this->calculateSfide();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateSfide().");
		DEBUG("exception caught in calculateSfide().");
	}

	try {
		this->calculateTotal();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateTotal().");
		DEBUG("exception caught in calculateTotal().");
	}

	try {
		this->calculateGoals();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateGoals().");
		DEBUG("exception caught in calculateGoals().");
	}

	try {
		this->calculateScorers();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateScorers().");
		DEBUG("exception caught in calculateScorers().");
	}

	return;
}
void Fanta::checkGiocatoSenzaVoto() {

	LOG(DBG, "<br/> ============================");
	LOG(DBG, " === Giocatori senza voto ===");
	LOG(DBG, " ============================<br/><br/>");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < this->Team[k].size(); j++) { // loop sui giocatori
			//	DEBUG( this->Team[k].at(j).Cognome.c_str());

			if ( this->Team[k].at(j).VotoGazzetta == -1 && (
					this->Team[k].at(j).Esp != 0 ||
					this->Team[k].at(j).Amm != 0 ||
					this->Team[k].at(j).Autoreti != 0 ||
					this->Team[k].at(j).Assist != 0 ||
					this->Team[k].at(j).GoalSubiti != 0 ||
					this->Team[k].at(j).GoalFatti != 0
			) ) { // se S.V. ma con bonus/malus

				if (this->Team[k].at(j).Ruolo2 == 0) { // se e' un portiere

					DEBUG("Giocato senza voto --> " << this->Team[k].at(j).Cognome.c_str() << " - portiere.");

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

				} else if (this->Team[k].at(j).Ruolo2 > 0) { //se non e' un portiere

					DEBUG("Giocato senza voto --> " << this->Team[k].at(j).Cognome.c_str() << " - giocatore di movimento.");

					LOG(
					DBG,
					" -> "
					+ QString::fromStdString(
							this->Team[k].at(j).Cognome) + " ("
					+ QString::fromStdString(
							this->Team[k].at(j).Squadra)
					+ ", giocatore di movimento) senza voto ma con bonus/malus. Fantavoto :  "
					+ QString::fromStdString(
							my::toString<float>(
									this->Team[k].at(j).FantaVotoGazzetta)));
				}

				this->Team[k].at(j).VotoGazzetta = 6.0;
				this->Team[k].at(j).FantaVotoGazzetta
				= this->Team[k].at(j).VotoGazzetta
				- this->Team[k].at(j).Esp - 0.5
				* this->Team[k].at(j).Amm - 2
				* this->Team[k].at(j).Autoreti
				+ this->Team[k].at(j).Assist;

				/*
				 * goal
				 */
				if (this->Team[k].at(j).Ruolo2 == 0) { // P

					this->Team[k].at(j).FantaVotoGazzetta -= this->Team[k].at(j).GoalSubiti;// subiti x un portiere !

				} else if (this->Team[k].at(j).Ruolo2 == 1) { // D

					this->Team[k].at(j).FantaVotoGazzetta += 4.5 * this->Team[k].at(j).GoalFatti;

				} else if (this->Team[k].at(j).Ruolo2 == 2) { // C

					if (this->Team[k].at(j).Ruolo == 4) { // T

						this->Team[k].at(j).FantaVotoGazzetta += 3.5 * this->Team[k].at(j).GoalFatti;

					} else if (this->Team[k].at(j).Ruolo == 2) { // C

						this->Team[k].at(j).FantaVotoGazzetta += 4.0 * this->Team[k].at(j).GoalFatti;

					} else {
						/*
						 * TODO
						 */
					}
				} else if (this->Team[k].at(j).Ruolo2 == 3) { // A

					if (this->Team[k].at(j).Ruolo == 4) { // T

						this->Team[k].at(j).FantaVotoGazzetta += 3.5 * this->Team[k].at(j).GoalFatti;

					} else if (this->Team[k].at(j).Ruolo == 3) { // A

						this->Team[k].at(j).FantaVotoGazzetta += 3.0 * this->Team[k].at(j).GoalFatti;

					} else {
						/*
						 * TODO
						 */
					}
				}

				//DEBUG(this->Team[k].at(j).Cognome << ". VotoGazzetta = _" << this->Team[k].at(j).VotoGazzetta << "_");
				//DEBUG(this->Team[k].at(j).Cognome << ". FantaVotoGazzetta = _" << this->Team[k].at(j).FantaVotoGazzetta << "_");
				continue;

			} else if ( this->Team[k].at(j).VotoGazzetta == -1 ) { // se S.V. ma senza bonus/malus

				QString answer;

				try {

					answer
					= this->questionMessage(
					QString::fromStdString(
							this->Team[k].at(j).Cognome));

					DEBUG(this->Team[k].at(j).Cognome.c_str() << " ha giocato piu' di 25 minuti ? " << answer.toStdString().c_str());

				} catch (...) {
					LOG(FATAL,
					"Exception caught in Fanta::checkGiocatoSenzaVoto()!");
				}

				if (answer == "Yes") { // giocato piu' di 25'
					DEBUG(this->Team[k].at(j).Cognome << ". VotoGazzetta = _" << this->Team[k].at(j).VotoGazzetta << "_");
					DEBUG(this->Team[k].at(j).Cognome << ". FantaVotoGazzetta = _" << this->Team[k].at(j).FantaVotoGazzetta << "_");

					if ( this->Team[k].at(j).Ruolo2 == 0 ) { // P
						this->Team[k].at(j).VotoGazzetta = 6.0;
						this->Team[k].at(j).FantaVotoGazzetta = 6.0;
					} else {
						this->Team[k].at(j).VotoGazzetta = 5.5;
						this->Team[k].at(j).FantaVotoGazzetta = 5.5;
					}

					LOG(DBG,
					" -> "
					+ QString::fromStdString(this->Team[k].at(j).Cognome)
					+ " ("
					+ QString::fromStdString(this->Team[k].at(j).Squadra)
					+ ") ha giocato 25'.");

				} else { // da sostituire

					DEBUG(this->Team[k].at(j).Cognome << " da sostituire.");

					this->Team[k].at(j).daSostituire = 1;// viene marcato per l'eliminazione

					LOG(DBG,
					" -> "
					+ QString::fromStdString(this->Team[k].at(j).Cognome)
					+ " ("
					+ QString::fromStdString(this->Team[k].at(j).Squadra)
					+ ") non ha giocato 25' : verra' effettuata una sostituzione.");
				}
			} // if ... else if ...
		} // loop giocatori
	} // loop squadre
}
QString Fanta::questionMessage(QString playerName) {

	DEBUG("");

	QString title = "Ha giocato almeno 25' ?";

	QString message =
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
	LOG(DBG, " === Giocatori che non hanno giocato ===");
	LOG(DBG, " =======================================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DBG,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)) + " :");

		for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
		{
			if (this->Team[k].at(j).VotoGazzetta == 0) {
				if (this->Team[k].at(j).FantaVotoGazzetta == 0) {

					this->Team[k].at(j).daSostituire = 1; // viene marcato per l'eliminazione

					LOG(DBG,
					"      "
					+ QString::fromStdString(this->Team[k].at(j).Cognome)
					+ " ("
					+ QString::fromStdString(this->Team[k].at(j).Squadra)
					+ ").");
				} else {
					// ma ha ricevuto voto dalla Gazzetta (caso di partite sospese ??? )
					this->Team[k].at(j).VotoGazzetta
					= this->Team[k].at(j).FantaVotoGazzetta;
					LOG(DBG,
					"      "
					+ QString::fromStdString(this->Team[k].at(j).Cognome)
					+ " ("
					+ QString::fromStdString(this->Team[k].at(j).Squadra)
					+ ") non ha giocato, ma ha ricevuto voto("
					+ QString::fromStdString(my::toString<float>(this->Team[k].at(j).FantaVotoGazzetta))
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
		for (unsigned int k = 0; k < 2; k++) // loop sulle squadre
				{
			try {
				for (signed int i = 0; i < 4; i++) // loop sui ruoli
						{

					for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
							{
						if (this->Team[k].at(j).Ruolo2 == i
								&& this->Fanta::teamOrderedByRuolo[k][i].size()
										< this->rosa[i]) {
							Fanta::teamOrderedByRuolo[k][i].push_back(
									this->Team[k].at(j));
							//DEBUG(i << " " << this->Team[k].at(j).Cognome.c_str());
						}
					}
				}
			} catch (...) {
				LOG(FATAL,
				"Exception caught in ruoli loop.");
			}
		}

		//for (size_t k = 0; k < 2; k++) // squadra
		//{
		//	for (size_t i = 0; i < 4; i++) // ruolo
		//	{
		//		for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size();
		//		j++) {
		//			DEBUG(this->getTeamName(k).c_str() << " : " <<
		//			this->teamOrderedByRuolo[k][i].at(j).Ruolo2 << " " <<
		//			this->teamOrderedByRuolo[k][i].at(j).Cognome.c_str() << ".");
		//		}
		//	}
		//}

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
			for (size_t j = Fanta::teamOrderedByRuolo[k][i].size(); j < rosa[i];
					j++) {
				Fanta::teamOrderedByRuolo[k][i].push_back(Fanta::NonHaGiocato);
				DEBUG("Squadra " << this->getTeamName(k).c_str() << " : aggiunto un Fanta::NonHaGiocato");
				//LOG(DBG, \
						QString::fromStdString(this->getTeamName(k)) \
								+ " : aggiunto un Fanta::NonHaGiocato");
			}
		}
	}
}

void Fanta::sendNGToBack() {

	DEBUG("");

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
					if (
							Fanta::teamOrderedByRuolo[k][i].at(t).Cognome == "---" && 	// l'AND e' per evitare che scambi di posto
							Fanta::teamOrderedByRuolo[k][i].at(t + 1).Cognome != "---"	// due giocatori che non hanno giocato
									)
						swap(Fanta::teamOrderedByRuolo[k][i].at(t),
								Fanta::teamOrderedByRuolo[k][i].at(t + 1));
				}
			}
		}
	}

	return;
}

/*
 * moduli raggiungibili
 *
 *
 *  modPos : 0
 *  5-4-1
 *
 *  modulo 0 (1-5-4-1) raggiungibile? : 0
 *  modulo 1 (1-4-5-1) raggiungibile? : 1
 *  modulo 2 (1-5-3-2) raggiungibile? : 1
 *  modulo 3 (1-4-4-2) raggiungibile? : 1
 *  modulo 4 (1-3-5-2) raggiungibile? : 0
 *  modulo 5 (1-4-3-3) raggiungibile? : 0
 *  modulo 6 (1-3-4-3) raggiungibile? : 0
 *
 *
 *  modPos : 1
 *  4-5-1
 *
 *  modulo 0 (1-5-4-1) raggiungibile? : 1
 *  modulo 1 (1-4-5-1) raggiungibile? : 0
 *  modulo 2 (1-5-3-2) raggiungibile? : 0
 *  modulo 3 (1-4-4-2) raggiungibile? : 1
 *  modulo 4 (1-3-5-2) raggiungibile? : 1
 *  modulo 5 (1-4-3-3) raggiungibile? : 0
 *  modulo 6 (1-3-4-3) raggiungibile? : 0
 *
 *
 *  modPos : 2
 *  5-3-2
 *
 *  modulo 0 (1-5-4-1) raggiungibile? : 1
 *  modulo 1 (1-4-5-1) raggiungibile? : 0
 *  modulo 2 (1-5-3-2) raggiungibile? : 0
 *  modulo 3 (1-4-4-2) raggiungibile? : 1
 *  modulo 4 (1-3-5-2) raggiungibile? : 0
 *  modulo 5 (1-4-3-3) raggiungibile? : 1
 *  modulo 6 (1-3-4-3) raggiungibile? : 0
 *
 *
 *  modPos : 3
 *  4-4-2
 *
 *  modulo 0 (1-5-4-1) raggiungibile? : 1
 *  modulo 1 (1-4-5-1) raggiungibile? : 1
 *  modulo 2 (1-5-3-2) raggiungibile? : 1
 *  modulo 3 (1-4-4-2) raggiungibile? : 0
 *  modulo 4 (1-3-5-2) raggiungibile? : 1
 *  modulo 5 (1-4-3-3) raggiungibile? : 1
 *  modulo 6 (1-3-4-3) raggiungibile? : 1
 *
 *
 *  modPos : 4
 *  3-5-2
 *
 *  modulo 0 (1-5-4-1) raggiungibile? : 0
 *  modulo 1 (1-4-5-1) raggiungibile? : 1
 *  modulo 2 (1-5-3-2) raggiungibile? : 0
 *  modulo 3 (1-4-4-2) raggiungibile? : 1
 *  modulo 4 (1-3-5-2) raggiungibile? : 0
 *  modulo 5 (1-4-3-3) raggiungibile? : 0
 *  modulo 6 (1-3-4-3) raggiungibile? : 1
 *
 *
 *  modPos : 5
 *  4-3-3
 *
 *  modulo 0 (1-5-4-1) raggiungibile? : 0
 *  modulo 1 (1-4-5-1) raggiungibile? : 0
 *  modulo 2 (1-5-3-2) raggiungibile? : 1
 *  modulo 3 (1-4-4-2) raggiungibile? : 1
 *  modulo 4 (1-3-5-2) raggiungibile? : 0
 *  modulo 5 (1-4-3-3) raggiungibile? : 0
 *  modulo 6 (1-3-4-3) raggiungibile? : 1
 *
 *
 *  modPos : 6
 *  3-4-3
 *
 *  modulo 0 (1-5-4-1) raggiungibile? : 0
 *  modulo 1 (1-4-5-1) raggiungibile? : 0
 *  modulo 2 (1-5-3-2) raggiungibile? : 0
 *  modulo 3 (1-4-4-2) raggiungibile? : 1
 *  modulo 4 (1-3-5-2) raggiungibile? : 1
 *  modulo 5 (1-4-3-3) raggiungibile? : 1
 *  modulo 6 (1-3-4-3) raggiungibile? : 0
 */

void Fanta::calculateMetrics(unsigned int k) {

	DEBUG("");

	/*
	 * esplora i moduli possibili
	 */
	for (size_t j = 0; j < 7; j++) {

		/*
		 * in campo, distanza e disponibili per tutti i moduli possibili
		 */
		for (size_t i = 0; i < 4; i++) { // ruolo

			for (size_t m = Fanta::moduli[j][i];
					m < Fanta::modulo[k][i]; m++) {

				if (Fanta::teamOrderedByRuolo[k][i].at(m).Cognome
						!= "---") {
					Fanta::originalsOutModuli[j][i]++;
				}
			}

			for (size_t m = 0; m < Fanta::moduli[j][i]; m++) {

				if (Fanta::teamOrderedByRuolo[k][i].at(m).Cognome
						!= "---")
					Fanta::inCampoModuli[j][i]++;
			}

			for (size_t m = Fanta::moduli[j][i]; m < rosa[i];
					m++) {
				if (Fanta::teamOrderedByRuolo[k][i].at(m).Cognome
						!= "---")
					Fanta::disponibiliModuli[j][i]++;
			}

			Fanta::distanzaModuli[j][i] = Fanta::moduli[j][i]
					- Fanta::inCampoModuli[j][i];
		}

		Fanta::distanzaTotaleModuli[j] =
				Fanta::distanzaModuli[j][0]
						+ Fanta::distanzaModuli[j][1]
						+ Fanta::distanzaModuli[j][2]
						+ Fanta::distanzaModuli[j][3];

		Fanta::originalsOutTotaleModuli[j] =
				Fanta::originalsOutModuli[j][0]
						+ Fanta::originalsOutModuli[j][1]
						+ Fanta::originalsOutModuli[j][2]
						+ Fanta::originalsOutModuli[j][3];

			DEBUG("######## START ####################");
			DEBUG("         modulo " << j << " : " << Fanta::moduli[j][0] << "-" << Fanta::moduli[j][1] << "-" << Fanta::moduli[j][2] << "-" << Fanta::moduli[j][3]);
			DEBUG("       in campo " << j << " : " << Fanta::inCampoModuli[j][0] << "-" << Fanta::inCampoModuli[j][1] << "-" << Fanta::inCampoModuli[j][2] << "-" << Fanta::inCampoModuli[j][3]);
			DEBUG("  originals out " << j << " : " << Fanta::originalsOutModuli[j][0] << "-" << Fanta::originalsOutModuli[j][1] << "-" << Fanta::originalsOutModuli[j][2] << "-" << Fanta::originalsOutModuli[j][3]);
			DEBUG("       distanza " << j << " : " << Fanta::distanzaModuli[j][0] << "-" << Fanta::distanzaModuli[j][1] << "-" << Fanta::distanzaModuli[j][2] << "-" << Fanta::distanzaModuli[j][3]);
			DEBUG("    disponibili " << j << " : " << Fanta::disponibiliModuli[j][0] << "-" << Fanta::disponibiliModuli[j][1] << "-" << Fanta::disponibiliModuli[j][2] << "-" << Fanta::disponibiliModuli[j][3]);
			DEBUG("               distanzaTotale : " << Fanta::distanzaTotaleModuli[j]);
			DEBUG("         originals out totale : " << Fanta::originalsOutTotaleModuli[j]);
	}

	return;
}

void Fanta::initializeMetrics() {

	DEBUG("");

	/*
	 * inizializzazione variabili
	 */
	for (size_t j = 0; j < 7; j++) {
		for (size_t i = 0; i < 4; i++) {
			Fanta::inCampoModuli[j][i] = 0;
			Fanta::distanzaModuli[j][i] = 0;
			Fanta::disponibiliModuli[j][i] = 0;
			Fanta::originalsOutModuli[j][i] = 0;
		}
		Fanta::distanzaTotaleModuli[j] = 0;
	}
	/***/
}

bool Fanta::nonAbbastanzaDisponibili(unsigned int j) {
	DEBUG("");

	return ( static_cast<signed int>(Fanta::disponibiliModuli[j][0]) < Fanta::distanzaModuli[j][0]
	|| static_cast<signed int>(Fanta::disponibiliModuli[j][1]) < Fanta::distanzaModuli[j][1]
	|| static_cast<signed int>(Fanta::disponibiliModuli[j][2]) < Fanta::distanzaModuli[j][2]
	|| static_cast<signed int>(Fanta::disponibiliModuli[j][3]) < Fanta::distanzaModuli[j][3] );
}

signed int Fanta::findModuloAttivo(unsigned int k) {
	DEBUG("");

	signed int moduloAttivo = -1;
	/*
	 * posizione del modulo attuale nell'array moduli[7]
	 */
	for (size_t j = 0; j < 7; j++) {
		if (Fanta::moduli[j][0] == Fanta::modulo[k][0]
				&& Fanta::moduli[j][1] == Fanta::modulo[k][1]
				&& Fanta::moduli[j][2] == Fanta::modulo[k][2]
				&& Fanta::moduli[j][3] == Fanta::modulo[k][3]) {
			moduloAttivo = j;
			break;
		}
	}
	/***/

	return moduloAttivo;
}

void Fanta::substitutions() {

	DEBUG("");

	unsigned int ordineSostituzioni[] = { 0, 3, 2, 1, 3, 2, 1, 3, 2, 1 };

	for (size_t k = 0; k < 2; k++) { // squadra

		for (size_t i = 0; i < 4; i++) { // ruolo

			for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size(); j++) { // loop sui tutti i giocatori

				if (this->teamOrderedByRuolo[k][i].at(j).daSostituire == 1) {
					Fanta::player tmpPlayer = Fanta::NonHaGiocato;
					tmpPlayer.Cognome_Sost = this->teamOrderedByRuolo[k][i].at(
							j).Cognome;
					tmpPlayer.Squadra_Sost = this->teamOrderedByRuolo[k][i].at(
							j).Squadra;
					this->teamOrderedByRuolo[k][i].at(j) = tmpPlayer;
				}
			}
		}
	}

	/*
	 * determina cosa c'è e cosa serve
	 */
	for (size_t k = 0; k < 2; k++) // squadra
			{

		DEBUG(" squadra : " << this->getTeamName(k));

		for (size_t i = 0; i < 4; i++) { // ruolo
			for (size_t j = 0; j < modulo[k][i]; j++) {

				if (Fanta::teamOrderedByRuolo[k][i].at(j).Cognome != "---")
					Fanta::inCampo[k][i]++;
			}

			for (size_t j = modulo[k][i]; j < rosa[i]; j++) {

				if (Fanta::teamOrderedByRuolo[k][i].at(j).Cognome != "---")
					Fanta::disponibili[k][i]++;
			}

			Fanta::distanza[k][i] = Fanta::modulo[k][i] - Fanta::inCampo[k][i];
		}

		DEBUG("         modulo " << k << " : " << Fanta::modulo[k][0] << "-" << Fanta::modulo[k][1] << "-" << Fanta::modulo[k][2] << "-" << Fanta::modulo[k][3]);
		DEBUG("       in campo " << k << " : " << Fanta::inCampo[k][0] << "-" << Fanta::inCampo[k][1] << "-" << Fanta::inCampo[k][2] << "-" << Fanta::inCampo[k][3]);
		DEBUG("       distanza " << k << " : " << Fanta::distanza[k][0] << "-" << Fanta::distanza[k][1] << "-" << Fanta::distanza[k][2] << "-" << Fanta::distanza[k][3]);
		DEBUG("    disponibili " << k << " : " << Fanta::disponibili[k][0] << "-" << Fanta::disponibili[k][1] << "-" << Fanta::disponibili[k][2] << "-" << Fanta::disponibili[k][3]);

		/*
		 * score dei moduli
		 */
		bool cambioModulo = false;

		unsigned int distanza = 0;
		for (size_t i = 0; i < 4; i++) { // ruolo
			distanza += Fanta::distanza[k][i];
		} DEBUG("distanza totale " << k << " : " << distanza);

		signed int moduloAttivo, newModuloAttivo;
		moduloAttivo = newModuloAttivo = findModuloAttivo(k);
		DEBUG("         posizione nell'array : " << moduloAttivo);

		if (distanza == 0) {
			continue;
		} else {

			if (distanza > 3) {
				cambioModulo = true;
			} else {
				for (size_t i = 0; i < 4; i++) { // ruolo
					if (Fanta::disponibili[k][i] < Fanta::distanza[k][i]) {
						cambioModulo = true;
					}
				}
			}

			bool foundNewModule = false;
			if (cambioModulo) {
				DEBUG("cambio modulo");

				initializeMetrics();
				calculateMetrics(k);

				/*
				 * check per modulo che :
				 * 1 - abbia una distanza minore o uguale a tre (permetta quindi di giocare in 11)
				 * 2 - abbia i giocatori disponibili per effettuare le sostituziooni
				 * 3 - conservi i titolari
				 */
				for (size_t j = 0; j < 7; j++) {

				if (Fanta::distanzaTotaleModuli[j] > 3				// condizione 1
				|| Fanta::nonAbbastanzaDisponibili(j) == true		// condizione 2
						|| Fanta::originalsOutTotaleModuli[j] > 0) {// condizione 3
					moduloPossibile[j] = false;
				}

					DEBUG(
							"modulo " << j << " (" << labelModuli[j].c_str() << ") possibile? : " << moduloPossibile[j]);
				}
				/***/

				/*
				 * Ricerca nuovo modulo
				 */
				newModuloAttivo = moduloAttivo; // modulo originario, se non si trova nulla rimane quello

				for (unsigned int j = moduloAttivo; j < 7; j++) {

					DEBUG("primo loop - j = " << j);

					if (moduloPossibile[j]) {
						DEBUG(
								"nuovo modulo " << k << " : " << labelModuli[j].c_str());
						foundNewModule = true;
						newModuloAttivo = j;
						DEBUG("before first break");
						break;
					}
				}

				if (!foundNewModule) {

					for (signed int j = moduloAttivo; j >= 0; j--) {

						DEBUG("secondo loop - j = " << j);

						if (moduloPossibile[j]) {
							DEBUG(
									"nuovo modulo " << k << " : " << labelModuli[j].c_str());
							foundNewModule = true;
							newModuloAttivo = j;
							DEBUG("before second break");
							break;
						}
					}
				}
				/***/

				/*
				 * Imposta nuovo modulo come modulo attuale
				 */
				if (!foundNewModule) {
					DEBUG("Non trovato nuovo modulo compatibile!");
				} else {

					for (size_t i = 0; i < 4; i++) // ruolo
							{
						/*
						 * salva stringa di sostituzione per cambio modulo
						 */
						if (Fanta::moduli[newModuloAttivo][i]
								> Fanta::modulo[k][i]) { // solo per ruolo dove aumenta il numero di giocatori

							for (unsigned int m = Fanta::modulo[k][i];
									m < Fanta::moduli[newModuloAttivo][i];
									m++) {

								QString sub =
										QString::fromStdString(
												Fanta::teamOrderedByRuolo[k][i].at(m).Cognome)
												+ " ("
												+ QString::fromStdString(
														Fanta::teamOrderedByRuolo[k][i].at(m).Squadra)
												+ ") per cambio di modulo.";

								Fanta::subsForModuleChange[k].push_back(
										sub);
							}
						}
					}

					Fanta::newModuleString[k].push_back(
							"Nuovo modulo "
									+ QString::number(
											Fanta::moduli[newModuloAttivo][1])
									+ "-"
									+ QString::number(
											Fanta::moduli[newModuloAttivo][2])
									+ "-"
									+ QString::number(
											Fanta::moduli[newModuloAttivo][3]));

					Fanta::modulo[k][0] =
							Fanta::moduli[newModuloAttivo][0];
					Fanta::modulo[k][1] =
							Fanta::moduli[newModuloAttivo][1];
					Fanta::modulo[k][2] =
							Fanta::moduli[newModuloAttivo][2];
					Fanta::modulo[k][3] =
							Fanta::moduli[newModuloAttivo][3];

					distanza = distanzaTotaleModuli[newModuloAttivo];
					Fanta::distanza[k][0] =
							Fanta::distanzaModuli[newModuloAttivo][0];
					Fanta::distanza[k][1] =
							Fanta::distanzaModuli[newModuloAttivo][1];
					Fanta::distanza[k][2] =
							Fanta::distanzaModuli[newModuloAttivo][2];
					Fanta::distanza[k][3] =
							Fanta::distanzaModuli[newModuloAttivo][3];
				}

			}

			/***/

			//for (size_t j = 0; j < 7; j++) {
			//	DEBUG("       distanza " << j << " : " << Fanta::distanzaModuli[j][0] << "-" << Fanta::distanzaModuli[j][1] << "-" << Fanta::distanzaModuli[j][2] << "-" << Fanta::distanzaModuli[j][3]);
			//}
			//
			//for (size_t j = 0; j < 7; j++) {
			//	DEBUG("       distanza " << j << " : " << Fanta::distanzaModuli[j][ordineSostituzioni[0]] << "-" << Fanta::distanzaModuli[j][ordineSostituzioni[1]] << "-" << Fanta::distanzaModuli[j][ordineSostituzioni[2]] << "-" << Fanta::distanzaModuli[j][ordineSostituzioni[3]]);
			//}

			while (distanza > 0) {

				unsigned int index = 0;
				for (size_t i = 0; i < 10; i++) {

					if (Fanta::distanza[k][ordineSostituzioni[i]] > 0) {
						Fanta::ruoloDaSostituire[k][index] =
								ordineSostituzioni[i];
						index++;
						Fanta::distanza[k][ordineSostituzioni[i]]--;
						distanza--;
					}

					if (distanza == 0)
						break;
				}
			}

			DEBUG("ruoloDaSostituire[" << k << "][0] : " << Fanta::ruoloDaSostituire[k][0]);DEBUG("ruoloDaSostituire[" << k << "][1] : " << Fanta::ruoloDaSostituire[k][1]);DEBUG("ruoloDaSostituire[" << k << "][2] : " << Fanta::ruoloDaSostituire[k][2]);

		}
	}

	sendNGToBack(); /* prima delle sostituzioni da avvenire lo "scivolamento"
					/* dei giocatori senza voto alla fine dei titolari del modulo scelto

	//for (size_t k = 0; k < 2; k++) // squadra
	//		{
	//	for (size_t i = 0; i < 4; i++) // ruolo
	//			{
	//		for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size();
	//				j++) {
	//			DEBUG(this->getTeamName(k).c_str() << " : " <<
	//					this->teamOrderedByRuolo[k][i].at(j).Ruolo2 << " " <<
	//					this->teamOrderedByRuolo[k][i].at(j).Cognome.c_str() << ".");
	//		}
	//	}
	//}
    //
	//DEBUG("#########################################");

	/*
	 * SOSTITUZIONI
	 */
	for (size_t k = 0; k < 2; k++) {
		for (size_t i = 0; i < 10; i++) { // loop sulla seconda dimensione di Fanta::ruoloDaSostituire[k][i]

			if (Fanta::ruoloDaSostituire[k][i] == -1)
				continue;

			unsigned int w = Fanta::modulo[k][Fanta::ruoloDaSostituire[k][i]];

			for (size_t j = 0; j < w; j++) // loop sui giocatori
					{
				if (Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
						j).Cognome == "---" && Fanta::sostituzioni[k] < 3) {

					for (size_t x = w;
							x
									< Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].size();
							x++) {
						if (Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
								x).Cognome != "---") {
							Fanta::sostituzioni[k]++;

							QString sub =
									"      "
											+ QString::fromStdString(
													Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
															x).Cognome) + " ("
											+ QString::fromStdString(
													Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
															x).Squadra)
											+ ") al posto di "
											+ QString::fromStdString(
													Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
															j).Cognome_Sost)
											+ " ("
											+ QString::fromStdString(
													Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
															j).Squadra_Sost)
											+ ").";

							Fanta::subs[k].push_back(sub);

							DEBUG(k << " : " << Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(x).Cognome
									<< " ("
									<< Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(x).Squadra
									<< ") al posto di "
									<< Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(j).Cognome_Sost
									<< " ("
									<< Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(j).Squadra_Sost
									<< ").");

							swap(
									Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
											x),
									Fanta::teamOrderedByRuolo[k][Fanta::ruoloDaSostituire[k][i]].at(
											j));

							goto label; // serve per poter uscire da due loop contemporaneamente
						}
					}
				}
			}
			label: ; // solo una sostituzione per ruolo ( per volta )
		}
		//}
	}

	/*
	 * LOGGING
	 */
	LOG(DBG, "<br/> =====================");
	LOG(DBG, " === Cambio modulo ===");
	LOG(DBG, " =====================");

	for (size_t k = 0; k < 2; k++) {
		if (Fanta::newModuleString[k].size() == 1) {
			LOG(DBG,
			"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");
			LOG(DBG, newModuleString[k].front());
		} else if (Fanta::newModuleString[k].size() > 1) {

			if (Fanta::newModuleString[k].size() > 1) {
				LOG(DBG,
				"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");

				LOG(WARN, "Trovato più di un muovo modulo!");

				for (size_t j = 0; j < Fanta::newModuleString[k].size(); j++) {
					LOG(WARN, newModuleString[k].at(j));
				}

			}
		} else {
			/*
			 * non necessario
			 */
		}
	}

	LOG(DBG, "<br/> ====================");
	LOG(DBG, " === Sostituzioni ===");
	LOG(DBG, " ====================");

	for (size_t k = 0; k < 2; k++) {
		if (Fanta::subsForModuleChange[k].size() > 0
				|| Fanta::subs[k].size() > 0)
			LOG(DBG,
			"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");

			for (size_t j = 0; j < Fanta::subsForModuleChange[k].size(); j++) {
				LOG(DBG, subsForModuleChange[k].at(j));
			}
			for (size_t j = 0; j < Fanta::subs[k].size(); j++) {
				LOG(DBG, subs[k].at(j));
			}
		}

	//for (size_t k = 0; k < 2; k++) // squadra
	//		{
	//	for (size_t i = 0; i < 4; i++) // ruolo
	//			{
	//		for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size();
	//				j++) {
	//			DEBUG(this->getTeamName(k).c_str() << " : " <<
	//					this->teamOrderedByRuolo[k][i].at(j).Ruolo2 << " " <<
	//					this->teamOrderedByRuolo[k][i].at(j).Cognome.c_str() << ".");
	//		}
	//	}
	//}
    //
	//DEBUG("#########################################");

	for (size_t k = 0; k < 2; k++) // squadra
			{
		for (size_t i = 0; i < 4; i++) // ruolo
				{
			Fanta::teamOrderedByRuolo[k][i].resize(Fanta::modulo[k][i]);
		}
	}

	//for (size_t k = 0; k < 2; k++) // squadra
	//		{
	//	for (size_t i = 0; i < 4; i++) // ruolo
	//			{
	//		for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size();
	//				j++) {
	//			DEBUG(this->getTeamName(k).c_str() << " : " <<
	//					this->teamOrderedByRuolo[k][i].at(j).Ruolo2 << " " <<
	//					this->teamOrderedByRuolo[k][i].at(j).Cognome.c_str() << ".");
	//		}
	//	}
	//}

}
void Fanta::calculateFantaVoto() {

	LOG(DBG, "<br/> =================");
	LOG(DBG, " === Fantavoti ===");
	LOG(DBG, " =================");
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

				(this->teamOrderedByRuolo[k][i].at(j).Cognome.size() > longerName)
				?
				longerName=this->teamOrderedByRuolo[k][i].at(j).Cognome.size()
				:
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
				LOG(DBG, "      ["
				+ STR_MOD->rightQString(my::toQString<int>(counter++), 2)
				+ "] "
				+ QString::fromStdString(STR_MOD->leftString(this->teamOrderedByRuolo[k][i].at(j).Cognome, longerName))
				+ " : "
				+ my::toQString<float>(this->teamOrderedByRuolo[k][i].at(j).FantaVoto));

				j++;
			}
		}
	}

}
void Fanta::calculateDefenseMean() {

	LOG(DBG, "<br/> ====================");
	LOG(DBG, " === Media difesa ===");
	LOG(DBG, " ====================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DBG,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)) + " :");

		size_t j = 0;
		while (j < Fanta::modulo[k][1]) {
			if (Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta != 0) {
				Fanta::defenseMean[k] +=
				Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta;
				Fanta::defenders[k]++;

				LOG(DBG, "      ["
				+ my::toQString<size_t>(j + 1)
				+ "] "
				+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][1].at(j).Cognome)
				+ " ("
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta)
				+ ")");
			}
			j++;
		}
		Fanta::defenseMean[k] /= Fanta::defenders[k];

		LOG(DBG, "      media = "
		+ my::toQString<double>(Fanta::defenseMean[k]));
	}
}
void Fanta::calculateDefenseModifier() {

	LOG(DBG, "<br/> =================================");
	LOG(DBG, " === Modificatore della difesa ===");
	LOG(DBG, " =================================");
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
		LOG(DBG, "<br> -> "
		+ QString::fromStdString(this->getTeamName(k))
		+ "<br>      modificatore : "
		+ my::toQString<signed int>(Fanta::modifier[k]));
	}
}
void Fanta::calculateSfide() {

	LOG(DBG, "<br/> =====================");
	LOG(DBG, " === Calcolo sfide ===");
	LOG(DBG, " =====================<br>");
	DEBUG("");

	QString winner, loser, team;
	int longerName = max(this->getTeamName(0).size(), this->getTeamName(1).size());

	QString def0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][1].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(0))
	+ ")";

	QString cen0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][2].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(0))
	+ ")";

	QString att0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][3].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(0))
	+ ")";

	QString def1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][1].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(1))
	+ ")";

	QString cen1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][2].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(1))
	+ ")";

	QString att1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][3].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(1))
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

	LOG (DBG, "    [1] "
	+ team
	+ " : "
	+ winner
	+ " - "
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

	LOG (DBG, "    [2] "
	+ team
	+ " : "
	+ winner
	+ " - "
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

	LOG (DBG, "    [3] "
	+ team
	+ " : "
	+ winner
	+ " - "
	+ loser);

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DBG,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));
		LOG(DBG,
		+ "      sfide = " + my::toQString<unsigned int>(Fanta::sfide[k]));
	}
}
void Fanta::calculateTotal() {

	LOG(DBG, "<br/> =========================");
	LOG(DBG, " === Calcolo punteggio ===");
	LOG(DBG, " =========================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		QString message;

		LOG(DBG,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));

		Fanta::Total[k] += Fanta::atHome[k];
		message = "      "
		+ my::toQString<double>(Fanta::Total[k])
		+ " ("
		+ my::toQString<unsigned int>(Fanta::atHome[k])
		+ ", in casa)";

		LOG(DBG, message);

		Fanta::Total[k] += Fanta::modifier[k];
		message = "      "
		+ my::toQString<double>(Fanta::Total[k])
		+ " ("
		+ my::toQString<signed int>(Fanta::modifier[k])
		+ ", modificatore difesa)";

		LOG(DBG, message);

		Fanta::Total[k] += Fanta::sfide[k];
		message = "      "
		+ my::toQString<double>(Fanta::Total[k])
		+ " ("
		+ my::toQString<unsigned int>(Fanta::sfide[k])
		+ ", sfide)";

		LOG(DBG, message);

		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::Total[k]
				+= Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto;

				message = "      "
				+ my::toQString<double>(Fanta::Total[k])
				+ " ("
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto)
				+ ", "
				+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][i].at(j).Cognome)
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
	LOG(DBG, " === Calcolo goals ===");
	LOG(DBG, " =====================");
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

		LOG(DBG,
		"<br>      Entrambe le due squadre hanno totalizzato meno di 66 punti");

		for (size_t k = 0; k < 2; k++) {
			LOG(DBG, "      "
			+ STR_MOD->leftQString(QString::fromStdString(this->getTeamName(k)), FANTA->longerNameLength)
			+ " : "
			+ my::toQString<double>(Fanta::Total[k])
			+ " --> "
			+ my::toQString<signed int>(Fanta::goals[k])
			+ " goals");
		}
	}

	if (Fanta::goals[0] < 0 || Fanta::goals[1] < 0) {

		LOG(DBG, "");
		for (size_t k = 0; k < 2; k++) {
			if (Fanta::goals[k] < 0) {
				LOG(DBG,
				"      "
				+ STR_MOD->leftQString(QString::fromStdString(this->getTeamName(k)), FANTA->longerNameLength)
				+ " ha totalizzato un numero negativo di goals ("
				+ my::toQString<signed int>(Fanta::goals[k]) + " --> 0)");

				Fanta::goals[k] = 0;

			}
		}
	}

	for (size_t k = 0; k < 2; k++) {
		LOG(DBG, "<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));
		LOG(DBG, "      goals : "
		+ my::toQString<signed int>(Fanta::goals[k]));
	}

}
void Fanta::calculateScorers() {

	LOG(DBG, "<br/> =================");
	LOG(DBG, " === Marcatori ===");
	LOG(DBG, " =================");
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

		LOG(DBG,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));

		if (Fanta::goals[k] == 0) {
			LOG(DBG,
			"      ---");
			continue;
		}

		do {
			Fanta::bSort(tmpVector[k]);
			Fanta::scorers[k].push_back(tmpVector[k].at(0).Cognome);

			LOG(DBG,
			"      "
			+ QString::fromStdString(tmpVector[k].at(0).Cognome)
			+ " (" + my::toQString<float>(tmpVector[k].at(0).FantaVoto)
			+ ")");

			tmpVector[k].at(0).FantaVoto -= 3.0;
		}while (Fanta::scorers[k].size() < Fanta::goals[k]);
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
				else if (vect.at(i).VotoGazzetta
						== vect.at(i + 1).VotoGazzetta) {
					if (vect.at(i).Ruolo2 < vect.at(i + 1).Ruolo2) // poi per Ruolo
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

	QString area =
			"<p> |                              |__________________|                              |</p>";

	QString area_sotto =
			area
					+ "<p> |                                      \\__/                                      |</p>"
					+ bordi;

	QString area_sopra =
			"<p> |                                       __                                       |</p><p> |                               _______/__\\_______                               |</p><p> |                              |                  |                              |</p>";

	QString separatore =
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
					tmpString += QString::fromStdString(STR_MOD->centerString(
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
					tmpString += QString::fromStdString(STR_MOD->centerString(
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
