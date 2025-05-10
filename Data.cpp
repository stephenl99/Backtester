#pragma once
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Data.h"
#include "Main.h"

Day::Day(std::string line) {
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
    if (tickers.back() != Name) {
        tickers.push_back(Name);
    }
}

Data::Data(std::string file) {
    std::ifstream inputFile (file);
    std::string line;
    getline(inputFile, line);
    while(getline(inputFile, line)) {
        Day day = Day(line);
        if (!stockMap.count(day.Name)) {
            std::vector<Day> days;
            stockMap.insert(make_pair(day.Name, days));
        }
        stockMap.at(day.Name).push_back(day);
    }
}

std::map<std::string, std::vector<Day> > Data::getMap() {
    return stockMap;
}