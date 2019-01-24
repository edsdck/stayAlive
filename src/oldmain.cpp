#include "Functions.hpp"
#include "Globals.hpp"
#include "Constants.h"
#include "LevelGenerator.hpp"
#include "Pathfind.hpp"

int main(int argc, char *args[])
{
	LevelGenerator lg;
	lg.generate();
	lg.makeGrid(map);
	lg.saveGrid(map);

	Tile* tiles[PAR::TOTAL_TILES];
	if (!initialize())
	{
		return 1;
	}
	if (!loadMedia(tiles))
	{
		return 1;
	}

	std::vector<std::vector<std::pair<int, int>>> came_from;
	came_from = pathFinding(map, 1, 1);


	bool running = true;
	bool gameStarted = true;
	while (running)
	{
		SDL_Rect camera = { 0, 0, PAR::SCREEN_WIDTH, PAR::SCREEN_HEIGHT };

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
			if (gameStarted)
			{
				dot.handleEvent();
			}
		}
		if (gameStarted)
		{
			//Set details of character
			dot.updateChar();
			foe.update();
			foe.walk(came_from, tiles);
			dot.move(tiles);
			dot.setCamera(camera);

			//Set screen's settings
			SDL_SetRenderDrawColor(renderer, 0x75, 0x8C, 0x8E, 0xFF);
			SDL_RenderClear(renderer);

			//Render tiles to the screen
			for (int i = 0; i < PAR::TOTAL_TILES; i++)
			{
				tiles[i]->tileRender(camera);
			}

			//Render character and bot to the screen
			foe.renderEnemy(camera.x, camera.y);
			dot.renderTexture(camera.x, camera.y);
		}
		else
		{
			//Set screen's settings
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(renderer);
		}

		SDL_RenderPresent(renderer);
	}
	close(tiles);

	return 0;
}