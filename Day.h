
#ifndef DAY_H
#define DAY_H
#include <fstream>
class Day {
public:
    explicit Day(std::string line = "", Day* prev = nullptr); // Default constructor to empty string
    Day* prev = nullptr; // Previous day pointer in case of maligned data
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
