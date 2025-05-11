#ifndef DATA_H
#define DATA_H
#include "Day.h"
#include <map>
#include <vector>
#include <fstream>
#include <string>

class Data {
    // Initial data structure of map, can change if needed
private:
    std::map<std::string, std::vector<Day> > stockMap; // Maps each ticker to vector of days
public:
    explicit Data(std::string file);
    std::map<std::string, std::vector<Day> > getMap();
};
#endif //DATA_H
