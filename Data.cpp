#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Data.h"
using namespace std;

Day::Day(string line) {
    stringstream ss(line);
    vector<string> strings;
    while (ss.good()) {
        string substring;
        getline(ss, substring, ',');
        strings.push_back(substring);
    }
    string timeInfo = strings.at(0);
    vector<string> timeStrings;
    stringstream ssTime(timeInfo);
    while (ssTime.good()) {
        string substring;
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

Data::Data(string file) {
    ifstream inputFile (file);
    string line;
    getline(inputFile, line);
    while(getline(inputFile, line)) {
        Day day = Day(line);
        if (!stockMap.count(day.Name)) {
            vector<Day> days;
            stockMap.insert(make_pair(day.Name, days));
        }
        stockMap.at(day.Name).push_back(day);
    }
}
map<string, vector<Day> > Data::getMap() {
    return stockMap;
}