#include "Prehistoria.h"
#include "Textures.h"
#include "Physics.h"
#include "App.h"
#include "Render.h"
#include "SceneGameplay.h"
#include "Map.h"
#include "Audio.h"


void Prehistoria::Update()
{
	
	if (app->map->actualmap == 2)
	{
		if (TP_Prehistoria_1 == NULL)
			TP_Prehistoria_1 = app->physics->CreateRectangleSensor(1290, 300, 10, 279, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA);
		TP_Prehistoria_1_bool = true;
	}
	if (app->map->actualmap == 3)
	{
		if (TP_Prehistoria_2 == NULL)
			TP_Prehistoria_2 = app->physics->CreateRectangleSensor(1290, 230, 10, 100, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA);
		TP_Prehistoria_2_bool = true;
	}
	if (app->map->actualmap == 4)
	{
		if (TP_Prehistoria_Jovani == NULL)
			TP_Prehistoria_Jovani = app->physics->CreateRectangleSensor(1120, 225, 25, 18, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA_JOVANI);
		TP_Prehistoria_Jovani_bool = true;
	}
	if (app->map->actualmap == 4)
	{
		if (TP_Prehistoria_3 == NULL)
			TP_Prehistoria_3 = app->physics->CreateRectangleSensor(580, 735, 230, 10, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA);
		TP_Prehistoria_3_bool = true;
	}
	if (app->map->actualmap == 6)
	{
		if (TP_Prehistoria_5 == NULL)
			TP_Prehistoria_5 = app->physics->CreateRectangleSensor(1290, 500, 10, 112, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA);
		TP_Prehistoria_5_bool = true;
	}
	if (app->map->actualmap == 7)
	{
		if (TP_Prehistoria_Final == NULL)
			TP_Prehistoria_Final = app->physics->CreateRectangleSensor(640, 10, 30, 15, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA);
		TP_Prehistoria_Final_bool = true;
	}

	//Reversa
	if (app->map->actualmap == 2)
	{
		if (TP_Prehistoria_1_Reversa == NULL)
			TP_Prehistoria_1_Reversa = app->physics->CreateRectangleSensor(-10, 275, 10, 279, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA_REVERS);
		TP_Prehistoria_1_bool_Reversa = true;
	}

	if (app->map->actualmap == 3)
	{
		if (TP_Prehistoria_2_Reversa == NULL)
			TP_Prehistoria_2_Reversa = app->physics->CreateRectangleSensor(-15, 295, 10, 279, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA_REVERS);
		TP_Prehistoria_2_bool_Reversa = true;
	}
	if (app->map->actualmap == 4)
	{
		if (TP_Prehistoria_3_Reversa == NULL)
			TP_Prehistoria_3_Reversa = app->physics->CreateRectangleSensor(-15, 295, 10, 279, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA_REVERS);
		TP_Prehistoria_3_bool_Reversa = true;
	}
	if (app->map->actualmap == 5)
	{
		if (TP_Prehistoria_Jovani_bool_Reversa == NULL)
			TP_Prehistoria_Jovani_Reversa = app->physics->CreateRectangleSensor(317, 730, 25, 15, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA_REVERS);
		TP_Prehistoria_Jovani_bool_Reversa = true;
	}
	if (app->map->actualmap == 6)
	{
		if (TP_Prehistoria_5_Reversa == NULL)
			TP_Prehistoria_5_Reversa = app->physics->CreateRectangleSensor(250, -15, 120, 15, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA_REVERS);
		TP_Prehistoria_5_bool_Reversa = true;
	}
	if (app->map->actualmap == 7)
	{
		if (TP_Prehistoria_Final_Reversa == NULL)
			TP_Prehistoria_Final_Reversa = app->physics->CreateRectangleSensor(-10, 400, 10, 260, bodyType::KINEMATIC, ColliderType::TELEPORT_PREHISTORIA_REVERS);
		TP_Prehistoria_Final_bool_Reversa = true;
	}
}

