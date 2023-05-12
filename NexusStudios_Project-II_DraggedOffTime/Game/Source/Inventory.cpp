#include "Inventory.h"
#include "Input.h"
#include "app.h"
#include "Log.h"
#include "Render.h"
#include "Player.h"
#include "Item.h"

Inventory::Inventory()
{

	// TODO 1: initialize the inventory capacity, the number of items contained and the array of this items
	this->cap = 33;
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


bool Inventory::PostUpdate()
{

	// TODO 4: delete the last item picked when pressing a key
	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && nrOfItems)
	{
		removeItem();
	}

	if (inventoryOn)
	{
		//	TODO 4: Show the items' sprites in the inventory
		for (int i = 0; i < nrOfItems; i++)
		{
			if (i < 8) {

				app->render->DrawTexture(items[i]->icon, 264 + 98 * i, 210, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 8 && i < 16) {

				app->render->DrawTexture(items[i]->icon, 264 + 98 * i - 98 * 8, 310, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 16 && i < 24) {

				app->render->DrawTexture(items[i]->icon, 264 + 98 * i - 98 * 16, 410, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 24) {

				app->render->DrawTexture(items[i]->icon, 264 + 98 * i - 98 * 24, 510, &SDL_Rect({ 0,0,62,62 }));

			}
			
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
	if (nrOfItems < cap - 1) {

		this->items[this->nrOfItems++] = new Item(item);

	}
	
}


void Inventory::removeItem()
{
	delete items[nrOfItems--];
}