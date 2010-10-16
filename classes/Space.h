#ifndef SPACE_H
#define SPACE_H

#include <string>

#include "..\settings.h"
#include "Property.h"
#include "Chance.h"

class Space {
	public:
	
	Space();
	Space(int);
	Space(Property *);
	Space(Chance *);
	~Space();
	
	private:
	
	int iSpaceType;	
	Property *pProperty;
	Chance *pChance;
	int iGoAmount;
	
	public:
	
	std::string getSpace();
	
	int getGoAmount();
	void setGoAmount(int);

	void setSpaceType(int);
	int getSpaceType();

	Property * getProperty();
	Chance * getChance();

};

#endif
