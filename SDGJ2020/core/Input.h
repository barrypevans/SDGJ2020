#include <sdl/SDL.h>
class Input
{
	bool leftKey;
	bool rightKey;
	bool upKey;
	bool downKey;

public:
	Input();
	bool getLeftKey() {
		return this->leftKey;
	}
	bool getRightKey() {
		return this->rightKey;
	}
	bool getUpKey() {
		return this->upKey;
	}
	bool getDownKey() {
		return this->downKey;
	}

	void handleEvent(SDL_Event& event);

private:
	void setLeftKey(bool key) {
		this->leftKey = key;
	};
	void setRightKey(bool key) {
		this->rightKey = key;
	};
	void setUpKey(bool key) {
		this->upKey = key;
	};
	void setDownKey(bool key) {
		this->downKey = key;
	};

};

static Input* g_pInput;