#pragma once 
#include "ISystem.h"
#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

#include "game.h"

class Audio : public ISystem
{

public:
#define CLIP_DEF(val, type) k##val,
	enum GameClip {
#include "clip-defs.h"
		kNumClips // For iteration, don't remove
	};
#undef CLIP_DEF

	virtual void Init() override;
	virtual void CleanUp() override;
	virtual void Update() override;

	void Play(GameClip clip, float volume = 1, int loopCount= 0);

	static Audio* g_pAudio;

private:

	FMOD::System* system;
	FMOD::Sound* clips[1];
	void PrepareClips();
	FMOD::Sound* LoadClip(Audio::GameClip clip);
	


#define CLIP_DEF(val, type) "resources/sounds/"#val"."#type,
	const char* GameClipStrings[GameClip::kNumClips] = {
		#include "clip-defs.h"
	};
#undef CLIP_DEF
};

