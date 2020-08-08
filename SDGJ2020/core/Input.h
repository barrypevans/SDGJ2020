#include <sdl/SDL.h>
class Input
{
	bool leftKey[2];
	bool rightKey[2];
	bool upKey[2];
	bool downKey[2];
	

public:
	Input();
	void pushPrevKey() {
		this->leftKey[0] = this->leftKey[1];
		this->rightKey[0] = this->rightKey[1];
		this->upKey[0] = this->upKey[1];
		this->downKey[0] = this->downKey[1];
	}
	bool getLeftKeyPress() {
		return (!this->leftKey[0] && this->leftKey[1]);
	}
	bool getRightKeyPress() {
		return (!this->rightKey[0] && this->rightKey[1]);
	}
	bool getUpKeyPress() {
		return (!this->upKey[0] && this->upKey[1]);
	}
	bool getDownKeyPress() {
		return (!this->downKey[0] && this->downKey[1]);
	}

	bool getLeftKeyRel() {
		return (this->leftKey[0] && !this->leftKey[1]);
	}
	bool getRightKeyRel() {
		return (this->rightKey[0] && !this->rightKey[1]);
	}
	bool getUpKeyRel() {
		return (this->upKey[0] && !this->upKey[1]);
	}
	bool getDownKeyRel() {
		return (this->downKey[0] && !this->downKey[1]);
	}

	void handleEvent(SDL_Event& event);

private:
	void setLeftKey(bool key) {
		this->leftKey[1] = key;
	};
	void setRightKey(bool key) {
		this->rightKey[1] = key;
	};
	void setUpKey(bool key) {
		this->upKey[1] = key;
	};
	void setDownKey(bool key) {
		this->downKey[1] = key;
	};
	void setLeftKeyPrev(bool key) {
		this->leftKey[0] = key;
	};
	void setRightKeyPrev(bool key) {
		this->rightKey[0] = key;
	};
	void setUpKeyPrev(bool key) {
		this->upKey[0] = key;
	};
	void setDownKeyPrev(bool key) {
		this->downKey[0] = key;
	};

};

static Input* g_pInput;