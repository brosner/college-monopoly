#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

/*
 * used for storing an owner...no need to access anything
 */
class Player;

class Property {
	public:
	
	Property();
	Property(std::string);
	Property(int);
	Property(std::string,int);
	~Property();
	
	private:
	
	std::string sPropertyName;
	int iPropertyCost;
	int iPropertyRent;
	int iHouseCost;
	int iHouses;

	Player **propertyOwner;
	bool isOwned;

	void propertyInit() {
		this->iHouses = 0;
		this->isOwned = false;
	}
	
	public:

	std::string getPropertyName();
	void setPropertyName(std::string);

	int getPropertyCost();
	void setPropertyCost(int);
	
	int getPropertyRent();
	void setPropertyRent(int);
	
	int getHouseCost();
	void setHouseCost(int);

	Player ** getPropertyOwner();
	bool getOwned();
	void setPropertyOwner(Player **);

	void addHouses(int);
};

#endif
