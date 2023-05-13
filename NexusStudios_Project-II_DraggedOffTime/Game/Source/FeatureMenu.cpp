#include "FeatureMenu.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "SceneGameplay.h"
#include "Pause.h"

#include "SDL_mixer/include/SDL_mixer.h"

void FeatureMenu::Load()
{
	//UI Buttons

	ChangeCharacters = false;

	stats = app->tex->Load("Assets/UI/Stats/Stats_Spritesheet.png");
	Stats = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, stats, "", { 199,84,177,59 }, (Module*)app->sceneGameplay);
	Stats->state = GuiControlState::DISABLED;

	Stats_visual = app->tex->Load("Assets/UI/Stats/CharacterStats_Spritesheet.png");

	inventory_ = app->tex->Load("Assets/UI/Stats/Inventory_Spritesheet.png");
	Inventory_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, inventory_, "", { 376,84,177,59 }, (Module*)app->sceneGameplay);
	Inventory_->state = GuiControlState::DISABLED;

	Inventory_visual = app->tex->Load("Assets/UI/Stats/Inventory.png");

	equipment = app->tex->Load("Assets/UI/Stats/Equipment_Spritesheet.png");
	Equipment = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, equipment, "", { 553,83,177,59 }, (Module*)app->sceneGameplay);
	Equipment->state = GuiControlState::DISABLED;

	skills = app->tex->Load("Assets/UI/Stats/Skills_Spritesheet.png");
	Skills = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, skills, "", { 730,83,177,59 }, (Module*)app->sceneGameplay);
	Skills->state = GuiControlState::DISABLED;

	quests = app->tex->Load("Assets/UI/Stats/Quests_Spritesheet.png");
	Quests = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, quests, "", { 907,83,177,59 }, (Module*)app->sceneGameplay);
	Quests->state = GuiControlState::DISABLED;

	OpenPause = app->audio->LoadFx("Assets/Audio/Fx/OpenPause.wav");
	ClosePause = app->audio->LoadFx("Assets/Audio/Fx/ClosePause.wav");

	//Stats Character Selection

	medieval = app->tex->Load("Assets/UI/Stats/Medieval_Selection.png");
	Medieval = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, medieval, "", { 238,178,90,90 }, (Module*)app->sceneGameplay);
	Medieval->state = GuiControlState::INVISIBLE;

	prehistorical = app->tex->Load("Assets/UI/Stats/Prehistoric_Selection.png");
	Prehistorical = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, prehistorical, "", { 238,279,90,90 }, (Module*)app->sceneGameplay);
	Prehistorical->state = GuiControlState::INVISIBLE;

	cyberpunk = app->tex->Load("Assets/UI/Stats/Cyberpunk_Selection.png");
	Cyberpunk = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, cyberpunk, "", { 238,385,90,90 }, (Module*)app->sceneGameplay);
	Cyberpunk->state = GuiControlState::INVISIBLE;

	apocalypse = app->tex->Load("Assets/UI/Stats/Apocalypse_Selection.png");
	Apocalypse = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, apocalypse, "", { 238,485,90,90 }, (Module*)app->sceneGameplay);
	Apocalypse->state = GuiControlState::INVISIBLE;

	//Inventory

	Slot_texture = app->tex->Load("Assets/UI/Stats/Inventory_Slot.png");

	Inventory_1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, Slot_texture, "", { 281,227,90,90 }, (Module*)app->sceneGameplay);
	Inventory_1->state = GuiControlState::DISABLED;

	Inventory_2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, Slot_texture, "", { 407,227,90,90 }, (Module*)app->sceneGameplay);
	Inventory_2->state = GuiControlState::DISABLED;

	Inventory_3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, Slot_texture, "", { 533,227,90,90 }, (Module*)app->sceneGameplay);
	Inventory_3->state = GuiControlState::DISABLED;

	Inventory_4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, Slot_texture, "", { 659,227,90,90 }, (Module*)app->sceneGameplay);
	Inventory_4->state = GuiControlState::DISABLED;

	Inventory_5 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, Slot_texture, "", { 785,227,90,90 }, (Module*)app->sceneGameplay);
	Inventory_5->state = GuiControlState::DISABLED;

	Inventory_6 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, Slot_texture, "", { 911,227,90,90 }, (Module*)app->sceneGameplay);
	Inventory_6->state = GuiControlState::DISABLED;

	Inventory_7 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, Slot_texture, "", { 281,349,90,90 }, (Module*)app->sceneGameplay);
	Inventory_7->state = GuiControlState::DISABLED;

	Inventory_8 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, Slot_texture, "", { 407,349,90,90 }, (Module*)app->sceneGameplay);
	Inventory_8->state = GuiControlState::DISABLED;

	Inventory_9 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, Slot_texture, "", { 533,349,90,90 }, (Module*)app->sceneGameplay);
	Inventory_9->state = GuiControlState::DISABLED;

	Inventory_10 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, Slot_texture, "", { 659,349,90,90 }, (Module*)app->sceneGameplay);
	Inventory_10->state = GuiControlState::DISABLED;

	Inventory_11 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, Slot_texture, "", { 785,349,90,90 }, (Module*)app->sceneGameplay);
	Inventory_11->state = GuiControlState::DISABLED;

	Inventory_12 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, Slot_texture, "", { 911,349,90,90 }, (Module*)app->sceneGameplay);
	Inventory_12->state = GuiControlState::DISABLED;

	Inventory_13 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, Slot_texture, "", { 281,471,90,90 }, (Module*)app->sceneGameplay);
	Inventory_13->state = GuiControlState::DISABLED;

	Inventory_14 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, Slot_texture, "", { 407,471,90,90 }, (Module*)app->sceneGameplay);
	Inventory_14->state = GuiControlState::DISABLED;

	Inventory_15 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, Slot_texture, "", { 533,471,90,90 }, (Module*)app->sceneGameplay);
	Inventory_15->state = GuiControlState::DISABLED;

	Inventory_16 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, Slot_texture, "", { 659,471,90,90 }, (Module*)app->sceneGameplay);
	Inventory_16->state = GuiControlState::DISABLED;

	Inventory_17 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 16, Slot_texture, "", { 785,471,90,90 }, (Module*)app->sceneGameplay);
	Inventory_17->state = GuiControlState::DISABLED;

	Inventory_18 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 17, Slot_texture, "", { 911,471,90,90 }, (Module*)app->sceneGameplay);
	Inventory_18->state = GuiControlState::DISABLED;

	//Equipment

	leftArrow = app->tex->Load("Assets/UI/Stats/Left_Arrow.png");
	LeftArrow = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, leftArrow, "", { 454,242,34,27 }, (Module*)app->sceneGameplay);
	LeftArrow->state = GuiControlState::DISABLED;

	rightArrow = app->tex->Load("Assets/UI/Stats/Right_Arrow.png");
	RightArrow = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, rightArrow, "", { 620,242,34,27 }, (Module*)app->sceneGameplay);
	RightArrow->state = GuiControlState::DISABLED;

	Equipment_visual = app->tex->Load("Assets/UI/Stats/Equipment_Weapon_SpriteSheet.png");

	//Skills

	Skills_visual = app->tex->Load("Assets/UI/Stats/Skills_Text_Spritesheet.png"); 

	//Quests

	Quests_visual = app->tex->Load("Assets/UI/Stats/Quest_Background.png");


	Fondo = app->tex->Load("Assets/UI/PauseBackground.png");

	for (int i = 0; i < 4; i++) {

		KleosIdle.PushBack({ 275 * (0 + i), 275 * 0, 275, 275 });

	}
	KleosIdle.loop = true;
	KleosIdle.speed = 0.06f;

	/*texture = app->tex->Load("Assets/UI/Stats/SpritesheetMenu.png");

	statsSheet = app->tex->Load("Assets/UI/Stats/StatsSheet4.png");

	jambitaEstirada = app->tex->Load("Assets/UI/Stats/unknown.png");

	inventory = app->tex->Load("Assets/UI/Stats/Inventory.png");

	skills = app->tex->Load("Assets/UI/Stats/Skills.png");

	equipment = app->tex->Load("Assets/UI/Stats/Equipment.png");

	quests = app->tex->Load("Assets/UI/Stats/Quests.png");*/

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

}

