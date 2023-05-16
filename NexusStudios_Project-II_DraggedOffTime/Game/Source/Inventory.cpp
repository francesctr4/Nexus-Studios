#include "Inventory.h"
#include "Input.h"
#include "app.h"
#include "Log.h"
#include "Render.h"
#include "Player.h"
#include "Item.h"

// Constructor
Inventory::Inventory() {}

// Destructor
Inventory::~Inventory() {}

bool Inventory::PostUpdate()
{

	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && items.size())
	{
		RemoveLastItem();
	}

	/*if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && items.size())
	{
		RemoveCertainItem(1);
	}*/

	if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
	{
		EmptyInventory();
	}

	if (inventoryOn)
	{
		// Show the items' sprites in the inventory

		for (int i = 0; i < items.size(); i++)
		{
			if (i < 6) {

				app->render->DrawTexture(items[i].icon, 294 + 126 * i, 237, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 6 && i < 12) {

				app->render->DrawTexture(items[i].icon, 294 + 126 * i - 126 * 6, 359, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 12) {

				app->render->DrawTexture(items[i].icon, 294 + 126 * i - 126 * 12, 481, &SDL_Rect({ 0,0,62,62 }));

			}
			
		}

	}

	return true;
}

void Inventory::AddItem(Item& item)
{
	if (items.size() < cap) {

		items.push_back(item);

	}
	
}

void Inventory::RemoveLastItem()
{
	
	items.erase(items.end() - 1);

}

void Inventory::RemoveCertainItem(int index)
{
	if (index < items.size()) {

		items.erase(items.begin() + index);

	}
	
}

void Inventory::EmptyInventory()
{

	items.clear();

}
