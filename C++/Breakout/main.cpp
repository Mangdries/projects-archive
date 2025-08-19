#include <iostream>
#include <SDL2/SDL.h>
#include "renderwindow.cpp"

const int WIDTH = 680;
const int HEIGHT = 480;

int
main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL Failed to initalize. Error: " << SDL_GetError() << std::endl;
    }
    
    RenderWindow window;
    window.createWindow("SDL2 Breakout", WIDTH, HEIGHT);

    SDL_Event event;

    bool running = true;
    bool isLeftPressed = false;
    bool isRightPressed = false;

    window.initBricks();

    while(running) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        auto keyboardState = SDL_GetKeyboardState(nullptr);

        if(keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]) {
            isLeftPressed = true;
        }
        if(keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]) {
            isRightPressed = true;
        }
        if(keyboardState[SDL_SCANCODE_ESCAPE]) {
            running = false;
        }

        window.clear();
        window.present();
        window.movePaddle(isLeftPressed, isRightPressed);
        window.moveBall();
        window.delay();
        isRightPressed = false;
        isLeftPressed = false;
    }

    window.cleanup();
    return 0; 
}
