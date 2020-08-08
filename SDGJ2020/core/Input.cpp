#include "Input.h"
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

Input* Input::g_pInput;

Input::Input() {
	setLeftKey(false);
	setRightKey(false);
	setUpKey(false);
	setDownKey(false);

	setLeftKeyPrev(false);
	setRightKeyPrev(false);
	setUpKeyPrev(false);
	setDownKeyPrev(false);
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
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_UP: setUpKey(false); break;
		case SDLK_DOWN: setDownKey(false); break;
		case SDLK_LEFT: setLeftKey(false); break;
		case SDLK_RIGHT: setRightKey(false); break;
		}
	}
}