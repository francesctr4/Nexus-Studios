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
	if (app->sceneGameplay->player->godMode) {

		if (app->input->GetKey(SDL_SCANCODE_M) && !map_selector)
		{
			map_selector = true;
		}

		if (map_selector) {

			if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN && !timerActivated)
			{
				lobby = true;

				if (!timerActivated) {

					selectionTimer.Start();
					timerActivated = true;

				}
			}
			if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && !timerActivated)
			{
				prehistoria = true;
				
				if (!timerActivated) {

					selectionTimer.Start();
					timerActivated = true;

				}

			}
			else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && !timerActivated)
			{
				medieval = true;
				
				if (!timerActivated) {

					selectionTimer.Start();
					timerActivated = true;

				}

			}
			else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && !timerActivated)
			{
				infierno = true;
				
				if (!timerActivated) {

					selectionTimer.Start();
					timerActivated = true;

				}

			}

			if (app->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && lobby)
			{
				lobby = false;
			}
			else if (app->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && prehistoria)
			{
				prehistoria = false;
			}
			else if (app->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && medieval)
			{
				medieval = false;
			}
			else if (app->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && infierno)
			{
				infierno = false;
			}

		}

	}
	else {

		map_selector = false;

		lobby = false;
		prehistoria = false;
		medieval = false;
		infierno = false;

	}

	if (app->sceneGameplay->player->godMode)
	{
		app->render->DrawText("GODMODE", 100, 100, 130, 80, { 255, 255, 255, 255 });
		app->render->DrawText("M. Maps", 150, 165, 85, 50, { 255, 255, 255, 255 });

		if (map_selector)
		{
			app->render->DrawText("0. Lobby Map", 245, 170, 160, 45, { 255, 255, 255, 255 });
			app->render->DrawText("1. Prehistoric Map", 245, 200, 160, 45, { 255, 255, 255, 255 });
			app->render->DrawText("2. Medieval Map", 245, 230, 160, 45, { 255, 255, 255, 255 });
			app->render->DrawText("3. Infernal Map", 245, 260, 160, 45, { 255, 255, 255, 255 });

			if (lobby)
			{
				app->render->DrawText("0- Cave Room", 420, 180, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("1- Doors Room", 420, 210, 125, 20, { 255, 255, 255, 255 });
			}
			else if (prehistoria)
			{
				app->render->DrawText("0- 1st Room", 420, 180, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("1- Puzzle1 Room", 420, 210, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("2- Puzzle2 Room", 420, 240, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("3- Jovani Room", 420, 270, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("4- Puzzle3 Room", 420, 300, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("5- Boss Room", 420, 330, 125, 20, { 255, 255, 255, 255 });
			}
			else if (medieval)
			{
				app->render->DrawText("0- 1st Room", 420, 180, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("1- Puzzle1 Room", 420, 210, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("2- Puzzle2 Room", 420, 240, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("3- Jovani Room", 420, 270, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("4- Chest Room", 420, 300, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("5- Boss Room", 420, 330, 125, 20, { 255, 255, 255, 255 });
			}
			else if (infierno)
			{
				app->render->DrawText("0- 1st Room", 420, 180, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("1- 2nd Room", 420, 210, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("2- 3rd Room", 420, 240, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("3- 4th Room", 420, 270, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("4- Boss Room", 420, 300, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("5- Puzzle1 Room", 420, 330, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("6- Puzzle2 Room", 420, 360, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("7- Puzzle3 Room", 420, 390, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("8- Jovani Room", 420, 420, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("9- Chest Room", 420, 450, 125, 20, { 255, 255, 255, 255 });
			}
		}

	}

	// TP to maps logic

	if (app->sceneGameplay->player->godMode)
	{
		if (selectionTimer.ReadMSec() >= 100) {

			if (lobby) {

				if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(0);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;

				}
				else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(1);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}

			}
			else if (prehistoria) {

				if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(2);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(3);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(4);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(5);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(6);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(7);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}

			}
			else if (medieval) {

				if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(8);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(150, 430);

				}
				else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(9);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(10);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(11);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(12);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(13);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
				}

			}
			else if (infierno) {

				if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(14);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(650, 700);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(15);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(1265, 560);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(16);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(1255, 106);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(17);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(10, 300);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(18);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(12, 600);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(19);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 700);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(20);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 700);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(21);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 700);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(22);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(650, 700);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(23);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(650, 700);
					timerActivated = false;
				}

			}
		}
	}

	// Change all the sensors on the different maps

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

void Infierno::TeleportInfierno()
{
	switch (app->map->actualmap)
	{
	case 0:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_0);
		app->sceneGameplay->trigger_3 = true;
		//app->sceneGameplay->LoadMap(1);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(0, 300);

		break;

	case 1:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_1);
		//app->sceneGameplay->LoadMap(2);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(1265, 560);
		break;

	case 2:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_2);
		//app->sceneGameplay->LoadMap(3);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(1255, 106);
		break;
	case 3:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_3);
		//app->sceneGameplay->LoadMap(6);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(10, 300);
		break;
	case 4:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_4);
		//app->sceneGameplay->LoadMap(5);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(640, 700);
		break;
	case 5:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.TP_Infierno_5);
		//app->sceneGameplay->LoadMap(0);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(200, 671);
		break;
	case 6:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.Tp_Puzzle1);
		//app->sceneGameplay->LoadMap(7);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(12, 600);
		break;
	case 7:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.Tp_Puzzle2);
		//app->sceneGameplay->LoadMap(8);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(640, 700);
		break;

	case 8:
		app->physics->DestroyBody(app->sceneGameplay->mapa_Infierno.Tp_Puzzle3);
		//app->sceneGameplay->LoadMap(4);
		app->sceneGameplay->mapa_Infierno.map_selector = false;
		app->sceneGameplay->player->Teleport(637, 700);
		break;

	default:
		break;
	}
}
