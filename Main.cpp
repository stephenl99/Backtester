#include "Main.h"
#include <iostream>
#include <filesystem>

#include "DataHandler.h"
#include "ExecutionHandler.h"
#include "Portfolio.h"
#include "Strategy.h"

int main() {
    const Data data("../all_stocks_5yr.csv");
    stockMap = data.getMap();
    maxTimestamp = (*stockMap)["A"].size();// Set maxtimestamp
    for (auto& pair : *stockMap) {
        tickers.push_back(pair.first);
    }
    auto* dataHandler = new HistoricDataHandler();
    auto* strat = new BuyHoldStrategy(dataHandler);
    auto naivePortfolio = new NaivePortfolio(dataHandler);
    auto noLatencyExecutionHandler = new NoLatencyExecutionHandler(dataHandler);


    while (true) {
        if (dataHandler->getContinueExecution()) {
            dataHandler->updateBars();
        } else {
            break;
        }
        while (true) {
            std::queue<Event*>* q = dataHandler->getEventQueue();
            if (q->empty() || !dataHandler->getContinueExecution()) {
                break;
            }
            Event* event = q->front();
            q->pop();

            if (event != nullptr) {
                if (event->getType() == "MARKET") {
                    strat->calculateSignals(event);
                    naivePortfolio->updateTime(event);
                } else if (event->getType() == "SIGNAL") {
                    naivePortfolio->updateSignal(event);
                } else if (event->getType() == "ORDER") {
                    noLatencyExecutionHandler->executeOrder(event);
                } else if (event->getType() == "FILL") {
                    naivePortfolio->updateFill(event);
                }
            }
        }
    }
    std::cout << "Finished" << std::endl;
    double cashSpent = naivePortfolio->current_holdings()->at("cash");
    double cashEarned = naivePortfolio->current_holdings()->at("total");
    std::cout << cashEarned + cashSpent << std::endl;
    // for (std::string ticker : tickers) {
    //     std::cout << (*naivePortfolio->current_holdings())[ticker] << std::endl;
    // }

    return 0;
}
