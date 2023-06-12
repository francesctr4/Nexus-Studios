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
				app->render->DrawText("4- Puzzle3 Room", 420, 300, 125, 20, { 255, 255, 255, 255 });
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
					app->sceneGameplay->player->Teleport(600, 400);
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
	if (app->map->actualmap == 18)
	{	
		if(TP_Infierno_5 == NULL)
		TP_Infierno_5 = app->physics->CreateRectangleSensor(950, 81, 22, 42, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_Boss = true;
	}
}

void Infierno::CleanUp()
{

}

void Infierno::TeleportInfierno()
{
	if (app->map->actualmap == 18 && Tp_Boss == true)
	{
		app->sceneGameplay->LoadMap(1);
		app->physics->DestroyBody(TP_Infierno_5);
		TP_Infierno_5 = NULL;
		app->sceneGameplay->lobbies.FinalPrehistoria = true;
	}
}

void Infierno::TeleportInfiernoReversa()
{
}

void Infierno::TeleportInfiernoJovani()
{
}
