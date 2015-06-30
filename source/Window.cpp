#include "Window.hpp"

#include <stdio.h>

Window& Window::_instance(){
	static Window instance;
	return instance;
}

Window::~Window(){
	_running = false;

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_GL_DeleteContext(_glcontext);
}

bool Window::_setupSDL(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("%s! %s: %s\n", "Failed to initialize SDL", "SDL Error", SDL_GetError());
		return false;
	}

	// Setting OpenGL to 2.1 fixed pipeline
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Window object
	_window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _size.x(), _size.y(), SDL_WINDOW_OPENGL);

	if (!_window){
		printf("%s! %s: %s\n", "Failed to create window", "SDL Error", SDL_GetError());
		return false;
	}

	// Renderer object (for 2D graphics only)
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (!_renderer){
		printf("%s! %s: %s\n", "Failed to create renderer", "SDL Error", SDL_GetError());
		return false;
	}

	SDL_SetWindowFullscreen(_window, _mode);

	return true;
}

bool Window::_setupGL(){
	// OpenGl context object
	_glcontext = SDL_GL_CreateContext(_window);

	if (!_glcontext){
		printf("%s! %s: %s\n", "Failed to create OpenGL context", "SDL Error", SDL_GetError());
		return false;
	}

	// OpenGl settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_PROGRAM_POINT_SIZE);

	// Extensions
	GLenum error = glewInit();

	if (error != GLEW_OK){
		printf("%s! %s: %s\n", "Failed to initiate Glew", "Glew Error", glewGetErrorString(error));
		return false;
	}

	return true;
}

bool Window::reshape(){
	// Setting up OpenGL matrices
	float ar = (float)_instance()._size.x() / (float)_instance()._size.y();

	glViewport(0, 0, _instance()._size.x(), _instance()._size.y());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 59 vfov = ~90 hfov
	gluPerspective(59, ar, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError();

	if (error != GL_NO_ERROR){
		printf("%s! %s: %s\n", "Failed to reshape OpenGL matrices", "OpenGL Error", gluErrorString(error));
		return false;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

bool Window::initiate(){
	if (_instance()._running){
		SDL_DestroyWindow(_instance()._window);
		SDL_DestroyRenderer(_instance()._renderer);
		SDL_GL_DeleteContext(_instance()._glcontext);
	}
	else{
		_instance()._running = true;
	}

	if (!_instance()._setupSDL())
		return false;

	if (!_instance()._setupGL())
		return false;

	return reshape();
}

void Window::swapBuffer(){
	SDL_GL_SwapWindow(_instance()._window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

SDL_Renderer* Window::renderer(){
	return _instance()._renderer;
}

int Window::width(){
	return _instance()._size.x();
}

int Window::height(){
	return _instance()._size.y();
}

void Window::fullscreen(WindowModes mode){
	_instance()._mode = mode;
	
	if (_instance()._running)
		SDL_SetWindowFullscreen(_instance()._window, mode);
}

void Window::size(int width, int height){
	_instance()._size = Vector2i(width, height);

	if (_instance()._running){
		SDL_SetWindowSize(_instance()._window, width, height);
		_instance().initiate();
	}
}

Vector2i Window::size(){
	return _instance()._size;
}


void Window::title(const char* title){
	_instance()._title = title;

	if (_instance()._running)
		SDL_SetWindowTitle(_instance()._window, title);
}