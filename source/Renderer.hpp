#pragma once

#include <SDL.h>
#include <GL\glew.h>
#include <string>

#include "Math\Vector2.hpp"

// Renderer modes, derived from SDL renderer modes
enum WindowModes{
	WINDOW_WINDOWED = SDL_WINDOW_SHOWN,
	WINDOW_FULLSCREEN = SDL_WINDOW_FULLSCREEN,
	WINDOW_FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP
};

class Renderer{
	bool _running = false;

	SDL_Window* _window = 0;
	SDL_Renderer* _sdl_renderer = 0; // Hasn't really been used yet
	SDL_GLContext _glcontext;

	const char* _title = "3D Component Engine";

	Vector2i _size = Vector2i(1280, 720);

	WindowModes _mode = WINDOW_WINDOWED;

	bool _setupSDL(); // Returns false if failed
	bool _setupGL();  // "
	
	// Private singleton used by static methods
	static Renderer& _instance();

public:	
	~Renderer();

	// Setters
	static void size(int width, int height);
	static void title(const char* title);
	static void fullscreen(WindowModes mode);

	// Getters
	static int width();
	static int height();
	static SDL_Renderer* sdl_renderer();
	
	// Setup and updating
	static bool initiate();
	static void swapBuffer();

	// Reshapes the OpenGL matrices to initial shape
	static bool reshape(); 
};