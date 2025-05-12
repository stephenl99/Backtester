#include "Main.h"
#include <iostream>
int main() {
    const Data data("all_stocks_5yr.csv");
    stockMap = data.getMap();
    for (auto& pair : *stockMap) {
        tickers.push_back(pair.first);
    }
    std::cout << stockMap << std::endl;
    return 0;
}
