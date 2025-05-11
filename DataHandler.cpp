#pragma once
#include "DataHandler.h"
#include "Event.h"
// Gets the data from the next sequential day
Day HistoricDataHandler::getLatestData(std::string symbol, int timestamp) override {
    Day day = stockMap[symbol][timestamp];
    return day;
}
//Updates the bars for the current strategy
void HistoricDataHandler::updateBars() {
    for (std::string ticker : tickers) {
        this->latestData[ticker] = getLatestData(ticker, timestamp);
    }
    MarketEvent* marketEvent = new MarketEvent();
    this->events.push(*marketEvent); // Pushes next market event to end of queue
}
