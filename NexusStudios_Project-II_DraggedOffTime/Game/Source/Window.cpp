#include "Window.h"
#include "App.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL.h"


Window::Window(bool startEnabled) : Module(startEnabled)
{	
	window = NULL;
	screenSurface = NULL;
	name.Create("window");
}

// Destructor
Window::~Window()
{
}

// Called before render is available
bool Window::Awake(pugi::xml_node& config)
{
	LOG("Init SDL window & surface");
	bool ret = true;

	configWindow = config;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		// Create window
		// Load all required configurations from config.xml
		// Tip: get the name of the child and the attribute value
		Uint32 flags = SDL_WINDOW_SHOWN;
		fullscreen = config.child("fullscreen").attribute("value").as_bool(); // get from config
		borderless = config.child("bordeless").attribute("value").as_bool(); // get from config
		resizable = config.child("resizable").attribute("value").as_bool(); // get from config
		fullscreen_window = config.child("fullscreen_window").attribute("value").as_bool(); // get from config

		width = config.child("resolution").attribute("width").as_int(); //get from config 
		height = config.child("resolution").attribute("height").as_int();; //get from config 
		scale = config.child("resolution").attribute("scale").as_int();; //get from config 

		if (fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN;
		if (borderless == true) flags |= SDL_WINDOW_BORDERLESS;
		if (resizable == true) flags |= SDL_WINDOW_RESIZABLE;
		if (fullscreen_window == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow(app->GetTitle(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			// Get window surface
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called each loop iteration
bool Window::Update(float dt) {

	return true;
}

// Called before quitting
bool Window::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	// Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	// Quit SDL subsystems
	SDL_Quit();
	return true;
}

// Set new window title
void Window::SetTitle(const char* new_title)
{
	//title.create(new_title);
	SDL_SetWindowTitle(window, new_title);
}

void Window::GetWindowSize(uint& width, uint& height) const
{
	width = this->width;
	height = this->height;
}

uint Window::GetScale() const
{
	return scale;
}