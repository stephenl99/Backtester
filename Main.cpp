#include "Data.cpp"
int main() {
    Data data("all_stocks_5yr.csv");
    map<string, vector<Day> > stockMap = data.getMap();
    return 0;
}