#pragma once
#include <sdl/SDL.h>
#include "ISystem.h"

class Input : public ISystem
{
	bool leftKey[3];
	bool rightKey[3];
	bool upKey[3];
	bool downKey[3];
	bool escKey[3];
	

public:
	Input();
	
	virtual void Init() override {};
	virtual void CleanUp() override {};
	
	void pushPrevKey() {
		this->leftKey[0] = this->leftKey[1];
		this->rightKey[0] = this->rightKey[1];
		this->upKey[0] = this->upKey[1];
		this->downKey[0] = this->downKey[1];
		this->escKey[0] = this->downKey[1];
		this->leftKey[2] = false;
		this->rightKey[2] = false;
		this->upKey[2] = false;
		this->downKey[2] = false;
		this->escKey[2] = false;
	}
	bool getAnyPress() {
		return (this->getDownKeyPress() || this->getLeftKeyPress() || this->getRightKeyPress() || this->getUpKeyPress());
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
		return this->leftKey[2];
	}
	bool getRightKeyRel() {
		return this->rightKey[2];
	}
	bool getUpKeyRel() {
		return this->upKey[2];
	}
	bool getDownKeyRel() {
		return this->downKey[2];
	}
	bool getEscKey() {
		return (!this->escKey[0] && this->escKey[1]);
	}
	void handleEvent(SDL_Event& event);
	static Input* g_pInput;

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
	void setEscKey(bool key) {
		this->escKey[1] = key;
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
	void setEscKeyPrev(bool key) {
		this->escKey[0] = key;
	};

	void setLeftKeyRelease(bool key) {
		this->leftKey[2] = key;
	}
	void setRightKeyRelease(bool key) {
		this->rightKey[2] = key;
	}
	void setUpKeyRelease(bool key) {
		this->upKey[2] = key;
	}
	void setDownKeyRelease(bool key) {
		this->downKey[2] = key;
	}
	void setEscKeyRelease(bool key) {
		this->escKey[2] = key;
	}
};

