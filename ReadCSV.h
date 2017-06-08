#ifndef __READCSVH__
#define __READCSVH__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

class ReadCSV
{
public:
    ReadCSV(const std::string & , const char , char *r);
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

#endif
