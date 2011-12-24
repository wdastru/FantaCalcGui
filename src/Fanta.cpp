/*
 * Fanta.cpp
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#include "Fanta.h"

Fanta * Fanta::Inst() {
	if (pInstance == NULL) {
		pInstance = new Fanta();
	}
	return pInstance;
}

Fanta * Fanta::pInstance = NULL;

Fanta::Fanta() {
	this->initialize();
}
Fanta::~Fanta() {
}
void Fanta::initialize() {
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
	}

	Fanta::longerNameLength = 0;

	Fanta::NonHaGiocato.Nome = "---";
	Fanta::NonHaGiocato.Nome_Sost = "---";
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

	Fanta::fakePlayer.Nome = "fake";
	Fanta::fakePlayer.Nome_Sost = "---";
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
	Fanta::fakePlayer.Amm = -0;
	Fanta::fakePlayer.Esp = -0;
	Fanta::fakePlayer.daSostituire = 0;

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
				"In Fanta::setTeamName(const std::string str, unsigned int k) --> Tried to add more than 2 team names!");
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
		LOG(
				DEBUG,
				"In Fanta::addPlayer(...) --> str : " + QString::fromStdString(
						str));

		Fanta::player tmpPlayer;

		// nome
		tmpPlayer.Nome = STR_MOD->msk(str, DELIM, ColNomeCognome);

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

		// fantavoto
		if (STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta) == "-")
			tmpPlayer.FantaVotoGazzetta = 0;
		else
			tmpPlayer.FantaVotoGazzetta = atof(
					STR_MOD->msk(str, DELIM, ColFantaVotoGazzetta).c_str());

		// voto gazzetta
		if (STR_MOD->msk(str, DELIM, ColVotoGazzetta) == "-")
			tmpPlayer.VotoGazzetta = 0;
		else if (STR_MOD->msk(str, DELIM, ColVotoGazzetta) == "S.V.")
			tmpPlayer.VotoGazzetta = -1;
		else
			tmpPlayer.VotoGazzetta = atof(
					STR_MOD->msk(str, DELIM, ColVotoGazzetta).c_str());

		// --> goal decisivi
		tmpPlayer.GoalDecVitt = atoi(
				STR_MOD->msk(str, DELIM, ColGoalDecVitt).c_str());
		if (tmpPlayer.GoalDecVitt != 0 && tmpPlayer.GoalFatti == 0) {
			LOG(DEBUG, "In Fanta::addPlayer( ... ) --> PLAYER_GDV_NO_GOAL");
			Fanta::Team[k].push_back(this->fakePlayer);
			return PLAYER_GDV_NO_GOAL;
		}

		tmpPlayer.GoalDecPar = atoi(
				STR_MOD->msk(str, DELIM, ColGoalDecPar).c_str());
		if (tmpPlayer.GoalDecPar != 0 && tmpPlayer.GoalFatti == 0) {
			LOG(DEBUG, "In Fanta::addPlayer( ... ) --> PLAYER_GDP_NO_GOAL");
			Fanta::Team[k].push_back(this->fakePlayer);
			return PLAYER_GDP_NO_GOAL;
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
				if (tmpPlayer.Nome == Fanta::Team[kk].at(i).Nome
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

const unsigned int cost_del = 1;
const unsigned int cost_ins = 1;
const unsigned int cost_sub = 1;

unsigned int Fanta::LevenshteinDistance(const std::string& s1,
		const std::string& s2) {
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

	LOG(DEBUG, "In void Fanta::execute().");

	try {
		this->checkGiocatoSenzaVoto();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in checkGiocatoSenzaVoto().");
	}

	try {
		this->checkNonHaGiocato();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in checkNonHaGiocato().");
	}

	try {
		this->orderByRuolo();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in orderByRuolo().");
	}

	try {
		this->fillWithNonHaGiocato();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in fillWithNonHaGiocato().");
	}

	try {
		this->substitutions();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in substitutions().");
	}

	try {
		this->calculateFantaVoto();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in calculateFantaVoto().");
	}

	try {
		this->calculateDefenseMean();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in calculateDefenseMean().");
	}

	try {
		this->calculateDefenseModifier();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in calculateDefenseModifier().");
	}

	try {
		this->calculateSfide();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in calculateSfide().");
	}

	try {
		this->calculateTotal();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in calculateTotal().");
	}

	try {
		this->calculateGoals();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in calculateGoals().");
	}

	try {
		this->calculateScorers();
	} catch (...) {
		LOG(DEBUG,
				"In void Fanta::execute() --> exception caught in calculateScorers().");
	}

	return;
}
void Fanta::checkGiocatoSenzaVoto() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
		{
			if (this->Team[k].at(j).VotoGazzetta == -1) {
				if (this->Team[k].at(j).Ruolo == 0) // se � un portiere
				{
					this->Team[k].at(j).VotoGazzetta = 6.0; // il portiere non si sostituisce se ha giocato (ma non ha preso voto),
					this->Team[k].at(j).FantaVotoGazzetta
							= this->Team[k].at(j).VotoGazzetta
									- this->Team[k].at(j).Esp - 0.5
									* this->Team[k].at(j).Amm - 2
									* this->Team[k].at(j).Autoreti
									+ this->Team[k].at(j).Assist
									- this->Team[k].at(j).GoalSubiti; // subiti x un portiere !

					LOG(
							DEBUG,
							"In Fanta::checkGiocatoSenzaVoto() --> "
									+ QString::fromStdString(
											this->Team[k].at(j).Nome) + " ("
									+ QString::fromStdString(
											this->Team[k].at(j).Squadra)
									+ ", portiere) senza voto ma ha giocato. Fantavoto :  "
									+ QString::fromStdString(
											my::toString<float>(
													this->Team[k].at(j).FantaVotoGazzetta)));

				} else //se non � un portiere
				{
					string answer;

					Less25MinDialog less25MinDialog;
					less25MinDialog.setPlayer(this->Team[k].at(j).Nome);
					less25MinDialog.exec();

					answer = less25MinDialog.getAnswer();

					if (answer == "Yes") {
						this->Team[k].at(j).VotoGazzetta = 6.0;
						this->Team[k].at(j).FantaVotoGazzetta
								= this->Team[k].at(j).VotoGazzetta
										- this->Team[k].at(j).Esp - 0.5
										* this->Team[k].at(j).Amm - 2
										* this->Team[k].at(j).Autoreti
										+ this->Team[k].at(j).Assist + 3
										* this->Team[k].at(j).GoalFatti;

						if (this->Team[k].at(j).FantaVotoGazzetta == 6.0) {
							this->Team[k].at(j).VotoGazzetta = 5.5;
							this->Team[k].at(j).FantaVotoGazzetta = 5.5;

							LOG(
									DEBUG,
									"In Fanta::checkGiocatoSenzaVoto() --> "
											+ QString::fromStdString(
													this->Team[k].at(j).Nome)
											+ " (" + QString::fromStdString(
											this->Team[k].at(j).Squadra)
											+ ") ha giocato 25'.");
						}
					} else {
						this->Team[k].at(j).daSostituire = 1; // viene marcato per l'eliminazione

						LOG(
								DEBUG,
								"In Fanta::checkGiocatoSenzaVoto() --> "
										+ QString::fromStdString(
												this->Team[k].at(j).Nome)
										+ " (" + QString::fromStdString(
										this->Team[k].at(j).Squadra)
										+ ") non ha giocato 25' : verr� effettuata una sostituzione.");
					}

					continue;
				}
			}
		}
	}
}
void Fanta::checkNonHaGiocato() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
		{
			if (this->Team[k].at(j).VotoGazzetta == 0) {
				if (this->Team[k].at(j).FantaVotoGazzetta == 0) {

					this->Team[k].at(j).daSostituire = 1; // viene marcato per l'eliminazione

					LOG(
							DEBUG,
							"In Fanta::checkNonHaGiocato() --> "
									+ QString::fromStdString(
											this->Team[k].at(j).Nome) + " ("
									+ QString::fromStdString(
											this->Team[k].at(j).Squadra)
									+ ") non ha giocato.");
				} else {
					// ma ha ricevuto voto dalla Gazzetta (caso di partite sospese ??? )
					this->Team[k].at(j).VotoGazzetta
							= this->Team[k].at(j).FantaVotoGazzetta;
					LOG(
							DEBUG,
							"In Fanta::checkNonHaGiocato() --> "
									+ QString::fromStdString(
											this->Team[k].at(j).Nome) + " ("
									+ QString::fromStdString(
											this->Team[k].at(j).Squadra)
									+ ") non ha giocato, ma ha ricevuto voto("
									+ QString::fromStdString(
											my::toString<float>(
													this->Team[k].at(j).FantaVotoGazzetta))
									+ ").");
				}
			} else {
				LOG(
						DEBUG,
						"In Fanta::checkNonHaGiocato() --> "
								+ QString::fromStdString(
										this->Team[k].at(j).Nome) + " ("
								+ QString::fromStdString(
										this->Team[k].at(j).Squadra)
								+ ") fantavoto : " + QString::fromStdString(
								my::toString<float>(
										this->Team[k].at(j).FantaVotoGazzetta))
								+ ".");
			}
		}
	}
}
void Fanta::orderByRuolo() {

	LOG(DEBUG, "In Fanta::orderByRuolo().");

	try {
		for (unsigned int k = 0; k < 2; k++)// loop sulle squadre
		{
			try {
				LOG(
						DEBUG,
						"In Fanta::orderByRuolo() --> Squadra : "
								+ QString::fromStdString(this->teamName.at(k)));
				throw(this->teamName.at(k));
			} catch (std::string str) {
				LOG(
						DEBUG,
						"In Fanta::orderByRuolo() --> exception caught : this->teamName.at("
								+ my::toQString<unsigned int>(k) + ") = "
								+ QString::fromStdString(str));
			}

			try {
				for (signed int i = 0; i < 4; i++) // loop sui ruoli
				{

					for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
					{
						if (this->Team[k].at(j).Ruolo == i) {
							Fanta::teamOrderedByRuolo[k][i].push_back(
									this->Team[k].at(j));
							LOG(
									DEBUG,
									"In Fanta::orderByRuolo() --> "
											+ QString::fromStdString(
													my::toString<unsigned int>(
															i)) + " "
											+ QString::fromStdString(
													this->Team[k].at(j).Nome));
						}
					}
				}
			} catch (...) {
				LOG(FATAL,
						"In Fanta::orderByRuolo() --> exception caught in for (i) loop.");
			}
		}
	} catch (...) {
		LOG(FATAL,
				"In Fanta::orderByRuolo() --> exception caught in for (k) loop.");
	}
}
void Fanta::fillWithNonHaGiocato() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			for (size_t j = Fanta::teamOrderedByRuolo[k][i].size(); j
					< modulo[k][i] + 2; j++) {
				Fanta::teamOrderedByRuolo[k][i].push_back(Fanta::NonHaGiocato);
				LOG(
						DEBUG,
						"In Fanta::fillWithNonHaGiocato() --> Squadra "
								+ QString::fromStdString(this->getTeamName(k))
								+ " : aggiunto un Fanta::NonHaGiocato");
			}
		}
	}
}
void Fanta::substitutions() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size(); j++) // loop sui tutti i giocatori
			{
				if (this->teamOrderedByRuolo[k][i].at(j).daSostituire == 1) {
					Fanta::player tmpPlayer = Fanta::NonHaGiocato;
					tmpPlayer.Nome_Sost
							= this->teamOrderedByRuolo[k][i].at(j).Nome;
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
					if (Fanta::teamOrderedByRuolo[k][i].at(t).Nome == "---")
						swap(Fanta::teamOrderedByRuolo[k][i].at(t),
								Fanta::teamOrderedByRuolo[k][i].at(t + 1));
				}
			}
		}
	}

	/*
	 *  se il primo panchinaro non ha giocato lo swappa con il secondo:
	 *  se anch'esso non ha giocato non serve a nulla, se ha giocato lo porta in prima posizione
	 */

	for (size_t k = 0; k < 2; k++) // squadre
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			if (Fanta::teamOrderedByRuolo[k][i].at(Fanta::modulo[k][i]).Nome
					== "---")
				swap(
						Fanta::teamOrderedByRuolo[k][i].at(Fanta::modulo[k][i]),
						Fanta::teamOrderedByRuolo[k][i].at(
								Fanta::modulo[k][i] + 1));
		}
	}

	unsigned int a[7] = { 0, 3, 2, 1, 3, 2, 1 }; // ordine delle sostituzioni

	for (size_t k = 0; k < 2; k++) {
		for (size_t t = 0; t < 3; t++) { // ripetere il loop sottostante per esaurire tutte le sostituzioni
			for (size_t i = 0; i < 7; i++) { // loop sulla dimensione di a[]
				unsigned int w = Fanta::modulo[k][a[i]];

				for (size_t j = 0; j < w; j++) // loop sui giocatori
				{
					if (Fanta::teamOrderedByRuolo[k][a[i]].at(j).Nome == "---"
							&& sostituzioni[k] < 3) {

						for (size_t x = w; x
								< Fanta::teamOrderedByRuolo[k][a[i]].size(); x++) {
							if (Fanta::teamOrderedByRuolo[k][a[i]].at(x).Nome
									!= "---") {
								sostituzioni[k]++;

								LOG(
										DEBUG,
										"In Fanta::substitutions() --> Sostituzione di "
												+ QString::fromStdString(
														Fanta::teamOrderedByRuolo[k][a[i]].at(
																j).Nome_Sost)
												+ " ("
												+ QString::fromStdString(
														Fanta::teamOrderedByRuolo[k][a[i]].at(
																j).Squadra_Sost)
												+ ") con "
												+ QString::fromStdString(
														Fanta::teamOrderedByRuolo[k][a[i]].at(
																x).Nome) + " ("
												+ QString::fromStdString(
														Fanta::teamOrderedByRuolo[k][a[i]].at(
																x).Squadra)
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

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size(); j++) {
				LOG(
						DEBUG,
						"In Fanta::substitutions() --> Squadra "
								+ QString::fromStdString(this->getTeamName(k))
								+ " : " + my::toQString<signed int>(
								this->teamOrderedByRuolo[k][i].at(j).Ruolo)
								+ " " + QString::fromStdString(
								this->teamOrderedByRuolo[k][i].at(j).Nome)
								+ ".");
			}
		}
	}
}
void Fanta::calculateFantaVoto() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto
						= Fanta::teamOrderedByRuolo[k][i].at(j).FantaVotoGazzetta
								+ Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecVitt
								+ Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecPar
										* 0.5;

				LOG(
						DEBUG,
						"In Fanta::calculateFantaVoto() --> Squadra "
								+ QString::fromStdString(this->getTeamName(k))
								+ " : " + QString::fromStdString(
								this->teamOrderedByRuolo[k][i].at(j).Nome)
								+ " FV = " + my::toQString<float>(
								this->teamOrderedByRuolo[k][i].at(j).FantaVoto)
								+ ".");
				j++;
			}
		}
	}
}
void Fanta::calculateDefenseMean() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][1]) {
			if (Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta != 0) {
				Fanta::defenseMean[k]
						+= Fanta::teamOrderedByRuolo[k][1].at(j).VotoGazzetta;
				Fanta::defenders[k]++;
			}
			j++;
		}
		Fanta::defenseMean[k] /= Fanta::defenders[k];

		LOG(
				DEBUG,
				"In Fanta::calculateDefenseMean() --> Squadra "
						+ QString::fromStdString(this->getTeamName(k)) + " : "
						+ my::toQString<unsigned int>(Fanta::defenders[k])
						+ " difensori, media = " + my::toQString<double>(
						Fanta::defenseMean[k]) + ".");
	}
}
void Fanta::calculateDefenseModifier() {
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
		LOG(
				DEBUG,
				"In Fanta::calculateDefenseModifier() --> Squadra "
						+ QString::fromStdString(this->getTeamName(k))
						+ " modificatore = " + my::toQString<signed int>(
						Fanta::modifier[k]) + ".");
	}
}
void Fanta::calculateSfide() {
	/*
	 *  difensori - attaccanti
	 */
	if (Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;
	} else if (Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;
	}

	LOG(
			DEBUG,
			"In Fanta::calculateSfide() --> sfida 1 : "
					+ QString::fromStdString(
							Fanta::teamOrderedByRuolo[0][1].at(0).Nome) + " ("
					+ my::toQString<float>(
							Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta)
					+ ", " + QString::fromStdString(this->getTeamName(0))
					+ ") - " + QString::fromStdString(
					Fanta::teamOrderedByRuolo[1][3].at(0).Nome) + " ("
					+ my::toQString<float>(
							Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta)
					+ ", " + QString::fromStdString(this->getTeamName(1))
					+ ").");

	/*
	 *  centrocampisti - centrocampisti
	 */
	if (Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;
	} else if (Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;
	}

	LOG(
			DEBUG,
			"In Fanta::calculateSfide() --> sfida 2 : "
					+ QString::fromStdString(
							Fanta::teamOrderedByRuolo[0][2].at(0).Nome) + " ("
					+ my::toQString<float>(
							Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta)
					+ ", " + QString::fromStdString(this->getTeamName(0))
					+ ") - " + QString::fromStdString(
					Fanta::teamOrderedByRuolo[1][2].at(0).Nome) + " ("
					+ my::toQString<float>(
							Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta)
					+ ", " + QString::fromStdString(this->getTeamName(1))
					+ ").");

	/*
	 *  attaccanti - difensori
	 */
	if (Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta) {
		Fanta::sfide[0]++;
	} else if (Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta) {
		Fanta::sfide[1]++;
	}

	LOG(
			DEBUG,
			"In Fanta::calculateSfide() --> sfida 3 : "
					+ QString::fromStdString(
							Fanta::teamOrderedByRuolo[0][3].at(0).Nome) + " ("
					+ my::toQString<float>(
							Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta)
					+ ", " + QString::fromStdString(this->getTeamName(0))
					+ ") - " + QString::fromStdString(
					Fanta::teamOrderedByRuolo[1][1].at(0).Nome) + " ("
					+ my::toQString<float>(
							Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta)
					+ ", " + QString::fromStdString(this->getTeamName(1))
					+ ").");

	for (size_t k = 0; k < 2; k++) // squadra
	{
		LOG(
				DEBUG,
				"In Fanta::calculateSfide() --> Squadra "
						+ QString::fromStdString(this->getTeamName(k))
						+ " sfide = " + my::toQString<unsigned int>(
						Fanta::sfide[k]) + ".");
	}
}
void Fanta::calculateTotal() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		QString message;
		Fanta::Total[k] += Fanta::atHome[k];
		message = "In Fanta::calculateTotal() --> squadra "
				+ QString::fromStdString(this->getTeamName(k)) + " : "
				+ my::toQString<double>(Fanta::Total[k]) + " in casa ("
				+ my::toQString<unsigned int>(Fanta::atHome[k]) + ").";

		LOG(DEBUG, message);

		Fanta::Total[k] += Fanta::modifier[k];
		message = "In Fanta::calculateTotal() --> squadra "
				+ QString::fromStdString(this->getTeamName(k)) + " : "
				+ (my::toQString<double>(Fanta::Total[k])
						+ " modificatore difesa (" + my::toQString<signed int>(
						Fanta::modifier[k]) + ").");
		LOG(DEBUG, message);

		Fanta::Total[k] += Fanta::sfide[k];
		message = "In Fanta::calculateTotal() --> squadra "
				+ QString::fromStdString(this->getTeamName(k)) + " : "
				+ (my::toQString<double>(Fanta::Total[k]) + " sfide vinte."
						+ " (" + my::toQString<unsigned int>(Fanta::sfide[k])
						+ ").");
		LOG(DEBUG, message);

		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::Total[k]
						+= Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto;

				message = "In Fanta::calculateTotal() --> squadra "
						+ QString::fromStdString(this->getTeamName(k)) + " : "
						+ my::toQString<double>(Fanta::Total[k]) + " "
						+ QString::fromStdString(
								Fanta::teamOrderedByRuolo[k][i].at(j).Nome)
						+ " (" + my::toQString<float>(
						Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto) + ").";
				LOG(DEBUG, message);

				j++;
			}
		}

		message = "In Fanta::calculateTotal() --> squadra "
				+ QString::fromStdString(this->getTeamName(k)) + " : Totale "
				+ my::toQString<double>(Fanta::Total[k]);
		LOG(DEBUG, message);
	}
}
void Fanta::calculateGoals() {
	for (size_t k = 0; k < 2; k++) {
		for (size_t i = 0;; i++) {
			if (Fanta::Total[k] >= (6 * i))
				continue;

			Fanta::goals[k] = i - 11;

			LOG(
					DEBUG,
					"In Fanta::calculateGoals() --> squadra "
							+ QString::fromStdString(this->getTeamName(k))
							+ " : "
							+ my::toQString<signed int>(Fanta::goals[k]) + " ("
							+ my::toQString<double>(Fanta::Total[k]) + ")");

			break;
		}
	}

	if (Fanta::Total[0] < 66 && Fanta::Total[1] < 66) {
		if (Fanta::Total[0] >= Fanta::Total[1] + 6) {
			Fanta::goals[0] = 1;
		} else if (Fanta::Total[1] >= Fanta::Total[0] + 6) {
			Fanta::goals[1] = 1;
		}

		LOG(
				DEBUG,
				"In Fanta::calculateGoals() --> entrambe le due squadre hanno totalizzato meno di 66 punti.<br/>"
						+ QString::fromStdString(this->getTeamName(0)) + " : "
						+ my::toQString<signed int>(Fanta::goals[0]) + " ("
						+ my::toQString<double>(Fanta::Total[0]) + ")<br/>"
						+ QString::fromStdString(this->getTeamName(1)) + " : "
						+ my::toQString<signed int>(Fanta::goals[1]) + " ("
						+ my::toQString<double>(Fanta::Total[1]) + ")");
	}

	for (size_t k = 0; k < 2; k++) {
		if (Fanta::goals[k] < 0) {
			LOG(
					DEBUG,
					"In Fanta::calculateGoals() --> la squadra "
							+ QString::fromStdString(this->getTeamName(k))
							+ " ha totalizzato un numero negativo di goals ("
							+ my::toQString<signed int>(Fanta::goals[k]) + ").");

			Fanta::goals[k] = 0;

			LOG(
					DEBUG,
					"<br/>" + QString::fromStdString(this->getTeamName(0))
							+ " : "
							+ my::toQString<signed int>(Fanta::goals[0]) + " ("
							+ my::toQString<double>(Fanta::Total[0]) + ")<br/>"
							+ QString::fromStdString(this->getTeamName(1u))
							+ " : "
							+ my::toQString<signed int>(Fanta::goals[1]) + " ("
							+ my::toQString<double>(Fanta::Total[1]) + ")");
		}
	}
}
void Fanta::calculateScorers() {
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
		if (Fanta::goals[k] == 0)
			continue;
		do {
			Fanta::bSort(tmpVector[k]);
			Fanta::scorers[k].push_back(tmpVector[k].at(0).Nome);

			LOG(
					DEBUG,
					"In Fanta::calculateScorers() --> squadra "
							+ QString::fromStdString(this->getTeamName(k))
							+ " : " + QString::fromStdString(
							tmpVector[k].at(0).Nome) + " (" + my::toQString<
							float>(tmpVector[k].at(0).FantaVoto) + ").");

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
void Fanta::setFileGazzetta(QString _fileGazzetta) {
	this->fileGazzetta = _fileGazzetta;
}
void Fanta::printRiepilogo() {

	QString output = "<br/> --- Modulo  ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : "
			+ QString::fromStdString(FANTA->getModuloSquadra(0));

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : "
			+ QString::fromStdString(FANTA->getModuloSquadra(1));

	output += "<br/><br/> --- Fattore Campo ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->atHome[0]);

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->atHome[1]);

	output += "<br/><br/> --- Ammonizioni ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getAmmonizioniTot(0));
	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getAmmonizioniTot(1));

	output += "<br/><br/> --- Espulsioni ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getEspulsioniTot(0));

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getEspulsioniTot(1));

	output += "<br/><br/> --- Goal decisivi vittoria ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getGoalDecVittTot(0));

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getGoalDecVittTot(1));

	output += "<br/><br/> --- Goal decisivi pareggio ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getGoalDecParTot(0));

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getGoalDecParTot(1));

	output += "<br/><br/> --- Assist ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getAssistTot(0));

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->getAssistTot(1));

	output += "<br/><br/> --- Sostituzioni ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->sostituzioni[0]);

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->sostituzioni[1]);

	output += "<br/><br/> --- Sfide ---<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->sfide[0]);

	output += "<br/>"
			+ QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
			unsigned int>(FANTA->sfide[1]);

	output += "<br/><br/> Dettaglio :<br/>";

	output += "<br/>\t|";

	output
			+= "<br/>\t| Dif " + QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
					float>(FANTA->teamOrderedByRuolo[0][1].at(0).VotoGazzetta)
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[0][1].at(0).Nome);

	output
			+= "<br/>\t| Att " + QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
					float>(FANTA->teamOrderedByRuolo[1][3].at(0).VotoGazzetta)
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[1][3].at(0).Nome);

	output += "<br/>\t|";

	output
			+= "<br/>\t| Cen " + QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
					float>(FANTA->teamOrderedByRuolo[0][2].at(0).VotoGazzetta)
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[0][2].at(0).Nome);

	output
			+= "<br/>\t| Cen " + QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
					float>(FANTA->teamOrderedByRuolo[1][2].at(0).VotoGazzetta)
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[1][2].at(0).Nome);

	output += "<br/>\t|";

	output
			+= "<br/>\t| Att " + QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(0),
							FANTA->longerNameLength)) + " : " + my::toQString<
					float>(FANTA->teamOrderedByRuolo[0][3].at(0).VotoGazzetta)
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[0][3].at(0).Nome);

	output
			+= "<br/>\t| Dif " + QString::fromStdString(
					STR_MOD->leftString(FANTA->getTeamName(1),
							FANTA->longerNameLength)) + " : " + my::toQString<
					float>(FANTA->teamOrderedByRuolo[1][1].at(0).VotoGazzetta)
					+ '\t' + QString::fromStdString(
					FANTA->teamOrderedByRuolo[1][1].at(0).Nome);

	output += "<br/>\t|";

	output += "<br/>\t+---------------------------------------------><br/>";

	output += "<br/> --- Media Difesa ---<br/>";

	for (size_t i = 0; i < 2; i++) {
		QString string = QString::fromStdString(
				STR_MOD->leftString(FANTA->getTeamName(i),
						FANTA->longerNameLength)) + " : " + my::toQString<
				double>(FANTA->defenseMean[i]) + " ( " + my::toQString<
				unsigned int>(FANTA->defenders[i]) + " )";

		output += string + "<br/>";
	}

	output += "<br/> --- Modificatore ---<br/>";

	for (size_t i = 0; i < 2; i++) {
		QString string = QString::fromStdString(
				STR_MOD->leftString(FANTA->getTeamName(i),
						FANTA->longerNameLength)) + " : " + my::toQString<
				signed int>(FANTA->modifier[i]);

		output += string + "<br/>";
	}

	output += "<br/> --- Marcatori ---<br/>";

	for (size_t i = 0; i < 2; i++) {
		QString string = QString::fromStdString(
				STR_MOD->leftString(FANTA->getTeamName(i),
						FANTA->longerNameLength)) + " : " + my::toQString<
				signed int>(FANTA->goals[i]) + " ( " + my::toQString<double>(
				FANTA->Total[i]) + " ";

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

	LOG(DEBUG, output + "<br/>");
}
void Fanta::printTitolo(std::string str) {
	QString tmp = "<br/> +";
	for (unsigned int i = 0; i < str.size() + 6; i++) {
		tmp += "-";
	}
	tmp += "+<br/> | +";

	for (unsigned int i = 0; i < str.size() + 2; i++) {
		tmp += "-";
	}
	tmp += "+ |<br/> | | " + QString::fromStdString(str) + " | |<br/> | +";
	for (unsigned int i = 0; i < str.size() + 2; i++)
		tmp += "-";
	tmp += "+ |<br/> +";
	for (unsigned int i = 0; i < str.size() + 6; i++)
		tmp += "-";
	tmp += "+<br/>";

	LOG(INFO, tmp);
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
unsigned int Fanta::getSubstitutions(size_t k) const {
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

	std::string
			bordi =
					"<pre> |                                                                                |</pre>";
	std::string
			fondo =
					"<pre> +------------------------------+------------------+------------------------------+</pre>";

	std::string
			area =
					"<pre> |                              |__________________|                              |</pre>";

	std::string
			area_sotto =
					area
							+ "<pre> |                                      \\__/                                      |</pre>"
							+ bordi;

	std::string
			area_sopra =
					"<pre> |                                       __                                       |</pre><pre> |                               _______/__\\_______                               |</pre><pre> |                              |                  |                              |</pre>";

	std::string
			separatore =
					"<pre> |                                       ___                                      |</pre><pre> |                                      /   \\                                     |</pre><pre> |-------------------------------------(--o--)------------------------------------|</pre><pre> |                                      \\___/                                     |</pre><pre> |                                                                                |</pre>";

	output += QString::fromStdString(fondo);

	/*
	 *  squadra in casa    : por --> att
	 *  squadra fuori casa :                   att --> por
	 */
	unsigned int a[2][4] = { { 0, 1, 2, 3 }, { 3, 2, 1, 0 } };

	for (size_t k = 0; k < 2; k++) // squadre
	{
		for (size_t j = 0; j < 4; j++) // ruoli
		{
			std::string tmpString = "<pre> |";

			/*
			 *  nomi giocatori
			 */
			for (size_t i = 0; i < Fanta::modulo[k][a[k][j]]; i++) { // giocatori
				if (Fanta::modulo[k][a[k][j]] == 3) {
					tmpString
							+= STR_MOD->centerString(
									STR_MOD->onlySurname(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).Nome), 26);
				} else if (a[k][j] == 0) { // portiere
					if (k == 1) {
						output += QString::fromStdString(area_sopra);
					}

					tmpString
							+= "                              |"
									+ STR_MOD->centerString(
											STR_MOD->onlySurname(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).Nome), 18)
									+ "|                              |";
				} else {
					tmpString
							+= STR_MOD->centerString(
									STR_MOD->onlySurname(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).Nome),
									80 / Fanta::modulo[k][a[k][j]]);
				}
			}

			if (Fanta::modulo[k][a[k][j]] == 3) {
				output += QString::fromStdString(tmpString + "  |</pre>");
			} else if (a[k][j] == 0) {
				output += QString::fromStdString(tmpString) + "</pre>";
			} else {
				output += QString::fromStdString(tmpString + "|</pre>");
			}

			tmpString = "";

			if (a[k][j] != 0)
				tmpString += "<pre> |";

			/*
			 *  voti giocatori
			 */
			for (size_t i = 0; i < Fanta::modulo[k][a[k][j]]; i++) { // giocatori
				if (Fanta::modulo[k][a[k][j]] == 3) {
					tmpString
							+= STR_MOD->centerString(
									(my::toString(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).FantaVoto) + " ("

											+ my::toString(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).VotoGazzetta)
											+ ")"), 26);
				} else if (a[k][j] == 0) { // portiere
					tmpString
							+= "<pre> |                              |"
									+ STR_MOD->centerString(
											(my::toString(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).FantaVoto)
													+ " ("

													+ my::toString(
															Fanta::teamOrderedByRuolo[k][a[k][j]].at(
																	i).VotoGazzetta)
													+ ")"), 18)
									+ "|                              |";

					if (k == 0) {
						tmpString += "</pre>" + area_sotto;
					}
				} else {
					tmpString
							+= STR_MOD->centerString(
									(my::toString(
											Fanta::teamOrderedByRuolo[k][a[k][j]].at(
													i).FantaVoto) + " ("

											+ my::toString(
													Fanta::teamOrderedByRuolo[k][a[k][j]].at(
															i).VotoGazzetta)
											+ ")"),
									80 / Fanta::modulo[k][a[k][j]]);
				}
			}

			if (Fanta::modulo[k][a[k][j]] == 3) {
				output += QString::fromStdString(
						tmpString + "  |</pre>" + bordi);
			} else if (a[k][j] == 0) {
				output += QString::fromStdString(tmpString);
			} else {
				output += QString::fromStdString(tmpString + "|</pre>" + bordi);
			}

			tmpString = "";
		}

		if (k == 0) {
			output += QString::fromStdString(separatore + bordi);
		}
	}

	output += QString::fromStdString("</pre>" + fondo);
	LOG(INFO, output);
}
