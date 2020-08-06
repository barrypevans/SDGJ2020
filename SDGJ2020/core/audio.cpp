#include "audio.h"
#include <stdio.h>
#include <iostream>
#include "assert.h"

void Audio::Init() 
{
    FMOD_RESULT result;

    result = FMOD::System_Create(&system);      // Create the main system object.
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    result = system->set3DSettings(0,1,1);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    PrepareClips();
}

void Audio::Update() 
{
    system->update();
}

void Audio::Play(GameClip clip, float volume, int loopCount) 
{
    FMOD_RESULT result;
    FMOD::Channel* channel;

    result = system->playSound(clips[(int)clip], 0, false, &channel);
    if (result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    if (volume != 1)
        channel->setVolume(volume);
    if (loopCount>0) 
    {
        channel->setMode(FMOD_LOOP_NORMAL);
        channel->setLoopCount(loopCount);
    }
}

void Audio::PrepareClips() 
{
    for (int clip = (GameClip)0; clip != GameClip::kClipCap; clip++) 
        clips[clip] = LoadClip((GameClip)clip);
}
FMOD::Sound* Audio::LoadClip(GameClip clip)
{
    FMOD_RESULT result;
    FMOD::Sound* testSound;

    result = system->createSound(GameClipStrings[(int)clip], FMOD_2D | FMOD_CREATESTREAM, 0, &testSound);
    if (result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
    return testSound;
}


void Audio::CleanUp() 
{
    system->release();
    delete[]clips;
}

