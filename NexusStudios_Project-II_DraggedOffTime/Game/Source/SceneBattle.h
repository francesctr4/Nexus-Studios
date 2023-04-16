#pragma once

struct SDL_Texture;

class SceneBattle : public Module
{
public:

	SceneBattle(bool startEnabled);
	
	// Destructor
	virtual ~SceneBattle();

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

	//Sprite player (TODO)

	//Variables a cambiar por las del player y las del enemigo
	//Player
	int p_HP = 100;
	int p_max_HP = 100;
	int p_DEF = 10;
	int p_DMG = 50;

	//Enemy
	int e_HP = 60;
	int e_max_HP = 60;
	int e_DEF = 10;
	int e_DMG = 20;


};