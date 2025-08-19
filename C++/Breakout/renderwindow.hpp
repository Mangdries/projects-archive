#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <thread>
extern const int HEIGHT;
extern const int WIDTH;

class RenderWindow {
    public:
    void createWindow(const char* p_title, int p_w, int p_h);
    void clear();
    void movePaddle(bool left, bool right);
    void moveBall();
    void initBricks();
    void reset();
    void present();
    void delay();
    void cleanup();

    private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    SDL_Rect Paddle = {WIDTH/2, HEIGHT - 30, 80 ,10}; //Hardcoded :(
    SDL_Rect Ball = {WIDTH/2, HEIGHT/2, 20, 15};
    int paddleSpeed = 8;
    int ballYSpeed = 3;
    int ballXSpeed = 3;
    int bricksPerCol = 6;
    int bricksPerRow = 5;
    const int BRICKVERTGAP = 20;
    const int BRICKHORGAP = 10;
    const int BRICKHEIGHT = 10;
    SDL_Rect bricks[6][7];
};
