#include <SDL2/SDL_image.h>
#include <iostream>
#include <ctime>                                     #include <stdio>                                            

#include <time.h>
//using namespace sf;
using namespace std;


struct Point {
    int x, y;
};

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    
    srand(static_cast<unsigned>(time(0)));

    SDL_Window* window = SDL_CreateWindow("Doodle Game!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 533, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* background = IMG_LoadTexture(renderer, "images/background.png");
    SDL_Texture* platform = IMG_LoadTexture(renderer, "images/platform.png");
    SDL_Texture* doodle = IMG_LoadTexture(renderer, "images/doodle.png");

    Point plat[20];

    for (int i = 0; i < 10; i++) {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) x += 3;
        if (currentKeyStates[SDL_SCANCODE_LEFT]) x -= 3;

        dy += 0.2;
        y += static_cast<int>(dy);
        if (y > 500) dy = -10;

        if (y < h) {
            y = h;
            for (int i = 0; i < 10; i++) {
                y = h;
                plat[i].y = plat[i].y - static_cast<int>(dy);
                if (plat[i].y > 533) {
                    plat[i].y = 0;
                    plat[i].x = rand() % 400;
                }
            }
        }

        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)) dy = -10;

        SDL_RenderClear(renderer);

        SDL_Rect backgroundRect = {0, 0, 400, 533};
        SDL_RenderCopy(renderer, background, NULL, &backgroundRect);

        SDL_Rect doodleRect = {x, y, 64, 64}; // Assuming doodle texture size is 64x64
        SDL_RenderCopy(renderer, doodle, NULL, &doodleRect);

        for (int i = 0; i < 10; i++) {
            SDL_Rect platformRect = {plat[i].x, plat[i].y, 68, 14}; // Assuming platform texture size is 68x14
            SDL_RenderCopy(renderer, platform, NULL, &platformRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(platform);
    SDL_DestroyTexture(doodle);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}