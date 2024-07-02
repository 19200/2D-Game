#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Godzilla Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart; // how long it's taken to update game in milliseconds.
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime); //delay our frames to make it constant if running to fast
        }
    }

    game->clean();

    return 0;
}
