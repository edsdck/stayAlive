#include "Functions.hpp"
#include "Constants.h"
#include "TilesNames.h"
#include "CharRotations.h"
#include "Globals.hpp"

bool initialize()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}
	else
	{
		window = SDL_CreateWindow(PAR::title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PAR::SCREEN_WIDTH, PAR::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr)
			{
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				if (TTF_Init() == -1)
				{
					success = false;
				}
				else
				{
					if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
					{
						success = false;
					}
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	font = TTF_OpenFont("assets/Bungee-Regular.ttf", 50);
	if (font == NULL)
	{
		success = false;
	}
	else
	{
		SDL_Color color = { 0xFF, 0xFF, 0xFF };
		SDL_Color highlight = { 0x9B, 0x59, 0xB6 };
		if (!menuOption[0].loadFromText(PAR::options[0], highlight))
		{
			success = false;
		}
		if (!menuOption[1].loadFromText(PAR::options[1], color))
		{
			success = false;
		}
		if (!menuOption[2].loadFromText(PAR::options[2], color))
		{
			success = false;
		}
		if (!gameOver.loadFromText("Oh no you've been found by a bot!", color))
		{
			success = false;
		}
	}

	if (!dot.loadFromFile("assets/char3.png"))
	{
		success = false;
	}
	else
	{
		//face to the camera
		charClips[faceIdle].x = 0;
		charClips[faceIdle].y = 0;
		charClips[faceIdle].w = 45;
		charClips[faceIdle].h = 50;

		charClips[faceRun1].x = 45;
		charClips[faceRun1].y = 0;
		charClips[faceRun1].w = 45;
		charClips[faceRun1].h = 50;

		charClips[faceRun2].x = 90;
		charClips[faceRun2].y = 0;
		charClips[faceRun2].w = 45;
		charClips[faceRun2].h = 50;
		//back to the camera
		charClips[backIdle].x = 0;
		charClips[backIdle].y = 50;
		charClips[backIdle].w = 45;
		charClips[backIdle].h = 50;

		charClips[backRun1].x = 45;
		charClips[backRun1].y = 50;
		charClips[backRun1].w = 45;
		charClips[backRun1].h = 50;

		charClips[backRun2].x = 90;
		charClips[backRun2].y = 50;
		charClips[backRun2].w = 45;
		charClips[backRun2].h = 50;
		//right arm to the camera
		charClips[rightIdle].x = 0;
		charClips[rightIdle].y = 100;
		charClips[rightIdle].w = 45;
		charClips[rightIdle].h = 50;

		charClips[rightRun1].x = 45;
		charClips[rightRun1].y = 100;
		charClips[rightRun1].w = 45;
		charClips[rightRun1].h = 50;

		charClips[rightRun2].x = 90;
		charClips[rightRun2].y = 100;
		charClips[rightRun2].w = 45;
		charClips[rightRun2].h = 50;
		//left arm to the camera
		charClips[leftIdle].x = 0;
		charClips[leftIdle].y = 150;
		charClips[leftIdle].w = 45;
		charClips[leftIdle].h = 50;

		charClips[leftRun1].x = 45;
		charClips[leftRun1].y = 150;
		charClips[leftRun1].w = 45;
		charClips[leftRun1].h = 50;

		charClips[leftRun2].x = 90;
		charClips[leftRun2].y = 150;
		charClips[leftRun2].w = 45;
		charClips[leftRun2].h = 50;
	}
	if (!foe.loadFromFile("assets/char3.png"))
	{
		success = false;
	}
	else
	{
		//face to the camera
		charClips[faceIdle].x = 0;
		charClips[faceIdle].y = 0;
		charClips[faceIdle].w = 45;
		charClips[faceIdle].h = 50;

		charClips[faceRun1].x = 45;
		charClips[faceRun1].y = 0;
		charClips[faceRun1].w = 45;
		charClips[faceRun1].h = 50;

		charClips[faceRun2].x = 90;
		charClips[faceRun2].y = 0;
		charClips[faceRun2].w = 45;
		charClips[faceRun2].h = 50;
		//back to the camera
		charClips[backIdle].x = 0;
		charClips[backIdle].y = 50;
		charClips[backIdle].w = 45;
		charClips[backIdle].h = 50;

		charClips[backRun1].x = 45;
		charClips[backRun1].y = 50;
		charClips[backRun1].w = 45;
		charClips[backRun1].h = 50;

		charClips[backRun2].x = 90;
		charClips[backRun2].y = 50;
		charClips[backRun2].w = 45;
		charClips[backRun2].h = 50;
		//right arm to the camera
		charClips[rightIdle].x = 0;
		charClips[rightIdle].y = 100;
		charClips[rightIdle].w = 45;
		charClips[rightIdle].h = 50;

		charClips[rightRun1].x = 45;
		charClips[rightRun1].y = 100;
		charClips[rightRun1].w = 45;
		charClips[rightRun1].h = 50;

		charClips[rightRun2].x = 90;
		charClips[rightRun2].y = 100;
		charClips[rightRun2].w = 45;
		charClips[rightRun2].h = 50;
		//left arm to the camera
		charClips[leftIdle].x = 0;
		charClips[leftIdle].y = 150;
		charClips[leftIdle].w = 45;
		charClips[leftIdle].h = 50;

		charClips[leftRun1].x = 45;
		charClips[leftRun1].y = 150;
		charClips[leftRun1].w = 45;
		charClips[leftRun1].h = 50;

		charClips[leftRun2].x = 90;
		charClips[leftRun2].y = 150;
		charClips[leftRun2].w = 45;
		charClips[leftRun2].h = 50;
	}
	if (!tileSet.loadFromFile("assets/tile.png"))
	{
		success = false;
	}
	return success;
}

bool loadTiles(Tile* tiles[])
{
	bool success = true;
	int x = 0, y = 0;
	std::ifstream fMap("data/tile.map");
	if (!fMap.is_open())
	{
		success = false;
	}
	else
	{
		for (int i = 0; i < PAR::TOTAL_TILES; i++)
		{
			int tileType = -1;
			char temp;
			fMap >> temp;
			tileType = temp - '0';
			if (fMap.fail())
			{
				success = false;
				break;
			}
			if ((tileType >= 0) && (tileType <= PAR::TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType);
			}
			else
			{
				success = false;
				break;
			}

			x += PAR::TILE_WIDTH;
			if (x >= PAR::LEVEL_WIDTH)
			{
				x = 0;
				y += PAR::TILE_HEIGHT;
			}
		}

		if (success)
		{
			tileClips[boxWood1].x = 0;
			tileClips[boxWood1].y = 0;
			tileClips[boxWood1].w = PAR::TILE_WIDTH;
			tileClips[boxWood1].h = PAR::TILE_HEIGHT;

			tileClips[boxWood2].x = 64;
			tileClips[boxWood2].y = 0;
			tileClips[boxWood2].w = PAR::TILE_WIDTH;
			tileClips[boxWood2].h = PAR::TILE_HEIGHT;

			tileClips[boxSteel1].x = 128;
			tileClips[boxSteel1].y = 0;
			tileClips[boxSteel1].w = PAR::TILE_WIDTH;
			tileClips[boxSteel1].h = PAR::TILE_HEIGHT;

			tileClips[boxSteel2].x = 196;
			tileClips[boxSteel2].y = 0;
			tileClips[boxSteel2].w = PAR::TILE_WIDTH;
			tileClips[boxSteel2].h = PAR::TILE_HEIGHT;

			tileClips[ground].x = 256;
			tileClips[ground].y = 0;
			tileClips[ground].w = PAR::TILE_WIDTH;
			tileClips[ground].h = PAR::TILE_HEIGHT;
		}
	}
	fMap.close();
	return success;
}

void loadTilesToVector()
{
	std::ifstream fMap("data/tile.map");

	for (int y = 0; y < PAR::TOTAL_VERTICAL; y++)
	{
		for (int x = 0; x < PAR::TOTAL_HORIZONTAL; x++)
		{
			int tileID = -1;
			char temp;
			fMap >> temp;
			tileID = temp - '0';
			map[y][x] = tileID;
		}
	}
	fMap.close();
}

bool collisionWithWall(SDL_Rect a, Tile *tiles[])
{
	for (int i = 0; i < PAR::TOTAL_TILES; i++)
	{
		if (tiles[i]->getType() >= boxWood1 && tiles[i]->getType() <= boxSteel2)
		{
			if (SDL_HasIntersection(&a, &tiles[i]->getBox()) == SDL_TRUE)
			{
				return true;
			}
		}
	}
	return false;
}

std::vector<std::vector<std::pair<int, int>>> pathFinding(std::vector<std::vector<int>> &map, int sourceY, int sourceX)
{
	//Breadth first algorithm
	//Using queue - FIFO
	std::queue<std::pair<int, int>> frontier;
	frontier.push(std::make_pair(sourceY, sourceX));
	//Data structure for storing path
	std::vector<std::vector<std::pair<int, int>>> came_from;
	//Initiliazing with -1, it means tile wasn't visited
	came_from.resize(PAR::TOTAL_VERTICAL, std::vector<std::pair<int, int>>(PAR::TOTAL_HORIZONTAL, std::pair<int, int>(-1, -1)));
	came_from[sourceY][sourceX] = { sourceY, sourceX };
	while (!frontier.empty())
	{
		int x, y;
		//Current cell
		y = frontier.front().first;
		x = frontier.front().second;
		frontier.pop();
		//Checking neighbors if they are passable 
		//and if they are pushing them to frontier
		//and also setting that they came from current cell
		if (map[y - 1][x] == ground && (came_from[y - 1][x].first == -1)) //-1 stands for unvisited
		{
			frontier.push(std::make_pair(y - 1, x));
			came_from[y - 1][x] = { y, x };
		}

		if (map[y + 1][x] == ground && (came_from[y + 1][x].first == -1))
		{
			frontier.push(std::make_pair(y + 1, x));
			came_from[y + 1][x] = { y, x };
		}

		if (map[y][x - 1] == ground && (came_from[y][x - 1].first == -1))
		{
			frontier.push(std::make_pair(y, x - 1));
			came_from[y][x - 1] = { y, x };
		}

		if (map[y][x + 1] == ground && (came_from[y][x + 1].first == -1))
		{
			frontier.push(std::make_pair(y, x + 1));
			came_from[y][x + 1] = { y, x };
		}
	}
	return came_from;
}

void savePositions()
{
	SDL_Rect box;
	std::ofstream positions("data/positions.map");
	box = foe.getBox();
	positions << box.x << " " << box.y << "\n";
	positions << foe.getSourceX() << " " << foe.getSourceY() << "\n";
	box = dot.getBox();
	positions << box.x << " " << box.y;
	positions.close();
}

bool loadPositions()
{
	bool success = true;
	std::ifstream fPos("data/positions.map");
	if (!fPos.is_open())
	{
		success = false;
	}
	else
	{
		int x, y;
		fPos >> x >> y;
		foe.setBox(x, y);
		fPos >> x >> y;
		foe.setSource(x, y);
		fPos >> x >> y;
		dot.setBox(x, y);
	}
	return success;
}

void close()
{
	savePositions();
	dot.free();
	tileSet.free();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

void deleteTiles(Tile* tiles[])
{
	for (int i = 0; i < PAR::TOTAL_TILES; i++)
	{
		delete tiles[i];
		tiles[i] = NULL;
	}
}