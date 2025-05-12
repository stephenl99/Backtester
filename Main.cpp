#include "Main.h"
#include <iostream>
int main() {
    const Data data("/Users/stephenlinder/Desktop/Projects/Backtester/all_stocks_5yr.csv");
    stockMap = data.getMap();
    for (auto& pair : *stockMap) {
        tickers.push_back(pair.first);
    }
    return 0;
}
