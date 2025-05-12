#include "Data.h"

#include <iostream>

Data::Data(std::string file) {
    this->stockMap = new std::map<std::string, std::vector<Day>>;
    std::ifstream inputFile(file);
    std::string line;
    getline(inputFile, line);
    Day* prev = nullptr;
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            Day day = Day(line, prev);
            prev = &day;
            if (!this->stockMap->count(day.Name)) {
                std::vector<Day> days;
                this->stockMap->insert(std::make_pair(day.Name, days));
            }
            this->stockMap->at(day.Name).push_back(day);
        }
    } else {
        std::cerr << "Unable to open file " << file << std::endl;
    }
    inputFile.close();
}
std::map<std::string, std::vector<Day> >* Data::getMap() const {
    return this->stockMap;
}
