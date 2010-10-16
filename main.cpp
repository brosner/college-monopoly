#include <iostream>
#include <windows.h>

#include "settings.h"
#include "classes\Player.h"
#include "classes\Space.h"

using namespace std;

/* function prototypes */
inline int randomNumber(int);
void initGame();
void runSimulation();
void rollDice(int *);
void nextPlayer();
void movePlayer(int);

/* global variables */
Space *arGameSpaces[MONOPOLY_BOARD_SPACES];
Space **pGameSpace = arGameSpaces;

Player *arGamePlayers[MONOPOLY_NUM_PLAYERS];
Player **pGamePlayer = arGamePlayers;

inline int randomNumber(int iMax) {
	__int64 seed;
	QueryPerformanceCounter((LARGE_INTEGER *)&seed);
	srand((unsigned int)seed);
	return (rand() % iMax) + 1;
}
void Write(char *);
void Write(char *,int);

int main(int argc,char *argv[]) {
	/* initialize the game */
	initGame();

	__int64 pf,st,et;

	QueryPerformanceFrequency((LARGE_INTEGER *)&pf);
	QueryPerformanceCounter((LARGE_INTEGER *)&st);
	runSimulation();
	QueryPerformanceCounter((LARGE_INTEGER *)&et);

	double ticks = et - st;
	double secs = ticks / (double)pf;
	double milsecs = secs * 1000;
	double microsecs = milsecs * 1000;

	int decimal,sign;
	char* buffer = _fcvt(milsecs,2,&decimal,&sign);
	Write("\nDuration: ");
	Write(buffer,decimal);
	Write(".");
	Write(buffer+decimal);
	Write(" milliseconds\n");
	
	/* pause system */
	system("pause");
}

void Write(char* line) {
	Write(line,strlen(line));
}

void Write(char* line, int charcount) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;
	WriteConsoleA(hOut,line,charcount,&written,0);
}


void initGame() {
	/* setup each property */
	arGameSpaces[0] = new Space(200);
	arGameSpaces[1] = new Space(new Property("A",2000));
	arGameSpaces[2] = new Space(new Chance(CHANCE_ASSIGN_NEW_INVESTMENT_STRATEGY,0));
	arGameSpaces[3] = new Space(new Chance(CHANCE_GIVE_PLAYER_MONEY,300));
	arGameSpaces[4] = new Space(new Property("B",500));
	arGameSpaces[5] = new Space(new Property("C",800));
	arGameSpaces[6] = new Space(new Chance(CHANCE_TAKE_PLAYER_MONEY,500));
	arGameSpaces[7] = new Space(new Chance(CHANCE_MOVE_BACK_PLAYER,3));
	arGameSpaces[8] = new Space(new Property("D",1200));
	arGameSpaces[9] = new Space(new Chance(CHANCE_ASSIGN_NEW_INVESTMENT_STRATEGY,0));
	
	/* create players */
	arGamePlayers[0] = new Player("Computer #1",pGameSpace);
	arGamePlayers[1] = new Player("Computer #2",pGameSpace);
	arGamePlayers[2] = new Player("Computer #3",pGameSpace);
	arGamePlayers[3] = new Player("Computer #4",pGameSpace);
}

