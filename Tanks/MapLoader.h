#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Wall.h"

class Wall;

//Loads map from external file. This class DO NOT remove dynamic allocated memory - you have to do it manually.
class MapLoader
{
public:
	MapLoader();
	MapLoader(std::string path);
	~MapLoader();
	void loadFromFile(std::string path);

	//Take addresses of Wall objects and write them to new vector.
	void getWalls(std::vector<Wall*> &arg);

	//Take addresses of Tank objects and write them to new vector.
	void getTanks(std::vector<Tank*> &arg);

	//You may use this method to free memory
	void freeDynamicAllocatedMemory();

private:
	std::ifstream file;
	std::vector<Wall*> wall;
	std::vector<Tank*> tank;
};

