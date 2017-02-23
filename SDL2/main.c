#include "SDL.h"
#include <windows.h>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

int main(int argc, char *args[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &window, &renderer);
	SDL_SetWindowTitle(window, "SDL2 Demo");
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	int running = 1;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}
		}

		Sleep(10);
	}
}