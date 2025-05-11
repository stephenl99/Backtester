
#ifndef DAY_H
#define DAY_H
#include <fstream>
class Day {
public:
    explicit Day(std::string line = ""); // Default constructor to empty string
    int year;
    int month;
    int day;
    double open;
    double high;
    double low;
    double close;
    int volume;
    std::string Name;
};
#endif //DAY_H
