#ifndef MAP_FILE_H
#define MAP_FILE_H

#include <fstream>
#include <vector>
#include "MapParser.hpp"

using namespace std;

class MapFile
{
public:
    MapFile(string fileName, string labelsFileName, string lastTileMap);

    MapParser *mapFile;

    int mapWidth;
    int mapHeight;

    vector<string> backMap;
    vector<string> labelMap;
    vector<string> tileMap;

    vector<string> labelTexts;

private:
    ifstream file;
    string line;
};

#endif // MAP_FILE_H
