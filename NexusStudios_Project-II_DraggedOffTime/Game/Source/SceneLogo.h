#pragma once

struct SDL_Texture;

class SceneLogo : public Module
{
public:

	SceneLogo(bool startEnabled);

	// Destructor
	virtual ~SceneLogo();

	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);
	
public:

	bool enableMusic;

private:

	SDL_Texture* nexusStudiosLogo;

	uint logoFX;
	bool FX_played;

};