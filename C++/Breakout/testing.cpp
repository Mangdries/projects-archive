#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

const int WIDTH = 680;
const int HEIGHT = 480;

int
main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL Failed to initalize: Error " << SDL_GetError() << std::endl;
    }

    SDL_Window* window = SDL_CreateWindow("SDL testing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        std::cout << "SDL Window Failed to be created: " << SDL_GetError() << std::endl;
        return -1; 
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    std::vector<SDL_Rect> blocks;
    SDL_Rect block = {WIDTH/2, HEIGHT/2, 30, 30};

    blocks.push_back(block);

    while (running) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                running = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderFillRect(renderer, nullptr);
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, blocks.at(0));
        SDL_RenderPresent(renderer);
    }
    

    return 0;
}