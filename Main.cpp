#include "Main.h"
#include <iostream>
#include <filesystem>
int main() {
    const Data data("../all_stocks_5yr.csv");
    stockMap = data.getMap();
    for (auto& pair : *stockMap) {
        tickers.push_back(pair.first);
    }
    return 0;
}