void FeatureMenu::Update()
{
	//Menu


	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		statsEnabled = !statsEnabled;

	

		ChangeCharacters = !ChangeCharacters;
		ChangeWeapons = false;
		ShowSlots = false;
		
	}


	//UI Buttons

	if (Stats->state == GuiControlState::PRESSED) {

		i = 0;

		ChangeCharacters = true;
		ChangeWeapons = false;
		ShowSlots = false;
	}

	if (Inventory_->state == GuiControlState::PRESSED) {

		i = 1;

		ChangeCharacters = false;
		ChangeWeapons = false;
		ShowSlots = true;
	}

	if (Equipment->state == GuiControlState::PRESSED) {

		i = 2;

		ChangeCharacters = true;
		ChangeWeapons = true;
		ShowSlots = false;
	}

	if (Skills->state == GuiControlState::PRESSED) {

		i = 3;

		ChangeCharacters = true;
		ChangeWeapons = false;
		ShowSlots = false;
	}

	if (Quests->state == GuiControlState::PRESSED) {

		i = 4;

		ChangeCharacters = false;
		ChangeWeapons = false;
		ShowSlots = false;
	}

	//Stats Character Selection

	if (Medieval->state == GuiControlState::PRESSED) {

		j = 0;
	}

	if (Prehistorical->state == GuiControlState::PRESSED) {

		j = 1;
	}

	if (Cyberpunk->state == GuiControlState::PRESSED) {

		j = 2;
	}

	if (Apocalypse->state == GuiControlState::PRESSED) {

		j = 3;
	}

	//Weapon Selection Arrows

	if (LeftArrow->state == GuiControlState::PRESSED) {

		if (k > 0) k--;
	}

	if (RightArrow->state == GuiControlState::PRESSED) {

		if (k <= 1 ) k++;
	}



	//if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN /* && !app->sceneGameplay->showPause && !app->sceneGameplay->showSettings*/) {

	//	statsEnabled = !statsEnabled;

	//}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {

		if (i < 4) i++;
		
	}

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {

		if (i > 0) i--;

	}

	if (!statsEnabled || i != 1) {

		inventoryManager.inventoryOn = false;

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

		if (statsEnabled) inventoryManager.inventoryOn = true;

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

}

