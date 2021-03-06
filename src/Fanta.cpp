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
#include "RinviateDialog.h"

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

	Fanta::rinviate.clear();

	Fanta::ordineSostituzioni[0] = 0;
	Fanta::ordineSostituzioni[1] = 3;
	Fanta::ordineSostituzioni[2] = 2;
	Fanta::ordineSostituzioni[3] = 1;
	Fanta::ordineSostituzioni[4] = 3;
	Fanta::ordineSostituzioni[5] = 2;
	Fanta::ordineSostituzioni[6] = 1;
	Fanta::ordineSostituzioni[7] = 3;
	Fanta::ordineSostituzioni[8] = 2;
	Fanta::ordineSostituzioni[9] = 1;
	
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
		Fanta::Team[k].clear();

		for (size_t j = 0; j < 7; j++) {
			Fanta::sostituzioni[k][j] = 0;
		}
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

	//for (size_t k = 0; k < 2; k++) {
	//	for (size_t j = 0; j < 7; j++) {
	//		for (size_t i = 0; i < 4; i++) {
	//			Fanta::teamOrderedByRuolo[k][j][i].resize(Fanta::moduli[j][i]);
	//		}
	//	}
	//}

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
		|| this->modulo[k][3] < 1 || this->modulo[k][3] > 3) {
		return EXIT_FAILURE;

	} else { 

		/*
		* posizione del modulo attuale nell'array moduli[7]
		*/
		Fanta::moduloIndex[k] = -1;
		for (size_t j = 0; j < 7; j++) {
			if (Fanta::moduli[j][0] == Fanta::modulo[k][0]
			&& Fanta::moduli[j][1] == Fanta::modulo[k][1]
			&& Fanta::moduli[j][2] == Fanta::modulo[k][2]
			&& Fanta::moduli[j][3] == Fanta::modulo[k][3]) {
				Fanta::moduloIndex[k] = j;
			}
		}

		if (Fanta::moduloIndex[k] == -1) {
			DEBUG("Modulo non consentito!!!");
			return EXIT_FAILURE;
		}
		/***/

		return EXIT_SUCCESS;
	}
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
			atof(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
			tmpPlayer.RigoreSbagliato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo2) == "D") {
			tmpPlayer.Ruolo = 1;
			tmpPlayer.Ruolo2 = 1;
			tmpPlayer.GoalFatti = atof(
			STR_MOD->msk(str, DELIM, ColGoalFatti).c_str())/* / 4.5*/;
			tmpPlayer.GoalSubiti = 0;
			tmpPlayer.RigoreSbagliato = fabs(
			atof(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			tmpPlayer.RigoreParato = 0;
		} else if (STR_MOD->msk(str, DELIM, ColRuolo2) == "C") {
			tmpPlayer.Ruolo2 = 2;
			if (STR_MOD->msk(str, DELIM, ColRuolo) == "T") {
				tmpPlayer.Ruolo = 4;
				tmpPlayer.GoalFatti = atof(
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str())/* / 3.5*/;
				tmpPlayer.RigoreSbagliato = fabs(
				atof(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "C") {
				tmpPlayer.Ruolo = 2;
				tmpPlayer.GoalFatti = atof(
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str())/* / 4.0*/;
				tmpPlayer.RigoreSbagliato = fabs(
				atof(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
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
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str())/* / 3.5*/;
				tmpPlayer.RigoreSbagliato = fabs(
				atof(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
			} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "A") {
				tmpPlayer.Ruolo = 3;
				tmpPlayer.GoalFatti = atof(
				STR_MOD->msk(str, DELIM, ColGoalFatti).c_str())/* / 3.0*/;
				tmpPlayer.RigoreSbagliato = fabs(
				atof(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3); /* WHAT TODO ??? */
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

		//DEBUG("Cognome            : " << tmpPlayer.Cognome);
//		//DEBUG("Nome_Sost          : " << tmpPlayer.Cognome_Sost);
		//DEBUG("Squadra            : " << tmpPlayer.Squadra);
//		//DEBUG("Squadra_Sost       : " << tmpPlayer.Squadra_Sost);
		//DEBUG("Ruolo              : " << tmpPlayer.Ruolo);
		//DEBUG("Ruolo2             : " << tmpPlayer.Ruolo2);
//		//DEBUG("FantaVoto          : " << tmpPlayer.FantaVoto);
		//DEBUG("FantaVotoGazzetta  : " << tmpPlayer.FantaVotoGazzetta);
		//DEBUG("VotoGazzetta       : " << tmpPlayer.VotoGazzetta);
		//DEBUG("GoalFatti          : " << tmpPlayer.GoalFatti);
		//DEBUG("GoalSubiti         : " << tmpPlayer.GoalSubiti);
		//DEBUG("Autoreti           : " << tmpPlayer.Autoreti);
//		//DEBUG("RigoreParato       : " << tmpPlayer.RigoreParato);
//		//DEBUG("RigoreSbagliato    : " << tmpPlayer.RigoreSbagliato);
		//DEBUG("GoalDecVitt        : " << tmpPlayer.GoalDecVitt);
		//DEBUG("GoalDecPar         : " << tmpPlayer.GoalDecPar);
		//DEBUG("Assist             : " << tmpPlayer.Assist);
		//DEBUG("Amm                : " << tmpPlayer.Amm);
		//DEBUG("Esp                : " << tmpPlayer.Esp);
//		//DEBUG("daSostituire       : " << tmpPlayer.daSostituire);

		Fanta::Team[k].push_back(tmpPlayer);
		return PLAYER_OK;
	} catch (...) {
		Fanta::Team[k].push_back(this->fakePlayer);
		return PLAYER_ERROR;
	}
}
unsigned int Fanta::LevenshteinDistance(const std::string& s1, const std::string& s2) {

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
		this->partiteRinviate();
	} catch (...) {
		LOG(ERR, "Exception caught in partiteRinviate().");
		DEBUG("exception caught in partiteRinviate().");
	}

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
		this->saveOriginals();
	} catch (...) {
		LOG(ERR, "Exception caught in saveOriginals().");
		DEBUG("exception caught in saveOriginals().");
	}

	try {
		this->fillWithNonHaGiocato();
	} catch (...) {
		LOG(ERR, "Exception caught in fillWithNonHaGiocato().");
		DEBUG("exception caught in fillWithNonHaGiocato().");
	}

	try {
		this->markForSubstitution();
	} catch (...) {
		LOG(ERR, "Exception caught in markForSubstitution().");
		DEBUG("exception caught in markForSubstitution().");
	}

	try {
		this->sendNGToBack();
	} catch (...) {
		LOG(ERR, "Exception caught in sendNGToBack().");
		DEBUG("exception caught in sendNGToBack().");
	}

	try {
		this->initializeMetrics();
	} catch (...) {
		LOG(ERR, "Exception caught in initializeMetrics().");
		DEBUG("exception caught in initializeMetrics().");
	}

	try {
		this->calculateMetrics();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateMetrics().");
		DEBUG("exception caught in calculateMetrics().");
	}

	try {
		this->substitutionsForTeam();
	} catch (...) {
		LOG(ERR, "Exception caught in substitutionsForTeam().");
		DEBUG("exception caught in substitutionsForTeam().");
	}

	try {
		this->calculateOriginalsOut();
	} catch (...) {
		LOG(ERR, "Exception caught in calculateOriginalsOut().");
		DEBUG("exception caught in calculateOriginalsOut().");
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
void Fanta::partiteRinviate() {
	LOG(DEB, "<br/> ========================");
	LOG(DEB, " === Partite rinviate ===");
	LOG(DEB, " ========================<br/><br/>");
	DEBUG("");

	QString answer;

	try {

		QString title = "Partite rinviate";
 		QString message = "Ci sono state partite rinviate ?";
		answer = this->questionMessage(title, message);

		DEBUG(" Partite rinviate ? " << answer.toStdString().c_str());

	} catch (...) {
		LOG(FATAL,
		"Exception caught in Fanta::partiteRinviate()!");
	}

	if (answer == "Yes") { // partite rinviate

		RinviateDialog::Inst()->exec();
		rinviate = RinviateDialog::Inst()->partiteRinviate();

		std::string squadre;
		for (unsigned int i = 0; i < rinviate.size(); i++) {
			DEBUG(rinviate.at(i));
			if ( i != rinviate.size() - 1 ) {
				squadre += rinviate.at(i) + ", ";
			} else {
				squadre += rinviate.at(i) + ".";
			}
		}

		LOG(DEB, " -> Rinviate le partite di " + QString::fromStdString(squadre) );

	} else { // nessuna partita rinviata
		LOG(DEB,
				" Nessuna partita rinviata.");
		return;
	}
}
void Fanta::checkGiocatoSenzaVoto() {

	LOG(DEB, "<br/> ============================");
	LOG(DEB, " === Giocatori senza voto ===");
	LOG(DEB, " ============================<br/><br/>");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < this->Team[k].size(); j++) { // loop sui giocatori
			//	DEBUG( this->Team[k].at(j).Cognome.c_str());

			bool giocatoreDiPartitaRinviata = false;
			for (unsigned int i = 0; i < rinviate.size(); i++) {
				if (this->Team[k].at(j).Squadra == rinviate.at(i)) {
					giocatoreDiPartitaRinviata = true;
					break;
				}
			}

			if (giocatoreDiPartitaRinviata) { // Partita rinviata

				this->Team[k].at(j).VotoGazzetta = 6.0;
				this->Team[k].at(j).FantaVotoGazzetta = 6.0;

			} else if ( this->Team[k].at(j).VotoGazzetta == -1 && (

				this->Team[k].at(j).Esp != 0 ||
				this->Team[k].at(j).Amm != 0 ||
				this->Team[k].at(j).Autoreti != 0 ||
				this->Team[k].at(j).Assist != 0 ||
				this->Team[k].at(j).GoalSubiti != 0 ||
				this->Team[k].at(j).GoalFatti != 0

			) ) { // se S.V. ma con bonus/malus

			if (this->Team[k].at(j).Ruolo2 == 0) { // se e' un portiere

					DEBUG("Giocato senza voto --> " << this->Team[k].at(j).Cognome.c_str() << " - portiere.");

					LOG(DEB,
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

					LOG(DEB,
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

					QString title = "Ha giocato almeno 25' ?";
					QString message = "Il giocatore \n" + QString::fromStdString(this->Team[k].at(j).Cognome)
									+ " \nha giocato, ma non e\' stato giudicato. \nHa giocato piu\' di 25\' ?";

					answer = this->questionMessage(title, message);

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

					LOG(DEB,
					" -> "
					+ QString::fromStdString(this->Team[k].at(j).Cognome)
					+ " ("
					+ QString::fromStdString(this->Team[k].at(j).Squadra)
					+ ") ha giocato 25'.");

				} else { // da sostituire

					DEBUG(this->Team[k].at(j).Cognome << " da sostituire.");

					this->Team[k].at(j).daSostituire = 1;// viene marcato per l'eliminazione

					LOG(DEB,
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
QString Fanta::questionMessage(QString title, QString message) {

	DEBUG("");

	QString answer;

	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(THE_LOGGER, title, message, QMessageBox::Yes | QMessageBox::No);
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

	LOG(DEB, "<br/> =======================================");
	LOG(DEB, " === Giocatori che non hanno giocato ===");
	LOG(DEB, " =======================================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DEB,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)) + " :");

		for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
		{
			if (this->Team[k].at(j).VotoGazzetta == 0) {
				if (this->Team[k].at(j).FantaVotoGazzetta == 0) {

					this->Team[k].at(j).daSostituire = 1; // viene marcato per l'eliminazione

					LOG(DEB,
					"      "
					+ QString::fromStdString(this->Team[k].at(j).Cognome)
					+ " ("
					+ QString::fromStdString(this->Team[k].at(j).Squadra)
					+ ").");
				} else {
					// ma ha ricevuto voto dalla Gazzetta (caso di partite sospese ??? )
					this->Team[k].at(j).VotoGazzetta
					= this->Team[k].at(j).FantaVotoGazzetta;
					LOG(DEB,
					"      "
					+ QString::fromStdString(this->Team[k].at(j).Cognome)
					+ " ("
					+ QString::fromStdString(this->Team[k].at(j).Squadra)
					+ ") non ha giocato, ma ha ricevuto voto("
					+ QString::fromStdString(my::toString<float>(this->Team[k].at(j).FantaVotoGazzetta))
					+ ").");
				}
			} else {
				//LOG(DEB, \
						" -> " \
						+ QString::fromStdString(this->Team[k].at(j).Cognome) \
						+ " (" \
						+ QString::fromStdString(this->Team[k].at(j).Squadra) \
						+ ") fantavoto : " \
						+ QString::fromStdString(my::toString<float>(this->Team[k].at(j).FantaVotoGazzetta)) \
						+ ".");
			}

			//DEBUG(this->Team[k].at(j).Cognome);
			//DEBUG(this->Team[k].at(j).daSostituire);
		}
	}
}
void Fanta::orderByRuolo() {

	DEBUG("");

	for (unsigned int k = 0; k < 2; k++) // loop sulle squadre
	{
		for (signed int j = 0; j < 7; j++) // loop sui moduli
		{
			for (signed int i = 0; i < 4; i++) // loop sui ruoli
			{
				for (size_t m = 0; m < this->Team[k].size(); m++) // loop sui giocatori
				{
					if (this->Team[k].at(m).Ruolo2 == i
						&& this->Fanta::teamOrderedByRuolo[k][j][i].size()
						< this->rosa[i]) {
							Fanta::teamOrderedByRuolo[k][j][i].push_back(this->Team[k].at(m));
					}
				}
			}
		}
	}

	//for (size_t k = 0; k < 2; k++) // squadra
	//{
	//	for (size_t j = 0; j < 1; j++) // moduli --- i sette moduli sono tutti uguali a questo punto !!! Mostro solo il primo.
	//	{
	//		for (size_t i = 0; i < 4; i++) // ruolo
	//		{
	//			for (size_t m = 0; m < Fanta::teamOrderedByRuolo[k][j][i].size(); m++) {
	//				DEBUG(this->getTeamName(k).c_str() << " : " <<
	//					this->teamOrderedByRuolo[k][j][i].at(m).Ruolo2 << " " <<
	//					this->teamOrderedByRuolo[k][j][i].at(m).Cognome.c_str() << ".");
	//			}
	//		}
	//	}
	//}
}
void Fanta::saveOriginals() {
	DEBUG("");
	
	for (size_t k = 0; k < 2; k++) { // squadra
		for (size_t i = 0; i < 4; i++) { // ruolo
			for (size_t m = 0; m < Fanta::modulo[k][i]; m++) {
				Fanta::originals[k].push_back(Fanta::teamOrderedByRuolo[k][Fanta::modulo[k][i]][i].at(m));
			}
		}
		
		for (size_t i = 0; i < Fanta::originals[k].size(); i++)
		{
			DEBUG("Fanta::originals[" << k << "].at(" << i << ").Cognome : " << Fanta::originals[k].at(i).Cognome);
		}
	}
}
void Fanta::fillWithNonHaGiocato() {

	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < 7; j++) // moduli
		{
			for (size_t i = 0; i < 4; i++) // ruolo
			{
				//DEBUG(Fanta::teamOrderedByRuolo[k][j][i].size());
				for (size_t m = Fanta::teamOrderedByRuolo[k][j][i].size(); m < rosa[i]; m++) {

						Fanta::teamOrderedByRuolo[k][j][i].push_back(Fanta::NonHaGiocato);
						DEBUG("Squadra " << this->getTeamName(k).c_str() << " : aggiunto un Fanta::NonHaGiocato");
						//LOG(DEB, \
						QString::fromStdString(this->getTeamName(k)) \
						+ " : aggiunto un Fanta::NonHaGiocato");
				}
			}
		}
	}
}
void Fanta::sendNGToBack() {

	/*
	*  sposta i 'NON HA GIOCATO' al fondo dei giocatori in campo
	*/
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < 7; j++) // moduli
		{
			DEBUG("modulo " << labelModuli[j]);
			for (size_t i = 0; i < 4; i++) // ruolo
			{
				//DEBUG("Fanta::moduli[" << j << "][" << i << "] : " << Fanta::moduli[j][i]);

				size_t xx = Fanta::moduli[j][i] - 1;

				for (size_t y = 0; y < xx; y++) {
					for (size_t t = 0; t < xx - y; t++) {
						if (
							Fanta::teamOrderedByRuolo[k][j][i].at(t).Cognome == "---" && 	// l'AND e' per evitare che scambi di posto
							Fanta::teamOrderedByRuolo[k][j][i].at(t + 1).Cognome != "---"	// due giocatori che non hanno giocato
							)
							swap(Fanta::teamOrderedByRuolo[k][j][i].at(t),
							Fanta::teamOrderedByRuolo[k][j][i].at(t + 1));
					}
				}

				size_t yy = Fanta::rosa[i] - 1;

				for (size_t y = Fanta::moduli[j][i]; y < yy; y++) {
					for (size_t t = Fanta::moduli[j][i]; t < yy - y + Fanta::moduli[j][i]; t++) {
						if (
							Fanta::teamOrderedByRuolo[k][j][i].at(t).Cognome == "---" && 	// l'AND e' per evitare che scambi di posto
							Fanta::teamOrderedByRuolo[k][j][i].at(t + 1).Cognome != "---"	// due giocatori che non hanno giocato
							)
							swap(Fanta::teamOrderedByRuolo[k][j][i].at(t),
							Fanta::teamOrderedByRuolo[k][j][i].at(t + 1));
					}
				}
			}


			//for (size_t i = 0; i < 4; i++) // ruolo
			//{
			//	for (size_t m = 0; m < Fanta::teamOrderedByRuolo[k][j][i].size(); m++) {
			//
			//			DEBUG(this->getTeamName(k).c_str() << " : " <<
			//				this->teamOrderedByRuolo[k][j][i].at(m).Ruolo2 << " " <<
			//				this->teamOrderedByRuolo[k][j][i].at(m).Cognome.c_str() << " (" << 
			//				this->teamOrderedByRuolo[k][j][i].at(m).Cognome_Sost.c_str() << ").");
			//	}
			//}
		}
	}

	return;
}
void Fanta::calculateMetrics() {

	for (size_t k = 0; k < 2; k++) {

		//DEBUG("squadra : " << this->getTeamName(k));

		/*
		* esplora i moduli possibili
		*/
		for (size_t j = 0; j < 7; j++) {

			//for (size_t i = 0; i < 4; i++) // ruolo
			//{
			//	for (size_t m = 0; m < Fanta::teamOrderedByRuolo[k][j][i].size(); m++) {
			//
			//			DEBUG(this->getTeamName(k).c_str() << " : " <<
			//				this->teamOrderedByRuolo[k][j][i].at(m).Ruolo2 << " " <<
			//				this->teamOrderedByRuolo[k][j][i].at(m).Cognome.c_str() << " (" << 
			//				this->teamOrderedByRuolo[k][j][i].at(m).Cognome_Sost.c_str() << ").");
			//	}
			//}

			//DEBUG("######## START ####################");

			/*
			* in campo, distanza e disponibili per tutti i moduli possibili
			*/
			for (size_t i = 0; i < 4; i++) { // ruolo

				for (size_t m = 0; m < Fanta::moduli[j][i]; m++) {

					if (Fanta::teamOrderedByRuolo[k][j][i].at(m).Cognome != "---")
						Fanta::inCampoModuli[k][j][i]++;
				}

				for (size_t m = Fanta::moduli[j][i]; m < rosa[i]; m++) {

					if (Fanta::teamOrderedByRuolo[k][j][i].at(m).Cognome != "---")
						Fanta::disponibiliModuli[k][j][i]++;
				}

				//for (size_t m = Fanta::moduli[j][i]; m < Fanta::modulo[k][i]; m++) {
				//
				//	if (Fanta::teamOrderedByRuolo[k][j][i].at(m).Cognome != "---") {
				//		DEBUG("      original out : " << Fanta::teamOrderedByRuolo[k][j][i].at(m).Cognome);
				//
				//		QString str =
				//			QString::fromStdString(
				//			Fanta::teamOrderedByRuolo[k][j][i].at(m).Cognome)
				//			+ " ("
				//			+ QString::fromStdString(
				//			Fanta::teamOrderedByRuolo[k][j][i].at(m).Squadra)
				//			+ ", " 
				//			+ QString::fromStdString(Fanta::roleLetter(i))
				//			+ ") uscito dai titolari.";
				//
				//		Fanta::originalsOutModuliNames[k][j][i].push_back(str);
				//		Fanta::originalsOutModuli[k][j][i]++;
				//	}
				//} 

				Fanta::distanzaModuli[k][j][i] = Fanta::moduli[j][i] - Fanta::inCampoModuli[k][j][i];
			}

			Fanta::distanzaTotaleModuli[k][j] =
				Fanta::distanzaModuli[k][j][0]
			+ Fanta::distanzaModuli[k][j][1]
			+ Fanta::distanzaModuli[k][j][2]
			+ Fanta::distanzaModuli[k][j][3];

			//Fanta::originalsOutTotaleModuli[k][j] =
			//	Fanta::originalsOutModuli[k][j][0]
			//+ Fanta::originalsOutModuli[k][j][1]
			//+ Fanta::originalsOutModuli[k][j][2]
			//+ Fanta::originalsOutModuli[k][j][3];

			//DEBUG("         modulo " << j << " : " << Fanta::moduli[j][0] << "-" << Fanta::moduli[j][1] << "-" << Fanta::moduli[j][2] << "-" << Fanta::moduli[j][3]);
			//DEBUG("       in campo " << j << " : " << Fanta::inCampoModuli[k][j][0] << "-" << Fanta::inCampoModuli[k][j][1] << "-" << Fanta::inCampoModuli[k][j][2] << "-" << Fanta::inCampoModuli[k][j][3]);
			//DEBUG("  originals out " << j << " : " << Fanta::originalsOutModuli[k][j][0] << "-" << Fanta::originalsOutModuli[k][j][1] << "-" << Fanta::originalsOutModuli[k][j][2] << "-" << Fanta::originalsOutModuli[k][j][3]);
			//DEBUG("       distanza " << j << " : " << Fanta::distanzaModuli[k][j][0] << "-" << Fanta::distanzaModuli[k][j][1] << "-" << Fanta::distanzaModuli[k][j][2] << "-" << Fanta::distanzaModuli[k][j][3]);
			//DEBUG("    disponibili " << j << " : " << Fanta::disponibiliModuli[k][j][0] << "-" << Fanta::disponibiliModuli[k][j][1] << "-" << Fanta::disponibiliModuli[k][j][2] << "-" << Fanta::disponibiliModuli[k][j][3]);
			//DEBUG("               distanzaTotale : " << Fanta::distanzaTotaleModuli[k][j]);
			//DEBUG("         originals out totale : " << Fanta::originalsOutTotaleModuli[k][j]);
		}
	}

	return;
}
void Fanta::calculateOriginalsOut() {

	for (size_t k = 0; k < 2; k++) { // squadra

		DEBUG("squadra : " << this->getTeamName(k));

		for (size_t j = 0; j < 7; j++) {

			//for (size_t i = 0; i < 4; i++) // ruolo
			//{
			//	for (size_t m = 0; m < Fanta::teamOrderedByRuolo[k][j][i].size(); m++) {
			//
			//			DEBUG(this->getTeamName(k).c_str() << " : " <<
			//				this->teamOrderedByRuolo[k][j][i].at(m).Ruolo2 << " " <<
			//				this->teamOrderedByRuolo[k][j][i].at(m).Cognome.c_str() << " (" << 
			//				this->teamOrderedByRuolo[k][j][i].at(m).Cognome_Sost.c_str() << ").");
			//	}
			//}

			DEBUG("######## START " << Fanta::labelModuli[j] << " ####################");

			for (size_t i = 0; i < 4; i++) { // ruolo

				for (size_t n = Fanta::moduli[j][i]; n < Fanta::rosa[i]; n++) { // modulo

					for (size_t m = 0; m < Fanta::originals[k].size(); m++) { // giocatori originali

						if (Fanta::teamOrderedByRuolo[k][j][i].at(n).Cognome == Fanta::originals[k].at(m).Cognome /*|| 
							Fanta::teamOrderedByRuolo[k][j][i].at(n).Cognome == Fanta::originals[k].at(m).Cognome_Sost ||
							Fanta::teamOrderedByRuolo[k][j][i].at(n).Cognome_Sost == Fanta::originals[k].at(m).Cognome ||
							Fanta::teamOrderedByRuolo[k][j][i].at(n).Cognome_Sost == Fanta::originals[k].at(m).Cognome_Sost*/ ) {

								//DEBUG("      original out : " << Fanta::teamOrderedByRuolo[k][j][i].at(n).Cognome << " - " << Fanta::teamOrderedByRuolo[k][j][i].at(n).Cognome_Sost);

								QString str =
									QString::fromStdString(
									Fanta::teamOrderedByRuolo[k][j][i].at(n).Cognome)
									+ " ("
									+ QString::fromStdString(
									Fanta::teamOrderedByRuolo[k][j][i].at(n).Squadra)
									+ ", " 
									+ QString::fromStdString(Fanta::roleLetter(i))
									+ ") uscito dai titolari.";

								Fanta::originalsOutModuliNames[k][j][i].push_back(str);
								Fanta::originalsOutModuli[k][j][i]++;
						}
					} 
				}

				//Fanta::distanzaModuli[k][j][i] = Fanta::moduli[j][i] - Fanta::inCampoModuli[k][j][i];
			}

			//Fanta::distanzaTotaleModuli[k][j] =
			//	Fanta::distanzaModuli[k][j][0]
			//+ Fanta::distanzaModuli[k][j][1]
			//+ Fanta::distanzaModuli[k][j][2]
			//+ Fanta::distanzaModuli[k][j][3];

			Fanta::originalsOutTotaleModuli[k][j] =
				Fanta::originalsOutModuli[k][j][0]
			+ Fanta::originalsOutModuli[k][j][1]
			+ Fanta::originalsOutModuli[k][j][2]
			+ Fanta::originalsOutModuli[k][j][3];

			//DEBUG("         modulo " << j << " : " << Fanta::moduli[j][0] << "-" << Fanta::moduli[j][1] << "-" << Fanta::moduli[j][2] << "-" << Fanta::moduli[j][3]);
			//DEBUG("       in campo " << j << " : " << Fanta::inCampoModuli[k][j][0] << "-" << Fanta::inCampoModuli[k][j][1] << "-" << Fanta::inCampoModuli[k][j][2] << "-" << Fanta::inCampoModuli[k][j][3]);
			DEBUG("  originals out " << j << " : " << Fanta::originalsOutModuli[k][j][0] << "-" << Fanta::originalsOutModuli[k][j][1] << "-" << Fanta::originalsOutModuli[k][j][2] << "-" << Fanta::originalsOutModuli[k][j][3]);
			//DEBUG("       distanza " << j << " : " << Fanta::distanzaModuli[k][j][0] << "-" << Fanta::distanzaModuli[k][j][1] << "-" << Fanta::distanzaModuli[k][j][2] << "-" << Fanta::distanzaModuli[k][j][3]);
			//DEBUG("    disponibili " << j << " : " << Fanta::disponibiliModuli[k][j][0] << "-" << Fanta::disponibiliModuli[k][j][1] << "-" << Fanta::disponibiliModuli[k][j][2] << "-" << Fanta::disponibiliModuli[k][j][3]);
			//DEBUG("               distanzaTotale : " << Fanta::distanzaTotaleModuli[k][j]);
			DEBUG("  originals out totale : " << Fanta::originalsOutTotaleModuli[k][j]);
		}
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
			Fanta::inCampoModuli[0][j][i] = 0;
			Fanta::inCampoModuli[1][j][i] = 0;
			Fanta::distanzaModuli[0][j][i] = 0;
			Fanta::distanzaModuli[1][j][i] = 0;
			Fanta::disponibiliModuli[0][j][i] = 0;
			Fanta::disponibiliModuli[1][j][i] = 0;
			Fanta::originalsOutModuli[0][j][i] = 0;
			Fanta::originalsOutModuli[1][j][i] = 0;
		}
		Fanta::distanzaTotaleModuli[0][j] = 0;
		Fanta::distanzaTotaleModuli[1][j] = 0;
	}
	/***/
}
std::string Fanta::roleLetter(unsigned int role) {
	if (role == 0) {
		return "P";
	} else if (role == 1) {
		return "D";
	} else if (role == 2) {
		return "C";
	} else if (role == 3) {
		return "A";
	} else {
		DEBUG("ruolo sconosciuto : " << role);
		return "?";
	}
}
void Fanta::substitutionsForTeam() {

	unsigned int inCampoPreSubs[2];
	for (size_t k = 0; k < 2; k++) {

		DEBUG("squadra : " << this->getTeamName(k));

		/*
		* esplora i moduli possibili
		*/
		for (size_t jj = 0; jj < 7; jj++) {

			DEBUG("######## START ###################");
			DEBUG(this->labelModuli[jj].c_str());

			//for (size_t i = 0; i < 4; i++) // ruolo
			//{
			//	for (size_t m = 0; m < Fanta::teamOrderedByRuolo[k][jj][i].size(); m++) {
			//
			//			DEBUG(this->getTeamName(k).c_str() << " : " <<
			//				this->teamOrderedByRuolo[k][jj][i].at(m).Ruolo2 << " " <<
			//				this->teamOrderedByRuolo[k][jj][i].at(m).Cognome.c_str() << " (" << 
			//				this->teamOrderedByRuolo[k][jj][i].at(m).Cognome_Sost.c_str() << ").");
			//	}
			//}

			DEBUG("distanzaTotaleModuli[" << k << "][" << jj << "] = " << Fanta::distanzaTotaleModuli[k][jj]);

			unsigned int sostituzioni_da_fare = std::min(3, Fanta::distanzaTotaleModuli[k][jj]);
			DEBUG("sostituzioni_da_fare = " << sostituzioni_da_fare);

			Fanta::inCampoPreSubs[k][jj] = Fanta::inCampoModuli[k][jj][0] +
				Fanta::inCampoModuli[k][jj][1] +
				Fanta::inCampoModuli[k][jj][2] +
				Fanta::inCampoModuli[k][jj][3];

			unsigned int sostituzione = 0;

			for (size_t i = 0; i < 10; i++) {

				//DEBUG("sostituzione = " << sostituzione);
				//DEBUG("moduloIndex = " << moduloIndex);
				//DEBUG("ordineSostituzioni[" << i << "] = " << Fanta::ordineSostituzioni[i]);
				//DEBUG(Fanta::distanzaModuli[moduloIndex][Fanta::ordineSostituzioni[i]]);

				if (Fanta::distanzaModuli[k][jj][Fanta::ordineSostituzioni[i]] > 0) {

					Fanta::ruoloDaSostituire[k][sostituzione] = Fanta::ordineSostituzioni[i];
					Fanta::distanzaModuli[k][jj][Fanta::ordineSostituzioni[i]]--;
					sostituzione++;
					if ( sostituzione == sostituzioni_da_fare )
						break;
				}
			}

			DEBUG("ruoloDaSostituire[" << k << "][0] : " << Fanta::ruoloDaSostituire[k][0]);
			DEBUG("ruoloDaSostituire[" << k << "][1] : " << Fanta::ruoloDaSostituire[k][1]);
			DEBUG("ruoloDaSostituire[" << k << "][2] : " << Fanta::ruoloDaSostituire[k][2]);

			for (size_t i = 0; i < 4; i++) { // ruolo

				if (Fanta::originalsOutModuli[k][jj][i] > 0) {

					DEBUG("Fanta::originalsOutModuli[" << k << "][" << jj << "][" << i << "] = " << Fanta::originalsOutModuli[k][jj][i]);

					/* N.B.: un original che esce dal modulo 
					* � sicuramente in prima posizione per la sostituzione
					* quindi rientrer� se la distanza � maggiore
					* degli originals da sostituire
					*/

					if ( Fanta::distanzaModuli[k][jj][i] < Fanta::originalsOutModuli[k][jj][i] ) {
						DEBUG("Fanta::distanzaModuli[" << k << "][" << jj << "][" << i << "] (" << Fanta::distanzaModuli[k][jj][i] << ") < Fanta::originalsOutModuli[" << k << "][" << jj << "][" << i << "] (" << Fanta::originalsOutModuli[k][jj][i] << ")");
					}
				}
			}

			/*
			* SOSTITUZIONI
			*/
			for (size_t i = 0; i < 10; i++) { // loop sulla seconda dimensione di Fanta::ruoloDaSostituire[squadra][i]

				if (Fanta::ruoloDaSostituire[k][i] == -1)
					continue;

				unsigned int w = Fanta::moduli[jj][Fanta::ruoloDaSostituire[k][i]];

				for (size_t j = 0; j < w; j++) // loop sui giocatori
				{
					if (Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(j).Cognome == "---" && Fanta::sostituzioni[k][jj] < 3) {

							for (size_t x = w; x < Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].size(); x++) {

								if (Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(x).Cognome != "---") {
										
									Fanta::sostituzioni[k][jj]++;

										QString sub =
											"      "
											+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(x).Cognome) 
											+ " ("
											+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(x).Squadra)
											+ ", " 
											+ QString::fromStdString(Fanta::roleLetter(Fanta::ruoloDaSostituire[k][i]))
											+ ") al posto di "
											+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(j).Cognome_Sost)
											+ " ("
											+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(j).Squadra_Sost)
											+ ", " 
											+ QString::fromStdString(Fanta::roleLetter(Fanta::ruoloDaSostituire[k][i]))
											+ ").";

										Fanta::subs[k][jj].push_back(sub);

										DEBUG(k << " : " << Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(x).Cognome
											<< " ("
											<< Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(x).Squadra
											<< ") al posto di "
											<< Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(j).Cognome_Sost
											<< " ("
											<< Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(j).Squadra_Sost
											<< ").");

										swap(
											Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(
											x),
											Fanta::teamOrderedByRuolo[k][jj][Fanta::ruoloDaSostituire[k][i]].at(
											j));

										goto label; // serve per poter uscire da due loop contemporaneamente
								}
							}
					}
				}
label: ; // solo una sostituzione per ruolo ( per volta )
			}

			DEBUG("Fanta::inCampoPreSubs[" << k << "][" << jj << "]  = " << Fanta::inCampoPreSubs[k][jj]);
			DEBUG("Fanta::sostituzioni[" << k << "][" << jj << "]    = " << Fanta::sostituzioni[k][jj]);
			Fanta::inCampoPostSubs[k][jj] = Fanta::inCampoPreSubs[k][jj] + Fanta::sostituzioni[k][jj];
			DEBUG("Fanta::inCampoPostSubs[" << k << "][" << jj << "] = " << Fanta::inCampoPostSubs[k][jj]);

			//for (size_t i = 0; i < 4; i++) // ruolo
			//{
			//	for (size_t m = 0; m < Fanta::teamOrderedByRuolo[k][jj][i].size(); m++) {
			//
			//			DEBUG(this->getTeamName(k).c_str() << " : " <<
			//				this->teamOrderedByRuolo[k][jj][i].at(m).Ruolo2 << " " <<
			//				this->teamOrderedByRuolo[k][jj][i].at(m).Cognome.c_str() << " (" << 
			//				this->teamOrderedByRuolo[k][jj][i].at(m).Cognome_Sost.c_str() << ").");
			//	}
			//}

			DEBUG("######## END ####################");

		}
	}

}
void Fanta::markForSubstitution() {

	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < 7; j++) // moduli
		{
			for (size_t i = 0; i < 4; i++) // ruolo
			{
				for (size_t m = 0; m < Fanta::teamOrderedByRuolo[k][j][i].size(); m++) { // loop sui tutti i giocatori

					if (this->teamOrderedByRuolo[k][j][i].at(m).daSostituire == 1) {
						Fanta::player tmpPlayer = Fanta::NonHaGiocato;
						tmpPlayer.Cognome_Sost = this->teamOrderedByRuolo[k][j][i].at(m).Cognome;
						tmpPlayer.Squadra_Sost = this->teamOrderedByRuolo[k][j][i].at(m).Squadra;
						this->teamOrderedByRuolo[k][j][i].at(m) = tmpPlayer;
					}
				}
			}
		}
	}
}
void Fanta::substitutions() {

	for (size_t k = 0; k < 2; k++) { // squadra

		//for (size_t i = 0; i < 4; i++) // ruolo
		//{
		//	for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].size();
		//		j++) {
		//			DEBUG(this->getTeamName(k).c_str() << " : " <<
		//				this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Ruolo2 << " " <<
		//				this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Cognome.c_str() << ".");
		//	}
		//}

		bool cambioModulo = false;

		if (inCampoPostSubs[k][Fanta::moduloIndex[k]] != 11) {
			cambioModulo = true;
			DEBUG("cambio modulo per giocatori < 11 (" << Fanta::labelModuli[Fanta::moduloIndex[k]] << ": " << inCampoPostSubs[k][Fanta::moduloIndex[k]] << ")" );
		} else {
			continue;
		}

		signed int oldModulo = Fanta::moduloIndex[k]; // modulo originario
		unsigned int maxInCampoPostSubs = inCampoPostSubs[k][oldModulo];

		if (cambioModulo) {

			/*
			* Ricerca nuovo modulo
			*/
			bool foundNewModule = false;

			for (unsigned int j = oldModulo; j < 7; j++) {

				if (j == oldModulo) 
					continue;

				DEBUG("ricerca modulo piu' offensivo - " << labelModuli[j].c_str());

				if (Fanta::originalsOutTotaleModuli[k][j] == 0) { // nessun original � fuori squadra

					/* Se non si � ancora trovato
					 * un modulo nuovo il modulo test (j) deve
					 * avere un numero di giocatori in campo
					 * almeno di 1 in pi� rispetto al
					 * modulo originario (checkValue = maxInCampoPostSubs + 1 se foundNewModule � false, 
					 * perch� a parit� di giocatori in campo prevale il modulo originario)
					 * Se un nuovo modulo � stato gi� trovato
					 * allora un eventuale modulo nuovo pi� offensivo pu� anche avere 
					 * lo stesso numero di giocatori 
					 * (checkValue = maxInCampoPostSubs se foundNewModule � true)
					 */
					unsigned int checkValue = (foundNewModule) ? maxInCampoPostSubs : maxInCampoPostSubs + 1;	

					if (Fanta::inCampoPostSubs[k][j] >= checkValue) {
						
						foundNewModule = true;
						Fanta::moduloIndex[k] = j;
						maxInCampoPostSubs = Fanta::inCampoPostSubs[k][j];	// non mettere il break perch�
																			// potrebbero esserci moduli pi� offensivi 
						DEBUG(
							"trovato nuovo modulo piu' offensivo : " << labelModuli[j].c_str() << " (" << maxInCampoPostSubs << ")");
					}
				}
			}

			if (maxInCampoPostSubs != 11) {

				for (signed int j = oldModulo; j >= 0; j--) {

					if (j == oldModulo) 
						continue;

					DEBUG("ricerca modulo meno offensivo - " << labelModuli[j].c_str());

					if (Fanta::originalsOutTotaleModuli[k][j] == 0) { // nessun original � fuori squadra

						/* 
						 * come sopra ...
						 */
						unsigned int checkValue = (foundNewModule) ? maxInCampoPostSubs : maxInCampoPostSubs + 1;

						if (Fanta::inCampoPostSubs[k][j] >= checkValue) {

							foundNewModule = true;
							Fanta::moduloIndex[k] = j;
							maxInCampoPostSubs = Fanta::inCampoPostSubs[k][j];
							DEBUG(
								"trovato nuovo modulo meno offensivo : " << labelModuli[j].c_str() << " (" << maxInCampoPostSubs << ")");

							if ( maxInCampoPostSubs == 11 ) {
								break; // non ci saranno moduli pi� offensivi di questo
							}
						}
					}
				}
			}
			/***/

			/*
			* Imposta nuovo modulo come modulo attuale
			*/
			if (!foundNewModule) {
				DEBUG("Non trovato nuovo modulo!");
			} else {

				for (size_t i = 0; i < 4; i++) { // ruolo
					/*
					* salva stringa di sostituzione per cambio modulo
					*/
					if (Fanta::moduli[Fanta::moduloIndex[k]][i] > Fanta::moduli[oldModulo][i]) { // solo per ruolo dove aumenta il numero di giocatori

						for (unsigned int m = Fanta::moduli[oldModulo][i]; m < Fanta::moduli[Fanta::moduloIndex[k]][i]; m++) {

							QString sub =
								QString::fromStdString(
								Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(m).Cognome)
								+ " ("
								+ QString::fromStdString(
								Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(m).Squadra)
								+ ", " 
								+ QString::fromStdString(Fanta::roleLetter(i))
								+ ") nuovo titolare.";

							Fanta::subsForModuleChange[k].push_back(
								sub);
						}
					}

					for (unsigned int m = 0; m < Fanta::originalsOutModuliNames[k][Fanta::moduloIndex[k]][i].size(); m++) {
						Fanta::origOutForModuleChange[k].push_back(Fanta::originalsOutModuliNames[k][Fanta::moduloIndex[k]][i].at(m));
					}

				}

				Fanta::newModuleString[k].push_back(
					"Nuovo modulo "
					+ QString::number(
					Fanta::moduli[Fanta::moduloIndex[k]][1])
					+ "-"
					+ QString::number(
					Fanta::moduli[Fanta::moduloIndex[k]][2])
					+ "-"
					+ QString::number(
					Fanta::moduli[Fanta::moduloIndex[k]][3]));

				Fanta::modulo[k][0] =
					Fanta::moduli[Fanta::moduloIndex[k]][0];
				Fanta::modulo[k][1] =
					Fanta::moduli[Fanta::moduloIndex[k]][1];
				Fanta::modulo[k][2] =
					Fanta::moduli[Fanta::moduloIndex[k]][2];
				Fanta::modulo[k][3] =
					Fanta::moduli[Fanta::moduloIndex[k]][3];
			}
		} 
	}

	/*
	* LOGGING
	*/
	LOG(DEB, "<br/> =====================");
	LOG(DEB, " === Cambio modulo ===");
	LOG(DEB, " =====================");

	for (size_t k = 0; k < 2; k++) {
		if (Fanta::newModuleString[k].size() == 1) {
			LOG(DEB,
				"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");
			LOG(DEB, newModuleString[k].front());

			if (Fanta::subsForModuleChange[k].size() > 0 ) {
				for (size_t j = 0; j < Fanta::subsForModuleChange[k].size(); j++) {
					LOG(DEB, subsForModuleChange[k].at(j));
				}
			}

			if (Fanta::origOutForModuleChange[k].size() > 0 ) {
				for (size_t j = 0; j < Fanta::origOutForModuleChange[k].size(); j++) {
					LOG(DEB, origOutForModuleChange[k].at(j));
				}
			}

		} else if (Fanta::newModuleString[k].size() > 1) {

			LOG(DEB,
				"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");

			LOG(WARN, "Trovato pi� di un muovo modulo!");

			for (size_t j = 0; j < Fanta::newModuleString[k].size(); j++) {
				LOG(WARN, newModuleString[k].at(j));
			}

		} else {
			/*
			* non necessario
			*/
		}
	}

	LOG(DEB, "<br/> ====================");
	LOG(DEB, " === Sostituzioni ===");
	LOG(DEB, " ====================");

	for (size_t k = 0; k < 2; k++) {
		if (Fanta::subsForModuleChange[k].size() > 0
			|| Fanta::subs[k][Fanta::moduloIndex[k]].size() > 0)
			LOG(DEB,
			"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");

		for (size_t j = 0; j < Fanta::subs[k][Fanta::moduloIndex[k]].size(); j++) {
			LOG(DEB, subs[k][Fanta::moduloIndex[k]].at(j));
		}
	}

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].resize(Fanta::moduli[Fanta::moduloIndex[k]][i]);
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

	DEBUG("Out.");

}
void Fanta::calculateFantaVoto() {

	LOG(DEB, "<br/> =================");
	LOG(DEB, " === Fantavoti ===");
	LOG(DEB, " =================");
	DEBUG("");

	int longerName = 0;

	for (size_t k = 0; k < 2; k++) { // squadra
		for (size_t i = 0; i < 4; i++) { // ruolo
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).FantaVoto =
				Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).FantaVotoGazzetta
				+ Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalDecVitt
				+ Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalDecPar * 0.5;

				(this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Cognome.size() > longerName)
				?
				longerName=this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Cognome.size()
				:
				longerName;

				j++;
			}
		}
	}

	int counter;
	for (size_t k = 0; k < 2; k++) { // squadra
		LOG(DEB,
		"<br> -> " + QString::fromStdString(this->getTeamName(k)) + " :");

		counter = 1;

		for (size_t i = 0; i < 4; i++) { // ruolo

			size_t j = 0;

			while (j < Fanta::modulo[k][i]) {
				LOG(DEB, "      ["
				+ STR_MOD->rightQString(my::toQString<int>(counter++), 2)
				+ "] "
				+ QString::fromStdString(STR_MOD->leftString(this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Cognome, longerName))
				+ " : "
				+ my::toQString<float>(this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).FantaVoto));

				j++;
			}
		}
	}

}
void Fanta::calculateDefenseMean() {

	LOG(DEB, "<br/> ====================");
	LOG(DEB, " === Media difesa ===");
	LOG(DEB, " ====================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DEB,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)) + " :");

		size_t j = 0;
		while (j < Fanta::modulo[k][1]) {
			if (Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][1].at(j).VotoGazzetta != 0) {
				Fanta::defenseMean[k] +=
				Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][1].at(j).VotoGazzetta;
				Fanta::defenders[k]++;

				LOG(DEB, "      ["
				+ my::toQString<size_t>(j + 1)
				+ "] "
				+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][1].at(j).Cognome)
				+ " ("
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][1].at(j).VotoGazzetta)
				+ ")");
			}
			j++;
		}
		Fanta::defenseMean[k] /= Fanta::defenders[k];

		LOG(DEB, "      media = "
		+ my::toQString<double>(Fanta::defenseMean[k]));
	}
}
void Fanta::calculateDefenseModifier() {

	LOG(DEB, "<br/> =================================");
	LOG(DEB, " === Modificatore della difesa ===");
	LOG(DEB, " =================================");
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
		LOG(DEB, "<br> -> "
		+ QString::fromStdString(this->getTeamName(k))
		+ "<br>      modificatore : "
		+ my::toQString<signed int>(Fanta::modifier[k]));
	}
}
void Fanta::calculateSfide() {

	LOG(DEB, "<br/> =====================");
	LOG(DEB, " === Calcolo sfide ===");
	LOG(DEB, " =====================<br>");
	DEBUG("");

	QString winner, loser, team;
	int longerName = max(this->getTeamName(0).size(), this->getTeamName(1).size());

	QString def0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][1].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][1].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(0))
	+ ")";

	QString cen0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][2].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][2].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(0))
	+ ")";

	QString att0 = QString::fromStdString(Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][3].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][3].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(0))
	+ ")";

	QString def1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][1].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][1].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(1))
	+ ")";

	QString cen1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][2].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][2].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(1))
	+ ")";

	QString att1 = QString::fromStdString(Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][3].at(0).Cognome)
	+ " ("
	+ my::toQString<float>(Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][3].at(0).VotoGazzetta)
	+ ", "
	+ QString::fromStdString(this->getTeamName(1))
	+ ")";

	/*
	 *  difensori - attaccanti
	 */

	if (Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][1].at(0).VotoGazzetta
	> Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][3].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(0)), longerName);
		winner = def0;
		loser = att1;

	} else if (Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][1].at(0).VotoGazzetta
	< Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][3].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(1)), longerName);
		winner = att1;
		loser = def0;

	} else {

		team = STR_MOD->leftQString("---", longerName);
		winner = def0;
		loser = att1;

	}

	LOG (DEB, "    [1] "
	+ team
	+ " : "
	+ winner
	+ " - "
	+ loser);

	/*
	 *  centrocampisti - centrocampisti
	 */

	if (Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][2].at(0).VotoGazzetta
	> Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][2].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(0)), longerName);
		winner = cen0;
		loser = cen1;

	} else if (Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][2].at(0).VotoGazzetta
	< Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][2].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(1)), longerName);
		winner = cen1;
		loser = cen0;

	} else {

		team = STR_MOD->leftQString("---", longerName);
		winner = cen0;
		loser = cen1;

	}

	LOG (DEB, "    [2] "
	+ team
	+ " : "
	+ winner
	+ " - "
	+ loser);

	/*
	 *  attaccanti - difensori
	 */

	if (Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][3].at(0).VotoGazzetta
	> Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][1].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(0)), longerName);
		winner = att0;
		loser = def1;

	} else if (Fanta::teamOrderedByRuolo[0][Fanta::moduloIndex[0]][3].at(0).VotoGazzetta
	< Fanta::teamOrderedByRuolo[1][Fanta::moduloIndex[1]][1].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;

		team = STR_MOD->leftQString(QString::fromStdString(this->getTeamName(1)), longerName);
		winner = def1;
		loser = att0;

	} else {

		team = STR_MOD->leftQString("---", longerName);
		winner = att0;
		loser = def1;

	}

	LOG(DEB, "    [3] "
	+ team
	+ " : "
	+ winner
	+ " - "
	+ loser);

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(DEB,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));
		LOG(DEB,
		+ "      sfide = " + my::toQString<unsigned int>(Fanta::sfide[k]));
	}
}
void Fanta::calculateTotal() {

	LOG(DEB, "<br/> =========================");
	LOG(DEB, " === Calcolo punteggio ===");
	LOG(DEB, " =========================");
	DEBUG("");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		QString message;

		LOG(DEB,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));

		Fanta::Total[k] += Fanta::atHome[k];
		message = "      "
		+ my::toQString<double>(Fanta::Total[k])
		+ " ("
		+ my::toQString<unsigned int>(Fanta::atHome[k])
		+ ", in casa)";

		LOG(DEB, message);

		Fanta::Total[k] += Fanta::modifier[k];
		message = "      "
		+ my::toQString<double>(Fanta::Total[k])
		+ " ("
		+ my::toQString<signed int>(Fanta::modifier[k])
		+ ", modificatore difesa)";

		LOG(DEB, message);

		Fanta::Total[k] += Fanta::sfide[k];
		message = "      "
		+ my::toQString<double>(Fanta::Total[k])
		+ " ("
		+ my::toQString<unsigned int>(Fanta::sfide[k])
		+ ", sfide)";

		LOG(DEB, message);

		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::Total[k]
				+= Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).FantaVoto;

				message = "      "
				+ my::toQString<double>(Fanta::Total[k])
				+ " ("
				+ my::toQString<float>(Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).FantaVoto)
				+ ", "
				+ QString::fromStdString(Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Cognome)
				+ ")";

				LOG(DEB, message);

				j++;
			}
		}

		message = "<br>    Totale : "
		+ my::toQString<double>(Fanta::Total[k]);

		LOG(DEB, message);
	}
}
void Fanta::calculateGoals() {

	LOG(DEB, "<br/> =====================");
	LOG(DEB, " === Calcolo goals ===");
	LOG(DEB, " =====================");
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

		LOG(DEB,
		"<br>      Entrambe le due squadre hanno totalizzato meno di 66 punti");

		for (size_t k = 0; k < 2; k++) {
			LOG(DEB, "      "
			+ STR_MOD->leftQString(QString::fromStdString(this->getTeamName(k)), FANTA->longerNameLength)
			+ " : "
			+ my::toQString<double>(Fanta::Total[k])
			+ " --> "
			+ my::toQString<signed int>(Fanta::goals[k])
			+ " goals");
		}
	}

	if (Fanta::goals[0] < 0 || Fanta::goals[1] < 0) {

		LOG(DEB, "");
		for (size_t k = 0; k < 2; k++) {
			if (Fanta::goals[k] < 0) {
				LOG(DEB,
				"      "
				+ STR_MOD->leftQString(QString::fromStdString(this->getTeamName(k)), FANTA->longerNameLength)
				+ " ha totalizzato un numero negativo di goals ("
				+ my::toQString<signed int>(Fanta::goals[k]) + " --> 0)");

				Fanta::goals[k] = 0;

			}
		}
	}

	for (size_t k = 0; k < 2; k++) {
		LOG(DEB, "<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));
		LOG(DEB, "      goals : "
		+ my::toQString<signed int>(Fanta::goals[k]));
	}

}
void Fanta::calculateScorers() {

	LOG(DEB, "<br/> =================");
	LOG(DEB, " === Marcatori ===");
	LOG(DEB, " =================");
	DEBUG("");

	vector<Fanta::player> tmpVector[2];

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				// preparing a single vector
				tmpVector[k].push_back(Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j));
				j++;
			}
		}
	}

	for (size_t k = 0; k < 2; k++) // squadra
	{

		LOG(DEB,
		"<br> -> "
		+ QString::fromStdString(this->getTeamName(k)));

		if (Fanta::goals[k] == 0) {
			LOG(DEB,
			"      ---");
			continue;
		}

		do {
			Fanta::bSort(tmpVector[k]);
			Fanta::scorers[k].push_back(tmpVector[k].at(0).Cognome);

			LOG(DEB,
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
		+ my::toQString<unsigned int>(FANTA->sostituzioni[0][Fanta::moduloIndex[0]]);

	output += "<br/>   " + team_B + " : " + my::toQString<unsigned int>(
		FANTA->sostituzioni[1][Fanta::moduloIndex[1]]);

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
							FANTA->teamOrderedByRuolo[0][Fanta::moduloIndex[0]][1].at(
									0).VotoGazzetta), 3))
	+ '\t' + QString::fromStdString(
			FANTA->teamOrderedByRuolo[0][Fanta::moduloIndex[0]][1].at(0).Cognome);

	output
	+= "<br/>   | Att " + team_B + " : "
	+ QString::fromStdString(
			STR_MOD->leftString(
					my::toString<float>(
							FANTA->teamOrderedByRuolo[1][Fanta::moduloIndex[1]][3].at(
									0).VotoGazzetta), 3))
	+ '\t' + QString::fromStdString(
			FANTA->teamOrderedByRuolo[1][Fanta::moduloIndex[1]][3].at(0).Cognome);

	output += "<br/>   |";

	output
	+= "<br/>   | Cen " + team_A + " : "
	+ QString::fromStdString(
			STR_MOD->leftString(
					my::toString<float>(
							FANTA->teamOrderedByRuolo[0][Fanta::moduloIndex[0]][2].at(
									0).VotoGazzetta), 3))
	+ '\t' + QString::fromStdString(
			FANTA->teamOrderedByRuolo[0][Fanta::moduloIndex[0]][2].at(0).Cognome);

	output
	+= "<br/>   | Cen " + team_B + " : "
	+ QString::fromStdString(
			STR_MOD->leftString(
					my::toString<float>(
							FANTA->teamOrderedByRuolo[1][Fanta::moduloIndex[1]][2].at(
									0).VotoGazzetta), 3))
	+ '\t' + QString::fromStdString(
			FANTA->teamOrderedByRuolo[1][Fanta::moduloIndex[1]][2].at(0).Cognome);

	output += "<br/>   |";

	output
	+= "<br/>   | Att " + team_A + " : "
	+ QString::fromStdString(
			STR_MOD->leftString(
					my::toString<float>(
							FANTA->teamOrderedByRuolo[0][Fanta::moduloIndex[0]][3].at(
									0).VotoGazzetta), 3))
	+ '\t' + QString::fromStdString(
			FANTA->teamOrderedByRuolo[0][Fanta::moduloIndex[0]][3].at(0).Cognome);

	output
	+= "<br/>   | Dif " + team_B + " : "
	+ QString::fromStdString(
			STR_MOD->leftString(
					my::toString<float>(
							FANTA->teamOrderedByRuolo[1][Fanta::moduloIndex[1]][1].at(
									0).VotoGazzetta), 3))
	+ '\t' + QString::fromStdString(
			FANTA->teamOrderedByRuolo[1][Fanta::moduloIndex[1]][1].at(0).Cognome);

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

	if (where == DEB) {
		LOG(DEB, tmp.replace(QString(" "), QString("&nbsp;")));
	} else if (where == INFO) {
		LOG(INFO, tmp.replace(QString(" "), QString("&nbsp;")));
	}

}
void Fanta::printPlayersInfo() {
	for (size_t k = 0; k < 2; k++) // squadre
			{

		FANTA->printTitolo(FANTA->teamName.at(k), DEB);

		QString tmp = "";

		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < FANTA->modulo[k][i]) {
				tmp += QObject::tr("<br/><br/>   ==== %1 ====").arg(
						QString::fromStdString(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Cognome));

				tmp += "<br/><br/>";

				tmp += STR_MOD->rightQString("Voto :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).VotoGazzetta),
						5);
				tmp += STR_MOD->rightQString("Fantavoto :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).FantaVoto),
						5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Goal fatti :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalFatti),
						5);
				tmp += STR_MOD->rightQString("Goal subiti :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalSubiti),
						5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Goal dec vitt :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalDecVitt),
						5);
				tmp += STR_MOD->rightQString("Goal dec par :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalDecPar),
						5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Ammonizioni :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Amm),
						5);
				tmp += STR_MOD->rightQString("Espulsioni :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Esp),
						5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Assist :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<unsigned int>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Assist),
						5);
				tmp += STR_MOD->rightQString("Autoreti :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<float>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Autoreti),
						5);
				tmp += "<br/>";

				tmp += STR_MOD->rightQString("Rigore parato :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<unsigned int>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).RigoreParato),
						5);
				tmp += STR_MOD->rightQString("Rigore sbagliato :", 20);
				tmp
				+= STR_MOD->rightQString(
						my::toQString<unsigned int>(
								FANTA->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).RigoreSbagliato),
						5);
				tmp += "<br/>";

				j++;
			}
		}

		LOG(DEB, tmp.replace(QString(" "), QString("&nbsp;")));
	}
}
unsigned int Fanta::getAmmonizioniTot(unsigned int k) const {
	unsigned int amm = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
			{
		size_t j = 0;
		while (j < this->moduli[Fanta::moduloIndex[k]][i]) {
			DEBUG("ammonizioni : " << this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Cognome << " " << this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Amm);
			amm += this->teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Amm;
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
		while (j < moduli[Fanta::moduloIndex[k]][i]) {
			esp += Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Esp;
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
		while (j < moduli[Fanta::moduloIndex[k]][i]) {
			GDVT += Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalDecVitt;
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
		while (j < moduli[Fanta::moduloIndex[k]][i]) {
			GDPT += Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).GoalDecPar;
			j++;
		}
	}

	return GDPT;
}
unsigned int Fanta::getSubstitutions(unsigned int k, unsigned int moduloIdx) const {
	return Fanta::sostituzioni[k][Fanta::moduloIndex[moduloIdx]];
}
unsigned int Fanta::getAssistTot(unsigned int k) const {
	unsigned int AssTot = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
			{
		size_t j = 0;
		while (j < moduli[Fanta::moduloIndex[k]][i]) {
			AssTot += Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][i].at(j).Assist;
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
									Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
											i).Cognome), 26));
				} else if (a[k][j] == 0) { // portiere
					if (k == 1) {
						output += area_sopra;
					}

					tmpString
					+= QString::fromStdString("                              |"
					+ STR_MOD->centerString(
							STR_MOD->onlySurname(
									Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
											i).Cognome), 18)
					+ "|                              |");
				} else {
					tmpString
					+= QString::fromStdString(STR_MOD->centerString(
							STR_MOD->onlySurname(
									Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
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
											Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
													i).FantaVoto) + " ("

									+ my::toString(
											Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
													i).VotoGazzetta)
									+ ")"), 26));
				} else if (a[k][j] == 0) { // portiere
					tmpString
					+= QString::fromStdString("<p> |                              |"
					+ STR_MOD->centerString(
							(my::toString(
											Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
													i).FantaVoto)
									+ " ("

									+ my::toString(
											Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
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
											Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
													i).FantaVoto) + " ("

									+ my::toString(
											Fanta::teamOrderedByRuolo[k][Fanta::moduloIndex[k]][a[k][j]].at(
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
