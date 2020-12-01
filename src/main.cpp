//============================================================================
// Name        : main.cpp
// Author      : meteoritenhagel
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include "gameoflife_test.h"

#include "gameoflife.h"
#include "renderingengine.h"

#include <SDL.h>

#include <cassert>
#include <iostream>
using namespace std;

bool events()
{
	bool quit = false;
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			quit = true;
		}
	}
	return quit;
}

void loop(GameOfLife &gameOfLife)
{
	gameOfLife.nextGeneration();
	SDL_Delay(16);
	return;
}

void render(const GameOfLife &gameOfLife, const RenderingEngine &renderingEngine, SDL_Texture *texture)
{
	uint32_t *pixelData;
	int pitch = 0;

	SDL_LockTexture(texture, NULL, reinterpret_cast<void**>(&pixelData), &pitch);
	int offset = pitch/sizeof(*pixelData);

	for (int i = 0; i < gameOfLife.getHeight(); ++i)
		for (int j = 0; j < gameOfLife.getWidth(); ++j)
			if(gameOfLife.isCellAlive(i, j))
			{
				pixelData[i + offset*j] = 0xFFFFFFFF;
			}
			else
				pixelData[i + offset*j] = 0xFF000000;

	SDL_UnlockTexture(texture);
	SDL_RenderCopy(renderingEngine.getRenderer(), texture, NULL, NULL);
	SDL_RenderPresent(renderingEngine.getRenderer());
	return;
}

int main()
{
	srand(time(NULL));

	const int screenWidth = 1000;
	const int screenHeight = 1000;

	const int gridWidth = 600;
	const int gridHeight = 600;

	GameOfLife gameOfLife(gridWidth, gridHeight);
	gameOfLife.applyRandomState();

	RenderingEngine renderingEngine(screenWidth, screenHeight, "Conway's Game of Life");

	SDL_Texture *texture = SDL_CreateTexture(renderingEngine.getRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, gridWidth, gridHeight);

	render(gameOfLife, renderingEngine, texture);
	SDL_Delay(1000);

	bool quit = false;
	while(!quit)
	{
		quit = events();
		render(gameOfLife, renderingEngine, texture);
		loop(gameOfLife);
	}

//	GameOfLife_Test golTest;
//	golTest.testAll();

	return 0;
}
