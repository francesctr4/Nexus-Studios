#include "App.h"

#include "Defs.h"
#include "Log.h"

// NOTE: SDL redefines main function
#include "SDL/include/SDL.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2.lib")
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2main.lib")

#include <stdlib.h>

#include "External/Optick/include/optick.h"

enum class MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* app = NULL;

int main(int argc, char* args[])
{
	MainState state = MainState::CREATE;
	int result = EXIT_FAILURE;

	while(state != MainState::EXIT)
	{
		switch (state)
		{
			// Allocate the engine --------------------------------------------
		case MainState::CREATE:
			
			app = new App(argc, args);

			if (app != NULL)
				state = MainState::AWAKE;
			else
				state = MainState::FAIL;

			break;

			// Awake all modules -----------------------------------------------
		case MainState::AWAKE:
			
			if (app->Awake() == true)
				state = MainState::START;
			else
			{
				state = MainState::FAIL;
			}

			break;

			// Call all modules before first frame  ----------------------------
		case MainState::START:
			
			if (app->Start() == true)
			{
				state = MainState::LOOP;
				
			}
			else
			{
				state = MainState::FAIL;
				
			}
			break;

			// Loop all modules until we are asked to leave ---------------------
			case MainState::LOOP:
			{
				OPTICK_FRAME("Main Loop")

				if (app->Update() == false)
					state = MainState::CLEAN;
			}
			break;

			// Cleanup allocated memory -----------------------------------------
			case MainState::CLEAN:
			
			if(app->CleanUp() == true)
			{
				RELEASE(app);
				result = EXIT_SUCCESS;
				state = MainState::EXIT;
			}
			else
				state = MainState::FAIL;

			break;

			// Exit with errors and shame ---------------------------------------
			case MainState::FAIL:
			
			result = EXIT_FAILURE;
			state = MainState::EXIT;
			break;
		}
	}

	// Dump memory leaks
	return result;
}