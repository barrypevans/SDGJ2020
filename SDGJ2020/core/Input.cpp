#include "Input.h"
#include <stdio.h>


Input* Input::g_pInput;

Input::Input() {
	setLeftKey(false);
	setRightKey(false);
	setUpKey(false);
	setDownKey(false);
	setEscKey(false);

	setLeftKeyPrev(false);
	setRightKeyPrev(false);
	setUpKeyPrev(false);
	setDownKeyPrev(false);
	setEscKeyPrev(false);
		
	setUpKeyRelease(false);
	setDownKeyRelease(false);
	setLeftKeyRelease(false);
	setRightKeyRelease(false);
	setEscKeyRelease(false);
}




void Input::handleEvent(SDL_Event& event)
{
	//Key has been pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_UP: setUpKey(true); break;
		case SDLK_DOWN: setDownKey(true); break;
		case SDLK_LEFT: setLeftKey(true); break;
		case SDLK_RIGHT: setRightKey(true); break;
		case SDLK_ESCAPE: setEscKey(true); break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_UP: setUpKey(false); setUpKeyRelease(true); break;
		case SDLK_DOWN: setDownKey(false); setDownKeyRelease(true); break;
		case SDLK_LEFT: setLeftKey(false); setLeftKeyRelease(true); break;
		case SDLK_RIGHT: setRightKey(false); setRightKeyRelease(true); break;
		case SDLK_ESCAPE: setEscKey(false); setEscKeyRelease(true); break;
		}
	}
}