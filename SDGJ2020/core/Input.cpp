#include "Input.h"
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;


Input::Input() {
	setLeftKey(false);
	setRightKey(false);
	setUpKey(false);
	setDownKey(false);
}




void Input::handleEvent(SDL_Event& event)
{
	//Key has been pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: setUpKey(true);
			case SDLK_DOWN: setDownKey(true);
			case SDLK_LEFT: setLeftKey(true);
			case SDLK_RIGHT: setRightKey(true);
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_UP: setUpKey(false);
		case SDLK_DOWN: setDownKey(false);
		case SDLK_LEFT: setLeftKey(false);
		case SDLK_RIGHT: setRightKey(false);
		}
	}
}