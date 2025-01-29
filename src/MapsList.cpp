#include "../include/MapsList.hpp"
#include <iostream>

using namespace std;

MapsList::MapsList()
{
    file.open("levels.ini");
    while (getline(file, line)) {fileContent.push_back(line);}
    file.close();

    for ( unsigned int i = 0; i < fileContent.size(); i++ )
    {
        line = fileContent.at(i);

        string map_text = "Map = ";
        size_t start_point = line.find(map_text);
        start_point = start_point + map_text.size();
        size_t end_point = line.find(";", start_point);
        maps.push_back(line.substr(start_point, end_point-start_point));

        string labels_text = "Labels = ";
        start_point = line.find(labels_text);
        start_point = start_point + labels_text.size();
        end_point = line.find(";", start_point);
        labelsMaps.push_back(line.substr(start_point, end_point-start_point));
    }
}