void Prehistoria::TeleportPrehistoria()
{
	if (app->map->actualmap == 2 && TP_Prehistoria_1_bool == true)
	{
		app->sceneGameplay->LoadMap(3);
		app->physics->DestroyBody(TP_Prehistoria_1);
		TP_Prehistoria_1 = NULL;
		app->sceneGameplay->player->Teleport(20, 275);
		TP_Prehistoria_1_bool = false;
		TP_Prehistoria_2_bool = false;
		TP_Prehistoria_3_bool = false;
		TP_Prehistoria_5_bool = false;
		TP_Prehistoria_Final_bool = false;

	}
	if (app->map->actualmap == 3 && TP_Prehistoria_2_bool == true)
	{
		app->sceneGameplay->LoadMap(4);
		app->physics->DestroyBody(TP_Prehistoria_2);
		TP_Prehistoria_2 = NULL;
		app->sceneGameplay->player->Teleport(20, 285);
		TP_Prehistoria_1_bool = false;
		TP_Prehistoria_2_bool = false;
		TP_Prehistoria_3_bool = false;
		TP_Prehistoria_5_bool = false;
		TP_Prehistoria_Final_bool = false;
	}
	if (app->map->actualmap == 4 && TP_Prehistoria_3_bool == true)
	{
		app->sceneGameplay->LoadMap(6);
		app->physics->DestroyBody(TP_Prehistoria_3);
		TP_Prehistoria_3 = NULL;
		app->sceneGameplay->player->Teleport(250, 10);
		TP_Prehistoria_1_bool = false;
		TP_Prehistoria_2_bool = false;
		TP_Prehistoria_3_bool = false;
		TP_Prehistoria_5_bool = false;
		TP_Prehistoria_Final_bool = false;
	}
	if (app->map->actualmap == 6 && TP_Prehistoria_5_bool == true)
	{
		app->sceneGameplay->LoadMap(7);
		app->physics->DestroyBody(TP_Prehistoria_5);
		TP_Prehistoria_5 = NULL;
		app->sceneGameplay->player->Teleport(10, 500);
		TP_Prehistoria_1_bool = false;
		TP_Prehistoria_2_bool = false;
		TP_Prehistoria_3_bool = false;
		TP_Prehistoria_5_bool = false;
		TP_Prehistoria_Final_bool = false;
	}
	if (app->map->actualmap == 7 && TP_Prehistoria_Final_bool == true)
	{
		app->sceneGameplay->LoadMap(1);
		app->physics->DestroyBody(TP_Prehistoria_Final);
		TP_Prehistoria_Final = NULL;
		app->sceneGameplay->player->Teleport(317, 700);
		TP_Prehistoria_1_bool = false;
		TP_Prehistoria_2_bool = false;
		TP_Prehistoria_3_bool = false;
		TP_Prehistoria_5_bool = false;
		TP_Prehistoria_Final_bool = false;
	}
}

void Prehistoria::TeleportPrehistoriaJovani()
{
	if (app->map->actualmap == 4 && TP_Prehistoria_Jovani_bool == true)
	{
		app->sceneGameplay->LoadMap(5);
		app->physics->DestroyBody(TP_Prehistoria_Jovani);
		TP_Prehistoria_Jovani = NULL;
		app->sceneGameplay->player->Teleport(317, 700);
		TP_Prehistoria_Jovani_bool = false;
	}
}

