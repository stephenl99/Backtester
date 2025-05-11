#include "Day.h"
#include <iostream>
#include <sstream>
Day::Day(std::string line) {
    if (line.length() == 0) {
        throw std::invalid_argument("Empty line for day constructor");
    }
    std::stringstream ss(line);
    std::vector<std::string> strings;
    while (ss.good()) {
        std::string substring;
        getline(ss, substring, ',');
        strings.push_back(substring);
    }
    std::string timeInfo = strings.at(0);
    std::vector<std::string> timeStrings;
    std::stringstream ssTime(timeInfo);
    while (ssTime.good()) {
        std::string substring;
        getline(ssTime, substring, '-');
        timeStrings.push_back(substring);
    }
    year = stoi(timeStrings.at(0));
    month = stoi(timeStrings.at(1));
    day = stoi(timeStrings.at(2));
    open = stod(strings.at(3));
    high = stod(strings.at(4));
    low = stod(strings.at(5));
    close = stod(strings.at(6));
    volume = stoi(strings.at(7));
    Name = strings.at(8);
}
