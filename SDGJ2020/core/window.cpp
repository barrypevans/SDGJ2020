#include "window.h"
#include <stdio.h>
#include "assert.h"
#include "Input.h"
#include "metronome.h"


Window* Window::g_pWindow;

void Window::Init()
{
	// Setup GL Version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Init Sdl
	ASSERT(SDL_Init(SDL_INIT_VIDEO) >= 0, 
		"Error Initializing SDL: %s", SDL_GetError());

	// Init Sdl Window
	m_pSdlWindow = SDL_CreateWindow("H Y P E !", 100, 100, 1920, 1080,  SDL_WINDOW_OPENGL);
	ASSERT(m_pSdlWindow != nullptr, 
		"Error Creating SDL Window: %s", SDL_GetError());

	// Create GL Context
	m_glContext = SDL_GL_CreateContext(m_pSdlWindow);
	ASSERT(nullptr != m_glContext, "Error Creating SDL GL Context: %s", SDL_GetError());
	
	SDL_GL_SetSwapInterval(1);

	// Initialize Glew (used for easily loading Opengl extensions)
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	ASSERT(GLEW_OK == err, "Error: %s\n", glewGetErrorString(err));
}

void Window::Update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(m_pSdlWindow);
}

void Window::PollEvents()
{
	SDL_Event event;
	Input::g_pInput->pushPrevKey();
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT)
			m_pGame->RequestShutDown();
		
		Input::g_pInput->handleEvent(event);
		if (Input::g_pInput->getDownKeyPress() || Input::g_pInput->getUpKeyPress() || Input::g_pInput->getLeftKeyPress() || Input::g_pInput->getRightKeyPress()) // Sample beat matching, ok to drop
		{
			bool win = (float)Metronome::g_pMetronome->ActiveBeatOffset() < Metronome::kBeatThreshold;
			//printf(win ? "beat " : "wrong ");
			//Audio::g_pAudio->Play(win ? Audio::GameClip::kMetUp : Audio::GameClip::kMetDown, .1f);
		}
	}
}

float Window::GetAspect()
{
	int w, h;
	SDL_GetWindowSize(m_pSdlWindow, &w, &h);
	return static_cast<float>(h) / static_cast<float>(w);
}

glm::vec2 Window::GetDimensions()
{
	int w, h;
	SDL_GetWindowSize(m_pSdlWindow, &w, &h);
	return glm::vec2(w,h);
}

void Window::CleanUp()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_pSdlWindow);
	SDL_Quit();
}