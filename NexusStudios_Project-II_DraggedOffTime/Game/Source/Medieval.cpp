#include "Medieval.h"
#include "Textures.h"
#include "Physics.h"
#include "App.h"
#include "Render.h"
#include "SceneGameplay.h"
#include "Map.h"
#include "Audio.h"


void Medieval::Update()
{

	if (app->map->actualmap == 8)
	{
		if (TP_Medieval_1 == NULL)
			TP_Medieval_1 = app->physics->CreateRectangleSensor(385, 720, 112, 11, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL);
		TP_Medieval_1_bool = true;
	}
	if (app->map->actualmap == 9)
	{
		if (TP_Medieval_2 == NULL)
			TP_Medieval_2 = app->physics->CreateRectangleSensor(400,410, 25, 10, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL);
		TP_Medieval_2_bool = true;
	}
	if (app->map->actualmap == 10)
	{
		if (TP_Medieval_3 == NULL)
		{
			TP_Medieval_3 = app->physics->CreateRectangleSensor(100, 293, 25, 10, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL);
			TP_Medieval_3_bool = true;
		}
		if (TP_Medieval_6 == NULL)
		{
			/*TP_Medieval_6 = app->physics->CreateRectangleSensor(400, 410, 25, 10, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_JOVANI);
			TP_Medieval_Jovani_bool = true;*/
		}
	}
	
	if (app->map->actualmap == 12)
	{
		if (TP_Medieval_5 == NULL)
		{
			TP_Medieval_5 = app->physics->CreateRectangleSensor(640, 95, 25, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL);
			TP_Medieval_5_bool = true;
		}
	}
	if (app->map->actualmap == 13)
	{
		if (TP_Medieval_Final == NULL)
		{
			TP_Medieval_Final = app->physics->CreateRectangleSensor(640, 48, 25, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL);
			TP_Medieval_Final_bool = true;
		}
	}


}

void Medieval::TeleportMedieval()
{
	if (app->map->actualmap == 8 && TP_Medieval_1_bool == true)
	{
		app->physics->DestroyBody(TP_Medieval_1);
		TP_Medieval_1 = NULL;
		app->sceneGameplay->LoadMap(9);
		app->sceneGameplay->player->Teleport(745, 20);
		TP_Medieval_1_bool = false;
		TP_Medieval_2_bool = false;
		TP_Medieval_3_bool = false;
		TP_Medieval_5_bool = false;
		TP_Medieval_Final_bool = false;
		TP_Medieval_Jovani = false;
		TP_Medieval_5 = false;
		TP_Medieval_Final = false;
	}

	if (app->map->actualmap == 9 && TP_Medieval_2_bool == true)
	{
		app->sceneGameplay->LoadMap(10);
		app->sceneGameplay->player->Teleport(1041, 700);
		app->physics->DestroyBody(TP_Medieval_2);
		TP_Medieval_2 = NULL;
		TP_Medieval_1_bool = false;
		TP_Medieval_2_bool = false;
		TP_Medieval_3_bool = false;
		TP_Medieval_5_bool = false;
		TP_Medieval_Final_bool = false;
		TP_Medieval_Jovani = false;
		TP_Medieval_5 = false;
		TP_Medieval_Final = false;
	}

	if (app->map->actualmap == 10 && TP_Medieval_3_bool == true)
	{
		app->sceneGameplay->LoadMap(12);
		app->sceneGameplay->player->Teleport(890, 700);
		app->physics->DestroyBody(TP_Medieval_3);
		TP_Medieval_3 = NULL;

		TP_Medieval_1_bool = false;
		TP_Medieval_2_bool = false;
		TP_Medieval_3_bool = false;
		TP_Medieval_5_bool = false;
		TP_Medieval_Final_bool = false;
		TP_Medieval_Jovani = false;
		TP_Medieval_5 = false;
		TP_Medieval_Final = false;
	}
	if (app->map->actualmap == 12 && TP_Medieval_5_bool == true)
	{
		app->sceneGameplay->LoadMap(13);
		app->sceneGameplay->player->Teleport(650, 700);
		app->physics->DestroyBody(TP_Medieval_5);
		TP_Medieval_5 = NULL;

		TP_Medieval_1_bool = false;
		TP_Medieval_2_bool = false;
		TP_Medieval_3_bool = false;
		TP_Medieval_5_bool = false;
		TP_Medieval_Final_bool = false;
		TP_Medieval_Jovani = false;
		TP_Medieval_5 = false;
		TP_Medieval_Final = false;
	}
	if (app->map->actualmap == 13 && TP_Medieval_Final_bool == true)
	{
		app->sceneGameplay->LoadMap(1);
		app->physics->DestroyBody(TP_Medieval_Final);
		TP_Medieval_Final = NULL;
		app->sceneGameplay->player->Teleport(650, 700);

		TP_Medieval_1_bool = false;
		TP_Medieval_2_bool = false;
		TP_Medieval_3_bool = false;
		TP_Medieval_5_bool = false;
		TP_Medieval_Final_bool = false;
		TP_Medieval_Jovani = false;
		TP_Medieval_5 = false;
		TP_Medieval_Final = false;
	}
}

void Medieval::TeleportMedievalReversa()
{
	
}

void Medieval::TeleportMedievalJovani()
{
	if (app->map->actualmap == 10 && TP_Medieval_Jovani_bool == true)
	{
		app->sceneGameplay->LoadMap(11);
		app->sceneGameplay->player->Teleport(632, 700);

		TP_Medieval_1_bool = false;
		TP_Medieval_2_bool = false;
		TP_Medieval_3_bool = false;
		TP_Medieval_5_bool = false;
		TP_Medieval_Final_bool = false;
		TP_Medieval_Jovani = false;
		TP_Medieval_5 = false;
		TP_Medieval_Final = false;
	}

}
