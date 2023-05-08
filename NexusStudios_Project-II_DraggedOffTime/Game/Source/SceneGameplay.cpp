#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Physics.h"
#include "Window.h"
#include "Map.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "SceneTitle.h"

#include "SceneGameplay.h"

#include "SDL_mixer/include/SDL_mixer.h"

SceneGameplay::SceneGameplay(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneGameplay");
}

// Destructor
SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Awake(pugi::xml_node& config)
{
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->parameters = config.child("player");

	for (pugi::xml_node npcNode = config.child("npc"); npcNode; npcNode = npcNode.next_sibling("npc"))
	{
		NPC* npc = (NPC*)app->entityManager->CreateEntity(EntityType::NPC);
		npc->parameters = npcNode;

		npcs.Add(npc);

	}

	for (pugi::xml_node enemyNode = config.child("enemy"); enemyNode; enemyNode = enemyNode.next_sibling("enemy"))
	{
		Enemy* enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = enemyNode;

		enemies.Add(enemy);

	}

	for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;

	}
	
	return true;
}

// Called before the first frame
bool SceneGameplay::Start()
{
	app->map->actualmap = 0;

	bool retLoad = app->map->Load();
	//app->map->Enable();

	enableMusic = true;

	Fondo = app->tex->Load("Assets/UI/PauseBackground.png");

	//Pause UI

	PauseTitle = app->tex->Load("Assets/UI/PauseTitle.png");

	resume = app->tex->Load("Assets/UI/Resume.png");
	Resume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, resume, "", { 560,267,154,38 }, this);
	Resume->state = GuiControlState::DISABLED;

	settings = app->tex->Load("Assets/UI/PauseSettings.png");
	Settings = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, settings, "", { 544,374,186,42 }, this);
	Settings->state = GuiControlState::DISABLED;

	backTitle = app->tex->Load("Assets/UI/BackTitle.png");
	BackTitle = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, backTitle, "", { 502,481,270,38 }, this);
	BackTitle->state = GuiControlState::DISABLED;

	exit = app->tex->Load("Assets/UI/PauseExit.png");
	Exit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, exit, "", { 592,588,90,38 }, this);
	Exit->state = GuiControlState::DISABLED;

	//Settings UI

	showSettings = false;

	SettingsTitle = app->tex->Load("Assets/UI/SettingsTitle.png");

	checkBox = app->tex->Load("Assets/UI/CheckBox.png");

	checkBoxFullscreen = app->tex->Load("Assets/UI/Fullscreen.png");
	CheckBoxFullscreen = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, checkBox, "", { 729,195,48,47 }, this);
	CheckBoxFullscreen->state = GuiControlState::DISABLED;

	checkBoxVsync = app->tex->Load("Assets/UI/Vsync.png");
	CheckBoxVsync = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, checkBox, "", { 729,270,48,47 }, this);
	CheckBoxVsync->state = GuiControlState::DISABLED;


	framecap = app->tex->Load("Assets/UI/Framecap.png");
	FPS = app->tex->Load("Assets/UI/60FPS.png");

	framecapUP = app->tex->Load("Assets/UI/FramecapUP.png");
	FramecapUP = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, framecapUP, "", { 787,352,25,26 }, this);
	FramecapUP->state = GuiControlState::DISABLED;

	framecapDOWN = app->tex->Load("Assets/UI/FramecapDOWN.png");
	FramecapDOWN = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, framecapDOWN, "", { 787,374,25,26 }, this);
	FramecapDOWN->state = GuiControlState::DISABLED;


	slider = app->tex->Load("Assets/UI/Slider.png");
	SlideBar = app->tex->Load("Assets/UI/SlideBar.png");

	Music = app->tex->Load("Assets/UI/Music.png");
	SliderMusic = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, slider, "", { 692,417,30,59 }, this);
	SliderMusic->state = GuiControlState::DISABLED;

	SFX = app->tex->Load("Assets/UI/SFX.png");
	SliderFX = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 8, slider, "", { 692,494,30,59 }, this);
	SliderFX->state = GuiControlState::DISABLED;


	back = app->tex->Load("Assets/UI/Back.png");
	Back = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, back, "", { 586,622,102,38 }, this);
	Back->state = GuiControlState::DISABLED;

	OpenPause = app->audio->LoadFx("Assets/Audio/Fx/OpenPause.wav");
	ClosePause = app->audio->LoadFx("Assets/Audio/Fx/ClosePause.wav");

	sensorJovani = app->physics->CreateCircleSensor(500,500,10, bodyType::KINEMATIC, ColliderType::PUERTA_JOVANI);

	sensorJovani->listener;


	return true;
}

