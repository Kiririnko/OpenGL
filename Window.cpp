#include "Window.h"
#include <stdexcept>
#include <string>

Window::Window(int width, int height)
: _width(width), _height(height)
{
	_window = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
					"OpenGL Window",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					_width, _height,
					SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL),
			SDL_DestroyWindow);
	if (_window == nullptr)
		throw std::runtime_error(
				std::string("При создании окна произошла ошибка: ") +
				std::string(SDL_GetError()));


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	_gl_context = std::shared_ptr<void>(
			SDL_GL_CreateContext(_window.get()),
			SDL_GL_DeleteContext);
	if (_gl_context == nullptr)
		throw std::runtime_error(
				std::string("При создании контекста OpenGL произошла ошибка: ") +
				std::string(SDL_GetError()));


}

void Window::main_loop()
{
	setup();

	auto keys = SDL_GetKeyboardState(nullptr);
	SDL_Event event;
	for(;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
			handle_event(event);
		}
		if (keys[SDL_SCANCODE_ESCAPE]) return;
		handle_keys(keys);

		do_logic();

		render();

		SDL_GL_SwapWindow(_window.get());

	}
}
