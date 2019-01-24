#include "Functions.hpp" //must
#include "Globals.hpp"
#include "Constants.h"
#include "LevelGenerator.hpp"
#include "Pathfind.hpp"
#include <iostream>

int main(int argc, char *args[])
{
	if (!initialize()) //if failed to initialize SDL libraries
	{
		return 0;
	}
	else
	{
		if (!loadMedia())
		{
			return 0;
		}
	}

	bool running = true; //game is running so it's true
	int currentOption = 0;
	SDL_Color highlight = { 0x9B, 0x59, 0xB6 };
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
	SDL_Rect camera = { 0, 0, PAR::SCREEN_WIDTH, PAR::SCREEN_HEIGHT }; //camera for the game

	while (running)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) //exit the game if close button is pressed
			{
				running = false;
				break;
			}

			if (game_state == 0) //if game state is in main menu
			{
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_DOWN:
						menuOption[currentOption].loadFromText(PAR::options[currentOption], textColor);
						currentOption++;
						if (currentOption == PAR::MAX_MENU_OPTIONS)
						{
							currentOption = 0;
						}
						menuOption[currentOption].loadFromText(PAR::options[currentOption], highlight);
						break;
					case SDLK_UP:
						menuOption[currentOption].loadFromText(PAR::options[currentOption], textColor);
						currentOption--;
						if (currentOption < 0)
						{
							currentOption = PAR::MAX_MENU_OPTIONS - 1;
						}
						menuOption[currentOption].loadFromText(PAR::options[currentOption], highlight);
						break;
					case SDLK_RETURN:
						switch (currentOption)
						{
						case 0:
							game_state = 1;
							break;
						case 1:
							game_state = 2; //LET'S START THE NEW GAME!
							break;
						case 2:
							running = false;
							break;
						}
						break;
					}
				}
			}
			else if (game_state > 0) //if game started
			{
				dot.handleEvent(); //handle players controls
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
						game_state = -1;
					}
				}
			}
		}
		if (game_state == 0)
		{
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(renderer);
			for (int i = 0; i < PAR::MAX_MENU_OPTIONS; i++)
			{
				menuOption[i].render((PAR::SCREEN_WIDTH - menuOption[i].getWidth()) / 2, (PAR::SCREEN_HEIGHT / 2) + menuOption[i].getHeight() * i);
			}
		}
		else if (game_state == 1)
		{
			//load map's tiles
			if (!loadTiles(tiles))
			{
				game_state = 0;
				menuOption[currentOption].loadFromText("Save does not exist", { 0xC0, 0x39, 0x2B });
			}
			else
			{
				if (!loadPositions())
				{
					game_state = 0;
					menuOption[currentOption].loadFromText("Save does not exist", { 0xC0, 0x39, 0x2B });
				}
				else
				{
					//set up foe's route
					loadTilesToVector();
					came_from = pathFinding(map, foe.getSourceY(), foe.getSourceX());
					game_state = 3; //set game state to the final game_state, which is playing the game
				}
			}

		}
		else if (game_state == 2) //level generating
		{
			//making everything default
			foe.setBox((PAR::TILE_WIDTH * PAR::HORIZONTAL_EDGES * 2) - PAR::TILE_WIDTH, PAR::TILE_HEIGHT);
			dot.setBox(PAR::TILE_WIDTH, PAR::TILE_HEIGHT);

			//creates new maze
			LevelGenerator level;
			level.generate();
			level.makeGrid(map);
			level.saveGrid(map);
			//load map's tiles
			if (!loadTiles(tiles))
			{
				return 0;
			}
			//set up foe's route
			came_from = pathFinding(map, 1, 1);
			foe.setSource(1, 1);
			game_state = 3; //set game state to the final game_state, which is playing the game
		}

		//state for playing the game, without else, so after setting up the level it immediately renders to the screen
		if (game_state == 3)
		{
			SDL_SetRenderDrawColor(renderer, 0x75, 0x8C, 0x8E, 0xFF);
			SDL_RenderClear(renderer);
			SDL_Rect playerPos = dot.getBox();
			/* Foe updating: updates the walk texture, updates the position of the foe's */
			if (foe.walk(came_from, tiles))
			{
				int destX = (playerPos.x / PAR::TILE_WIDTH);
				int destY = (playerPos.y / PAR::TILE_HEIGHT);
				came_from = pathFinding(map, destY, destX);
				foe.setSource(destX, destY);
			}
			foe.update();
			/* Dot updating: updates the texture as it walks, updates the position and set ups the camera according to dot's position */
			dot.updateChar();
			dot.move(tiles);
			dot.setCamera(camera);

			/* CHECK IF PLAYER IS IN FOE'S VIEW FIELD */
			if (foe.detectPlayer(playerPos))
			{
				remove("data/positions.map");
				remove("data/tile.map");
				game_state = 4;
			}

			/* Render tiles (map) to the screen */
			for (int i = 0; i < PAR::TOTAL_TILES; i++)
			{
				tiles[i]->tileRender(camera);
			}
			/* Render characters to the screen */
			foe.renderEnemy(camera.x, camera.y);
			dot.renderTexture(camera.x, camera.y);
		}
		if (game_state == 4)
		{
			SDL_SetRenderDrawColor(renderer, 0xE7, 0x4C, 0x3C, 0xFF); 
			SDL_RenderClear(renderer);
			gameOver.render((PAR::SCREEN_WIDTH - gameOver.getWidth()) / 2, PAR::SCREEN_HEIGHT / 2);
		}

		/* Render everything on the screen */
		SDL_RenderPresent(renderer);
	}
	close();
	deleteTiles(tiles);
	return 0;
}