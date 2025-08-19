#include "renderwindow.hpp"
#include <vector>
#include <time.h>
#include <chrono>
#include <iostream>

void RenderWindow::createWindow(const char* p_title, int p_w, int p_h) {
    
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); 
    if(window == NULL) {
        std::cout << "Window failed to be created, exiting";
        exit(1);
    }  
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::movePaddle(bool left, bool right) {
    if(left == true) {
        Paddle.x -= paddleSpeed;
        if(Paddle.x < 0) {
            Paddle.x = 0;
        }
    }

    if(right == true) {
        Paddle.x += paddleSpeed;
        if(Paddle.x + Paddle.w > WIDTH) {
            Paddle.x = WIDTH - Paddle.w;
        }
    }
}

void RenderWindow::moveBall() {
    Ball.y += ballYSpeed;
    Ball.x += ballXSpeed;
    if(SDL_HasIntersection(&Ball, &Paddle)) {
        ballYSpeed *= -1;
    }

    for(int row = 0; row < bricksPerRow + 1; ++row) {
        for(int col = 0; col < bricksPerCol + 1; col++) {
            if(SDL_HasIntersection(&Ball, &bricks[row][col])) {
                bricks[row][col] = {0,0,0,0};
                ballYSpeed *= -1;
            }
        }
    }

    if(Ball.y <= 0) {
        Ball.y = 0;
        ballYSpeed *= -1;
    } else if(Ball.y + Ball.h > HEIGHT) {
        reset();
        present();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } else if(Ball.x + Ball.w> WIDTH) {
        Ball.x = WIDTH - Ball.w;
        ballXSpeed *= -1;
    } else if(Ball.x < 0) {
        Ball.x = Ball.w;
        ballXSpeed *= -1;
    }
}

void RenderWindow::initBricks() {
    int brickWidth = (WIDTH - (BRICKHORGAP * 7))/6;

    if(brickWidth * 6 + BRICKHORGAP * 7 >= WIDTH) {
        exit(1);
    }
    for(int row = 0; row < bricksPerRow + 1; ++row) {
        for(int col = 0; col < bricksPerCol + 1; col++) {
            bricks[row][col] = {BRICKHORGAP * (row + 1) + brickWidth * (row), BRICKVERTGAP * (col + 1) + BRICKHEIGHT * (col + 1), brickWidth, BRICKHEIGHT};
        }
    }
}

void RenderWindow::reset() {
    Paddle = {WIDTH/2, HEIGHT - 30, 80 ,10}; //Hardcoded :(
    Ball = {WIDTH/2, HEIGHT/2, 20, 15};
    paddleSpeed = 8;
    ballYSpeed = 3;
    ballXSpeed = 3;
    initBricks();
}

void RenderWindow::present() {
    SDL_SetRenderDrawColor(renderer, 0,0,0,255); //Black
    SDL_RenderFillRect(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 51,153,255,255);
    SDL_RenderFillRect(renderer, &Paddle);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &Ball);
    for(int i = 0; i < bricksPerRow + 1; i++) {
        for(int j = 0; j < bricksPerCol + 1; j++) {
            SDL_RenderFillRect(renderer, &bricks[i][j]);
        }
    }

    bool shouldReset = true;
    for(int i = 0; i < bricksPerRow + 1; i++) {
        for(int j = 0; j < bricksPerCol + 1; j++) {
            if(bricks[i][j].h == 0) {
                continue;
            } else {
                shouldReset = false;
                break;
            }
        }
    }

    if(shouldReset == true) {
        reset();
    }
    
    SDL_RenderPresent(renderer);
}

void RenderWindow::delay() {
    SDL_Delay(10); //Delta time will be implemented later 
}

void RenderWindow::cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
