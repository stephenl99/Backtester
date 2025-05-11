#include "Data.h"

Data::Data(std::string file) {
    std::ifstream inputFile (file);
    std::string line;
    getline(inputFile, line);
    while(getline(inputFile, line)) {
        Day day = Day(line);
        if (!stockMap.count(day.Name)) {
            std::vector<Day> days;
            stockMap.insert(std::make_pair(day.Name, days));
        }
        stockMap.at(day.Name).push_back(day);
    }
}
std::map<std::string, std::vector<Day> > Data::getMap() {
    return stockMap;
}