#pragma once
#include "DataHandler.h"
#include "Event.h"

Day HistoricDataHandler::getLatestData(std::string symbol, int timestamp) override {
    Day day = stockMap[symbol][timestamp];
    return day;
}
void HistoricDataHandler::updateBars(int timestamp) {
    for (std::string ticker : tickers) {
        latestData[ticker] = getLatestData(ticker, timestamp);
    }
    MarketEvent* marketEvent = new MarketEvent();
    eventQueue.push(*marketEvent);
}
