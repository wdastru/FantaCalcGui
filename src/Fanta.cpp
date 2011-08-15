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
	// TODO Auto-generated destructor stub
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
		tmpPlayer.GoalFatti = atof(STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3;
		tmpPlayer.GoalSubiti = 0;
		tmpPlayer.RigoreSbagliato = fabs(
				atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
		tmpPlayer.RigoreParato = 0;
	} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "C") {
		tmpPlayer.Ruolo = 2;
		tmpPlayer.GoalFatti = atof(STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3;
		tmpPlayer.GoalSubiti = 0;
		tmpPlayer.RigoreSbagliato = fabs(
				atoi(STR_MOD->msk(str, DELIM, ColRigore).c_str()) / 3);
		tmpPlayer.RigoreParato = 0;
	} else if (STR_MOD->msk(str, DELIM, ColRuolo) == "A") {
		tmpPlayer.Ruolo = 3;
		tmpPlayer.GoalFatti = atof(STR_MOD->msk(str, DELIM, ColGoalFatti).c_str()) / 3;
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
		tmpPlayer.VotoGazzetta = atof(STR_MOD->msk(str, DELIM, ColVotoGazzetta).c_str());

	// goal decisivi ed altro
	tmpPlayer.GoalDecVitt = atoi(STR_MOD->msk(str, DELIM, ColGoalDecVitt).c_str());
	if (tmpPlayer.GoalDecVitt != 0 && tmpPlayer.GoalFatti == 0)
		return PLAYER_GDV_NO_GOAL;

	tmpPlayer.GoalDecPar = atoi(STR_MOD->msk(str, DELIM, ColGoalDecPar).c_str());
	if (tmpPlayer.GoalDecPar != 0 && tmpPlayer.GoalFatti == 0)
		return PLAYER_GDP_NO_GOAL;

	tmpPlayer.Assist = atoi(STR_MOD->msk(str, DELIM, ColAssist).c_str());
	tmpPlayer.Autoreti = abs(atoi(STR_MOD->msk(str, DELIM, ColAutoreti).c_str()) / 2);
	tmpPlayer.Amm = abs(int(atof(STR_MOD->msk(str, DELIM, ColAmm).c_str()) / 0.5));
	tmpPlayer.Esp = abs(atoi(STR_MOD->msk(str, DELIM, ColEsp).c_str()));

	tmpPlayer.daSostituire = 0;

	for (size_t kk = 0; kk < 2; kk++) {
		for (size_t i = 0; i < Team[kk].size(); i++) {
			if (tmpPlayer.Nome == Fanta::Team[kk].at(i).Nome && tmpPlayer.Ruolo
					== Fanta::Team[kk].at(i).Ruolo)
				return PLAYER_REPEATED;
		}
	}

	Fanta::Team[k].push_back(tmpPlayer);
	return PLAYER_OK;
}

const unsigned int cost_del = 1;
const unsigned int cost_ins = 1;
const unsigned int cost_sub = 1;

unsigned int Fanta::LevenshteinDistance(const std::string& s1, const std::string& s2) {
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
	this->checkGiocatoSenzaVoto();
	this->checkNonHaGiocato();
	this->orderByRuolo();
	this->fillWithNonHaGiocato();
	return;
//	this->substitutions();
//	this->calculateFantaVoto();
//	this->calculateDefenseMean();
//	this->calculateDefenseModifier();
//	this->calculateSfide();
//	this->calculateTotal();
//	this->calculateGoals();
//	this->calculateScorers();
}
void Fanta::checkGiocatoSenzaVoto() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t j = 0; j < this->Team[k].size(); j++) // loop sui giocatori
		{
			if (this->Team[k].at(j).VotoGazzetta == -1) {
				if (this->Team[k].at(j).Ruolo == 0) // se è un portiere
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

				} else //se non è un portiere
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
										+ ") non ha giocato 25' : verrà effettuata una sostituzione.");
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
	for (size_t k = 0; k < 2; k++)// loop sulle squadre
	{
		LOG(
				DEBUG,
				"In Fanta::orderByRuolo() --> Squadra : " + QString::fromStdString(
						this->getTeamName(k)));

		for (size_t i = 0; i < 4; i++) // loop sui ruoli
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
											my::toString<unsigned int>(i))
									+ " " + QString::fromStdString(
									this->Team[k].at(j).Nome));
				}
			}
		}
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
			}
			// aggiungere giocatori NonHaGiocato fino a completare il modulo + 2 sostituzioni
		}
	}
	//cout << "<-- fillWithNonHaGiocato" << endl;
}
/*
unsigned int Fanta::getSubstitutions(size_t k) const {
	return Fanta::sostituzioni[k];
}
unsigned int Fanta::getAmmonizioniTot(unsigned int k) const {
	unsigned int amm = 0;

	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][i]) {
			amm += Fanta::teamOrderedByRuolo[k][i].at(j).Amm;
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
std::string Fanta::getVariablesValues() {
	std::string message;
	message += "START of message: \n--------------------\n\n";
	for (size_t kk = 0; kk < 2; kk++) {
		for (size_t i = 0; i < Team[kk].size(); i++) {
			message += (Team[kk].at(i).Nome + '\n');
			message += ("    GoalDecVitt : " + QString::number(
					Team[kk].at(i).GoalDecVitt).toStdString() + '\n');
			message += ("    GoalDecPar  : " + QString::number(
					Team[kk].at(i).GoalDecPar).toStdString() + '\n');
		}
	}
	return message;
}

#define PLAYER_OK 			0
#define PLAYER_REPEATED 	1
#define PLAYER_GDV_NO_GOAL 	2
#define PLAYER_GDP_NO_GOAL 	3

void Fanta::printFormationPor2Att(unsigned int k) {
	std::string tmpStringNomi = "";
	std::string tmpStringVoti = "";
	std::string
			bordi =
					"|                                                                                |";
	std::string
			linea =
					"|--------------------------------------------------------------------------------|";

	cout << linea << endl << bordi << endl << bordi << endl;
	for (size_t j = 0; j < 4; j++)// ruolo
	{
		for (size_t i = 0; i < Fanta::modulo[k][j]; i++) {
			if (Fanta::modulo[k][j] != 3) {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][j].at(i).Nome),
								80 / Fanta::modulo[k][j]);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][j].at(i).FantaVoto)
										+ " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][j].at(
														i).VotoGazzetta) + ")"),
								80 / Fanta::modulo[k][j]);
			} else {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][j].at(i).Nome),
								25);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][j].at(i).FantaVoto)
										+ " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][j].at(
														i).VotoGazzetta) + ")"),
								25);
			}
		}

		cout << "|" << centerString(tmpStringNomi, 80) << "|" << endl;
		cout << "|" << centerString(tmpStringVoti, 80) << "|" << endl;
		cout << bordi << endl << bordi << endl;

		tmpStringNomi = "";
		tmpStringVoti = "";
	}
	cout << linea;
}
void Fanta::printFormationPor2Att_toFile(unsigned int k, ofstream & fOut) {
	std::string tmpStringNomi = "";
	std::string tmpStringVoti = "";
	std::string
			bordi =
					"|                                                                                |";
	std::string
			linea =
					"|--------------------------------------------------------------------------------|";

	fOut << linea << endl << bordi << endl << bordi << endl;
	for (size_t j = 0; j < 4; j++)// ruolo
	{
		for (size_t i = 0; i < Fanta::modulo[k][j]; i++) {
			if (Fanta::modulo[k][j] != 3) {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][j].at(i).Nome),
								80 / Fanta::modulo[k][j]);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][j].at(i).FantaVoto)
										+ " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][j].at(
														i).VotoGazzetta) + ")"),
								80 / Fanta::modulo[k][j]);
			} else {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][j].at(i).Nome),
								25);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][j].at(i).FantaVoto)
										+ " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][j].at(
														i).VotoGazzetta) + ")"),
								25);
			}
		}

		fOut << "|" << centerString(tmpStringNomi, 80) << "|" << endl;
		fOut << "|" << centerString(tmpStringVoti, 80) << "|" << endl;
		fOut << bordi << endl << bordi << endl;

		tmpStringNomi = "";
		tmpStringVoti = "";
	}
	fOut << linea;
}
void Fanta::printFormationAtt2Por(unsigned int k) {
	std::string tmpStringNomi = "";
	std::string tmpStringVoti = "";
	std::string
			bordi =
					"|                                                                                |";
	std::string
			linea =
					"|--------------------------------------------------------------------------------|";

	cout << linea << endl << bordi << endl << bordi << endl;
	for (size_t j = 0; j < 4; j++)// ruolo
	{
		for (size_t i = 0; i < Fanta::modulo[k][3 - j]; i++) {
			if (Fanta::modulo[k][3 - j] != 3) {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).Nome),
								80 / Fanta::modulo[k][3 - j]);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).FantaVoto) + " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][3
														- j].at(i).VotoGazzetta)
										+ ")"), 80 / Fanta::modulo[k][3 - j]);

			} else {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).Nome), 25);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).FantaVoto) + " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][3
														- j].at(i).VotoGazzetta)
										+ ")"), 25);
			}
		}

		cout << "|" << centerString(tmpStringNomi, 80) << "|" << endl;
		cout << "|" << centerString(tmpStringVoti, 80) << "|" << endl;
		cout << bordi << endl << bordi << endl;

		tmpStringNomi = "";
		tmpStringVoti = "";
	}
	cout << linea;
}
void Fanta::printFormationAtt2Por_toFile(unsigned int k, ofstream & fOut) {
	std::string tmpStringNomi = "";
	std::string tmpStringVoti = "";
	std::string
			bordi =
					"|                                                                                |";
	std::string
			linea =
					"|--------------------------------------------------------------------------------|";

	fOut << linea << endl << bordi << endl << bordi << endl;
	for (size_t j = 0; j < 4; j++)// ruolo
	{
		for (size_t i = 0; i < Fanta::modulo[k][3 - j]; i++) {
			if (Fanta::modulo[k][3 - j] != 3) {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).Nome),
								80 / Fanta::modulo[k][3 - j]);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).FantaVoto) + " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][3
														- j].at(i).VotoGazzetta)
										+ ")"), 80 / Fanta::modulo[k][3 - j]);

			} else {
				tmpStringNomi
						+= centerString(
								onlySurname(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).Nome), 25);

				tmpStringVoti
						+= centerString(
								(toString(
										Fanta::teamOrderedByRuolo[k][3 - j].at(
												i).FantaVoto) + " ("
										+ toString(
												Fanta::teamOrderedByRuolo[k][3
														- j].at(i).VotoGazzetta)
										+ ")"), 25);
			}
		}

		fOut << "|" << centerString(tmpStringNomi, 80) << "|" << endl;
		fOut << "|" << centerString(tmpStringVoti, 80) << "|" << endl;
		fOut << bordi << endl << bordi << endl;

		tmpStringNomi = "";
		tmpStringVoti = "";
	}
	fOut << linea;
}
void Fanta::printPlayersInfo(unsigned k) {
	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][i]) {
			cout << endl << '\t' << "---> "
					<< Fanta::teamOrderedByRuolo[k][i].at(j).Nome << " <---"
					<< endl;
			cout << endl;

			cout.width(17);
			cout << " Voto : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).VotoGazzetta;
			cout.width(17);
			cout << "FantaVoto : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto << endl;
			cout.width(17);
			cout << " Goal Fatti : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).GoalFatti;
			cout.width(17);
			cout << "Goal Subiti : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).GoalSubiti << endl;
			cout.width(17);
			cout << " Goal Dec Vitt : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecVitt;
			cout.width(17);
			cout << "Goal Dec Par : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecPar << endl;
			cout.width(17);
			cout << " Ammonizioni : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).Amm;
			cout.width(17);
			cout << "Espulsioni : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).Esp << endl;
			cout.width(17);
			cout << " Assist : ";
			cout.width(3);
			cout << Fanta::teamOrderedByRuolo[k][i].at(j).Assist << endl
					<< endl;
			j++;
		}
	}
}
void Fanta::printPlayersInfo_toFile(unsigned k, ofstream & fOut) {
	for (size_t i = 0; i < 4; i++) // ruolo
	{
		size_t j = 0;
		while (j < Fanta::modulo[k][i]) {
			if (Fanta::teamOrderedByRuolo[k][i].at(j).Nome != "---") {
				fOut << endl << '\t' << "---> "
						<< Fanta::teamOrderedByRuolo[k][i].at(j).Nome
						<< " <---" << endl;
				fOut << endl;

				fOut.width(18);
				fOut << " Voto : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).VotoGazzetta;
				fOut.width(18);
				fOut << "FantaVoto : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto << endl;
				fOut.width(18);
				fOut << " Goal Fatti : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).GoalFatti;
				fOut.width(18);
				fOut << "Goal Subiti : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).GoalSubiti
						<< endl;
				fOut.width(18);
				fOut << " Goal Dec Vitt : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecVitt;
				fOut.width(18);
				fOut << "Goal Dec Par : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).GoalDecPar
						<< endl;
				fOut.width(18);
				fOut << " Rig. Parato : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).RigoreParato;
				fOut.width(18);
				fOut << "Rig. Sbagliato : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).RigoreSbagliato
						<< endl;
				fOut.width(18);
				fOut << " Ammonizioni : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).Amm;
				fOut.width(18);
				fOut << "Espulsioni : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).Esp << endl;
				fOut.width(18);
				fOut << " Assist : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).Assist;
				fOut.width(18);
				fOut << "Autoreti : ";
				fOut.width(3);
				fOut << Fanta::teamOrderedByRuolo[k][i].at(j).Autoreti << endl
						<< endl;
			}
			j++;
		}
	}
}
void Fanta::printRiepilogo() {
	cout << " Modulo " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << getModuloSquadra(0) << endl;
	cout << " Modulo " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << getModuloSquadra(1) << endl
			<< endl;

	cout << " Fattore Campo " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::atHome[0] << endl;
	cout << " Fattore Campo " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::atHome[1] << endl
			<< endl;

	cout << " Ammonizioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getAmmonizioniTot(0)
			<< endl;
	cout << " Ammonizioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getAmmonizioniTot(1)
			<< endl << endl;

	cout << " Espulsioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getEspulsioniTot(0)
			<< endl;
	cout << " Espulsioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getEspulsioniTot(1)
			<< endl << endl;

	cout << " Goal decisivi vittoria " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecVittTot(0)
			<< endl;
	cout << " Goal decisivi vittoria " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecVittTot(1)
			<< endl << endl;

	cout << " Goal decisivi pareggio " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecParTot(0)
			<< endl;
	cout << " Goal decisivi pareggio " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecParTot(1)
			<< endl << endl;

	cout << " Assist " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getAssistTot(0) << endl;
	cout << " Assist " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getAssistTot(1) << endl
			<< endl;

	cout << " Numero sfide " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::sfide[0] << endl;
	cout << " Numero sfide " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::sfide[1] << endl
			<< endl;

	cout << " Sostituzioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::sostituzioni[0] << endl;
	cout << " Sostituzioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::sostituzioni[1] << endl
			<< endl;

	cout << " Dettaglio Sfide : " << endl;
	cout << "\t|" << endl;
	cout << "\t|" << " Dif " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	cout.width(3);
	cout << Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][1].at(0).Nome << endl;
	cout << "\t|" << " Att " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	cout.width(3);
	cout << Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][3].at(0).Nome << endl;
	cout << "\t|" << endl;
	cout << "\t|" << " Cen " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	cout.width(3);
	cout << Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][2].at(0).Nome << endl;
	cout << "\t|" << " Cen " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	cout.width(3);
	cout << Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][2].at(0).Nome << endl;
	cout << "\t|" << endl;
	cout << "\t|" << " Att " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	cout.width(3);
	cout << Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][3].at(0).Nome << endl;
	cout << "\t|" << " Dif " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	cout.width(3);
	cout << Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][1].at(0).Nome << endl;
	cout << "\t|" << endl;
	cout << "\t+--------------------------------------------->" << endl << endl;

	cout << " Media Difesa " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::defenseMean[0] << " ( "
			<< Fanta::defenders[0] << " )" << endl;
	cout << " Media Difesa " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::defenseMean[1] << " ( "
			<< Fanta::defenders[1] << " )" << endl << endl;

	cout << " Modificatore " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::modifier[0] << endl;
	cout << " Modificatore " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::modifier[1] << endl
			<< endl;

	cout << " " << leftString(Fanta::getTeamName(0), Fanta::longerNameLength)
			<< " : " << Fanta::goals[0] << " ( " << Fanta::Total[0] << " : ";
	for (size_t i = 0; i < Fanta::scorers[0].size(); i++) {
		cout << onlySurname(Fanta::scorers[0].at(i));
		if (i < Fanta::scorers[0].size() - 1)
			cout << ", ";
		else
			cout << " ";
	}
	cout << ")" << endl;
	cout << " " << leftString(Fanta::getTeamName(1), Fanta::longerNameLength)
			<< " : " << Fanta::goals[1] << " ( " << Fanta::Total[1] << " : ";
	for (size_t i = 0; i < Fanta::scorers[1].size(); i++) {
		cout << onlySurname(Fanta::scorers[1].at(i));
		if (i < Fanta::scorers[1].size() - 1)
			cout << ", ";
		else
			cout << " ";
	}
	cout << ")" << endl << endl;
}
void Fanta::printRiepilogo_toFile(ofstream & fOut) {
	fOut << " Modulo " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << getModuloSquadra(0) << endl;
	fOut << " Modulo " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << getModuloSquadra(1) << endl
			<< endl;

	fOut << " Fattore Campo " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::atHome[0] << endl;
	fOut << " Fattore Campo " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::atHome[1] << endl
			<< endl;

	fOut << " Ammonizioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getAmmonizioniTot(0)
			<< endl;
	fOut << " Ammonizioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getAmmonizioniTot(1)
			<< endl << endl;

	fOut << " Espulsioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getEspulsioniTot(0)
			<< endl;
	fOut << " Espulsioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getEspulsioniTot(1)
			<< endl << endl;

	fOut << " Goal decisivi vittoria " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecVittTot(0)
			<< endl;
	fOut << " Goal decisivi vittoria " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecVittTot(1)
			<< endl << endl;

	fOut << " Goal decisivi pareggio " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecParTot(0)
			<< endl;
	fOut << " Goal decisivi pareggio " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecParTot(1)
			<< endl << endl;

	fOut << " Assist " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getAssistTot(0) << endl;
	fOut << " Assist " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getAssistTot(1) << endl
			<< endl;

	fOut << " Numero sfide " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::sfide[0] << endl;
	fOut << " Numero sfide " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::sfide[1] << endl
			<< endl;

	fOut << " Sostituzioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::sostituzioni[0] << endl;
	fOut << " Sostituzioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::sostituzioni[1] << endl
			<< endl;

	fOut << " Dettaglio Sfide : " << endl;
	fOut << "\t|" << endl;
	fOut << "\t|" << " Dif " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][1].at(0).Nome << endl;
	fOut << "\t|" << " Att " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][3].at(0).Nome << endl;
	fOut << "\t|" << endl;
	fOut << "\t|" << " Cen " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][2].at(0).Nome << endl;
	fOut << "\t|" << " Cen " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][2].at(0).Nome << endl;
	fOut << "\t|" << endl;
	fOut << "\t|" << " Att " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][3].at(0).Nome << endl;
	fOut << "\t|" << " Dif " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][1].at(0).Nome << endl;
	fOut << "\t|" << endl;
	fOut << "\t+--------------------------------------------->" << endl << endl;

	fOut << " Media Difesa " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::defenseMean[0] << " ( "
			<< Fanta::defenders[0] << " )" << endl;
	fOut << " Media Difesa " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::defenseMean[1] << " ( "
			<< Fanta::defenders[1] << " )" << endl << endl;

	fOut << " Modificatore " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::modifier[0] << endl;
	fOut << " Modificatore " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::modifier[1] << endl
			<< endl;

	fOut << " " << leftString(Fanta::getTeamName(0), Fanta::longerNameLength)
			<< " : " << Fanta::goals[0] << " ( " << Fanta::Total[0] << " : ";
	for (size_t i = 0; i < Fanta::scorers[0].size(); i++) {
		fOut << onlySurname(Fanta::scorers[0].at(i));
		if (i < Fanta::scorers[0].size() - 1)
			fOut << ", ";
		else
			fOut << " ";
	}
	fOut << ")" << endl;
	fOut << " " << leftString(Fanta::getTeamName(1), Fanta::longerNameLength)
			<< " : " << Fanta::goals[1] << " ( " << Fanta::Total[1] << " : ";
	for (size_t i = 0; i < Fanta::scorers[1].size(); i++) {
		fOut << onlySurname(Fanta::scorers[1].at(i));
		if (i < Fanta::scorers[1].size() - 1)
			fOut << ", ";
		else
			fOut << " ";
	}
	fOut << ")" << endl << endl;
}
void Fanta::printRiepilogo_toHtml(ofstream & fOut) {
	fOut << " Modulo " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << getModuloSquadra(0) << endl;
	fOut << " Modulo " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << getModuloSquadra(1) << endl
			<< endl;

	fOut << " Fattore Campo " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::atHome[0] << endl;
	fOut << " Fattore Campo " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::atHome[1] << endl
			<< endl;

	fOut << " Ammonizioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getAmmonizioniTot(0)
			<< endl;
	fOut << " Ammonizioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getAmmonizioniTot(1)
			<< endl << endl;

	fOut << " Espulsioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getEspulsioniTot(0)
			<< endl;
	fOut << " Espulsioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getEspulsioniTot(1)
			<< endl << endl;

	fOut << " Goal decisivi vittoria " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecVittTot(0)
			<< endl;
	fOut << " Goal decisivi vittoria " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecVittTot(1)
			<< endl << endl;

	fOut << " Goal decisivi pareggio " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecParTot(0)
			<< endl;
	fOut << " Goal decisivi pareggio " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getGoalDecParTot(1)
			<< endl << endl;

	fOut << " Assist " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::getAssistTot(0) << endl;
	fOut << " Assist " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::getAssistTot(1) << endl
			<< endl;

	fOut << " Numero sfide " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::sfide[0] << endl;
	fOut << " Numero sfide " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::sfide[1] << endl
			<< endl;

	fOut << " Sostituzioni " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::sostituzioni[0] << endl;
	fOut << " Sostituzioni " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::sostituzioni[1] << endl
			<< endl;

	fOut << " Dettaglio Sfide : " << endl;
	fOut << "\t|" << endl;
	fOut << "\t|" << " Dif " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][1].at(0).Nome << endl;
	fOut << "\t|" << " Att " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][3].at(0).Nome << endl;
	fOut << "\t|" << endl;
	fOut << "\t|" << " Cen " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][2].at(0).Nome << endl;
	fOut << "\t|" << " Cen " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][2].at(0).Nome << endl;
	fOut << "\t|" << endl;
	fOut << "\t|" << " Att " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[0][3].at(0).Nome << endl;
	fOut << "\t|" << " Dif " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : ";
	fOut.width(3);
	fOut << Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta << '\t'
			<< Fanta::teamOrderedByRuolo[1][1].at(0).Nome << endl;
	fOut << "\t|" << endl;
	fOut << "\t+--------------------------------------------->" << endl << endl;

	fOut << " Media Difesa " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::defenseMean[0] << " ( "
			<< Fanta::defenders[0] << " )" << endl;
	fOut << " Media Difesa " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::defenseMean[1] << " ( "
			<< Fanta::defenders[1] << " )" << endl << endl;

	fOut << " Modificatore " << leftString(Fanta::getTeamName(0),
			Fanta::longerNameLength) << " : " << Fanta::modifier[0] << endl;
	fOut << " Modificatore " << leftString(Fanta::getTeamName(1),
			Fanta::longerNameLength) << " : " << Fanta::modifier[1] << endl
			<< endl;

	fOut << " " << leftString(Fanta::getTeamName(0), Fanta::longerNameLength)
			<< " : " << Fanta::goals[0] << " ( " << Fanta::Total[0] << " : ";
	for (size_t i = 0; i < Fanta::scorers[0].size(); i++) {
		fOut << onlySurname(Fanta::scorers[0].at(i));
		if (i < Fanta::scorers[0].size() - 1)
			fOut << ", ";
		else
			fOut << " ";
	}
	fOut << ")" << endl;
	fOut << " " << leftString(Fanta::getTeamName(1), Fanta::longerNameLength)
			<< " : " << Fanta::goals[1] << " ( " << Fanta::Total[1] << " : ";
	for (size_t i = 0; i < Fanta::scorers[1].size(); i++) {
		fOut << onlySurname(Fanta::scorers[1].at(i));
		if (i < Fanta::scorers[1].size() - 1)
			fOut << ", ";
		else
			fOut << " ";
	}
	fOut << ")" << endl << endl;
}
void Fanta::substitutions() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			for (size_t j = 0; j < Fanta::teamOrderedByRuolo[k][i].size(); j++) // loop sui tutti i giocatori
			{
				if (Fanta::teamOrderedByRuolo[k][i].at(j).daSostituire == 1)
					Fanta::teamOrderedByRuolo[k][i].at(j) = Fanta::NonHaGiocato;
			}
		}
	}

	// sposta i 'NON HA GIOCATO' al fondo dei giocatori in campo
	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			//			debug << endl;
			//			for(size_t yy = 0; yy < Fanta::teamOrderedByRuolo[ k ][ i ].size(); yy++ )
			//				debug << Fanta::teamOrderedByRuolo[ k ][ i ].at( yy ).Nome << endl;

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

	// se il primo panchinaro non ha giocato lo swappa con il secondo:
	// se anch'esso non ha giocato non serve a nulla, se ha giocato lo porta in prima posizione
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
		for (size_t t = 0; t < 3; t++) // ripetere il loop sottostante per esaurire tutte le sostituzioni
		{
			for (size_t i = 0; i < 7; i++) // loop sulla dimensione di a[]
			{
				unsigned int w = Fanta::modulo[k][a[i]];

				//				debug << endl << "#### modulo : " << w << endl;

				for (size_t j = 0; j < w; j++) // loop sui giocatori
				{
					if (Fanta::teamOrderedByRuolo[k][a[i]].at(j).Nome == "---"
							&& sostituzioni[k] < 3) {
						//						debug << endl;
						//						for(size_t yy = 0; yy < Fanta::teamOrderedByRuolo[ k ][ a[ i ] ].size(); yy++ )
						//							debug << Fanta::teamOrderedByRuolo[ k ][ a[ i ] ].at( yy ).Nome << endl;

						//						debug << endl << "if j( " << j << " ) : " << Fanta::teamOrderedByRuolo[ k ][ a[ i ] ].at( j ).Nome << tab << sostituzioni[ k ] << endl;

						for (size_t x = w; x
								< Fanta::teamOrderedByRuolo[k][a[i]].size(); x++) {
							if (Fanta::teamOrderedByRuolo[k][a[i]].at(x).Nome
									!= "---") {
								sostituzioni[k]++;
								//debug << endl << tab << "if x( " << x << " ) : " << Fanta::teamOrderedByRuolo[ k ][ a[ i ] ].at( x ).Nome  << tab << sostituzioni[ k ] << endl;
								swap(
										Fanta::teamOrderedByRuolo[k][a[i]].at(x),
										Fanta::teamOrderedByRuolo[k][a[i]].at(j));
								//debug << endl << tab << "if x( " << x << " ) : " << Fanta::teamOrderedByRuolo[ k ][ a[ i ] ].at( x ).Nome  << tab << sostituzioni[ k ] << endl;

								//debug << endl;
								//for(size_t yy = 0; yy < Fanta::teamOrderedByRuolo[ k ][ a[ i ] ].size(); yy++ )
								//debug << Fanta::teamOrderedByRuolo[ k ][ a[ i ] ].at( yy ).Nome << endl;

								//break;
								goto label;
								// serve per poter uscire da due loop contemporaneamente
							}
						}
					}
				}
				label: // solo una sostituzione per ruolo ( per volta )
				;
			}
		}
	}

	for (size_t k = 0; k < 2; k++) // squadra
	{
		for (size_t i = 0; i < 4; i++) // ruolo
		{
			Fanta::teamOrderedByRuolo[k][i].resize(Fanta::modulo[k][i]);

			// debug << endl;
			// for(size_t yy = 0; yy < Fanta::teamOrderedByRuolo[ k ][ i ].size(); yy++ )
			// debug << Fanta::teamOrderedByRuolo[ k ][ i ].at( yy ).Nome << endl;
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
				j++;
			}
		}
	}
	//cout << "<-- calculateFantaVoto" << endl;
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
	}
	//cout << "<-- calculateDefenseMean" << endl;
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
	//cout << "<-- calculateDefenseModifier" << endl;
}
void Fanta::calculateSfide() {
	if (Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta)
		Fanta::sfide[0]++;
	else if (Fanta::teamOrderedByRuolo[0][1].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][3].at(0).VotoGazzetta)
		Fanta::sfide[1]++;

	if (Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta)
		Fanta::sfide[0]++;
	else if (Fanta::teamOrderedByRuolo[0][2].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][2].at(0).VotoGazzetta)
		Fanta::sfide[1]++;

	if (Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta
			> Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta)
		Fanta::sfide[0]++;
	else if (Fanta::teamOrderedByRuolo[0][3].at(0).VotoGazzetta
			< Fanta::teamOrderedByRuolo[1][1].at(0).VotoGazzetta)
		Fanta::sfide[1]++;

	//cout << "<-- calculateSfide" << endl;
}
void Fanta::calculateTotal() {
	for (size_t k = 0; k < 2; k++) // squadra
	{
		Fanta::Total[k] += Fanta::atHome[k];
		Fanta::Total[k] += Fanta::modifier[k];
		Fanta::Total[k] += Fanta::sfide[k];

		for (size_t i = 0; i < 4; i++) // ruolo
		{
			size_t j = 0;
			while (j < Fanta::modulo[k][i]) {
				Fanta::Total[k]
						+= Fanta::teamOrderedByRuolo[k][i].at(j).FantaVoto;
				j++;
			}
		}
	}
	//cout << "<-- calculateTotal" << endl;
}
void Fanta::calculateGoals() {
	for (size_t k = 0; k < 2; k++) {
		for (size_t i = 0;; i++) {
			if (Fanta::Total[k] >= (6 * i))
				continue;

			if ((i - 10) > 0) {
				Fanta::goals[k] = i - 11;
				break;
			} else {
				Fanta::goals[k] = 0;
				break;
			}
		}
	}

	if (Fanta::Total[0] < 66 && Fanta::Total[1] < 66) {
		if (Fanta::Total[0] >= Fanta::Total[1] + 6) {
			Fanta::goals[0] = 1;
			Fanta::goals[1] = 0;
		} else if (Fanta::Total[1] >= Fanta::Total[0] + 6) {
			Fanta::goals[1] = 1;
			Fanta::goals[0] = 0;
		} else {
			Fanta::goals[1] = 0;
			Fanta::goals[0] = 0;
		}
	}

	for (size_t k = 0; k < 2; k++) {
		if (Fanta::goals[k] < 0)
			Fanta::goals[k] = 0;

	}
}
void Fanta::calculateScorers() {
	//debug << "--> calculateScorers" << endl;

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
			tmpVector[k].at(0).FantaVoto -= 3.0;
		} while (Fanta::scorers[k].size() < Fanta::goals[k]);
	}
	//debug << "<-- calculateScorers" << endl;
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
*/
