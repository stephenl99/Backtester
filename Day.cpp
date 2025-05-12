#include "Day.h"
#include <iostream>
#include <sstream>
Day::Day(std::string line, Day* prev) {
    this->prev = prev;
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
    this->year = stoi(timeStrings.at(0));
    this->month = stoi(timeStrings.at(1));
    this->day = stoi(timeStrings.at(2));
    if (strings.at(1) == "") {
        this->open = prev == nullptr ? 0.0 : prev->open; //Missing data
    } else {
        this->open = stod(strings.at(1)); // Normal
    }
    if (strings.at(2) == "") {
        this->high = prev == nullptr ? 0.0 : prev->high; //Missing data
    } else {
        this->high = stod(strings.at(2)); // Normal
    }
    if (strings.at(3) == "") {
        this->low = prev == nullptr ? 0.0 : prev->low; //Missing data
    } else {
        this->low = stod(strings.at(3)); // Normal
    }

    if (strings.at(4) == "") {
        this->close = prev == nullptr ? 0.0 : prev->close; //Missing data
    } else {
        this->close = stod(strings.at(4)); // Normal
    }
    this->volume = stoi(strings.at(5));
    this->Name = strings.at(6);
}
