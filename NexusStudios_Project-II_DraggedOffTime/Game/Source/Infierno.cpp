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
					app->sceneGameplay->player->Teleport(640, 360);
				}
				else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(3);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 440);
				}
				else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(4);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 360);
				}
				else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(5);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 390);
				}
				else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(6);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(500, 300);
				}
				else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(7);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 360);
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
					app->sceneGameplay->player->Teleport(640, 360);
					
					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final = NULL;

				}
				else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(9);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 300);

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final = NULL;
				}
				else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(10);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 360);

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final = NULL;
				}
				else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(11);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 360);

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final = NULL;
				}
				else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(12);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 360);


					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final = NULL;
				}
				else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(13);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					timerActivated = false;
					app->sceneGameplay->player->Teleport(640, 360);

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_1_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_2);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_2 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Jovani = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_3_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_5);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_5 = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final_Reversa = NULL;

					app->physics->DestroyBody(app->sceneGameplay->mapa_Medieval.TP_Medieval_Final);
					app->sceneGameplay->mapa_Medieval.TP_Medieval_Final = NULL;
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
					app->sceneGameplay->player->Teleport(640, 360);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(15);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 360);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(16);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 320);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(17);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 360);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(18);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 360);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(19);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 340);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(20);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(600, 360);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(21);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 360);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(22);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 320);
					timerActivated = false;
				}
				else if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {

					app->sceneGameplay->LoadMap(23);
					map_selector = false;
					lobby = false;
					prehistoria = false;
					medieval = false;
					infierno = false;
					app->sceneGameplay->player->Teleport(640, 360);
					timerActivated = false;
				}

			}
		}
	}
	// Change all the sensors on the different maps
	if (app->map->actualmap == 14)
	{	
		if (TP_Infierno_1 == NULL)
		{
			TP_Infierno_1 = app->physics->CreateRectangleSensor(-5, 530, 4, 110, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_1 = true;
		}
	}
	if (app->map->actualmap == 15)
	{
		if (TP_Infierno_2 == NULL)
		{
			TP_Infierno_2 = app->physics->CreateRectangleSensor(-10, 340, 4, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_2 = true;
		}
	}
	if (app->map->actualmap == 16)
	{
		if (Tp_Puzzle1 == NULL)
		{
			Tp_Puzzle1 = app->physics->CreateRectangleSensor(1290, 625, 6, 108, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_Puzzle_1 = true;
		}
	}
	if (app->map->actualmap == 19)
	{
		if (Tp_Puzzle2 == NULL)
		{
			Tp_Puzzle2 = app->physics->CreateRectangleSensor(1300, 200, 6, 108, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_Puzzle_2 = true;
		}
	}
	if (app->map->actualmap == 20)
	{
		if (Tp_Puzzle3 == NULL)
		{
			Tp_Puzzle3 = app->physics->CreateRectangleSensor(630, -10, 60, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_Puzzle_3 = true;
		}
	}
	if (app->map->actualmap == 21)
	{
		if (TP_Infierno_3 == NULL)
		{
			TP_Infierno_3 = app->physics->CreateRectangleSensor(630, -10, 60, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_3 = true;
		}
	}
	if (app->map->actualmap == 17)
	{
		if (TP_Infierno_4 == NULL)
		{
			TP_Infierno_4 = app->physics->CreateRectangleSensor(630, -10, 60, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_4 = true;
		}
	}
	if (app->map->actualmap == 17)
	{
		if (TP_Infierno_Jovani == NULL)
		{
			TP_Infierno_Jovani = app->physics->CreateRectangleSensor(1300, 270, 5, 100, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_JOVANI);
			Tp_Jovani = true;
		}
	}

	if (app->map->actualmap == 18)
	{
		if (TP_Infierno_5 == NULL)
		{
			TP_Infierno_5 = app->physics->CreateRectangleSensor(706, 15, 35, 10, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
			Tp_5 = true;
		}
	}

	//Reversa
	if (app->map->actualmap == 14)
	{
		if (TP_Infierno_1_Reversa == NULL)
		{
			TP_Infierno_1_Reversa = app->physics->CreateRectangleSensor(632, 740, 100, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_1_Reversa = true;
		}
	}
	if (app->map->actualmap == 15)
	{
		if (TP_Infierno_2_Reversa == NULL)
		{
			TP_Infierno_2_Reversa = app->physics->CreateRectangleSensor(1280, 565, 5, 100, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_2_Reversa = true;
		}
	}
	if (app->map->actualmap == 16)
	{
		if (TP_Infierno_3_Reversa == NULL)
		{
			TP_Infierno_3_Reversa = app->physics->CreateRectangleSensor(1285, 106, 5, 100, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_3_Reversa = true;
		}
	}
	if (app->map->actualmap == 19)
	{
		if (Tp_Puzzle1_Reversa == NULL)
		{
			Tp_Puzzle1_Reversa = app->physics->CreateRectangleSensor(-10, 280, 5, 100, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_Puzzle_1_Reversa = true;
		}
	}
	if (app->map->actualmap == 20)
	{
		if (Tp_Puzzle2_Reversa == NULL)
		{
			Tp_Puzzle2_Reversa = app->physics->CreateRectangleSensor(-10, 575, 5, 100, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_Puzzle_2_Reversa = true;
		}
	}
	if (app->map->actualmap == 21)
	{
		if (Tp_Puzzle3_Reversa == NULL)
		{
			Tp_Puzzle3_Reversa = app->physics->CreateRectangleSensor(640, 725, 100, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_Puzzle_3_Reversa = true;
		}
	}
	if (app->map->actualmap == 17)
	{
		if (TP_Infierno_4_Reversa == NULL)
		{
			TP_Infierno_4_Reversa = app->physics->CreateRectangleSensor(640, 725, 100, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_4_Reversa = true;
		}
	}
	if (app->map->actualmap == 18)
	{
		if (TP_Infierno_5_Reversa == NULL)
		{
			TP_Infierno_5_Reversa = app->physics->CreateRectangleSensor(640, 725, 100, 5, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_5_Reversa = true;
		}
	}
	if (app->map->actualmap == 22)
	{
		if (TP_Infierno_Jovani_Reversa == NULL)
		{
			TP_Infierno_Jovani_Reversa = app->physics->CreateRectangleSensor(0, 200, 5, 100, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO_REVERS);
			Tp_Jovani_Reversa = true;
		}
	}
	
}

void Infierno::CleanUp()
{

}

void Infierno::TeleportInfierno()
{
	if (app->map->actualmap == 14 && Tp_1 == true)
	{
		app->sceneGameplay->LoadMap(15);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;
		app->sceneGameplay->player->Teleport(1265, 560);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}
	if (app->map->actualmap == 15 && Tp_2 == true)
	{
		app->sceneGameplay->LoadMap(16);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		
		app->sceneGameplay->player->Teleport(1255, 106);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}
	if (app->map->actualmap == 16 && Tp_Puzzle_1 == true)
	{
		app->sceneGameplay->LoadMap(19);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;
		app->sceneGameplay->player->Teleport(20, 295);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}
	if (app->map->actualmap == 19 && Tp_Puzzle_2 == true)
	{
		app->sceneGameplay->LoadMap(20);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;
		app->sceneGameplay->player->Teleport(20,575);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}
	if (app->map->actualmap == 20 && Tp_Puzzle_3 == true)
	{
		app->sceneGameplay->LoadMap(21);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;
		app->sceneGameplay->player->Teleport(640, 675);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}
	if (app->map->actualmap == 21 && Tp_3 == true)
	{
		app->sceneGameplay->LoadMap(17);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;
		app->sceneGameplay->player->Teleport(640, 675);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}

	if (app->map->actualmap == 17 && Tp_4 == true)
	{
		app->sceneGameplay->LoadMap(18);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;


		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->sceneGameplay->player->Teleport(640, 675);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_5 = false;
		Tp_Jovani = false;
	}

	if (app->map->actualmap == 18 && Tp_5 == true)
	{
		app->sceneGameplay->LoadMap(1);
		app->physics->DestroyBody(TP_Infierno_1);
		TP_Infierno_1 = NULL;
		app->physics->DestroyBody(TP_Infierno_2);
		TP_Infierno_2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle1);
		Tp_Puzzle1 = NULL;
		app->physics->DestroyBody(Tp_Puzzle2);
		Tp_Puzzle2 = NULL;
		app->physics->DestroyBody(Tp_Puzzle3);
		Tp_Puzzle3 = NULL;
		app->physics->DestroyBody(TP_Infierno_3);
		TP_Infierno_3 = NULL;
		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;
		app->physics->DestroyBody(TP_Infierno_5);
		TP_Infierno_5 = NULL;

		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->sceneGameplay->player->Teleport(650, 700);

		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}	
}

void Infierno::TeleportInfiernoReversa()
{
	if (app->map->actualmap == 14 && Tp_1_Reversa == true)
	{
		app->sceneGameplay->LoadMap(1);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;


		app->sceneGameplay->player->Teleport(640, 20);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 15 && Tp_2_Reversa == true)
	{
		app->sceneGameplay->LoadMap(14);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;
		app->sceneGameplay->player->Teleport(15, 530);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 16 && Tp_2_Reversa == true)
	{
		app->sceneGameplay->LoadMap(15);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;
		app->sceneGameplay->player->Teleport(15, 340);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 19 && Tp_Puzzle_1_Reversa == true)
	{
		app->sceneGameplay->LoadMap(16);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;
		app->sceneGameplay->player->Teleport(1270, 585);
		
		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 20 && Tp_Puzzle_2_Reversa == true)
	{
		app->sceneGameplay->LoadMap(19);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->sceneGameplay->player->Teleport(1270, 255);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 21 && Tp_Puzzle_3_Reversa == true)
	{
		app->sceneGameplay->LoadMap(20);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->sceneGameplay->player->Teleport(665, 20);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 17 && Tp_4_Reversa == true)
	{
		app->sceneGameplay->LoadMap(21);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->sceneGameplay->player->Teleport(640, 20);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 18 && Tp_4_Reversa == true)
	{
		app->sceneGameplay->LoadMap(17);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->sceneGameplay->player->Teleport(640, 20);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
	if (app->map->actualmap == 22 && Tp_Jovani_Reversa == true)
	{
		app->sceneGameplay->LoadMap(17);
		app->physics->DestroyBody(TP_Infierno_1_Reversa);
		TP_Infierno_1_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_2_Reversa);
		TP_Infierno_2_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_3_Reversa);
		TP_Infierno_3_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle1_Reversa);
		Tp_Puzzle1_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle2_Reversa);
		Tp_Puzzle2_Reversa = NULL;
		app->physics->DestroyBody(Tp_Puzzle3_Reversa);
		Tp_Puzzle3_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_5_Reversa);
		TP_Infierno_5_Reversa = NULL;
		app->physics->DestroyBody(TP_Infierno_Jovani_Reversa);
		TP_Infierno_Jovani_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->sceneGameplay->player->Teleport(1270, 285);

		Tp_1_Reversa = false;
		Tp_2_Reversa = false;
		Tp_Puzzle_1_Reversa = false;
		Tp_Puzzle_2_Reversa = false;
		Tp_Puzzle_3_Reversa = false;
		Tp_3_Reversa = false;
		Tp_4_Reversa = false;
		Tp_Jovani_Reversa = false;
	}
}

void Infierno::TeleportInfiernoJovani()
{
	if (app->map->actualmap == 17 && Tp_Jovani == true)
	{
		app->sceneGameplay->LoadMap(22);
		app->physics->DestroyBody(TP_Infierno_Jovani);
		TP_Infierno_Jovani = NULL;

		app->physics->DestroyBody(TP_Infierno_4_Reversa);
		TP_Infierno_4_Reversa = NULL;

		app->physics->DestroyBody(TP_Infierno_4);
		TP_Infierno_4 = NULL;

		app->sceneGameplay->player->Teleport(20, 185);
		Tp_1 = false;
		Tp_2 = false;
		Tp_Puzzle_1 = false;
		Tp_Puzzle_2 = false;
		Tp_Puzzle_3 = false;
		Tp_3 = false;
		Tp_4 = false;
		Tp_Jovani = false;
	}
}