void runSimulation() {
	bool bRunGame = true, bMoveLimit = false, bWinner = false;
	int iMoveCount = 1, iDieRoll;
	Space **currPlayerSpace;

	while(bRunGame) {
		if(iMoveCount >= MONOPOLY_MOVE_LIMIT) {
			bMoveLimit = true;
			bRunGame = false;
		}
		
		if((*pGamePlayer)->getCash() <= 0) {
			bWinner = true;
			bRunGame = false;
		}
		
		/* roll dice and move player */
		rollDice(&iDieRoll);
		movePlayer(iDieRoll);
		
		/* get current player space */
		currPlayerSpace = (*pGamePlayer)->getCurrSpace();
		
		cout << (*pGamePlayer)->getPlayerName()
		<< " - Cash: " << (*pGamePlayer)->getCash()
		<< " - Rolled: " << iDieRoll
		<< " - Landed On: " << (*currPlayerSpace)->getSpace()
		/*<< " - Move: " << iMoveCount*/ << endl;
		
		/* player landed on GO add the pass go amount */
		if((*currPlayerSpace)->getSpaceType() == SPACE_TYPE_GO) {
			(*pGamePlayer)->addCash(PASS_GO_AMOUNT);
		}
		
		if((*currPlayerSpace)->getSpaceType() == SPACE_TYPE_PROPERTY) {
			/* get the property object */
			Property *p = (*currPlayerSpace)->getProperty();

			/* check if property is owned */
			if(p->getOwned()) {
				/* make player pay rent if it isn't the owner */
				if(pGamePlayer != p->getPropertyOwner()) {
					(*pGamePlayer)->takeCash(p->getPropertyRent());
					
					cout << "\tPayed rent to "
					 << (*p->getPropertyOwner())->getPlayerName()
					 << endl;
				}
				else {
					if((*pGamePlayer)->getStrategy() == 1) {
						int iRand = randomNumber(6) - 1;

						if((*pGamePlayer)->getCash() > (p->getHouseCost() * iRand)) {
							p->addHouses(iRand);

							cout << "\tPurchased "
								 << iRand << " houses for this property."
								 << endl;
						}
						else {
							cout << "\tPurchased 0 houses for this property."
								 << endl;
						}
					}
					else if((*pGamePlayer)->getStrategy() == 2) {
						for(int i = 5; i > 0; --i) {
							if((*pGamePlayer)->getCash() > (p->getHouseCost() * i)) {
								p->addHouses(i);
								
								cout << "\tPurchased "
									<< i << " houses for this property."
									<< endl;
								break;
							}
							else {
								if(i == 1) {
									cout << "\tPurchased 0 houses for this property." << endl;
								}
							}
						}
					}
					else if((*pGamePlayer)->getStrategy() == 3) {
						for(int i = 5; i > 0; --i) {
							if((*pGamePlayer)->getCash() > ((p->getHouseCost() * i) * 5)) {
								p->addHouses(i);
								
								cout << "\tPurchased "
									<< i << " houses for this property."
									<< endl;
								break;
							}
							else {
								if(i == 1) {
									cout << "\tPurchased 0 houses for this property." << endl;
								}
							}
						}
					}
					else {
						;
					}
				}
			}
			else {
				if((*pGamePlayer)->getStrategy() == 1) {
					/* random investment - flip coin */
					int iChoice = randomNumber(2);

					if(iChoice == 1) {
						if((*pGamePlayer)->getCash() > p->getPropertyCost()) {
							p->setPropertyOwner(pGamePlayer);

							cout << "\tPurchased Property "
								 << p->getPropertyName()
								 << endl;
						}
					}
					else {
						cout << "\tDecided not to purcahse property." << endl;
					}
				}
				else if((*pGamePlayer)->getStrategy() == 2) {
					if((*pGamePlayer)->getCash() > p->getPropertyCost()) {
						p->setPropertyOwner(pGamePlayer);

						cout << "\tPurchased Property "
								 << p->getPropertyName()
								 << endl;
					}
					else {
						cout << "\tDecided not to purcahse property." << endl;
					}
				}
				else if((*pGamePlayer)->getStrategy() == 3) {
					if((*pGamePlayer)->getCash() > (p->getPropertyCost() * 5)) {
						p->setPropertyOwner(pGamePlayer);

						cout << "\tPurchased Property "
								 << p->getPropertyName()
								 << endl;
					}
					else {
						cout << "\tDecided not to purcahse property." << endl;
					}
				}
				else {
					;
				}
			}
		}

		if((*currPlayerSpace)->getSpaceType() == SPACE_TYPE_CHANCE) {
			/* get the chance object */
			Chance *c = (*currPlayerSpace)->getChance();
			
			/* get the chance amount */
			int iChanceAmount = c->getChanceAmount();

			/* perform the chance action */
			if(c->getGivePlayerMoney()) {
				(*pGamePlayer)->addCash(iChanceAmount);

				cout << "\tReceived $"
					 << iChanceAmount
					 << endl;
			}
			else if(c->getTakePlayerMoney()) {
				(*pGamePlayer)->takeCash(iChanceAmount);

				cout << "\tLost $"
					 << iChanceAmount
					 << endl;
			}
			else if(c->getMoveBackPlayer()) {
				movePlayer(iChanceAmount * -1);

				cout << "\tMoved back "
					 << iChanceAmount << " spaces."
					 << endl;
			}
			else if(c->getMoveForwardPlayer()) {
				movePlayer(iChanceAmount);

				cout << "\tMoved forward "
					 << iChanceAmount << " spaces."
					 << endl;
			}
			else if(c->getAssignNewInvestmentStrategy()) {
				(*pGamePlayer)->setStrategy(0);

				cout << "\tReassigned an investment strategy."
					 << endl;
			}
		}

		/* move to the next player */
		nextPlayer();
		
		/* increase move count */
		++iMoveCount;
	}

	cout << endl << endl << "Completed in " << iMoveCount << " moves." << endl;
	
	if(bMoveLimit) {
		cout << "Move Limit Reached." << endl;
	}
	
	if(bWinner) {
		/* a really dumb sorting algorithm...it works for only 4 elements
		   and only on my array =) */
		Player **pp, **po;

		if(arGamePlayers[0]->getCash() > arGamePlayers[2]->getCash()) {
			pp = &arGamePlayers[0];
		}
		else {
			pp = &arGamePlayers[1];
		}

		if(arGamePlayers[3]->getCash() > arGamePlayers[4]->getCash()) {
			po = &arGamePlayers[3];
		}
		else {
			po = &arGamePlayers[4];
		}

		if(*pp > *po) {
			cout << endl << "Winner is " << (*pp)->getPlayerName()
				 << " with $" << (*pp)->getCash() << endl << endl;
		}
		else {
			cout << endl << "Winner is " << (*po)->getPlayerName()
				 << " with $" << (*po)->getCash() << endl << endl;
		}	
	}
}

void rollDice(int *iRoll) {
	*iRoll = randomNumber(6);
}

void movePlayer(int iMove) {
	/* get player's position */
	int iNewPos, iCurrPos = (*pGamePlayer)->getCurrSpace() - arGameSpaces;
	
	/* move player */
	iNewPos = iCurrPos + iMove;
	
	/* adjust if over */
	if(iNewPos >= MONOPOLY_BOARD_SPACES) {
		iNewPos -= MONOPOLY_BOARD_SPACES;
	}
	
	/* adjust if under (only possible with a backward chance) */
	if(iNewPos < 0) {
		iNewPos += MONOPOLY_BOARD_SPACES;
	}
	
	/* assign new space */
	Space **newSpace = &arGameSpaces[iNewPos];
	(*pGamePlayer)->setCurrSpace(newSpace);
}

/**
 * nextPlayer() keeps track of each player.
 * it will return a pointer to a Player object
 * of the next player to play.
 */
void nextPlayer() {
	static int iCurrPlayer = 0;
	
	++iCurrPlayer;
	++pGamePlayer;
	
	/* test for last player */
	if(iCurrPlayer == 4) {
		iCurrPlayer = 0;
		pGamePlayer = arGamePlayers;
	}
}