// Called each loop iteration
bool SceneGameplay::PreUpdate()
{
	OPTICK_EVENT();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/Level1_Music.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneGameplay::Update(float dt)
{
	OPTICK_EVENT();


	//UI

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		showPause = true;
	}

	if (Resume->state == GuiControlState::PRESSED) {

		showPause = false;
		app->audio->PlayFx(OpenPause);
	}

	if (Settings->state == GuiControlState::PRESSED) {

		showSettings = true;
		app->audio->PlayFx(OpenPause);
		Back->state = GuiControlState::NORMAL;

	}

	if (BackTitle->state == GuiControlState::PRESSED) {

		enableMusic = true;
		Resume->state = GuiControlState::DISABLED;
		Settings->state = GuiControlState::DISABLED;
		BackTitle->state = GuiControlState::DISABLED;
		Exit->state = GuiControlState::DISABLED;
		showPause = false;

		app->fadeToBlack->Fade(this, (Module*)app->sceneTitle);

	}

	if (CheckBoxFullscreen->crossed) {

		app->sceneTitle->CheckBoxFullscreen->crossed = true;
		SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_RenderSetLogicalSize(app->render->renderer, 1280, 720);

	}

	if (!CheckBoxFullscreen->crossed) {

		app->sceneTitle->CheckBoxFullscreen->crossed = false;
		SDL_SetWindowFullscreen(app->win->window, 0);

	}

	if (CheckBoxVsync->crossed) {

		app->sceneTitle->CheckBoxVsync->crossed = true;
		SDL_GL_SetSwapInterval(1);

	}
	if (!CheckBoxVsync->crossed) {

		app->sceneTitle->CheckBoxVsync->crossed = false;
		SDL_GL_SetSwapInterval(0);

	}
	
	app->sceneTitle->SliderMusic->bounds.x = SliderMusic->bounds.x;
	app->sceneTitle->SliderMusic->posx = SliderMusic->posx;

	app->sceneTitle->SliderFX->bounds.x = SliderFX->bounds.x;
	app->sceneTitle->SliderFX->posx = SliderFX->posx;

	Mix_VolumeMusic((SliderMusic->bounds.x - 631) * (128 - 0) / (753 - 631) + 0);

	for (int i = 0; i < app->audio->fx.Count(); i++) {

		Mix_VolumeChunk(app->audio->fx.At(i)->data, (SliderFX->bounds.x - 631) * (128 - 0) / (753 - 631) + 0);

	}

	if (Back->state == GuiControlState::PRESSED) {
		showSettings = false;
		showPause = true;
		app->audio->PlayFx(ClosePause);
	}

	

	//Player

	if (player->godMode == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		{
			map_selector = true;
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 0)
		{
			
			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 1;
			app->sceneGameplay->player->Teleport(650, 700);

			//Move Npcs Map_1
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			//Move Enemies Map_1
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 0)
		{
			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 2;
			app->sceneGameplay->player->Teleport(650, 700);
			
			//Move Npcs Map_2
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_2
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 1)
		{

			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 0;
			app->sceneGameplay->player->Teleport(150, 430);
			
			//Move Npcs Map_0
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			
			//Move Npcs Map_0
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 1)
		{

			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 2;
			app->sceneGameplay->player->Teleport(650, 700);
			
			//Move Npcs Map_2
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_2
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 2)
		{
			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 0;
			app->sceneGameplay->player->Teleport(150, 430);

			//Move Npcs Map_0
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			
			//Move Enemies Map_0
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 2)
		{
			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 1;
			app->sceneGameplay->player->Teleport(650, 700);
			
			//Move Npcs Map_1
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			//Move Enemies Map_1
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		}
	}



	if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		app->sceneGameplay->player->Teleport(700, 500);
	}

	if (!app->entityManager->IsEnabled()) {

		app->entityManager->Enable();

	}

	if (app->sceneGameplay->player->godMode) app->physics->debug = true;
	else app->physics->debug = false;


	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneBattle);

	}
	
	
	if (app->map->actualmap == 2)
	{
		
	}
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool SceneGameplay::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	app->guiManager->Draw();

	//Pause UI

	if (showPause || showSettings) app->render->DrawTexture(Fondo, 0, 0);

	if (showPause) {

		if (Resume->state == GuiControlState::DISABLED) Resume->state = GuiControlState::NORMAL;
		if (Settings->state == GuiControlState::DISABLED) Settings->state = GuiControlState::NORMAL;
		if (BackTitle->state == GuiControlState::DISABLED) BackTitle->state = GuiControlState::NORMAL;
		if (Exit->state == GuiControlState::DISABLED) Exit->state = GuiControlState::NORMAL;

		app->render->DrawTexture(PauseTitle, 512, 143);

		Resume->Draw(app->render);
		Settings->Draw(app->render);
		BackTitle->Draw(app->render);
		Exit->Draw(app->render);

	}
	if (!showPause) {

		if (Resume->state != GuiControlState::DISABLED) Resume->state = GuiControlState::DISABLED;
		if (Settings->state != GuiControlState::DISABLED) Settings->state = GuiControlState::DISABLED;
		if (BackTitle->state != GuiControlState::DISABLED) BackTitle->state = GuiControlState::DISABLED;
		if (Exit->state != GuiControlState::DISABLED) Exit->state = GuiControlState::DISABLED;

	}

	//Settings UI

	if (showSettings) {

		showPause = false;

		app->render->DrawTexture(SlideBar, 636, 438);
		app->render->DrawTexture(SlideBar, 636, 515);

		if (Back->state == GuiControlState::DISABLED) Back->state = GuiControlState::NORMAL;
		if (SliderMusic->state == GuiControlState::DISABLED) SliderMusic->state = GuiControlState::NORMAL;
		if (SliderFX->state == GuiControlState::DISABLED) SliderFX->state = GuiControlState::NORMAL;
		if (CheckBoxFullscreen->state == GuiControlState::DISABLED) CheckBoxFullscreen->state = GuiControlState::NORMAL;
		if (CheckBoxVsync->state == GuiControlState::DISABLED) CheckBoxVsync->state = GuiControlState::NORMAL;
		if (FramecapUP->state == GuiControlState::DISABLED) FramecapUP->state = GuiControlState::NORMAL;
		if (FramecapDOWN->state == GuiControlState::DISABLED) FramecapDOWN->state = GuiControlState::NORMAL;


		app->render->DrawTexture(SettingsTitle, 449, 73);
		app->render->DrawTexture(checkBoxFullscreen, 496, 202);
		app->render->DrawTexture(checkBoxVsync, 496, 279);
		app->render->DrawTexture(framecap, 496, 356);
		app->render->DrawTexture(FPS, 728, 364);
		app->render->DrawTexture(Music, 496, 433);
		app->render->DrawTexture(SFX, 496, 510);

		Back->Draw(app->render);
		SliderMusic->Draw(app->render);
		SliderFX->Draw(app->render);
		CheckBoxFullscreen->Draw(app->render);
		CheckBoxVsync->Draw(app->render);
		FramecapUP->Draw(app->render);
		FramecapUP->Draw(app->render);
		FramecapDOWN->Draw(app->render);



		/*if (app->win->configWindow.child("fullscreen").attribute("value").as_bool() == false) {
			app->win->configWindow.child("fullscreen").append_attribute("value") = "true";
		}*/

	}

	if (!showSettings) {

		if (Back->state != GuiControlState::DISABLED) Back->state = GuiControlState::DISABLED;
		if (SliderMusic->state != GuiControlState::DISABLED) SliderMusic->state = GuiControlState::DISABLED;
		if (SliderFX->state != GuiControlState::DISABLED) SliderFX->state = GuiControlState::DISABLED;
		if (CheckBoxFullscreen->state != GuiControlState::DISABLED) CheckBoxFullscreen->state = GuiControlState::DISABLED;
		if (CheckBoxVsync->state != GuiControlState::DISABLED) CheckBoxVsync->state = GuiControlState::DISABLED;
		if (FramecapUP->state != GuiControlState::DISABLED) FramecapUP->state = GuiControlState::DISABLED;
		if (FramecapDOWN->state != GuiControlState::DISABLED) FramecapDOWN->state = GuiControlState::DISABLED;

	}

	//Player
	if (player->godMode == true)
	{

		app->render->DrawText("GODMODE", 100, 100, 90, 40, { 255, 255, 255, 255 });
		app->render->DrawText("1. Maps", 150, 150, 60, 20, { 255, 255, 255, 255 });
		
		if (map_selector == true && actually == 0)
		{
			app->render->DrawText("1. Mapa Jovani", 260, 150, 125, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 108, 20, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 1)
		{
			app->render->DrawText("1. Mapa Mazmorra", 260, 150, 142, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 108, 20, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 2)
		{
			app->render->DrawText("1. Mapa Mazmorra", 260, 150, 142, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Jovani", 260, 180, 125, 20, { 255, 255, 255, 255 });
		}
	}

	if (Exit->state == GuiControlState::PRESSED) ret = false;

	return ret;
}

// Called before quitting
bool SceneGameplay::CleanUp()
{
	LOG("Freeing scene");
	//app->map->CleanUp();
	//app->physics->CleanUp();
	return true;
}

bool SceneGameplay::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}