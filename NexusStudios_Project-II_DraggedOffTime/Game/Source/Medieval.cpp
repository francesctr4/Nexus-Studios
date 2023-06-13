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
			TP_Medieval_1 = app->physics->CreateRectangleSensor(385, 725, 112, 11, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL);
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
			TP_Medieval_6 = app->physics->CreateRectangleSensor(570, 48, 25, 10, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_JOVANI);
			TP_Medieval_6_bool = true;
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

	//Reversa
	if (app->map->actualmap == 8)
	{
		if (TP_Medieval_1_Reversa == NULL)
		{
			TP_Medieval_1_Reversa = app->physics->CreateRectangleSensor(1290, 300, 5, 130, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_REVERS);
			TP_Medieval_1_bool_Reversa = true;
		}
	}
	if (app->map->actualmap == 9)
	{
		if (TP_Medieval_2_Reversa == NULL)
		{
			TP_Medieval_2_Reversa = app->physics->CreateRectangleSensor(730, 0, 50, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_REVERS);
			TP_Medieval_2_bool_Reversa = true;
		}
	}
	if (app->map->actualmap == 10)
	{
		if (TP_Medieval_3_Reversa == NULL)
		{
			TP_Medieval_3_Reversa = app->physics->CreateRectangleSensor(1040, 720, 150, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_REVERS);
			TP_Medieval_3_bool_Reversa = true;
		}
	}
	if (app->map->actualmap == 11)
	{
		if (TP_Medieval_Jovani_Reversa == NULL)
		{
			TP_Medieval_Jovani_Reversa = app->physics->CreateRectangleSensor(650, 720, 150, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_REVERS);
			TP_Medieval_Jovani_bool_Reversa = true;
		}
	}
	if (app->map->actualmap == 12)
	{
		if (TP_Medieval_5_Reversa == NULL)
		{
			TP_Medieval_5_Reversa = app->physics->CreateRectangleSensor(850, 730, 75, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_REVERS);
			TP_Medieval_5_bool_Reversa = true;
		}
	}
	if (app->map->actualmap == 13)
	{
		if (TP_Medieval_Final_Reversa == NULL)
		{
			TP_Medieval_Final_Reversa = app->physics->CreateRectangleSensor(640, 715, 75, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_MEDIEVAL_REVERS);
			TP_Medieval_Final_bool_Reversa = true;
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
		app->sceneGameplay->player->Teleport(890, 710);
		app->physics->DestroyBody(TP_Medieval_6);
		TP_Medieval_6 = NULL;
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
		app->sceneGameplay->player->Teleport(650, 700);

		app->physics->DestroyBody(TP_Medieval_1);
		TP_Medieval_1 = NULL;

		app->physics->DestroyBody(TP_Medieval_1_Reversa);
		TP_Medieval_1_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_2_Reversa);
		TP_Medieval_2_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_2);
		TP_Medieval_2 = NULL;

		app->physics->DestroyBody(TP_Medieval_Jovani_Reversa);
		TP_Medieval_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_Jovani);
		TP_Medieval_Jovani = NULL;

		app->physics->DestroyBody(TP_Medieval_3);
		TP_Medieval_3 = NULL;

		app->physics->DestroyBody(TP_Medieval_3_Reversa);
		TP_Medieval_3_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_5_Reversa);
		TP_Medieval_5_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_5);
		TP_Medieval_5 = NULL;

		app->physics->DestroyBody(TP_Medieval_Final_Reversa);
		TP_Medieval_Final_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_Final);
		TP_Medieval_Final = NULL;

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
	if (app->map->actualmap == 8 && TP_Medieval_1_bool_Reversa == true)
	{
		app->physics->DestroyBody(TP_Medieval_1_Reversa);
		TP_Medieval_1_Reversa = NULL;
		
		app->sceneGameplay->LoadMap(1);
		app->sceneGameplay->player->Teleport(15, 350);

		TP_Medieval_1_bool_Reversa = false;
		TP_Medieval_2_bool_Reversa = false;
		TP_Medieval_3_bool_Reversa = false;
		TP_Medieval_5_bool_Reversa = false;
		TP_Medieval_Final_bool_Reversa = false;
		TP_Medieval_Jovani_Reversa = false;
		TP_Medieval_5_Reversa = false;
		TP_Medieval_Final_Reversa = false;
	}

	if (app->map->actualmap == 9 && TP_Medieval_2_bool_Reversa == true)
	{
		app->physics->DestroyBody(TP_Medieval_2_Reversa);
		TP_Medieval_2_Reversa = NULL;

		app->sceneGameplay->LoadMap(8);
		app->sceneGameplay->player->Teleport(400, 680);

		app->physics->DestroyBody(TP_Medieval_1_Reversa);
		TP_Medieval_1_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_2);
		TP_Medieval_2 = NULL;

		TP_Medieval_1_bool_Reversa = false;
		TP_Medieval_2_bool_Reversa = false;
		TP_Medieval_3_bool_Reversa = false;
		TP_Medieval_5_bool_Reversa = false;
		TP_Medieval_Final_bool_Reversa = false;
		TP_Medieval_Jovani_Reversa = false;
		TP_Medieval_5_Reversa = false;
		TP_Medieval_Final_Reversa = false;
	}

	if (app->map->actualmap == 10 && TP_Medieval_3_bool_Reversa == true)
	{
		app->physics->DestroyBody(TP_Medieval_3_Reversa);
		TP_Medieval_3_Reversa = NULL;
		
		app->sceneGameplay->LoadMap(9);
		app->sceneGameplay->player->Teleport(400, 450);
		
		app->physics->DestroyBody(TP_Medieval_2_Reversa);
		TP_Medieval_2_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_3);
		TP_Medieval_3 = NULL;
		
		app->physics->DestroyBody(TP_Medieval_Jovani);
		TP_Medieval_Jovani = NULL;

		TP_Medieval_1_bool_Reversa = false;
		TP_Medieval_2_bool_Reversa = false;
		TP_Medieval_3_bool_Reversa = false;
		TP_Medieval_5_bool_Reversa = false;
		TP_Medieval_Final_bool_Reversa = false;
		TP_Medieval_Jovani_Reversa = false;
		TP_Medieval_5_Reversa = false;
		TP_Medieval_Final_Reversa = false;
	}
	if (app->map->actualmap == 11 && TP_Medieval_Jovani_bool_Reversa == true)
	{
		app->physics->DestroyBody(TP_Medieval_Jovani_Reversa);
		TP_Medieval_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Medieval_Jovani);
		TP_Medieval_Jovani= NULL;
		
		app->physics->DestroyBody(TP_Medieval_3_Reversa);
		TP_Medieval_3_Reversa = NULL;

		app->sceneGameplay->LoadMap(10);
		app->sceneGameplay->player->Teleport(570, 70);

		TP_Medieval_1_bool_Reversa = false;
		TP_Medieval_2_bool_Reversa = false;
		TP_Medieval_3_bool_Reversa = false;
		TP_Medieval_5_bool_Reversa = false;
		TP_Medieval_Final_bool_Reversa = false;
		TP_Medieval_Jovani_Reversa = false;
		TP_Medieval_5_Reversa = false;
		TP_Medieval_Final_Reversa = false;
	}
	if (app->map->actualmap == 12 && TP_Medieval_5_bool_Reversa == true)
	{
		app->physics->DestroyBody(TP_Medieval_5_Reversa);
		TP_Medieval_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Medieval_5);
		TP_Medieval_5 = NULL;

		app->physics->DestroyBody(TP_Medieval_3_Reversa);
		TP_Medieval_3_Reversa = NULL;

		app->sceneGameplay->LoadMap(10);
		app->sceneGameplay->player->Teleport(100, 315);

		TP_Medieval_1_bool_Reversa = false;
		TP_Medieval_2_bool_Reversa = false;
		TP_Medieval_3_bool_Reversa = false;
		TP_Medieval_5_bool_Reversa = false;
		TP_Medieval_Final_bool_Reversa = false;
		TP_Medieval_Jovani_Reversa = false;
		TP_Medieval_5_Reversa = false;
		TP_Medieval_Final_Reversa = false;
	}

	if (app->map->actualmap == 13 && TP_Medieval_Final_bool_Reversa == true)
	{
		app->physics->DestroyBody(TP_Medieval_Final_Reversa);
		TP_Medieval_Final_Reversa = NULL;
		app->physics->DestroyBody(TP_Medieval_Final);
		TP_Medieval_Final = NULL;

		app->sceneGameplay->LoadMap(12);
		app->sceneGameplay->player->Teleport(640, 115);

		TP_Medieval_1_bool_Reversa = false;
		TP_Medieval_2_bool_Reversa = false;
		TP_Medieval_3_bool_Reversa = false;
		TP_Medieval_5_bool_Reversa = false;
		TP_Medieval_Final_bool_Reversa = false;
		TP_Medieval_Jovani_Reversa = false;
		TP_Medieval_5_Reversa = false;
		TP_Medieval_Final_Reversa = false;
	}
}

void Medieval::TeleportMedievalJovani()
{
	if (app->map->actualmap == 10 && TP_Medieval_6_bool == true)
	{
		app->sceneGameplay->LoadMap(11);
		app->sceneGameplay->player->Teleport(632, 700);
		app->physics->DestroyBody(TP_Medieval_6);
		TP_Medieval_6 = NULL;
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

}
