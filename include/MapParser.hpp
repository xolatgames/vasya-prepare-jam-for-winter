#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <fstream>
#include <vector>

using namespace std;

class MapParser
{
public:
    MapParser(string fileName);

    vector<string> fileContent;

    int FindMapWidth();
    int FindMapHeight();
    vector<string> GetTiles(string layer, string lastTile);

private:
    ifstream file;
    string line;
};

#endif // MAP_PARSER_H
