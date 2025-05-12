#include "Main.h"
#include <iostream>
#include <filesystem>

#include "DataHandler.h"
#include "Strategy.h"

int main() {
    const Data data("../all_stocks_5yr.csv");
    stockMap = data.getMap();
    for (auto& pair : *stockMap) {
        tickers.push_back(pair.first);
    }
    auto* dataHandler = new HistoricDataHandler();
    auto* strat = new BuyHoldStrategy(dataHandler);

    return 0;
}
