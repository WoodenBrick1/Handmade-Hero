#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define internal static
#define local_persist static
#define global_variable static

internal void SDLHandleEvent(SDL_Event *event);
internal void SDLResizeTexture(SDL_Renderer *renderer, int32_t width,
                               int32_t height);
internal void SDLUpdateWindow(SDL_Renderer *renderer);

global_variable bool running = true;
global_variable void *pixels;
global_variable SDL_Texture *texture;
global_variable int32_t textureWidth;

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
    SDL_Event event;
    SDL_WaitEvent(&event);
    SDLHandleEvent(&event);
  }
  SDL_Quit();
  return 0;
}

void SDLHandleEvent(SDL_Event *event) {

  switch (event->type) {

  case SDL_QUIT: {
    printf("SDL_QUIT\n");
    running = false;
  } break;

  case SDL_WINDOWEVENT: {
    switch (event->window.event) {

    case SDL_WINDOWEVENT_SIZE_CHANGED: {
      SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
      SDL_Renderer *renderer = SDL_GetRenderer(window);
      SDLResizeTexture(renderer, event->window.data1, event->window.data2);

    } break;

    case SDL_WINDOWEVENT_EXPOSED: {
      SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
      SDL_Renderer *renderer = SDL_GetRenderer(window);

      SDLUpdateWindow(renderer);
    } break;
    }

  } break;
  }
}

void SDLResizeTexture(SDL_Renderer *renderer, int32_t width, int32_t height) {

  if (texture) {
    SDL_DestroyTexture(texture);
  }
  if (pixels) {
    free(pixels);
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, width, height);
  pixels = malloc(width * height * 4);
  textureWidth = width;
}

internal void SDLUpdateWindow(SDL_Renderer *renderer) {

   if (SDL_UpdateTexture(texture, 0, pixels, textureWidth * 4) != 0) {
    printf("ERROR WITH UPDATING TEXTURE");
  }

  SDL_RenderCopy(renderer, texture, 0, 0);
  SDL_RenderPresent(renderer);
}
