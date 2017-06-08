#include "ReadCSV.h"

ReadCSV::ReadCSV( const std::string & fileName 
        ,const char _delim, char *_r)
{
    /* Constructor for ReadCSV automatically reads in */
    delim   =       _delim;
    removeChar =    _r;
    data.open(fileName);
    std::string     line;
    if(!data.is_open()){
        std::string message ("Could Not Open File");
        throw message;
    }

    // Create Header Names from the first line
    std::getline(data,line);
    std::stringstream lineStream(line);
    std::string     cell;
    while(std::getline(lineStream,cell, delim))
    {
        HeaderNames.push_back(cell);
    }
}

bool ReadCSV::ReadLine()
{
    /* Read in a single line */
    std::string line;
    if(std::getline(data,line)){
        std::stringstream   lineStream(line);
        std::string         cell;
        for (int i = 0; i < HeaderNames.size(); i++)
        {
            std::getline(lineStream,cell,delim);
            for(size_t i = 0; i < strlen(removeChar); i++){
                cell.erase(std::remove(cell.begin(),cell.end(),removeChar[i]),cell.end());
            }
            Values[HeaderNames.at(i)]=cell;
        }
        currentLine = line;
        return true;
    }
    else{
        return false;
    }
}
