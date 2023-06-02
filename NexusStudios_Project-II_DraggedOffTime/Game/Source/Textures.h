#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "Module.h"

#include "List.h"

struct SDL_Texture;
struct SDL_Surface;

class Textures : public Module
{
public:

	explicit Textures(bool startEnabled);

	// Destructor
	virtual ~Textures();

	// Called before render is available
	bool Awake(pugi::xml_node&) override;

	// Called before the first frame
	bool Start() override;

	// Called before quitting
	bool CleanUp() override;

	// Load Texture
	SDL_Texture* const Load(const char* path);
	SDL_Texture* const LoadSurface(SDL_Surface* surface);
	bool UnLoad(const SDL_Texture* texture);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:

	List<SDL_Texture*> textures;
};


#endif // __TEXTURES_H__