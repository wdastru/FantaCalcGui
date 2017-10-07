/*
 * Fanta.h
 *
 *  Created on: 29/lug/2011
 *      Author: WAleViolaeIvan
 */

#ifndef FANTA_H_
#define FANTA_H_

#include <math.h>
#include <fstream>
#include <string>

//#include <QtGui/QMessageBox>

#include "defines.h"
#include "singletonQtLogger.h"
#include "StringModifier.h"

using namespace std;

class Fanta {

	friend class FileFormazioniReader;
	friend class Test;

private:
	static Fanta * pInstance;
	unsigned int modulo[2][4];// moduli delle squadre

	unsigned int inCampo[2][4];		// giocatori effettivamenti scesi in campo
	int distanza[2][4];		// giocatori che mancano per arrivare al modulo
	unsigned int disponibili[2][4];	// giocatori in panchina che possono essere usati

	unsigned int inCampoModuli[7][4];			// giocatori effettivamenti scesi in campo nei moduli possibili
	int distanzaModuli[7][4];					// giocatori che mancano per arrivare ai moduli possibili
	unsigned int disponibiliModuli[7][4];		// giocatori in panchina che possono essere usati per i moduli possibili
	unsigned int originalsOutModuli[7][4];		// giocatori orginariamente titolari che escono  per i moduli possibili
	signed int distanzaTotaleModuli[7]; 		// distanza dei giocatori in campo dai moduli possibili
	unsigned int originalsOutTotaleModuli[7]; 	// giocatori totali orginariamente titolari che escono  per i moduli possibili

	double Total[2];
	signed int ruoloDaSostituire[2][10]; // ruoli da sostituire
	signed int modifier[2];
	double defenseMean[2];
	unsigned int defenders[2];
	unsigned int sfide[2];
	unsigned int goals[2];
	unsigned int sostituzioni[2];

	unsigned int moduli[7][4];
	bool moduloPossibile[7];
	std::string labelModuli[7];
	std::vector<QString> subsForModuleChange[2];
	std::vector<QString> subs[2];
	std::vector<QString> newModuleString[2];

	signed int scoreModuli[7];

	size_t longerNameLength;
	signed int modifierValues[9][5];
	float modifierVoti[10];
	struct player {
		std::string Cognome;
		std::string Cognome_Sost;
		std::string Squadra;
		std::string Squadra_Sost;
		signed int Ruolo;
		signed int Ruolo2;
		float FantaVoto;
		float FantaVotoGazzetta;
		float VotoGazzetta;
		float GoalFatti;
		float GoalSubiti;
		float Autoreti;
		unsigned int RigoreParato;
		unsigned int RigoreSbagliato;
		unsigned int GoalDecVitt;
		unsigned int GoalDecPar;
		unsigned int Assist;
		float Amm;
		float Esp;
		unsigned int daSostituire;
	};
	player NonHaGiocato;
	player fakePlayer;
	std::vector<std::string> teamName;
	std::vector<Fanta::player> Team[2];
	unsigned int rosa[4];
	void checkGiocatoSenzaVoto();
	void checkNonHaGiocato();
	void orderByRuolo();
	std::vector<Fanta::player> teamOrderedByRuolo[2][4];
	void fillWithNonHaGiocato();
	void sendNGToBack();
	void substitutions();
	void calculateFantaVoto();
	void calculateDefenseMean();
	void calculateDefenseModifier();
	void calculateSfide();
	void calculateTotal();
	void calculateGoals();
	void calculateScorers();
	std::vector<std::string> scorers[2];
	QString fileGazzetta;
	QString questionMessage(QString);

	/*
	 void reorderPlayers();
	 */

public:
	Fanta();
	virtual ~Fanta();
	static Fanta * Inst();
	static Fanta * Refresh();
	void initialize();
	unsigned int atHome[2];
	void setTeamName(const std::string, unsigned int);
	std::string getTeamName(unsigned int);
	unsigned int setModulo(std::string &, size_t);
	std::string getModuloSquadra(size_t) const ;
	unsigned int getModulo(size_t, size_t) const;
	void setAtHome(unsigned int);
	unsigned int LevenshteinDistance(const std::string& s1,
			const std::string& s2);
	unsigned int addPlayer(std::string &, unsigned int);
	void execute();
	void bSort(std::vector<Fanta::player> &);
	QString getFileGazzetta();
//	void setFileGazzetta(QString);
	void printRiepilogo();
	void printTitolo(std::string, std::string);
	void printPlayersInfo();
	unsigned int getAmmonizioniTot(unsigned int) const ;
	unsigned int getEspulsioniTot(unsigned int) const ;
	unsigned int getGoalDecVittTot(unsigned int) const ;
	unsigned int getGoalDecParTot(unsigned int) const ;
	unsigned int getAssistTot(unsigned int) const ;
	unsigned int getSubstitutions(unsigned int) const ;
	unsigned int getGoals(unsigned int) const;
	double getTotal(unsigned int) const;
	std::string getScorer(unsigned int, unsigned int) const;
	unsigned int getScorersSize(unsigned int k) const;
	void printFormations();

	//	void printTitolo3(std::string);

	/*
	 std::string getVariablesValues();
	 void printRiepilogo_toFile(ofstream &);
	 void printRiepilogo_toHtml(ofstream &);
	 void printPlayersInfo(unsigned int);
	 void printPlayersInfo_toFile(unsigned int, ofstream &);
	 void printPlayersInfo_toHtml(unsigned int, ofstream &);
	 void printFormationPor2Att(
	 unsigned int);
	 void printFormationPor2Att_toHtml(unsigned int, ofstream &);
	 void printFormationAtt2Por(unsigned int);
	 void printFormationAtt2Por_toHtml(unsigned int, ofstream &);
	 bool repeated;
	 */
};

#endif /* FANTA_H_ */
