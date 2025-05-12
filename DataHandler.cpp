#include "DataHandler.h"
// Retrieves timestamp of this data handler
int DataHandler::getTimestamp() const {
    return timestamp;
}
HistoricDataHandler::HistoricDataHandler() {
    timestamp = 0;
    events = new std::queue<Event>;
    latestData = new std::unordered_map<std::string, Day>;
    symbolList = new std::vector<std::string>;
}

// Gets the data from the next sequential day
Day* HistoricDataHandler::getLatestData(std::string* symbol) {
    Day* day = &(*stockMap)[*symbol][this->timestamp];
    return day;
}
//Updates the bars for the current strategy
void HistoricDataHandler::updateBars() {
    for (std::string ticker : tickers) {
        (*this->latestData)[ticker] = *getLatestData(&ticker);
    }
    this->timestamp++;
    const MarketEvent* marketEvent = new MarketEvent();
    this->events->push(*marketEvent); // Pushes next market event to end of queue
}
