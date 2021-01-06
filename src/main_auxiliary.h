#ifndef CONWAYS_GAME_OF_LIFE_MAIN_AUXILIARY_H
#define CONWAYS_GAME_OF_LIFE_MAIN_AUXILIARY_H

#include "gameoflife.h"
#include "renderingengine/renderingengine.h"

#include <SDL.h>

/*
 * Event loop. Captures key events.
 *
 * @return true if program should be quit
 */
bool events();

/*
 * Game loop. Updates the game and sets the framerate to ~FPS.
 */
void loop(GameOfLife &gameOfLife);

/*
 * Render loop. Renders the game of life using SDL.
 */
void render(const GameOfLife &gameOfLife, RenderingEngine &renderingEngine, SDL_Texture *texture);

#endif //CONWAYS_GAME_OF_LIFE_MAIN_AUXILIARY_H
