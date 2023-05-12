#include "FeatureMenu.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Input.h"
#include "SceneGameplay.h"
#include "Pause.h"

void FeatureMenu::Load()
{

	for (int i = 0; i < 4; i++) {

		KleosIdle.PushBack({ 275 * (0 + i), 275 * 0, 275, 275 });

	}
	KleosIdle.loop = true;
	KleosIdle.speed = 0.06f;

	texture = app->tex->Load("Assets/UI/Stats/SpritesheetMenu.png");

	statsSheet = app->tex->Load("Assets/UI/Stats/StatsSheet4.png");

	jambitaEstirada = app->tex->Load("Assets/UI/Stats/unknown.png");

	inventory = app->tex->Load("Assets/UI/Stats/Inventory.png");

	skills = app->tex->Load("Assets/UI/Stats/Skills.png");

	equipment = app->tex->Load("Assets/UI/Stats/Equipment.png");

	quests = app->tex->Load("Assets/UI/Stats/Quests.png");

	kleosMedieval = app->tex->Load("Assets/UI/Stats/SpriteSheet_Kleos_Stats.png");

	//kleosPrehistoric = app->tex->Load("Assets/UI/Stats/SpriteSheet_Kleos_Stats.png");

	kleosCyberpunk = app->tex->Load("Assets/UI/Stats/Cyberpunk_Kleos_Stats.png");

	kleosApocalypse = app->tex->Load("Assets/UI/Stats/Demon_Kleos_Stats.png");

	statsEnabled = false;

	i = 0;
	j = 0;
	k = 0;
	l = 0;

	e_characterSelector = 0;
	e_weaponSelector = 0;

	currentAnimation = &KleosIdle;

	inventoryManager.Start();

}

void FeatureMenu::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN /* && !app->sceneGameplay->showPause && !app->sceneGameplay->showSettings*/) {

		statsEnabled = !statsEnabled;

	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {

		if (i < 4) i++;
		
	}

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {

		if (i > 0) i--;

	}

	switch (i) {

	case 0: 

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

			if (j < 3) j++;

		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

			if (j > 0) j--;

		}
		break;

	

	case 1: 


		break;

	

	case 2: 

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

			if (e_characterSelector < 3) {

				e_characterSelector++;

			}
			else if (e_characterSelector == 3) {

				e_characterSelector = 0;

			}

		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

			if (e_characterSelector > 0) {

				e_characterSelector--;

			}
			else if (e_characterSelector == 0) {

				e_characterSelector = 3;

			}

		}

		if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {

			if (e_weaponSelector < 2) {

				e_weaponSelector++;

			}
			else if (e_weaponSelector == 2) {

				e_weaponSelector = 0;

			}

		}

		if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {

			if (e_weaponSelector > 0) {

				e_weaponSelector--;

			}
			else if (e_weaponSelector == 0) {

				e_weaponSelector = 2;

			}

		}

		break;

	case 3: 


		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

			if (k < 3) k++;

		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

			if (k > 0) k--;

		}

		break;

	case 4:

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {

			if (l < 4) l++;

		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {

			if (l > 0) l--;

		}

		break;

	
	}

	currentAnimation->Update();

	inventoryManager.PreUpdate();

}

void FeatureMenu::PostUpdate()
{
	SDL_Rect rect = { 1280 * i, 0,1280,720 };

	SDL_Rect rect2 = { 1280 * j, 0,1280,720 };

	SDL_Rect rect3 = { 1280 * e_weaponSelector, 720 * e_characterSelector,1280,720 };

	SDL_Rect rect4 = { 0, 720 * k,1280,720 };

	SDL_Rect rect5 = { 0, 720 * l ,1280,720 };

	if (statsEnabled) {

		app->render->DrawTexture(texture, 0, 0, &rect);

		switch (i) {

			case 0: {

				app->render->DrawTexture(statsSheet, 0, 0, &rect2);

				if (j == 0) {

					SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

					app->render->DrawTexture(kleosMedieval, 340, 278, &kleosRect);

				}

				if (j == 2) {

					SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

					app->render->DrawTexture(kleosCyberpunk, 340, 278, &kleosRect);

				}

				if (j == 3) {

					SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

					app->render->DrawTexture(kleosApocalypse, 340, 278, &kleosRect);

				}
				
				break;

			}
				
			case 1: {

				app->render->DrawTexture(inventory, 0, 0);
				break;

			}
				
			case 2: {

				app->render->DrawTexture(equipment, 0, 0, &rect3);
				break;

			}

			case 3: {

				app->render->DrawTexture(skills, 0, 0, &rect4);
				break;

			}

			case 4: {
				
				app->render->DrawTexture(quests, 0, 0, &rect5);
				break;

			}
			
		}

	}

	
}
