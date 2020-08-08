#include "Input.h"
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

void Input::handleEvent(SDL_Event& event)
{
	//Key has been pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
			case SDLK_UP: cout << "UP key has been pressed\n";
			case SDLK_DOWN: cout << "DOWN key has been pressed\n";
			case SDLK_LEFT: cout << "LEFT key has been pressed\n";
			case SDLK_RIGHT: cout << "RIGHT key has been pressed\n";
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_UP: cout << "UP key has been released\n";
		case SDLK_DOWN: cout << "DOWN key has been released\n";
		case SDLK_LEFT: cout << "LEFT key has been released\n";
		case SDLK_RIGHT: cout << "RIGHT key has been released\n";
		}
	}
}