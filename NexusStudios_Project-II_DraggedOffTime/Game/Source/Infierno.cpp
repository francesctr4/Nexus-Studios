#include "Infierno.h"
#include "Textures.h"
#include "Physics.h"
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
	
}

void Infierno::Update()
{


	if (app->sceneGameplay->player->godMode == true)
	{
		app->render->DrawText("GODMODE", 100, 100, 130, 80, { 255, 255, 255, 255 });
		app->render->DrawText("1. Maps", 150, 165, 85, 50, { 255, 255, 255, 255 });

		if (map_selector == true)
		{
			app->render->DrawText("2- Mapa Infierno", 245, 170, 160, 45, { 255, 255, 255, 255 });
			if (infierno == true)
			{
				app->render->DrawText("0- 1st Room", 420, 180, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("1- 2nd Room", 420, 210, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("2- 3rd Room", 420, 240, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("3- 4th Room", 420, 270, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("4- 5th Room", 420, 300, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("5- 6th Room", 420, 330, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("6- 7th Room", 420, 360, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("7- Chest", 420, 390, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("8- Jovani Room", 420, 420, 125, 20, { 255, 255, 255, 255 });
			}
		}

	}
	if (app->sceneGameplay->player->godMode == true)
	{
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(0);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(200, 671);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(1);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(2);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(1265, 560);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(3);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(1255, 106);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(6);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(10, 300);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(7);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(12, 600);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(8);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(640, 700);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(4);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(640, 700);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(5);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(640, 700);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
		{
			app->sceneGameplay->LoadMap(9);
			map_selector = false;
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);
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
	//Charge all the sensors on the different maps
	if (app->map->actualmap == 0 && Tp_0 == true)
	{
		TP_Infierno_0 = app->physics->CreateRectangleSensor(1168, 365, 50, 50, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_0 = false;
	}

	if (app->map->actualmap == 1 && Tp_1 == true)
	{
		TP_Infierno_1 = app->physics->CreateRectangleSensor(0, 550, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_1 = false;
	}
	if (app->map->actualmap == 2 && Tp_2 == true)
	{
		TP_Infierno_2 = app->physics->CreateRectangleSensor(0, 350, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_2 = false;
	}

	if (app->map->actualmap == 3 && Tp_3 == true)
	{
		TP_Infierno_3 = app->physics->CreateRectangleSensor(1273, 590, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_3 = false;
	}

	if (app->map->actualmap == 3 && Tp_Cofre == true)
	{
		TP_Infierno_Cofre = app->physics->CreateRectangleSensor(1180, 255, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_JOVANI);
		Tp_Cofre = false;
	}

	if (app->map->actualmap == 6 && Tp_Puzzle_1 == true)
	{
		TP_Infierno_4 = app->physics->CreateRectangleSensor(1280, 210, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_4 = false;
	}
	if (app->map->actualmap == 7 && Tp_Puzzle_2 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(610, 0, 95, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_Jovani = false;
	}

	if (app->map->actualmap == 8 && Tp_Puzzle_3 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(610, 0, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_Jovani = false;
	}
	//Puzzle3
	if (app->map->actualmap == 4 && Tp_4 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(610, 0, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_4 = false;
	}
	//BossFinal
	if (app->map->actualmap == 5 && Tp_5 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(960, 80, 20, 20, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_5 = false;
	}

}

void Infierno::CleanUp()
{

}
