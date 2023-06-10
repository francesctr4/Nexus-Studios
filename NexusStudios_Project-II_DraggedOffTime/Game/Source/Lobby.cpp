#include "Lobby.h"
#include "Textures.h"
#include "Physics.h"
#include "App.h"
#include "Render.h"
#include "SceneGameplay.h"
#include "Map.h"
#include "Audio.h"
#include "Lobby.h"

void Infierno::Update()
{
	

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

Lobby::Lobby()
{
}

void Lobby::CleanUp()
{

}

void Lobby::Update()
{
}

void Lobby::TeleportLobby()
{
}
