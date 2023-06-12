#pragma once

#include "Animation.h"
#include "Tweening.h"

struct SDL_Texture;

class SceneLore : public Module
{
public:

	explicit SceneLore(bool startEnabled);

	// Destructor
	virtual ~SceneLore();

	bool Awake(pugi::xml_node& config) override;

	// Called before the first frame
	bool Start() override;

	// Called before all Updates
	bool PreUpdate() override;

	// Called each loop iteration
	bool Update(float dt) override;

	// Called after all Updates
	bool PostUpdate() override;

	// Called before quitting
	bool CleanUp() override;

	bool OnGuiMouseClickEvent(GuiControl* control) override;

public:

	bool enableMusic;

private:

	// Texture

	SDL_Texture* background;
	SDL_Texture* fullComic;

	SDL_Texture* vinyeta1;
	SDL_Texture* vinyeta2;
	SDL_Texture* vinyeta3;
	SDL_Texture* vinyeta4;
	SDL_Texture* vinyeta5;
	SDL_Texture* vinyeta6;

	int comicProgression;

	// Tweens

	int offset = 808;

	Tween Animation_Vinyeta1;
	float point_Vinyeta1;

	Tween Animation_Vinyeta2;
	float point_Vinyeta2;

	Tween Animation_Vinyeta3;
	float point_Vinyeta3;

	Tween Animation_Vinyeta4;
	float point_Vinyeta4;

	Tween Animation_Vinyeta5;
	float point_Vinyeta5;

	Tween Animation_Vinyeta6;
	float point_Vinyeta6;

	// FX

	uint FXvinyeta1 = 0;
	bool FXvinyeta1_active = false;

	uint FXvinyeta2 = 0;
	bool FXvinyeta2_active = false;

	uint FXvinyeta3 = 0;
	bool FXvinyeta3_active = false;

	uint FXvinyeta4 = 0;
	bool FXvinyeta4_active = false;

	uint FXvinyeta5 = 0;
	bool FXvinyeta5_active = false;

	uint FXvinyeta6 = 0;
	bool FXvinyeta6_active = false;

};