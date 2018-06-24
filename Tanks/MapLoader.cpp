#include "MapLoader.h"



MapLoader::MapLoader()
{
}

MapLoader::MapLoader(std::string path)
{
	loadFromFile(path);
}

MapLoader::~MapLoader()
{
}

void MapLoader::loadFromFile(std::string path)
{
	file.open(path);

	if (file)
	{
		char c;
		int line = 0;
		int row = 0;
		int tankCounter = 0;

		while (file.get(c))
		{
			if (row < MAP_WIDTH/WALL_WIDTH && line < MAP_HEIGHT/WALL_HEIGHT && c != '\n')
			{
				switch (c)
				{
					case 'X':
					{
						wall.push_back(new Wall(64 * row, 64 * line));
						break;
					}
					case '#':
					{
						wall.push_back(new Wall(64 * row, 64 * line, false));
						break;
					}
					case '^':
					case 'v':
					case '<':
					case '>':
					{
						if (tankCounter == 0)
						{
							switch (c)
							{
								case '^':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, UP, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
								case 'v':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, DOWN, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
								case '<':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, LEFT, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
								case '>':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, RIGHT, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
							}

						}
						else if (tankCounter == 1)
						{
							switch (c)
							{
								case '^':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, UP, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
								case 'v':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, DOWN, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
								case '<':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, LEFT, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
								case '>':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, RIGHT, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
							}
						}
						tankCounter++;
						break;
					}
				}
			}
			else if (c == '\n')
			{
				line++;
				row = -1;
			}
			row++;
		}

		//TO-DO: Exception when tankCounter < 2
	}
	else
	{
		std::cout << "File could not be opened" << std::endl;
	}

	file.close();
}

void MapLoader::freeDynamicAllocatedMemory()
{
	for (int i = 0; i < static_cast<int>(wall.size()); i++)
	{
		delete wall[i];
	}

	for (int i = 0; i < static_cast<int>(tank.size()); i++)
	{
		delete tank[i];
	}
}

void MapLoader::getWalls(std::vector<Wall*> &arg)
{
	for (auto x : wall)
	{
		arg.push_back(x);
	}
}

void MapLoader::getTanks(std::vector<Tank*> &arg)
{
	for (auto x : tank)
	{
		arg.push_back(x);
	}
}