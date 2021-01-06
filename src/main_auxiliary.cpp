#include "main_auxiliary.h"

bool events() {
    bool quit = false;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) // window is closed
        {
            quit = true;
        }
    }
    return quit;
}

void loop(GameOfLife &gameOfLife)
{
    gameOfLife.nextGeneration(); // lets the game develop by one time step
    SDL_Delay(16);
    return;
}

void render(const GameOfLife &gameOfLife, RenderingEngine &renderingEngine, SDL_Texture *texture)
{
    uint32_t *pixelData;

    int pitch; // length of the surface scanline in bytes
    SDL_LockTexture(texture, NULL, reinterpret_cast<void**>(&pixelData), &pitch);
    int offset = pitch/sizeof(*pixelData); // length of the surface scanline in pixels

    for (int i = 0; i < gameOfLife.getHeight(); ++i)
        for (int j = 0; j < gameOfLife.getWidth(); ++j) // go through all cells.
            if(gameOfLife.isCellAlive(i, j))
            {
                pixelData[i + offset*j] = 0xFFFFFFFF; //if alive, draw as white.
            }
            else
                pixelData[i + offset*j] = 0xFF000000; //if dead, draw as black.

    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderingEngine.get_renderer(), texture, NULL, NULL); // copy texture to renderer
    SDL_RenderPresent(renderingEngine.get_renderer()); // render
    return;
}
