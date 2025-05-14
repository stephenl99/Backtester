#include "DataHandler.h"
// Retrieves timestamp of this data handler
int DataHandler::getTimestamp() const {
    return timestamp;
}
bool DataHandler::getContinueExecution() const {
    return this->continueBacktest;
}
HistoricDataHandler::HistoricDataHandler() {
    timestamp = 0;
    events = new std::queue<Event*>;
    latestData = new std::unordered_map<std::string, Day*>;
    // symbolList = new std::vector<std::string>;
}

// Gets the data from the next sequential day
Day* HistoricDataHandler::getLatestData(std::string symbol) {
    Day* day = &(*stockMap)[symbol][this->timestamp];
    return day;
}
//Updates the bars for the current strategy
void HistoricDataHandler::updateBars() {
    if (timestamp == maxTimestamp - 5) {
        this->continueBacktest = false;
    }
    for (const std::string& ticker : tickers) {
        (*this->latestData)[ticker] = getLatestData(ticker);
    }
    this->timestamp++;
    auto* marketEvent = new MarketEvent();
    this->events->push(marketEvent); // Pushes next market event to end of queue
}
std::queue<Event*>* HistoricDataHandler::getEventQueue() const {
    return this->events;
}
void HistoricDataHandler::setEventQueue(std::queue<Event*>* events) {
    this->events = events;
}