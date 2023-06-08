#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Log.h"
#include "SceneTitle.h"
#include "SceneGameplay.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, SDL_Texture* tex, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;
	this->tex = tex;

	canClick = true;
	drawBasic = false;
	debug = false;

	buttonHovering = app->audio->LoadFx("Assets/Audio/Fx/HoveringButton.wav");
	hoverOnce = false;

	buttonPressed = app->audio->LoadFx("Assets/Audio/Fx/PressingButton.wav");
	pressedOnce = false;

	timePressed.Start();

}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{

	if (app->input->gamepadON) {

		if (app->sceneGameplay->pause.showPause) {

			maxID = 3;

		}
		else if (app->sceneTitle->showCredits || app->sceneTitle->showSettings || app->sceneGameplay->pause.showSettings) {

			maxID = 0;

		}
		else {

			maxID = 4;

		}

		if (state != GuiControlState::DISABLED && state != GuiControlState::INVISIBLE) {

			if (app->sceneGameplay->featureMenu.statsEnabled) {

				if (app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == KEY_DOWN) {

					selectedButton--;

				}
				
				if (app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == KEY_DOWN) {

					selectedButton++;

				}
				
				if (selectedButton < 0) {

					selectedButton = maxID;

				}

				if (selectedButton > maxID) {

					selectedButton = 0;

				}

			}
			else {

				if (app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN) {

					selectedButton--;

				}

				if (app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN) {

					selectedButton++;

				}

				if (selectedButton < 0) {

					selectedButton = maxID;

				}

				if (selectedButton > maxID) {

					selectedButton = 0;

				}

			}

			if (!app->sceneGameplay->featureMenu.statsEnabled) {

				if (id == selectedButton) {

					state = GuiControlState::FOCUSED;

					if (app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {

						state = GuiControlState::PRESSED;

					}

				}
				else {

					state = GuiControlState::NORMAL;

				}

			}
			else {

				if (id == featureMenuID[selectedButton]) {

					state = GuiControlState::FOCUSED;

					if (app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {

						state = GuiControlState::PRESSED;

					}

				}
				else {

					state = GuiControlState::NORMAL;

				}

			}

		}
		
	}
	else {

		if (state != GuiControlState::DISABLED && state != GuiControlState::INVISIBLE /* && timePressed.ReadMSec() > 100*/)
		{
			// Update the state of the GUiButton according to the mouse position
			app->input->GetMousePosition(mouseX, mouseY);

			GuiControlState previousState = state;

			// I'm inside the limitis of the button
			if (mouseX >= bounds.x && mouseX <= bounds.x + bounds.w &&
				mouseY >= bounds.y && mouseY <= bounds.y + bounds.h) {

				state = GuiControlState::FOCUSED;
				if (previousState != state) {
					LOG("Change state from %d to %d", previousState, state);
				}

				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT) {
					state = GuiControlState::PRESSED;
					//timePressed.Start();
				}

				//
				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP) {
					NotifyObserver();

				}
			}
			else {
				state = GuiControlState::NORMAL;
			}

		}

	}

	

	if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) {

		if (debug) debug = false;
		else debug = true;

	}

	return false;
}

bool GuiButton::Draw(Render* render)
{
	// Draw the button according the GuiControl State

	rect.x = 0;
	rect.y = 0;
	rect.w = bounds.w;
	rect.h = bounds.h;

	switch (state)
	{

	case GuiControlState::DISABLED:
		if (!app->sceneTitle->showSettings && app->sceneTitle->active && !app->sceneTitle->showCredits) {

			rect.y = bounds.h * 3;
			app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);
		}

		break;
	case GuiControlState::NORMAL:

		app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);
		if (debug) app->render->DrawRectangle({ -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, bounds.w, bounds.h }, 0, 255, 0, 255, false);
		hoverOnce = false;
		pressedOnce = false;
		break;
	case GuiControlState::FOCUSED:

		if (!hoverOnce) {
			app->audio->PlayFx(buttonHovering);
			hoverOnce = true;
		}
		;		rect.y = bounds.h;
		app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);
		if (debug) app->render->DrawRectangle({ -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, bounds.w, bounds.h }, 0, 0, 255, 255, false);

		break;
	case GuiControlState::PRESSED:

		if (!pressedOnce) {
			app->audio->PlayFx(buttonPressed);
			pressedOnce = true;
			
		}
		rect.y = bounds.h * 2;
		app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);
		if (debug) app->render->DrawRectangle({ -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, bounds.w, bounds.h }, 255, 0, 0, 255, false);

		break;

	case GuiControlState::INVISIBLE:


		if (!app->sceneGameplay->featureMenu.statsEnabled) {

			rect.y = bounds.h * 4;
			app->render->DrawTexture(tex, -app->render->camera.x + bounds.x, -app->render->camera.y + bounds.y, &rect);
		}

		break;
	}




	app->render->DrawText(text.GetString(), bounds.x, bounds.y, bounds.w, bounds.h, { 255,255,255 });

	return false;
}