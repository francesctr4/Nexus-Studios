#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "PathFinding.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "Player.h"

#include "SceneLore.h"

SceneLore::SceneLore(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneLore");

	enableMusic = true;

}

// Destructor
SceneLore::~SceneLore()
{}

bool SceneLore::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool SceneLore::Start()
{

	// Textures

	background = app->tex->Load("Assets/Textures/Comic/Background.png");
	fullComic = app->tex->Load("Assets/Textures/Comic/FullComic.png");

	vinyeta1 = app->tex->Load("Assets/Textures/Comic/Vinyeta1.png");
	vinyeta2 = app->tex->Load("Assets/Textures/Comic/Vinyeta2.png");
	vinyeta3 = app->tex->Load("Assets/Textures/Comic/Vinyeta3.png");
	vinyeta4 = app->tex->Load("Assets/Textures/Comic/Vinyeta4.png");
	vinyeta5 = app->tex->Load("Assets/Textures/Comic/Vinyeta5.png");
	vinyeta6 = app->tex->Load("Assets/Textures/Comic/Vinyeta6.png");

	// Tweens

	Animation_Vinyeta1.Set();
	Animation_Vinyeta1.smoothness = 4;
	Animation_Vinyeta1.AddTween(100, 40, QUADRATIC_OUT);

	Animation_Vinyeta2.Set();
	Animation_Vinyeta2.smoothness = 4;
	Animation_Vinyeta2.AddTween(100, 20, QUADRATIC_OUT);

	Animation_Vinyeta3.Set();
	Animation_Vinyeta3.smoothness = 4;
	Animation_Vinyeta3.AddTween(100, 10, QUADRATIC_IN);
	Animation_Vinyeta3.JumpTo(100, false);

	Animation_Vinyeta4.Set();
	Animation_Vinyeta4.smoothness = 4;
	Animation_Vinyeta4.AddTween(100, 50, QUADRATIC_OUT);

	Animation_Vinyeta5.Set();
	Animation_Vinyeta5.smoothness = 4;
	Animation_Vinyeta5.AddTween(100, 20, QUADRATIC_IN);
	Animation_Vinyeta5.JumpTo(100, false);

	Animation_Vinyeta6.Set();
	Animation_Vinyeta6.smoothness = 4;
	Animation_Vinyeta6.AddTween(100, 50, QUADRATIC_IN);
	Animation_Vinyeta6.JumpTo(100, false);

	return true;
}

// Called each loop iteration
bool SceneLore::PreUpdate()
{
	OPTICK_EVENT();

	app->entityManager->Disable();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/NoMusic.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneLore::Update(float dt)
{
	OPTICK_EVENT();

	//app->render->DrawText("LORE DRAGGED OFF TIME", 200, 300, 900, 90, { 255,255,255 });

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {

		comicProgression++;

	}

	if (comicProgression >= 0) {

		Animation_Vinyeta1.Step(1, false);
		Animation_Vinyeta1.Foward();

	}

	if (comicProgression >= 1) {

		Animation_Vinyeta2.Step(1, false);
		Animation_Vinyeta2.Foward();

	}

	if (comicProgression >= 2) {

		Animation_Vinyeta3.Step(1, false);
		Animation_Vinyeta3.Backward();

	}

	if (comicProgression >= 3) {

		Animation_Vinyeta4.Step(1, false);
		Animation_Vinyeta4.Foward();

	}

	if (comicProgression >= 4) {

		Animation_Vinyeta5.Step(1, false);
		Animation_Vinyeta5.Backward();

	}

	if (comicProgression >= 5) {

		Animation_Vinyeta6.Step(1, false);
		Animation_Vinyeta6.Backward();

	}

	point_Vinyeta1 = Animation_Vinyeta1.GetPoint();
	point_Vinyeta2 = Animation_Vinyeta2.GetPoint();
	point_Vinyeta3 = Animation_Vinyeta3.GetPoint();
	point_Vinyeta4 = Animation_Vinyeta4.GetPoint();
	point_Vinyeta5 = Animation_Vinyeta5.GetPoint();
	point_Vinyeta6 = Animation_Vinyeta6.GetPoint();

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || (app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) && comicProgression >= 6) {

		enableMusic = true;

		comicProgression = 0;
		Animation_Vinyeta1.JumpTo(0, false);
		Animation_Vinyeta2.JumpTo(0, false);
		Animation_Vinyeta3.JumpTo(100, false);
		Animation_Vinyeta4.JumpTo(0, false);
		Animation_Vinyeta5.JumpTo(100, false);
		Animation_Vinyeta6.JumpTo(100, false);

		app->fadeToBlack->Fade(this, reinterpret_cast<Module*>(app->sceneGameplay));
	}

	return true;
}

// Called each loop iteration
bool SceneLore::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	app->render->DrawTexture(background, 0, 0);

	//app->render->DrawTexture(fullComic, 0, 0);

	if (comicProgression >= 0) {

		//app->render->DrawTexture(vinyeta1, 179, 34);
		app->render->DrawTexture(vinyeta1, point_Vinyeta1 * offset - 629, 34);

	}

	if (comicProgression >= 1) {

		//app->render->DrawTexture(vinyeta2, 682, 34);
		app->render->DrawTexture(vinyeta2, 682, point_Vinyeta2 * offset - 774);

	}

	if (comicProgression >= 2) {

		//app->render->DrawTexture(vinyeta3, 682, 135);
		app->render->DrawTexture(vinyeta3, 682, point_Vinyeta3 * offset + 135);

	}

	if (comicProgression >= 3) {

		app->render->DrawTexture(vinyeta4, 342, 276);
		//app->render->DrawTexture(vinyeta4, 342, point_Vinyeta4 * offset + 135);

	}

	if (comicProgression >= 4) {

		//app->render->DrawTexture(vinyeta5, 190, 433);
		app->render->DrawTexture(vinyeta5, 190, point_Vinyeta5 * offset + 433);

	}

	if (comicProgression >= 5) {

		//app->render->DrawTexture(vinyeta6, 613, 420);
		app->render->DrawTexture(vinyeta6, point_Vinyeta6 * offset + 613, 420);

	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_BACK] == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneLore::CleanUp()
{

	return true;
}

bool SceneLore::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}