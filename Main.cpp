#include "Main.h"
#include <iostream>
#include <filesystem>

#include "DataHandler.h"
#include "ExecutionHandler.h"
#include "Portfolio.h"
#include "Strategy.h"
#include "PythonBinding.h"

namespace fs = std::filesystem;

int main() {
    // Get the path to the executable
    fs::path exe_path = fs::current_path();
    // Go up one directory if we're in build/
    if (exe_path.filename() == "build" || exe_path.filename() == "cmake-build-debug") {
        exe_path = exe_path.parent_path();
    }
    // Construct path to data file
    fs::path data_path = exe_path / "all_stocks_5yr.csv";
    
    std::cout << "Looking for data file at: " << data_path << std::endl;
    
    const Data data(data_path.string());
    stockMap = data.getMap();
    maxTimestamp = (*stockMap)["A"].size();// Set maxtimestamp
    for (auto& pair : *stockMap) {
        tickers.push_back(pair.first);
    }
    auto* dataHandler = new HistoricDataHandler();
    auto* strat = new BuyHoldStrategy(dataHandler);
    auto naivePortfolio = new NaivePortfolio(dataHandler);
    auto noLatencyExecutionHandler = new NoLatencyExecutionHandler(dataHandler);

    auto* positions = naivePortfolio->all_positions();
    auto* holdings = naivePortfolio->all_holdings();

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

    appleHoldings = naivePortfolio->NaivePortfolio::getHoldings( "AAPL");
    return 6;
}
