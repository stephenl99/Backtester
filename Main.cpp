#include "Main.h"
#include <iostream>


int main() {
    Data data = Data("all_stocks_5yr.csv");
    stockMap = data.getMap();
    for (auto& pair : stockMap) {
        tickers.push_back(pair.first);
    }
    return 0;
}
