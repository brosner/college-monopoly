
#include "Space.h"

Space::Space() {
}

Space::Space(int iGoAmount) {
	this->setSpaceType(SPACE_TYPE_GO);
	this->setGoAmount(iGoAmount);
}

Space::Space(Property *p) {
	this->setSpaceType(SPACE_TYPE_PROPERTY);
	this->pProperty = p;
}

Space::Space(Chance *c) {
	this->setSpaceType(SPACE_TYPE_CHANCE);
	this->pChance = c;
}

Space::~Space() {
}

std::string Space::getSpace() {
	std::string str;
	
	if(this->iSpaceType == SPACE_TYPE_GO) {
		str = "GO";
	}
	else if(this->iSpaceType == SPACE_TYPE_PROPERTY) {
		str = "Property";
	}
	else if(this->iSpaceType == SPACE_TYPE_CHANCE) {
		str = "Chance";
	}
	else {
		str = "Unknown";
	}
	
	return str;
}

int Space::getGoAmount() {
	return this->iGoAmount;
}

void Space::setGoAmount(int iAmount) {
	this->iGoAmount = iAmount;
}

int Space::getSpaceType() {
	return this->iSpaceType;
}

void Space::setSpaceType(int iSpace) {
	this->iSpaceType = iSpace;
}

Property * Space::getProperty() {
	return this->pProperty;
}

Chance * Space::getChance() {
	return this->pChance;
}
