#ifndef __MAPA_INFIERNO__
#define __MAPA_INFIERNO__

#include "SceneGameplay.h"

class Infierno
{
	Infierno();
	~Infierno();

	void Start();
	
	void Update();
	
	void CleanUp();

public:
	bool map_selector = false;
	bool infierno = false;
};


#endif