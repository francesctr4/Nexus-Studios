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
}

void Lobby::TeleportLobby()
{
	app->sceneGameplay->player->Teleport(864, 334);
	app->sceneGameplay->LoadMap(1);

	app->physics->DestroyBody(Tp_Lobby_1);
	Tp_Lobby_1 = NULL;
}
