
#include "Player.h"

Player::Player() {
	this->playerInit();
}

Player::Player(std::string sName) {
	this->playerInit();
	this->setPlayerName(sName);
}

Player::Player(std::string sName,Space **startPos) {
	this->playerInit();
	this->setPlayerName(sName);
	this->setCurrSpace(startPos);
}

Player::~Player() {
}

std::string Player::getPlayerName() {
	return this->sPlayerName;
}

void Player::setPlayerName(std::string sName) {
	this->sPlayerName = sName;
}

/**
 * getCash() returns how much money
 * this player owns.
 */
int Player::getCash() {
	return this->iCash;
}

/**
 * addCash() will add iAmount to the
 * player's total cash flow.
 */
void Player::addCash(int iAmount) {
	this->iCash += iAmount;
}

/**
 * takeCash() will substract iAmount of
 * the player's cash flow.
 */
void Player::takeCash(int iAmount) {
	this->iCash -= iAmount;
}

Space ** Player::getCurrSpace() {
	return this->currSpace;
}

void Player::setCurrSpace(Space **space) {
	this->currSpace = space;
}

/**
 * getStrategy() will return the player's
 * investment strategy.
 */
int Player::getStrategy() {
	return this->iStrategy;
}

/**
 * setStrategy() will set the player's
 * investment strategy to iStrategy.
 */
void Player::setStrategy(int iStrategy) {
	if(iStrategy == 0) {
		__int64 seed;
		QueryPerformanceCounter((LARGE_INTEGER *)&seed);
		
		srand((unsigned int)seed);
		iStrategy = (rand() % 3) + 1;
	}
	
	this->iStrategy = iStrategy;
}
