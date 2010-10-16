#ifndef CHANCE_H
#define CHANCE_H

#include "..\settings.h"

class Chance {
	
	public:
	
	Chance();
	Chance(int,int);
	~Chance();
	
	private:
	int iChanceAmount;
	
	bool bGivePlayerMoney;
	bool bTakePlayerMoney;
	bool bMoveBackPlayer;
	bool bMoveForwardPlayer;
	bool bAssignNewInvestmentStrategy;
	
	void chanceInit() {
		this->bGivePlayerMoney = false;
		this->bTakePlayerMoney = false;
		this->bMoveBackPlayer = false;
		this->bMoveForwardPlayer = false;
		this->bAssignNewInvestmentStrategy = false;
		
		this->iChanceAmount = 0;
	}
	
	public:
	
	int getChanceAmount();
	
	void setGivePlayerMoney(int);
	bool getGivePlayerMoney();
	
	void setTakePlayerMoney(int);
	bool getTakePlayerMoney();
	
	void setMoveBackPlayer(int);
	bool getMoveBackPlayer();
	
	void setMoveForwardPlayer(int);
	bool getMoveForwardPlayer();
	
	void setAssignNewInvestmentStrategy();
	bool getAssignNewInvestmentStrategy();
};

#endif