void FeatureMenu::PostUpdate()
{

	app->guiManager->Draw();

	if (statsEnabled) app->render->DrawTexture(Fondo, 0, 0);

	if (statsEnabled) {

		switch (i) {

		case 0: {

			if (j == 0) {

				app->render->DrawTexture(Stats_visual, 0, 0, &SDL_Rect({ 1280 * 0, 0, 1280, 720 }));

				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

				app->render->DrawTexture(kleosMedieval, 370, 278, &kleosRect);

			}


			if (j == 1) {

				app->render->DrawTexture(Stats_visual, 0, 0, &SDL_Rect({ 1280 * 1, 0, 1280, 720 }));

				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

				app->render->DrawTexture(kleosMedieval, 370, 278, &kleosRect);

			}

			if (j == 2) {

				app->render->DrawTexture(Stats_visual, 0, 0, &SDL_Rect({ 1280 * 2, 0, 1280, 720 }));

				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

				app->render->DrawTexture(kleosCyberpunk, 370, 278, &kleosRect);

			}

			if (j == 3) {

				app->render->DrawTexture(Stats_visual, 0, 0, &SDL_Rect({ 1280 * 3, 0, 1280, 720 }));

				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

				app->render->DrawTexture(kleosApocalypse, 370, 278, &kleosRect);

			}

			break;

		}

		case 1: {

			//app->render->DrawTexture(inventory, 0, 0);

			app->render->DrawTexture(Inventory_visual, 0, 0);

			break;

		}

		case 2: {

			//app->render->DrawTexture(equipment, 0, 0, &rect3);


			if (j == 0) {

				if (k == 0) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 0, 720 * 0, 1280, 720 }));

				}

				if (k == 1) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 1, 720 * 0, 1280, 720 }));
				}

				if (k == 2) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 2, 720 * 0, 1280, 720 }));
				}
			}


			if (j == 1) {

				if (k == 0) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 0, 720 * 1, 1280, 720 }));

				}

				if (k == 1) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 1, 720 * 1, 1280, 720 }));
				}

				if (k == 2) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 2, 720 * 1, 1280, 720 }));
				}

			}

			if (j == 2) {

				if (k == 0) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 0, 720 * 2, 1280, 720 }));

				}

				if (k == 1) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 1, 720 * 2, 1280, 720 }));
				}

				if (k == 2) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 2, 720 * 2, 1280, 720 }));
				}

			}

			if (j == 3) {

				if (k == 0) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 0, 720 * 3, 1280, 720 }));

				}

				if (k == 1) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 1, 720 * 3, 1280, 720 }));
				}

				if (k == 2) {

					app->render->DrawTexture(Equipment_visual, 0, 0, &SDL_Rect({ 1280 * 2, 720 * 3, 1280, 720 }));
				}

			}

			break;

		}

		case 3: {

			//app->render->DrawTexture(skills, 0, 0, &rect4);

			if (j == 0) {

				app->render->DrawTexture(Skills_visual, 0, 0, &SDL_Rect({ 1280 * 0, 0, 1280, 720 }));

			}

			if (j == 1) {

				app->render->DrawTexture(Skills_visual, 0, 0, &SDL_Rect({ 1280 * 1, 0, 1280, 720 }));

			}

			if (j == 2) {

				app->render->DrawTexture(Skills_visual, 0, 0, &SDL_Rect({ 1280 * 2, 0, 1280, 720 }));

			}

			if (j == 3) {

				app->render->DrawTexture(Skills_visual, 0, 0, &SDL_Rect({ 1280 * 3, 0, 1280, 720 }));

			}

			break;

		}

		case 4: {

			//app->render->DrawTexture(quests, 0, 0, &rect5);

			app->render->DrawTexture(Quests_visual, 0, 0, &SDL_Rect({ 0, 0, 1280, 720 }));

			break;

		}

		}

	}


	if (statsEnabled) {

		if (Stats->state == GuiControlState::DISABLED) Stats->state = GuiControlState::NORMAL;
		if (Inventory_->state == GuiControlState::DISABLED) Inventory_->state = GuiControlState::NORMAL;
		if (Equipment->state == GuiControlState::DISABLED) Equipment->state = GuiControlState::NORMAL;
		if (Skills->state == GuiControlState::DISABLED) Skills->state = GuiControlState::NORMAL;
		if (Quests->state == GuiControlState::DISABLED) Quests->state = GuiControlState::NORMAL;

		Stats->Draw(app->render);
		Inventory_->Draw(app->render);
		Equipment->Draw(app->render);
		Skills->Draw(app->render);
		Quests->Draw(app->render);

		if (ChangeCharacters) {

			if (Medieval->state == GuiControlState::INVISIBLE) Medieval->state = GuiControlState::NORMAL;
			if (Prehistorical->state == GuiControlState::INVISIBLE) Prehistorical->state = GuiControlState::NORMAL;
			if (Cyberpunk->state == GuiControlState::INVISIBLE) Cyberpunk->state = GuiControlState::NORMAL;
			if (Apocalypse->state == GuiControlState::INVISIBLE) Apocalypse->state = GuiControlState::NORMAL;

			Medieval->Draw(app->render);
			Prehistorical->Draw(app->render);
			Cyberpunk->Draw(app->render);
			Apocalypse->Draw(app->render);
		}
		if (!ChangeCharacters) {

			if (Medieval->state != GuiControlState::INVISIBLE) Medieval->state = GuiControlState::INVISIBLE;
			if (Prehistorical->state != GuiControlState::INVISIBLE) Prehistorical->state = GuiControlState::INVISIBLE;
			if (Cyberpunk->state != GuiControlState::INVISIBLE) Cyberpunk->state = GuiControlState::INVISIBLE;
			if (Apocalypse->state != GuiControlState::INVISIBLE) Apocalypse->state = GuiControlState::INVISIBLE;
		}

		if (ChangeWeapons) {

			if (LeftArrow->state == GuiControlState::DISABLED) LeftArrow->state = GuiControlState::NORMAL;
			if (RightArrow->state == GuiControlState::DISABLED) RightArrow->state = GuiControlState::NORMAL;

			LeftArrow->Draw(app->render);
			RightArrow->Draw(app->render);
	
		}
		if (!ChangeWeapons) {

			if (LeftArrow->state != GuiControlState::DISABLED) LeftArrow->state = GuiControlState::DISABLED;
			if (RightArrow->state != GuiControlState::DISABLED) RightArrow->state = GuiControlState::DISABLED;
		}

		if (ShowSlots) {

			if (Inventory_1->state == GuiControlState::DISABLED) Inventory_1->state = GuiControlState::NORMAL;
			if (Inventory_2->state == GuiControlState::DISABLED) Inventory_2->state = GuiControlState::NORMAL;
			if (Inventory_3->state == GuiControlState::DISABLED) Inventory_3->state = GuiControlState::NORMAL;
			if (Inventory_4->state == GuiControlState::DISABLED) Inventory_4->state = GuiControlState::NORMAL;
			if (Inventory_5->state == GuiControlState::DISABLED) Inventory_5->state = GuiControlState::NORMAL;
			if (Inventory_6->state == GuiControlState::DISABLED) Inventory_6->state = GuiControlState::NORMAL;
			if (Inventory_7->state == GuiControlState::DISABLED) Inventory_7->state = GuiControlState::NORMAL;
			if (Inventory_8->state == GuiControlState::DISABLED) Inventory_8->state = GuiControlState::NORMAL;
			if (Inventory_9->state == GuiControlState::DISABLED) Inventory_9->state = GuiControlState::NORMAL;
			if (Inventory_10->state == GuiControlState::DISABLED) Inventory_10->state = GuiControlState::NORMAL;
			if (Inventory_11->state == GuiControlState::DISABLED) Inventory_11->state = GuiControlState::NORMAL;
			if (Inventory_12->state == GuiControlState::DISABLED) Inventory_12->state = GuiControlState::NORMAL;
			if (Inventory_13->state == GuiControlState::DISABLED) Inventory_13->state = GuiControlState::NORMAL;
			if (Inventory_14->state == GuiControlState::DISABLED) Inventory_14->state = GuiControlState::NORMAL;
			if (Inventory_15->state == GuiControlState::DISABLED) Inventory_15->state = GuiControlState::NORMAL;
			if (Inventory_16->state == GuiControlState::DISABLED) Inventory_16->state = GuiControlState::NORMAL;
			if (Inventory_17->state == GuiControlState::DISABLED) Inventory_17->state = GuiControlState::NORMAL;
			if (Inventory_18->state == GuiControlState::DISABLED) Inventory_18->state = GuiControlState::NORMAL;

			Inventory_1->Draw(app->render);
			Inventory_2->Draw(app->render);
			Inventory_1->Draw(app->render);
			Inventory_2->Draw(app->render);
			Inventory_3->Draw(app->render);
			Inventory_4->Draw(app->render);
			Inventory_5->Draw(app->render);
			Inventory_6->Draw(app->render);
			Inventory_7->Draw(app->render);
			Inventory_8->Draw(app->render);
			Inventory_9->Draw(app->render);
			Inventory_10->Draw(app->render);
			Inventory_11->Draw(app->render);
			Inventory_12->Draw(app->render);
			Inventory_13->Draw(app->render);
			Inventory_14->Draw(app->render);
			Inventory_15->Draw(app->render);
			Inventory_16->Draw(app->render);
			Inventory_17->Draw(app->render);
			Inventory_18->Draw(app->render);

		}
		if (!ShowSlots) {

			if (Inventory_1->state != GuiControlState::DISABLED) Inventory_1->state = GuiControlState::DISABLED;
			if (Inventory_2->state != GuiControlState::DISABLED) Inventory_2->state = GuiControlState::DISABLED;
			if (Inventory_3->state != GuiControlState::DISABLED) Inventory_3->state = GuiControlState::DISABLED;
			if (Inventory_4->state != GuiControlState::DISABLED) Inventory_4->state = GuiControlState::DISABLED;
			if (Inventory_5->state != GuiControlState::DISABLED) Inventory_5->state = GuiControlState::DISABLED;
			if (Inventory_6->state != GuiControlState::DISABLED) Inventory_6->state = GuiControlState::DISABLED;
			if (Inventory_7->state != GuiControlState::DISABLED) Inventory_7->state = GuiControlState::DISABLED;
			if (Inventory_8->state != GuiControlState::DISABLED) Inventory_8->state = GuiControlState::DISABLED;
			if (Inventory_9->state != GuiControlState::DISABLED) Inventory_9->state = GuiControlState::DISABLED;
			if (Inventory_10->state != GuiControlState::DISABLED) Inventory_10->state = GuiControlState::DISABLED;
			if (Inventory_11->state != GuiControlState::DISABLED) Inventory_11->state = GuiControlState::DISABLED;
			if (Inventory_12->state != GuiControlState::DISABLED) Inventory_12->state = GuiControlState::DISABLED;
			if (Inventory_13->state != GuiControlState::DISABLED) Inventory_13->state = GuiControlState::DISABLED;
			if (Inventory_14->state != GuiControlState::DISABLED) Inventory_14->state = GuiControlState::DISABLED;
			if (Inventory_15->state != GuiControlState::DISABLED) Inventory_15->state = GuiControlState::DISABLED;
			if (Inventory_16->state != GuiControlState::DISABLED) Inventory_16->state = GuiControlState::DISABLED;
			if (Inventory_17->state != GuiControlState::DISABLED) Inventory_17->state = GuiControlState::DISABLED;
			if (Inventory_18->state != GuiControlState::DISABLED) Inventory_18->state = GuiControlState::DISABLED;
		}

	}
	if (!statsEnabled) {

		if (Stats->state != GuiControlState::DISABLED) Stats->state = GuiControlState::DISABLED;
		if (Inventory_->state != GuiControlState::DISABLED) Inventory_->state = GuiControlState::DISABLED;
		if (Equipment->state != GuiControlState::DISABLED) Equipment->state = GuiControlState::DISABLED;
		if (Skills->state != GuiControlState::DISABLED) Skills->state = GuiControlState::DISABLED;
		if (Quests->state != GuiControlState::DISABLED) Quests->state = GuiControlState::DISABLED;

		if (Medieval->state != GuiControlState::INVISIBLE) Medieval->state = GuiControlState::INVISIBLE;
		if (Prehistorical->state != GuiControlState::INVISIBLE) Prehistorical->state = GuiControlState::INVISIBLE;
		if (Cyberpunk->state != GuiControlState::INVISIBLE) Cyberpunk->state = GuiControlState::INVISIBLE;
		if (Apocalypse->state != GuiControlState::INVISIBLE) Apocalypse->state = GuiControlState::INVISIBLE;

		if (LeftArrow->state != GuiControlState::DISABLED) LeftArrow->state = GuiControlState::DISABLED;
		if (RightArrow->state != GuiControlState::DISABLED) RightArrow->state = GuiControlState::DISABLED;

		if (Inventory_1->state != GuiControlState::DISABLED) Inventory_1->state = GuiControlState::DISABLED;
		if (Inventory_2->state != GuiControlState::DISABLED) Inventory_2->state = GuiControlState::DISABLED;
		if (Inventory_3->state != GuiControlState::DISABLED) Inventory_3->state = GuiControlState::DISABLED;
		if (Inventory_4->state != GuiControlState::DISABLED) Inventory_4->state = GuiControlState::DISABLED;
		if (Inventory_5->state != GuiControlState::DISABLED) Inventory_5->state = GuiControlState::DISABLED;
		if (Inventory_6->state != GuiControlState::DISABLED) Inventory_6->state = GuiControlState::DISABLED;
		if (Inventory_7->state != GuiControlState::DISABLED) Inventory_7->state = GuiControlState::DISABLED;
		if (Inventory_8->state != GuiControlState::DISABLED) Inventory_8->state = GuiControlState::DISABLED;
		if (Inventory_9->state != GuiControlState::DISABLED) Inventory_9->state = GuiControlState::DISABLED;
		if (Inventory_10->state != GuiControlState::DISABLED) Inventory_10->state = GuiControlState::DISABLED;
		if (Inventory_11->state != GuiControlState::DISABLED) Inventory_11->state = GuiControlState::DISABLED;
		if (Inventory_12->state != GuiControlState::DISABLED) Inventory_12->state = GuiControlState::DISABLED;
		if (Inventory_13->state != GuiControlState::DISABLED) Inventory_13->state = GuiControlState::DISABLED;
		if (Inventory_14->state != GuiControlState::DISABLED) Inventory_14->state = GuiControlState::DISABLED;
		if (Inventory_15->state != GuiControlState::DISABLED) Inventory_15->state = GuiControlState::DISABLED;
		if (Inventory_16->state != GuiControlState::DISABLED) Inventory_16->state = GuiControlState::DISABLED;
		if (Inventory_17->state != GuiControlState::DISABLED) Inventory_17->state = GuiControlState::DISABLED;
		if (Inventory_18->state != GuiControlState::DISABLED) Inventory_18->state = GuiControlState::DISABLED;

	}

	

































	//SDL_Rect rect = { 1280 * i, 0,1280,720 };

	//SDL_Rect rect2 = { 1280 * j, 0,1280,720 };

	//SDL_Rect rect3 = { 1280 * e_weaponSelector, 720 * e_characterSelector,1280,720 };

	//SDL_Rect rect4 = { 0, 720 * k,1280,720 };

	//SDL_Rect rect5 = { 0, 720 * l ,1280,720 };

	//if (statsEnabled) {

	//	app->render->DrawTexture(texture, 0, 0, &rect);

	//	switch (i) {

	//		case 0: {

	//			app->render->DrawTexture(statsSheet, 0, 0, &rect2);

	//			if (j == 0) {

	//				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

	//				app->render->DrawTexture(kleosMedieval, 340, 278, &kleosRect);

	//			}

	//			if (j == 2) {

	//				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

	//				app->render->DrawTexture(kleosCyberpunk, 340, 278, &kleosRect);

	//			}

	//			if (j == 3) {

	//				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

	//				app->render->DrawTexture(kleosApocalypse, 340, 278, &kleosRect);

	//			}
	//			
	//			break;

	//		}
	//			
	//		case 1: {

	//			//app->render->DrawTexture(inventory, 0, 0);
	//			break;

	//		}
	//			
	//		case 2: {

	//			app->render->DrawTexture(equipment, 0, 0, &rect3);
	//			break;

	//		}

	//		case 3: {

	//			app->render->DrawTexture(skills, 0, 0, &rect4);
	//			break;

	//		}

	//		case 4: {
	//			
	//			app->render->DrawTexture(quests, 0, 0, &rect5);
	//			break;

	//		}
	//		
	//	}

	//}

	inventoryManager.PostUpdate();

}
