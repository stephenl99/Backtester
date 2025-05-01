#ifndef DATA_H
#define DATA_H
class Day {
public:
    Day(std::string line);
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
class Data {
    // Initial data structure of map, can change if needed
private:
    std::map<std::string, std::vector<Day> > stockMap;
public:
    Data(std::string file);
    std::map<std::string, std::vector<Day> > getMap();
};
#endif //DATA_H