void Prehistoria::TeleportPrehistoria_Revers()
{
	if (app->map->actualmap == 2 && TP_Prehistoria_1_bool_Reversa == true)
	{
		app->sceneGameplay->LoadMap(1);
		app->physics->DestroyBody(TP_Prehistoria_1_Reversa);
		TP_Prehistoria_1_Reversa = NULL;
		app->sceneGameplay->player->Teleport(1270, 360);
		TP_Prehistoria_1_bool_Reversa = false;
		TP_Prehistoria_2_bool_Reversa = false;
		TP_Prehistoria_3_bool_Reversa = false;
		TP_Prehistoria_Jovani_bool_Reversa = false;
		TP_Prehistoria_5_bool_Reversa = false;
		TP_Prehistoria_Final_bool_Reversa = false;
	}

	if (app->map->actualmap == 3 && TP_Prehistoria_2_bool_Reversa == true)
	{
		app->sceneGameplay->LoadMap(2);
		app->physics->DestroyBody(TP_Prehistoria_2_Reversa);
		TP_Prehistoria_2_Reversa = NULL;
		app->sceneGameplay->player->Teleport(1270, 350);
		TP_Prehistoria_1_bool_Reversa = false;
		TP_Prehistoria_2_bool_Reversa = false;
		TP_Prehistoria_3_bool_Reversa = false;
		TP_Prehistoria_Jovani_bool_Reversa = false;
		TP_Prehistoria_5_bool_Reversa = false;
		TP_Prehistoria_Final_bool_Reversa = false;
	}

	if (app->map->actualmap == 4 && TP_Prehistoria_3_bool_Reversa == true)
	{
		app->sceneGameplay->LoadMap(3);
		app->physics->DestroyBody(TP_Prehistoria_3_Reversa);
		TP_Prehistoria_3_Reversa = NULL;
		app->sceneGameplay->player->Teleport(1265, 265);
		TP_Prehistoria_1_bool_Reversa = false;
		TP_Prehistoria_2_bool_Reversa = false;
		TP_Prehistoria_3_bool_Reversa = false;
		TP_Prehistoria_Jovani_bool_Reversa = false;
		TP_Prehistoria_5_bool_Reversa = false;
		TP_Prehistoria_Final_bool_Reversa = false;
	}
	if (app->map->actualmap == 5 && TP_Prehistoria_Jovani_bool_Reversa == true)
	{
		app->sceneGameplay->LoadMap(4);
		app->physics->DestroyBody(TP_Prehistoria_Jovani_Reversa);
		TP_Prehistoria_Jovani_Reversa = NULL;
		app->sceneGameplay->player->Teleport(1120, 250);
		TP_Prehistoria_1_bool_Reversa = false;
		TP_Prehistoria_2_bool_Reversa = false;
		TP_Prehistoria_3_bool_Reversa = false;
		TP_Prehistoria_Jovani_bool_Reversa = false;
		TP_Prehistoria_5_bool_Reversa = false;
		TP_Prehistoria_Final_bool_Reversa = false;
	}
	if (app->map->actualmap == 6 && TP_Prehistoria_5_bool_Reversa == true)
	{
		app->sceneGameplay->LoadMap(4);
		app->physics->DestroyBody(TP_Prehistoria_5_Reversa);
		TP_Prehistoria_5_Reversa = NULL;
		app->sceneGameplay->player->Teleport(650, 690);
		TP_Prehistoria_1_bool_Reversa = false;
		TP_Prehistoria_2_bool_Reversa = false;
		TP_Prehistoria_3_bool_Reversa = false;
		TP_Prehistoria_Jovani_bool_Reversa = false;
		TP_Prehistoria_5_bool_Reversa = false;
		TP_Prehistoria_Final_bool_Reversa = false;
	}

	if (app->map->actualmap == 7 && TP_Prehistoria_Final_bool_Reversa == true)
	{
		app->sceneGameplay->LoadMap(6);
		app->physics->DestroyBody(TP_Prehistoria_Final_Reversa);
		TP_Prehistoria_Final_Reversa = NULL;
		app->sceneGameplay->player->Teleport(1270, 500);
		TP_Prehistoria_1_bool_Reversa = false;
		TP_Prehistoria_2_bool_Reversa = false;
		TP_Prehistoria_3_bool_Reversa = false;
		TP_Prehistoria_Jovani_bool_Reversa = false;
		TP_Prehistoria_5_bool_Reversa = false;
		TP_Prehistoria_Final_bool_Reversa = false;
	}
}
