#ifndef MAPS_LIST_H
#define MAPS_LIST_H

#include <fstream>
#include <vector>

using namespace std;

class MapsList
{
public:
    MapsList();

    vector<string> fileContent;

    vector<string> maps;
    vector<string> labelsMaps;

private:
    ifstream file;
    string line;
};

#endif // MAPS_LIST_H
