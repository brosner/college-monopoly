
#include "Property.h"

Property::Property() {
	this->propertyInit();
}

Property::Property(std::string sName) {
	this->propertyInit();
	this->setPropertyName(sName);
}

Property::Property(int iCost) {
	this->propertyInit();
	this->setPropertyCost(iCost);
}

Property::Property(std::string sName,int iCost) {
	this->propertyInit();
	
	this->setPropertyName(sName);
	this->setPropertyCost(iCost);
}

Property::~Property() {
}

std::string Property::getPropertyName() {
	return this->sPropertyName;
}

void Property::setPropertyName(std::string sName) {
	this->sPropertyName = sName;
}

int Property::getPropertyCost() {
	return this->iPropertyCost;
}

void Property::setPropertyCost(int iAmount) {
	/* calculate and set rent */
	this->setPropertyRent((int)(iAmount * 0.1));
	
	/* calculate and set house cost */
	this->setHouseCost(iAmount / 2);

	/* set cost */
	this->iPropertyCost = iAmount;
}

int Property::getPropertyRent() {
	return this->iPropertyRent;
}

void Property::setPropertyRent(int iAmount) {
	this->iPropertyRent = iAmount;
}

Player ** Property::getPropertyOwner() {
	return this->propertyOwner;
}

bool Property::getOwned() {
	return this->isOwned;
}

void Property::setPropertyOwner(Player **p) {
	this->propertyOwner = p;
	this->isOwned = true;
}

int Property::getHouseCost() {
	return this->iHouseCost;
}

void Property::setHouseCost(int iAmount) {
	this->iHouseCost = iAmount;
}

void Property::addHouses(int iAmount) {
	/* add a house */
	this->iHouses += iAmount;
	
	/* increase rent */
	int iRent = (int)((this->getPropertyRent() + (this->getHouseCost() * 0.1)) * iAmount);
	this->setPropertyRent(iRent);
}
