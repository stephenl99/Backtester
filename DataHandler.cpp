#include "DataHandler.h"
#include "Event.h"

class HistoricDataHandler : public DataHandler {
    // Timestamp is days since start of historic data
    Day getLatestData(std::string symbol, int timestamp) override {
        Day day = stockMap[symbol][timestamp];
        return day;
    }
    void updateBars(int timestamp) {
        for (string ticker : tickers) {
            latestData[ticker] = getLatestData(ticker, timestamp);
        }
        eventQueue.push(new MarketEvent())
    }
};