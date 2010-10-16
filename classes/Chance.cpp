
#include "Chance.h"

Chance::Chance() {
}

Chance::Chance(int iRule,int i) {
	this->chanceInit();
		
	switch(iRule) {
		case CHANCE_GIVE_PLAYER_MONEY:
			this->setGivePlayerMoney(i);
		break;
		case CHANCE_TAKE_PLAYER_MONEY:
			this->setTakePlayerMoney(i);
		break;
		case CHANCE_MOVE_BACK_PLAYER:
			this->setMoveBackPlayer(i);
		break;
		case CHANCE_MOVE_FORWARD_PLAYER:
			this->setMoveForwardPlayer(i);
		break;
		case CHANCE_ASSIGN_NEW_INVESTMENT_STRATEGY:
			this->setAssignNewInvestmentStrategy();
		break;
	}
}

int Chance::getChanceAmount() {
		return this->iChanceAmount;
	}
	
void Chance::setGivePlayerMoney(int i) {
	this->bGivePlayerMoney = true;
	this->iChanceAmount = i;
}
	
bool Chance::getGivePlayerMoney() {
	return this->bGivePlayerMoney;
}
	
void Chance::setTakePlayerMoney(int i) {
	this->bTakePlayerMoney = true;
	this->iChanceAmount = i;
}

bool Chance::getTakePlayerMoney() {
	return this->bTakePlayerMoney;
}
	
void Chance::setMoveBackPlayer(int i) {
	this->bMoveBackPlayer = true;
	this->iChanceAmount = i;
}
	
bool Chance::getMoveBackPlayer() {
	return this->bMoveBackPlayer;
}
	
void Chance::setMoveForwardPlayer(int i) {
	this->bMoveForwardPlayer = true;
	this->iChanceAmount = i;
}
	
bool Chance::getMoveForwardPlayer() {
	return this->bMoveForwardPlayer;
}
	
void Chance::setAssignNewInvestmentStrategy() {
	this->bAssignNewInvestmentStrategy = true;
}
	
bool Chance::getAssignNewInvestmentStrategy() {
	return this->bAssignNewInvestmentStrategy;
}
