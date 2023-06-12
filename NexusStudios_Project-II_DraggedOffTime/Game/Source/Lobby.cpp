#include "Lobby.h"
#include "Textures.h"
#include "Physics.h"
#include "App.h"
#include "Render.h"
#include "SceneGameplay.h"
#include "Map.h"
#include "Audio.h"
#include "Lobby.h"

void Lobby::Update()
{
	if (app->map->actualmap == 0)
	{
		if (Tp_Lobby_1 == NULL)
		{
			Tp_Lobby_1 = app->physics->CreateRectangleSensor(820, 370, 110, 110, bodyType::KINEMATIC, ColliderType::TELEPORT_LOBBY);
		}
	}
	
	if (app->map->actualmap == 1)
	{
		if (Tp_Lobby_Prehistoria == NULL)
		{
			Tp_Lobby_Prehistoria = app->physics->CreateRectangleSensor(1268, 318, 11, 65, bodyType::KINEMATIC, ColliderType::TELEPORT_LOBBY_PREHISTORIA);
			Prehistoria = true;
		}
		if (Tp_Lobby_Medieval == NULL)
		{
			Tp_Lobby_Medieval = app->physics->CreateRectangleSensor(50, 306, 7, 75, bodyType::KINEMATIC, ColliderType::TELEPORT_LOBBY_MEDIEVAL);
			Medieval = true;
		}
		if (Tp_Lobby_Infierno == NULL)
		{
			Tp_Lobby_Infierno = app->physics->CreateRectangleSensor(608, 0, 64, 12, bodyType::KINEMATIC, ColliderType::TELEPORT_LOBBY_INFIERNO);
			Infierno = true;
		}
	}

	if (app->map->actualmap != 0)
	{
		app->physics->DestroyBody(Tp_Lobby_1);
		Tp_Lobby_1 = NULL;
	}

	if (app->map->actualmap != 1)
	{
		app->physics->DestroyBody(Tp_Lobby_Infierno);
		Tp_Lobby_Infierno = NULL;

		app->physics->DestroyBody(Tp_Lobby_Medieval);
		Tp_Lobby_Medieval = NULL;

		app->physics->DestroyBody(Tp_Lobby_Prehistoria);
		Tp_Lobby_Prehistoria = NULL;
	}
}

void Lobby::TeleportLobby()
{	
	app->sceneGameplay->player->Teleport(864, 334);
	app->sceneGameplay->LoadMap(1);
}
void Lobby::TeleportPrehistoria()
{
	app->sceneGameplay->player->Teleport(6, 269);
	app->sceneGameplay->LoadMap(2);
	Prehistoria = false;
}

void Lobby::TeleportMedieval()
{
	if (FinalPrehistoria == true)
	{
		app->sceneGameplay->player->Teleport(1200, 327);
		app->sceneGameplay->LoadMap(8);
		Medieval = false;
	}
}

void Lobby::TeleportInfierno()
{
	if (FinalMedieval == true)
	{
		app->sceneGameplay->player->Teleport(632, 702);
		app->sceneGameplay->LoadMap(14);
		Infierno = false;
	}
}
