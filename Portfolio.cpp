#include "Portfolio.h"

#include <utility>
#include "Global.h"

NaivePortfolio::NaivePortfolio(HistoricDataHandler *dh, int startTimestamp, double initialCapital, std::vector<std::string> relevantTickers) {
    this->dataHandler = dh;
    this->startDate = startTimestamp;
    this->initialCapital = initialCapital;
    this->relevantTickers = std::move(relevantTickers); // Tickers we are considering, may be able to remove
}
std::unordered_map<std::string, int>* NaivePortfolio::current_positions() {
    return currentPositions;
}

std::unordered_map<std::string, double>* NaivePortfolio::current_holdings() {
    return currentHoldings;
}
std::vector<std::unordered_map<std::string, int>*>* NaivePortfolio::initAllPositions() const {
    std::unordered_map<std::string, int>* map = new std::unordered_map<std::string, int>;
    for (std::string ticker : tickers) {
        (*map)[ticker] = 0;
    }
    (*map)["dateTime"] = this->startDate; // start date added for reference
    std::vector<std::unordered_map<std::string, int>*>* vector = new std::vector<std::unordered_map<std::string, int>*>;
    vector->push_back(map);
    return vector;
}
std::unordered_map<std::string, int>* NaivePortfolio::initCurrentPositions() {
    return (*allPositions)[0];
}
std::vector<std::unordered_map<std::string, double>*>* NaivePortfolio::initAllHoldings() {
    std::unordered_map<std::string, double>* map = new std::unordered_map<std::string, double>;
    for (std::string ticker : tickers) {
        (*map)[ticker] = 0.0;
    }
    (*map)["dateTime"] = this->startDate;
    (*map)["cash"] = this->initialCapital;
    (*map)["commission"] = 0.0;
    (*map)["total"] = this->initialCapital;
    std::vector<std::unordered_map<std::string, double>*>* vector = new std::vector<std::unordered_map<std::string, double>*>;
    vector->push_back(map);
    return vector;
}
std::unordered_map<std::string, double>* NaivePortfolio::initCurrentHoldings() {
    // std::unordered_map<std::string, int>* map = new std::unordered_map<std::string, int>;
    // for (const std::string& ticker : tickers) {
    //     (*map)[ticker] = 0;
    // }
    // (*map)["dateTime"] = this->startDate;
    // (*map)["cash"] = this->initialCapital;
    // (*map)["commission"] = 0.0;
    // (*map)["total"] = this->initialCapital;
    // return map;
    return (*allHoldings)[0];
}
// Decided to all tickers may wish to change to relevant tickers eventually
//updates the positions and holdings for next day
void NaivePortfolio::updateTime(Event* event) {
    if (event->getType() == "MARKET") {
        auto* positionMap = new std::unordered_map<std::string, int>;
        for (const std::string& ticker : tickers) {
            (*positionMap)[ticker] = (*currentPositions)[ticker];
        }
        (*positionMap)["dateTime"] = (*currentPositions)["dateTime"] + 1;
        currentPositions = positionMap;
        allPositions->push_back(positionMap);

        std::unordered_map<std::string, double>* holdingMap = new std::unordered_map<std::string, double>;
        (*holdingMap)["total"] = 0;
        for (std::string ticker : tickers) {
            double marketValue = (*currentPositions)[ticker] * dataHandler->getLatestData(ticker)->close; // Currently using close value could update to open
            (*holdingMap)[ticker] = marketValue;
            (*holdingMap)["total"] += marketValue;
        }
        (*holdingMap)["dateTime"] = (*currentHoldings)["dateTime"] + 1;
        (*holdingMap)["cash"] = (*currentHoldings)["cash"];
        (*holdingMap)["commission"] = (*currentHoldings)["commission"];
        currentHoldings = holdingMap;
        allHoldings->push_back(holdingMap);
    }
}
void NaivePortfolio::updatePositionsFill(FillEvent* fillEvent) {
    int fillDirection = 0;
    if (fillEvent->getDirection()) {
        fillDirection = 1;
    } else {
        fillDirection = -1;
    }
    (*currentPositions)[fillEvent->getTicker()] += fillDirection * fillEvent->getQuantity();
}
void NaivePortfolio::updateHoldingsFill(FillEvent* fillEvent) {
    int fillDirection = 0;
    if (fillEvent->getDirection()) {
        fillDirection = 1;
    } else {
        fillDirection = -1;
    }
    double fillCost = dataHandler->getLatestData(fillEvent->getTicker())->close;
    double totalCost = fillDirection * fillCost * fillEvent->getQuantity();
    (*currentHoldings)[fillEvent->getTicker()] += totalCost;
    (*currentHoldings)["commission"] += fillEvent->getCommission();
    (*currentHoldings)["cash"] -= totalCost * fillEvent->getCommission();
    (*currentHoldings)["total"] -= totalCost * fillEvent->getCommission();
}
// Updates both positions and holdings
void NaivePortfolio::updateFill(Event* event) {
    if (event->type == "FILL") {
        updatePositionsFill(static_cast<FillEvent *>(event));
        updateHoldingsFill(static_cast<FillEvent *>(event));
    }
}
OrderEvent* NaivePortfolio::generateOrder(SignalEvent* signal, int quantity) {
    std::string ticker = signal->getSymbol();
    OrderEvent* orderEvent = nullptr;
    int t = (*currentPositions)[ticker];
    if (signal->getSignalType() == "LONG" && t == 0) {
        orderEvent = new OrderEvent(ticker, "MKT", quantity, "BUY");
    }
    if (signal->getSignalType() == "SHORT" && t == 0) {
        orderEvent = new OrderEvent(ticker, "MKT", quantity, "SELL");
    }
    if (signal->getSignalType() == "EXIT" && t > 0) {
        orderEvent = new OrderEvent(ticker, "MKT", abs(t), "SELL");
    }
    if (signal->getSignalType() == "EXIT" && t < 0) {
        orderEvent = new OrderEvent(ticker, "MKT", abs(t), "BUY");
    }
    return orderEvent;
}
void NaivePortfolio::updateSignal(Event* event) {
    if (event->getType() == "SIGNAL") {
        OrderEvent *orderEvent = generateOrder(static_cast<SignalEvent *>(event), 100);
        if (orderEvent != nullptr) {
            this->dataHandler->getEventQueue()->push(orderEvent);
        }
    }
}