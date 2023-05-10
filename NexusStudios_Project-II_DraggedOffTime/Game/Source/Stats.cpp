#include "Stats.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Input.h"

void Stats::Load()
{
	texture = app->tex->Load("Assets/UI/Stats/SpritesheetMenu.png");

	statsSheet = app->tex->Load("Assets/UI/Stats/StatsSheet.png");

	statsEnabled = false;

	i = 0;
	j = 0;
}

void Stats::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {

		statsEnabled = !statsEnabled;

	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {

		if (i < 3) i++;
		
	}

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {

		if (i > 0) i--;

	}

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

		if (j < 3) j++;

	}

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

		if (j > 0) j--;

	}
}

void Stats::Draw()
{
	SDL_Rect rect = { 1280 * i, 0,1280,720 };

	SDL_Rect rect2 = { 1280 * j, 0,1280,720 };

	if (statsEnabled) {

		app->render->DrawTexture(texture, 0, 0, &rect);

		if (i == 0) {

			app->render->DrawTexture(statsSheet, 0, 0, &rect2);

		}

	}
}
