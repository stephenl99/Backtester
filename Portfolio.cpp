#include "Portfolio.h"
#include "Global.h"
NaivePortfolio::NaivePortfolio(HistoricDataHandler *dh, std::queue<Event> *events, int startTimestamp, double initialCapital, std::vector<std::string> relevantTickers) {
    this->dataHandler = dh;
    this->startDate = startTimestamp;
    this->dataHandler->setEventQueue(events);
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