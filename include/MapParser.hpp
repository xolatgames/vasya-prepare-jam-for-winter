#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <fstream>
#include <vector>

using namespace std;

class MapFile
{
public:
    MapFile(string fileName);

    ifstream file;
    vector<string> fileContent;
    string line;

    int FindMapWidth();
    int FindMapHeight();
    vector<string> GetTiles(string layer, string lastTile);
};

#endif // MAP_PARSER_H
