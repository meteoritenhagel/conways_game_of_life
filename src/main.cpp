#include "gameoflife.h"
#include "main_auxiliary.h"
#include "renderingengine/renderingengine.h"

#include <SDL.h>

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    const int gameWidth = 600;
    const int gameHeight = 600;

    GameOfLife gameOfLife(gameWidth, gameHeight);
    gameOfLife.applyRandomState(); // Start with random initial state

    RenderingEngine renderingEngine(screenWidth, screenHeight, "Conway's Game of Life");
    // create texture as a frame buffer for drawing the pixels in it
    SDL_Texture *texture = SDL_CreateTexture(renderingEngine.get_renderer(), SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING, gameWidth, gameHeight);

    render(gameOfLife, renderingEngine, texture);
    SDL_Delay(1000); // wait one second

    while(!events())
    {
        render(gameOfLife, renderingEngine, texture);
        loop(gameOfLife);
    }

    SDL_DestroyTexture(texture); // texture cleanup

    return 0;
}
