#ifndef __READCSVH__
#define __READCSVH__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

namespace read
{
    

    class ReadCSV
    {
    public:
        ReadCSV(const std::string & , const char , char *r=(char*)0);
        // filename, deliminaator, ignore/remove character
        ~ReadCSV(){};
        
        template <class T>
        T GetValue(const std::string & Key)
        {
            const std::string & s = Values.at(Key);            
            std::stringstream   ss(s);
            T                   t;
            ss >> t;
            return t;
        };
        bool ReadLine();
        inline std::vector<std::string> GetHeaderNames();
        inline std::string GetLine();

    private:
        char delim;
        char *removeChar;
        std::map<std::string,std::string> Values;
        std::vector<std::string> HeaderNames;
        std::fstream data;
        std::string currentLine;
    };

    inline std::vector<std::string> ReadCSV::GetHeaderNames(){
        return HeaderNames;
    }

    inline std::string ReadCSV::GetLine(){
        return currentLine;
    }

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
                if (removeChar != (char*)0){
                    for(size_t i = 0; i < strlen(removeChar); i++){
                        cell.erase(std::remove(cell.begin(),cell.end(),removeChar[i]),cell.end());
                    }
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
}
#endif
