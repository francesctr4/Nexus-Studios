#pragma once

#include "Point.h"
#include "Module.h"
#include "Emitter.h"
#include <list>
#include <string>
#include "SDL/include/SDL.h"

#define MAX_NUM_EMITTERS_TYPE 11

class Emitter;
struct SDL_Texture;
struct SDL_Rect;
struct SDL_Color;

enum EmitterType
{
	EMITTER_TYPE_NONE = -1,
	EMITTER_TYPE_FIRE,
	EMITTER_TYPE_FIRE_PURPLE,
	EMITTER_TYPE_FLAME,
	EMITTER_TYPE_SMOKE,
	EMITTER_TYPE_PIXEL_SMOKE,
	EMITTER_TYPE_BURST,
	EMITTER_TYPE_WAVE_1,
	EMITTER_TYPE_WAVE_2,
	EMITTER_TYPE_BUBBLE,
	EMITTER_TYPE_SPARK
};

struct EmitterData
{
	fPoint angleRange = { 0.0f, 0.0f };
	float startSpeed = 0.0f, endSpeed = 0.0f;
	float startSize = 0.0f, endSize = 0.0f;
	uint emitNumber = 0u;
	uint emitVariance = 0u;
	uint maxParticleLife = 0u;
	SDL_Rect textureRect = { 0, 0 };
	double lifetime = -1.0f;
	SDL_Color startColor = { 0, 0, 0, 0 };
	SDL_Color endColor = { 0, 0, 0, 0 };
	SDL_BlendMode blendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;
	double rotSpeed = 0;

	// Randoms
	fPoint rotSpeedRand = { 0.0f, 0.0f };
	fPoint startSpeedRand = { 0.0f, 0.0f };
	fPoint endSpeedRand = { 0.0f, 0.0f };
	fPoint emitVarianceRand = { 0.0f, 0.0f };
	fPoint lifeRand = { 0.0f, 0.0f };
	fPoint startSizeRand = { 0.0f, 0.0f };
	fPoint endSizeRand = { 0.0f, 0.0f };

	// Vortex
	bool vortexSensitive = false;
};

class ParticleSystem : public Module
{

private:

	std::list<Emitter*> emittersList;
	std::list<Emitter*> emittersToDestroy;
	SDL_Texture* particleAtlas = nullptr;
	std::string nameParticleAtlas;

	// Static array that stores all the data of emitters
	EmitterData vecEmitterData[MAX_NUM_EMITTERS_TYPE];

public:

	explicit ParticleSystem(bool startEnabled);

	// Destructor
	virtual ~ParticleSystem();

	// Called when before render is available
	bool Awake(pugi::xml_node& config) override;

	// Call before first frame
	bool Start() override;

	// Called before all Updates
	bool PreUpdate() override;

	// Called each loop iteration
	bool Update(float dt) override;

	// Called after all Updates
	bool PostUpdate() override;

	// Called before quitting
	bool CleanUp() override;

	// Emitter methods
	Emitter* AddEmiter(fPoint pos, EmitterType type);
	bool RemoveEmitter(Emitter* emitter);
	bool RemoveAllEmitters();

	SDL_Texture* GetParticleAtlas() const;
	void LoadEmitterData(pugi::xml_node& config, EmitterType type);
};