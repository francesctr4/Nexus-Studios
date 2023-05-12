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

	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && items.size())
	{
		RemoveCertainItem(1);
	}

	if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
	{
		EmptyInventory();
	}

	if (inventoryOn)
	{
		// Show the items' sprites in the inventory

		for (int i = 0; i < items.size(); i++)
		{
			if (i < 8) {

				app->render->DrawTexture(items[i].icon, 264 + 98 * i, 210, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 8 && i < 16) {

				app->render->DrawTexture(items[i].icon, 264 + 98 * i - 98 * 8, 310, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 16 && i < 24) {

				app->render->DrawTexture(items[i].icon, 264 + 98 * i - 98 * 16, 410, &SDL_Rect({ 0,0,62,62 }));

			}
			else if (i >= 24) {

				app->render->DrawTexture(items[i].icon, 264 + 98 * i - 98 * 24, 510, &SDL_Rect({ 0,0,62,62 }));

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
