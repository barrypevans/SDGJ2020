#pragma once 
#include "ISystem.h"
#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#undef main

class Game;
#include "game.h"

class Audio : public ISystem
{

public:
	enum GameClip {
		kTest,
		kClipCap // For iteration, don't remove
	};

	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	void Play(GameClip clip, float volume = 1, int loopCount= 0);

private:

	FMOD::System* system;
	FMOD::Sound* clips[1];
	void PrepareClips();
	FMOD::Sound* LoadClip(Audio::GameClip clip);

	const char* GameClipStrings[1] = {
		"sounds/Test.mp3"
	};
};