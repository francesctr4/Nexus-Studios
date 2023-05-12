#pragma once

#include "Entity.h"
#include "Item.h"
#include <vector>

class Inventory
{
public:

	// Constructors & Destructors
	Inventory();
	virtual ~Inventory();

	// Module Step
	bool PostUpdate();

	// Inventory functions
	void AddItem(Item& item);
	void RemoveLastItem();
	void RemoveCertainItem(int index);
	void EmptyInventory();

public:

	bool inventoryOn = false;

	std::vector<Item> items;
	unsigned int cap = 32;

};