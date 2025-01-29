#include "../include/MapFile.hpp"

using namespace std;

MapFile::MapFile(string fileName, string labelsFileName, string lastTileMap)
{
    mapFile = new MapParser(fileName);

    mapWidth = mapFile->FindMapWidth();
    mapHeight = mapFile->FindMapHeight();

    backMap = mapFile->GetTiles("Back", "0");
    labelMap = mapFile->GetTiles("Labels", "0");
    tileMap = mapFile->GetTiles("Objects", lastTileMap);

    file.open(labelsFileName);
    while (getline(file, line)) {labelTexts.push_back(line);}
    file.close();
}
