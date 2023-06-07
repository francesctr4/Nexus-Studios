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
	Inventory_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 40, inventory_, "", { 376,84,177,59 }, (Module*)app->sceneGameplay);
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

	melee = app->tex->Load("Assets/UI/Stats/Melee_Slot.png");
	Melee = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 17, melee, "", { 753,321,60,60 }, (Module*)app->sceneGameplay);
	Melee->state = GuiControlState::DISABLED;

	mid = app->tex->Load("Assets/UI/Stats/Mid_Slot.png");
	Mid = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 17, mid, "", { 753,396,60,60 }, (Module*)app->sceneGameplay);
	Mid->state = GuiControlState::DISABLED;

	rangued = app->tex->Load("Assets/UI/Stats/Rangued_Slot.png");
	Rangued = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 17, rangued, "", { 753,471,60,60 }, (Module*)app->sceneGameplay);
	Rangued->state = GuiControlState::DISABLED;

	Equipment_visual = app->tex->Load("Assets/UI/Stats/Equipment_Weapon_SpriteSheet.png");

	//Skills

	Skills_visual = app->tex->Load("Assets/UI/Stats/Skills_Text_Spritesheet.png"); 

	//Quests

	Quests_visual = app->tex->Load("Assets/UI/Stats/Visual_Quests_Spritesheet.png");

	Quest_Completed = app->tex->Load("Assets/UI/Stats/Check.png");

	mainQuest = app->tex->Load("Assets/UI/Stats/MainQuest_Spritesheet.png");
	MainQuest = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, mainQuest, "", { 273,260,300,33 }, (Module*)app->sceneGameplay);
	MainQuest->state = GuiControlState::DISABLED;

	sideQuest_1 = app->tex->Load("Assets/UI/Stats/SideQuest1_Spritesheet.png");
	SideQuest_1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, sideQuest_1, "", { 273,398,300,33 }, (Module*)app->sceneGameplay);
	SideQuest_1->state = GuiControlState::DISABLED;

	sideQuest_2 = app->tex->Load("Assets/UI/Stats/SideQuest2_Spritesheet.png");
	SideQuest_2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, sideQuest_2, "", { 273,445,300,33 }, (Module*)app->sceneGameplay);
	SideQuest_2->state = GuiControlState::DISABLED;

	sideQuest_3 = app->tex->Load("Assets/UI/Stats/SideQuest3_Spritesheet.png");
	SideQuest_3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, sideQuest_3, "", { 273,492,300,33 }, (Module*)app->sceneGameplay);
	SideQuest_3->state = GuiControlState::DISABLED;

	//SFX
	Mission_Completed = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/Mission_Completed.wav");

	Fondo = app->tex->Load("Assets/UI/PauseBackground.png");

	for (int i = 0; i < 4; i++) {

		KleosIdle.PushBack({ 275 * (0 + i), 275 * 0, 275, 275 });

	}
	KleosIdle.loop = true;
	KleosIdle.speed = 0.06f;


	kleosMedieval = app->tex->Load("Assets/UI/Stats/SpriteSheet_Kleos_Stats.png");

	kleosPrehistoric = app->tex->Load("Assets/UI/Stats/Prehistoric_Kleos_Stats.png");

	kleosCyberpunk = app->tex->Load("Assets/UI/Stats/Cyberpunk_Kleos_Stats.png");

	kleosApocalypse = app->tex->Load("Assets/UI/Stats/Demon_Kleos_Stats.png");

	statsEnabled = false;

	i = 0;
	j = 0;
	k = 0;
	q = 0;

	currentAnimation = &KleosIdle;

	statsReference = app->tex->Load("Assets/UI/Stats/Reference_Stats.png");

	OpenPause = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/OpenPause.wav");
	ClosePause = app->audio->LoadFx("Assets/Audio/Fx/SceneGameplay/ClosePause.wav");

	// Tweens

	Animation_Stats.Set();
	Animation_Stats.smoothness = 4;
	Animation_Stats.AddTween(100, 50, EXPONENTIAL_OUT);

	Animation_Inventory.Set();
	Animation_Inventory.smoothness = 4;
	Animation_Inventory.AddTween(100, 60, EXPONENTIAL_OUT);

	Animation_Equipment.Set();
	Animation_Equipment.smoothness = 4;
	Animation_Equipment.AddTween(100, 70, EXPONENTIAL_OUT);

	Animation_Skills.Set();
	Animation_Skills.smoothness = 4;
	Animation_Skills.AddTween(100, 80, EXPONENTIAL_OUT);

	Animation_Quests.Set();
	Animation_Quests.smoothness = 4;
	Animation_Quests.AddTween(100, 90, EXPONENTIAL_OUT);

}

