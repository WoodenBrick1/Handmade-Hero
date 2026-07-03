#include <SDL2/SDL.h>
#include <stdbool.h>

void HandleEvent(SDL_Event *event);

bool running = true;

int main(int argc, char *argv[]) {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    // TODO: SDL_Init didn't work!
  }

  SDL_Window *window =
      SDL_CreateWindow("Handmade Hero", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
  if (!window) {
    printf("Window couldn't be created!\n");
    return -1;
  }
  // Renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    printf("Renderer couldn't be rendered!\n");
    return -1;
  }

  while (running) {
    SDL_Event *event;
    SDL_WaitEvent(event);
    HandleEvent(event);
    
  }
  SDL_Quit();
  return 0;
}

void HandleEvent(SDL_Event *event) {

  switch (event->type) {

  case SDL_QUIT: {
    printf("SDL_QUIT\n");
    running = false;
  } break;

  case SDL_WINDOWEVENT: {
    switch (event->window.event) {

    case SDL_WINDOWEVENT_RESIZED: {
      printf("Window Resized: %d %d\n", event->window.data1,
             event->window.data2);
    } break;

    case SDL_WINDOWEVENT_EXPOSED: {
      SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
      SDL_Renderer *renderer = SDL_GetRenderer(window);
      static bool isWhite = true;
      if (isWhite) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        isWhite = false;
      } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        isWhite = true;
      }

      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
    } break;
    }

  } break;
  }

}
