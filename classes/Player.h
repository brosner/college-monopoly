#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <windows.h>

#include "Space.h"

class Player {
	public:
	
	Player();
	Player(std::string);
	Player(std::string,Space **);
	~Player();
	
	private:
	
	std::string sPlayerName;
	int iCash;
	Space **currSpace;
	int iPosition;
	int iStrategy;
	
	void playerInit() {
		this->iCash = 0;
		this->sPlayerName = "";
		
		/* initialize default settings */
		this->addCash(5000);
		this->setStrategy(0);
	}
	
	public:
	
	std::string getPlayerName();
	void setPlayerName(std::string);

	int getCash();
	void addCash(int);
	void takeCash(int);

	Space ** getCurrSpace();
	void setCurrSpace(Space **);

	int getStrategy();
	void setStrategy(int);

};

#endif
