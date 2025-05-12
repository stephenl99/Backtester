
#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>
#include <map>
#include "Day.h"
extern std::map<std::string, std::vector<Day>>* stockMap; // Maps each symbol to list of days
extern std::vector<std::string> tickers; // Contains all the symbols on our dataset

#endif //GLOBAL_H
