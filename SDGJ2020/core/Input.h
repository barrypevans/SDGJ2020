#include <sdl/SDL.h>
class Input
{
public:
	Input();
	void handleEvent(SDL_Event& event);
};

static Input* g_pInput;