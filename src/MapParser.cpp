#include <fstream>
#include <vector>
#include "../include/MapParser.hpp"

using namespace std;

MapFile::MapFile(string fileName)
{
    file.open(fileName);
    while ( getline(file, line) ) { fileContent.push_back(line); }
    file.close();
}

int MapFile::FindMapWidth()
{
    for ( unsigned int i=0; i < fileContent.size(); i++ )
    {
        line = fileContent.at(i);

        string width = "width=\"";
        if ( line.find(width) != string::npos )
        {
            int start_pos = line.find(width) + width.size();
            int end_pos = line.find("\"") - start_pos;
            width = line.substr(start_pos, end_pos);
            return stoi(width);
        }
    }

    return 0;
}

int MapFile::FindMapHeight()
{
    for ( unsigned int i=0; i < fileContent.size(); i++ )
    {
        line = fileContent.at(i);

        string height = "height=\"";
        if ( line.find(height) != string::npos )
        {
            int start_pos = line.find(height) + height.size();
            int end_pos = line.find("\"") - start_pos;
            height = line.substr(start_pos, end_pos);
            return stoi(height);
        }
    }

    return 0;
}

vector<string> MapFile::GetTiles(string layer, string lastTile)
{
    vector<string> tiles;
    int start_line = 0;
    int end_line = 0;
    string tile;

    for ( unsigned int i=0; i < fileContent.size(); i++ )
    {
        line = fileContent.at(i);

        string start_point = "name=\""+layer+"\"";
        if ( line.find(start_point) != string::npos )
        {
            start_line = i+2;
            break;
        }
    }

    for ( unsigned int i=start_line; i < fileContent.size(); i++ )
    {
        line = fileContent.at(i);

        string end_point = "</data>";
        if ( line.find(end_point) != string::npos )
        {
            end_line = i;
            break;
        }
    }

    for ( int i = start_line; i <= end_line; i++ )
    {
        line = fileContent.at(i);
        size_t start_point = 0;
        size_t end_point;

        while ( line.find(",", start_point) != string::npos )
        {
            end_point = line.find(",", start_point);
            tile = line.substr(start_point, end_point-start_point);

            start_point = end_point+1;

            if ( tile.find("10") != string::npos )
            {
                tiles.push_back("Tr");
            }
            else if ( tile.find("22") != string::npos )
            {
                tiles.push_back("L");
            }
            else if ( tile.find("0") != string::npos )
            {
                tiles.push_back("0");
            }
            else if ( tile.find("2") != string::npos )
            {
                tiles.push_back("GT");
            }
            else if ( tile.find("3") != string::npos )
            {
                tiles.push_back("G");
            }
            else if ( tile.find("4") != string::npos )
            {
                tiles.push_back("J");
            }
            else if ( tile.find("5") != string::npos )
            {
                tiles.push_back("B");
            }
            else if ( tile.find("6") != string::npos )
            {
                tiles.push_back("R");
            }
            else if ( tile.find("7") != string::npos )
            {
                tiles.push_back("Tu");
            }
            else if ( tile.find("8") != string::npos )
            {
                tiles.push_back("P");
            }
            else if ( tile.find("9") != string::npos )
            {
                tiles.push_back("Ho");
            }
        }
    }

    tiles.push_back(lastTile);
    return tiles;
}