void FeatureMenu::Update()
{

	// Tweens logic

	Animation_Stats.Step(1, false);
	Animation_Inventory.Step(1, false);
	Animation_Equipment.Step(1, false);
	Animation_Skills.Step(1, false);
	Animation_Quests.Step(1, false);

	if (statsEnabled)
	{
		Animation_Stats.Foward();
		Animation_Inventory.Foward();
		Animation_Equipment.Foward();
		Animation_Skills.Foward();
		Animation_Quests.Foward();
	}
	else
	{
		Animation_Stats.JumpTo(0, false);
		Animation_Inventory.JumpTo(0, false);
		Animation_Equipment.JumpTo(0, false);
		Animation_Skills.JumpTo(0, false);
		Animation_Quests.JumpTo(0, false);
	}

	point_Stats = Animation_Stats.GetPoint();
	point_Inventory = Animation_Inventory.GetPoint();
	point_Equipment = Animation_Equipment.GetPoint();
	point_Skills = Animation_Skills.GetPoint();
	point_Quests = Animation_Quests.GetPoint();

	Stats->bounds.y = point_Stats * offset - 721;
	Inventory_->bounds.y = point_Inventory * offset - 721;
	Equipment->bounds.y = point_Equipment * offset - 721;
	Skills->bounds.y = point_Skills * offset - 721;
	Quests->bounds.y = point_Quests * offset - 721;

	//Menu

	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		statsEnabled = !statsEnabled;

		ChangeCharacters = !ChangeCharacters;
		ChangeWeapons = false;
		ShowSlots = false;
		ChangeQuests = false;

		if (statsEnabled) app->audio->PlayFx(OpenPause);
		else app->audio->PlayFx(ClosePause);
		
	}

	//UI Buttons

	if (Stats->state == GuiControlState::PRESSED) {

		i = 0;
	}

	if (Inventory_->state == GuiControlState::PRESSED) {

		i = 1;
	}

	if (Equipment->state == GuiControlState::PRESSED) {

		i = 2;
	}

	if (Skills->state == GuiControlState::PRESSED) {

		i = 3;
	}

	if (Quests->state == GuiControlState::PRESSED) {

		i = 4;
	}

	if (i == 0) {
		ChangeCharacters = true;
		ChangeWeapons = false;
		ShowSlots = false;
		ChangeQuests = false;
	}
	if (i == 1) {
		ChangeCharacters = false;
		ChangeWeapons = false;
		ShowSlots = true;
		ChangeQuests = false;
	}
	if (i == 2) {
		ChangeCharacters = true;
		ChangeWeapons = true;
		ShowSlots = false;
		ChangeQuests = false;
	}
	if (i == 3) {
		ChangeCharacters = true;
		ChangeWeapons = false;
		ShowSlots = false;
		ChangeQuests = false;
	}
	if (i == 4) {
		ChangeCharacters = false;
		ChangeWeapons = false;
		ShowSlots = false;
		ChangeQuests = true;
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

	//Weapon Selection 

	if (Melee->state == GuiControlState::PRESSED) {

		k = 0;
	}

	if (Mid->state == GuiControlState::PRESSED) {

		k = 1;
	}

	if (Rangued->state == GuiControlState::PRESSED) {

		k = 2;
	}

	//Quest selection

	if (MainQuest->state == GuiControlState::PRESSED) {

		q = 0;
	}

	if (SideQuest_1->state == GuiControlState::PRESSED) {

		q = 1;
	}

	if (SideQuest_2->state == GuiControlState::PRESSED) {

		q = 2;
	}

	if (SideQuest_3->state == GuiControlState::PRESSED) {

		q = 3;
	}

	if (i == 1) {

		if (statsEnabled) inventoryManager.inventoryOn = true;
	}


	if (!ShowSlots || !statsEnabled) {

		inventoryManager.inventoryOn = false;

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

				app->render->DrawTexture(statsReference, 784, 246);
				
				app->render->DrawRectangle(app->sceneGameplay->player->xpAccumulatedRect[0], 46, 119, 175);

				if (app->sceneGameplay->player->playerStats[0].level < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].level), 1008, 261, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[0].level >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].level), 986, 261, 50, 50, colorStats);

				}

				int result = app->sceneGameplay->player->playerStats[0].next - app->sceneGameplay->player->playerStats[0].currentXP;

				if (result < 10) {

					app->render->DrawText(std::to_string(result), 975, 300, 20, 30, colorStats);

				}
				else if (result >= 10 && result < 100) {

					app->render->DrawText(std::to_string(result), 965, 300, 30, 30, colorStats);

				}
				else if (result >= 100 && result < 1000) {

					app->render->DrawText(std::to_string(result), 955, 300, 40, 30, colorStats);

				}
				else if (result >= 1000) {

					app->render->DrawText(std::to_string(result), 945, 300, 50, 30, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[0].hp < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].hp), 1008, 351, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[0].hp >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].hp), 986, 351, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[0].atk < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].atk), 1008, 400, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[0].atk >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].atk), 986, 400, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[0].def < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].def), 1008, 449, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[0].def >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].def), 986, 449, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[0].ap < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].ap), 1008, 498, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[0].ap >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[0].ap), 986, 498, 50, 50, colorStats);

				}

			}


			if (j == 1) {

				app->render->DrawTexture(Stats_visual, 0, 0, &SDL_Rect({ 1280 * 1, 0, 1280, 720 }));

				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

				app->render->DrawTexture(kleosPrehistoric, 370, 278, &kleosRect);

				app->render->DrawTexture(statsReference, 784, 246);

				app->render->DrawRectangle(app->sceneGameplay->player->xpAccumulatedRect[1], 46, 119, 175);

				if (app->sceneGameplay->player->playerStats[1].level < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].level), 1008, 261, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[1].level >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].level), 986, 261, 50, 50, colorStats);

				}

				int result = app->sceneGameplay->player->playerStats[1].next - app->sceneGameplay->player->playerStats[1].currentXP;

				if (result < 10) {

					app->render->DrawText(std::to_string(result), 975, 300, 20, 30, colorStats);

				}
				else if (result >= 10 && result < 100) {

					app->render->DrawText(std::to_string(result), 965, 300, 30, 30, colorStats);

				}
				else if (result >= 100 && result < 1000) {

					app->render->DrawText(std::to_string(result), 955, 300, 40, 30, colorStats);

				}
				else if (result >= 1000) {

					app->render->DrawText(std::to_string(result), 945, 300, 50, 30, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[1].hp < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].hp), 1008, 351, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[1].hp >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].hp), 986, 351, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[1].atk < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].atk), 1008, 400, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[1].atk >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].atk), 986, 400, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[1].def < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].def), 1008, 449, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[1].def >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].def), 986, 449, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[1].ap < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].ap), 1008, 498, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[1].ap >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[1].ap), 986, 498, 50, 50, colorStats);

				}

			}

			if (j == 2) {

				app->render->DrawTexture(Stats_visual, 0, 0, &SDL_Rect({ 1280 * 2, 0, 1280, 720 }));

				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

				app->render->DrawTexture(kleosCyberpunk, 370, 278, &kleosRect);

				app->render->DrawTexture(statsReference, 784, 246);

				app->render->DrawRectangle(app->sceneGameplay->player->xpAccumulatedRect[2], 46, 119, 175);

				if (app->sceneGameplay->player->playerStats[2].level < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].level), 1008, 261, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[2].level >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].level), 986, 261, 50, 50, colorStats);

				}

				int result = app->sceneGameplay->player->playerStats[2].next - app->sceneGameplay->player->playerStats[2].currentXP;

				if (result < 10) {

					app->render->DrawText(std::to_string(result), 975, 300, 20, 30, colorStats);

				}
				else if (result >= 10 && result < 100) {

					app->render->DrawText(std::to_string(result), 965, 300, 30, 30, colorStats);

				}
				else if (result >= 100 && result < 1000) {

					app->render->DrawText(std::to_string(result), 955, 300, 40, 30, colorStats);

				}
				else if (result >= 1000) {

					app->render->DrawText(std::to_string(result), 945, 300, 50, 30, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[2].hp < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].hp), 1008, 351, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[2].hp >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].hp), 986, 351, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[2].atk < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].atk), 1008, 400, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[2].atk >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].atk), 986, 400, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[2].def < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].def), 1008, 449, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[2].def >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].def), 986, 449, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[2].ap < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].ap), 1008, 498, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[2].ap >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[2].ap), 986, 498, 50, 50, colorStats);

				}

			}

			if (j == 3) {

				app->render->DrawTexture(Stats_visual, 0, 0, &SDL_Rect({ 1280 * 3, 0, 1280, 720 }));

				SDL_Rect kleosRect = currentAnimation->GetCurrentFrame();

				app->render->DrawTexture(kleosApocalypse, 370, 278, &kleosRect);

				app->render->DrawTexture(statsReference, 784, 246);

				app->render->DrawRectangle(app->sceneGameplay->player->xpAccumulatedRect[3], 46, 119, 175);

				if (app->sceneGameplay->player->playerStats[3].level < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].level), 1008, 261, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[3].level >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].level), 986, 261, 50, 50, colorStats);

				}

				int result = app->sceneGameplay->player->playerStats[3].next - app->sceneGameplay->player->playerStats[3].currentXP;

				if (result < 10) {

					app->render->DrawText(std::to_string(result), 975, 300, 20, 30, colorStats);

				}
				else if (result >= 10 && result < 100) {

					app->render->DrawText(std::to_string(result), 965, 300, 30, 30, colorStats);

				}
				else if (result >= 100 && result < 1000) {

					app->render->DrawText(std::to_string(result), 955, 300, 40, 30, colorStats);

				}
				else if (result >= 1000) {

					app->render->DrawText(std::to_string(result), 945, 300, 50, 30, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[3].hp < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].hp), 1008, 351, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[3].hp >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].hp), 986, 351, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[3].atk < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].atk), 1008, 400, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[3].atk >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].atk), 986, 400, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[3].def < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].def), 1008, 449, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[3].def >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].def), 986, 449, 50, 50, colorStats);

				}

				if (app->sceneGameplay->player->playerStats[3].ap < 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].ap), 1008, 498, 30, 50, colorStats);

				}
				else if (app->sceneGameplay->player->playerStats[3].ap >= 10) {

					app->render->DrawText(std::to_string(app->sceneGameplay->player->playerStats[3].ap), 986, 498, 50, 50, colorStats);

				}

			}

			break;

		}

		case 1: {

			app->render->DrawTexture(Inventory_visual, 0, 0);

			break;

		}

		case 2: {

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

			if (q == 0) {
				app->render->DrawTexture(Quests_visual, 0, 0, &SDL_Rect({ 1280 * 0, 0, 1280, 720 }));
			}

			if (q == 1) {
				app->render->DrawTexture(Quests_visual, 0, 0, &SDL_Rect({ 1280 * 1, 0, 1280, 720 }));
			}

			if (q == 2) {
				app->render->DrawTexture(Quests_visual, 0, 0, &SDL_Rect({ 1280 * 2, 0, 1280, 720 }));
			}

			if (q == 3) {
				app->render->DrawTexture(Quests_visual, 0, 0, &SDL_Rect({ 1280 * 3, 0, 1280, 720 }));
			}

			if (app->sceneGameplay->first_mision) {

				app->render->DrawTexture(Quest_Completed, 582, 387);

			}

			if (app->sceneGameplay->second_mision) {

				app->render->DrawTexture(Quest_Completed, 582, 481);
				
			}

			if (app->sceneGameplay->third_mision) {

				app->render->DrawTexture(Quest_Completed, 582, 434);
				
			}
			
			break;

		}

		}

	}

	if (app->sceneGameplay->first_mision && !firstMissionFX) {

		app->audio->PlayFx(Mission_Completed);
		firstMissionFX = true;

	}

	if (app->sceneGameplay->second_mision && !secondMissionFX) {

		app->audio->PlayFx(Mission_Completed);
		secondMissionFX = true;

	}

	if (app->sceneGameplay->third_mision && !thirdMissionFX) {

		app->audio->PlayFx(Mission_Completed);
		thirdMissionFX = true;

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

			if (Melee->state == GuiControlState::DISABLED) Melee->state = GuiControlState::NORMAL;
			if (Mid->state == GuiControlState::DISABLED) Mid->state = GuiControlState::NORMAL;
			if (Rangued->state == GuiControlState::DISABLED) Rangued->state = GuiControlState::NORMAL;

			Melee->Draw(app->render);
			Mid->Draw(app->render);
			Rangued->Draw(app->render);
	
		}
		if (!ChangeWeapons) {

			if (Melee->state != GuiControlState::DISABLED) Melee->state = GuiControlState::DISABLED;
			if (Mid->state != GuiControlState::DISABLED) Mid->state = GuiControlState::DISABLED;
			if (Rangued->state != GuiControlState::DISABLED) Rangued->state = GuiControlState::DISABLED;
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

		if (ChangeQuests) {

			if (MainQuest->state == GuiControlState::DISABLED) MainQuest->state = GuiControlState::NORMAL;
			if (SideQuest_1->state == GuiControlState::DISABLED) SideQuest_1->state = GuiControlState::NORMAL;
			if (SideQuest_2->state == GuiControlState::DISABLED) SideQuest_2->state = GuiControlState::NORMAL;
			if (SideQuest_3->state == GuiControlState::DISABLED) SideQuest_3->state = GuiControlState::NORMAL;

			MainQuest->Draw(app->render);
			SideQuest_1->Draw(app->render);
			SideQuest_2->Draw(app->render);
			SideQuest_3->Draw(app->render);

		}
		if (!ChangeQuests) {

			if (MainQuest->state != GuiControlState::DISABLED) MainQuest->state = GuiControlState::DISABLED;
			if (SideQuest_1->state != GuiControlState::DISABLED) SideQuest_1->state = GuiControlState::DISABLED;
			if (SideQuest_2->state != GuiControlState::DISABLED) SideQuest_2->state = GuiControlState::DISABLED;
			if (SideQuest_3->state != GuiControlState::DISABLED) SideQuest_3->state = GuiControlState::DISABLED;
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

		if (Melee->state != GuiControlState::DISABLED) Melee->state = GuiControlState::DISABLED;
		if (Mid->state != GuiControlState::DISABLED) Mid->state = GuiControlState::DISABLED;
		if (Rangued->state != GuiControlState::DISABLED) Rangued->state = GuiControlState::DISABLED;

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

		if (MainQuest->state != GuiControlState::DISABLED) MainQuest->state = GuiControlState::DISABLED;
		if (SideQuest_1->state != GuiControlState::DISABLED) SideQuest_1->state = GuiControlState::DISABLED;
		if (SideQuest_2->state != GuiControlState::DISABLED) SideQuest_2->state = GuiControlState::DISABLED;
		if (SideQuest_3->state != GuiControlState::DISABLED) SideQuest_3->state = GuiControlState::DISABLED;

	}

	inventoryManager.PostUpdate();

}
