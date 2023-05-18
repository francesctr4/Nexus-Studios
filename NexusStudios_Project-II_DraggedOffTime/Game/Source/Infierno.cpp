#include "Infierno.h"
#include "Textures.h"
#include "App.h"
#include "Render.h"
#include "SceneGameplay.h"
#include "Map.h"
#include "Audio.h"

Infierno::Infierno()
{
}

Infierno::~Infierno()
{
}

void Infierno::Start()
{
	app->map->actualmap = 4;

	bool retLoad = app->map->Load();

}

void Infierno::Update()
{
	if (app->sceneGameplay->player->godMode == true)
	{
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(200, 671);

			//Move Npcs Map_1
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);

			//Move Enemies Map_1
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(95),PIXEL_TO_METERS(555) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(95),PIXEL_TO_METERS(555) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);

			//Move Npcs Map_1
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(220) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			//Move Enemies Map_1
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(1265, 560);

			//Move Npcs Map_2
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(956),PIXEL_TO_METERS(220) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(956),PIXEL_TO_METERS(220) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_2
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(490),PIXEL_TO_METERS(400) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(490),PIXEL_TO_METERS(400) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{

			app->map->CleanUp();
			app->map->actualmap = 3;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(1255, 106);

			//Move Npcs Map_3
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


			//Move Enemies Map_3
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(700),PIXEL_TO_METERS(500) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(700),PIXEL_TO_METERS(500) }, 0);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{

			app->map->CleanUp();
			app->map->actualmap = 6;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(10, 300);

			//Move Npcs Map_3
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(450),PIXEL_TO_METERS(350) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(450),PIXEL_TO_METERS(350) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_3
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(275) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(275) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 7;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(12, 600);

			//Move Npcs Map_3
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(550) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(800),PIXEL_TO_METERS(550) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_3
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(600),PIXEL_TO_METERS(200) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(600),PIXEL_TO_METERS(200) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 8;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(640, 700);

			//Move Npcs Map_3
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(642),PIXEL_TO_METERS(500) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(642),PIXEL_TO_METERS(500) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_3
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 4;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(640, 700);

			//Move Npcs Map_3
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_3
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(735),PIXEL_TO_METERS(310) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(735),PIXEL_TO_METERS(310) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 5;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(640, 700);

			//Move Npcs Map_2
			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(332),PIXEL_TO_METERS(200) }, 0);

			//Move Enemies Map_2
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 9;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);

			app->sceneGameplay->npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			//Move Enemies Map_2
			app->sceneGameplay->enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			app->sceneGameplay->enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);

			app->sceneGameplay->enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			app->sceneGameplay->enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			app->sceneGameplay->enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		}


		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && infierno == false)
		{
			map_selector = !map_selector;
		}
		if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			infierno = !infierno;
		}
		if (app->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && infierno == true)
		{
			infierno = false;
		}
	}

}

void Infierno::CleanUp()
{

}
