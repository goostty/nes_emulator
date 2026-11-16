#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <exception>
#include <iostream>

int main(int argc, char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO) && !SDL_Init(SDL_INIT_AUDIO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                 "SDL failed to initialize. Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Kingsley's NES Emulator", 800, 600, 0);

  if (!window) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                 "Failed to initialize window. Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  bool running = true;
  while (running) {
    try {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
          running = false;
          break;
        case SDL_EVENT_KEY_DOWN:
          if (event.key.key == SDLK_ESCAPE)
            running = false;
          break;
        }
      }
    } catch (const std::exception &e) {
      std::cerr << "Fatal Error: " << e.what() << '\n';
      return 1;
    }
  }

  // Cleanup
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
