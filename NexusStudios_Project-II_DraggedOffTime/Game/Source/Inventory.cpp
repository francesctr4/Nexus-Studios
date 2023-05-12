#include "Inventory.h"
#include "Input.h"
#include "app.h"
#include "Log.h"
#include "Render.h"
#include "Player.h"
#include "Item.h"
#include "SceneGameplay.h"


Inventory::Inventory(unsigned cap)
{

	// TODO 1: initialize the inventory capacity, the number of items contained and the array of this items
	this->cap = cap;
	this->nrOfItems = 0;
	this->items = new Item * [cap];
}


// Destructor
Inventory::~Inventory()
{
	//Delete the whole array
	for (int i = 0; i < this->nrOfItems; i++)
	{
		delete[] this->items;
	}
}

bool Inventory::Start()
{
	// TODO 1: Add a null pointer to every position of the inventory array
	for (int i = 0; i < this->cap; i++)
	{
		this->items[i] = nullptr;
	}
	return true;
}


bool Inventory::PreUpdate()
{

	// TODO 4: delete the last item picked when pressing a key
	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		removeItem();
	}
	
	SDL_Rect Rect = { 0,0,16,18 };

	if (app->sceneGameplay->featureMenu.inventoryManager.inventoryOn)
	{
		//	TODO 4: Show the items' sprites in the inventory
		for (int i = 0; i < app->sceneGameplay->featureMenu.inventoryManager.nrOfItems; i++)
		{
			app->render->DrawTexture(app->sceneGameplay->featureMenu.inventoryManager.items[i]->texture, 182 + 32 * i, 132, &Rect);
		}
	}

	return true;
}


// Called before quitting
bool Inventory::CleanUp()
{
	return true;
}


// TODO 2: Create functions to add and remove items from the inventory
void Inventory::addItem(Item& item)
{
	this->items[this->nrOfItems++] = new Item(item);
}


void Inventory::removeItem()
{
	delete items[nrOfItems--];
}