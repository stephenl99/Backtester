#include "Portfolio.h"
#include "Global.h"
NaivePortfolio::NaivePortfolio(HistoricDataHandler *dh, int startTimestamp, double initialCapital, std::vector<std::string> relevantTickers) {
    this->dataHandler = dh;
    this->startDate = startTimestamp;
    this->initialCapital = initialCapital;
    this->relevantTickers = relevantTickers; // Tickers we are considering, may be able to remove
}
std::vector<std::unordered_map<std::string, int>> NaivePortfolio::initAllPositions() const {
    std::unordered_map<std::string, int> map;
    for (std::string ticker : tickers) {
        map[ticker] = 0;
    }
    map["dateTime"] = this->startDate; // start date added for reference
    std::vector<std::unordered_map<std::string, int>> vector;
    vector.push_back(map);
    return vector;
}
std::unordered_map<std::string, int> NaivePortfolio::initCurrentPositions() {
    std::unordered_map<std::string, int> map;
    for (std::string symbol : tickers) {
        map[symbol] = 0;
    }
    return map;
}
std::vector<std::unordered_map<std::string, int>> NaivePortfolio::initAllHoldings() {
    std::unordered_map<std::string, int> map;
    for (std::string symbol : tickers) {
        map[symbol] = 0;
    }
    map["dateTime"] = this->startDate;
    map["cash"] = this->initialCapital;
    map["commission"] = 0.0;
    map["total"] = this->initialCapital;
    std::vector<std::unordered_map<std::string, int>> vector;
    vector.push_back(map);
    return vector;
}
std::unordered_map<std::string, int> NaivePortfolio::initCurrentHoldings() {
    std::unordered_map<std::string, int> map;
    for (std::string symbol : tickers) {
        map[symbol] = 0;
    }
    map["dateTime"] = this->startDate;
    map["cash"] = this->initialCapital;
    map["commission"] = 0.0;
    map["total"] = this->initialCapital;
    return map;
}
// Decided to all tickers may wish to change to relevant tickers eventually
//updates the positions and holdings for next day
void NaivePortfolio::updateTime(Event* event) {
    dataHandler->updateBars(); // Might be off by one on timestamp check
    std::unordered_map<std::string, int> positionMap;
    for (std::string ticker : tickers) {
        positionMap[ticker] = currentPositions[ticker];
    }
    positionMap["dateTime"] = dataHandler->getTimestamp() - 1;
    allPositions.push_back(positionMap);

    std::unordered_map<std::string, int> holdingMap;
    for (std::string ticker : tickers) {
        double marketValue = currentPositions[ticker] * dataHandler->getLatestData(ticker)->close; // Currently using close value could update to open
        holdingMap[ticker] = marketValue;
        holdingMap["total"] += marketValue;
    }
    allHoldings.push_back(holdingMap);
}
void NaivePortfolio::updatePositionsFill(FillEvent* fillEvent) {
    int fillDirection = 0;
    if (fillEvent->getDirection()) {
        fillDirection = 1;
    } else {
        fillDirection = -1;
    }
    currentPositions[fillEvent->getTicker()] += fillDirection * fillEvent->getQuantity();
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
    currentHoldings[fillEvent->getTicker()] += totalCost;
    currentHoldings["commission"] += fillEvent->getCommission();
    currentHoldings["cash"] -= totalCost * fillEvent->getCommission();
    currentHoldings["total"] -= totalCost * fillEvent->getCommission();
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
    OrderEvent* orderEvent;
    if (signal->getType() == "LONG" && currentPositions[ticker] == 0) {
        orderEvent = new OrderEvent(ticker, "MKT", quantity, "BUY");
    }
    if (signal->getType() == "SHORT" && currentPositions[ticker] == 0) {
        orderEvent = new OrderEvent(ticker, "MKT", quantity, "SELL");
    }
    if (signal->getType() == "EXIT" && currentPositions[ticker] > 0) {
        orderEvent = new OrderEvent(ticker, "MKT", abs(currentPositions[ticker]), "SELL");
    }
    if (signal->getType() == "EXIT" && currentPositions[ticker] < 0) {
        orderEvent = new OrderEvent(ticker, "MKT", abs(currentPositions[ticker]), "BUY");
    } else {
        throw std::invalid_argument("Invalid creation of order");
    }
    return orderEvent;
}
void NaivePortfolio::updateSignal(Event* event) {
    if (event->getType() == "SIGNAL") {
        OrderEvent *orderEvent = generateOrder(static_cast<SignalEvent *>(event), 100);
        this->dataHandler->getEventQueue()->push(orderEvent);
    }
}