#include "Strategy.h"

BuyHoldStrategy::BuyHoldStrategy(DataHandler* dh) {
    this->bars = dh;
    this->events = new std::queue<Event*>;
}
// Sets each bought value to false since we don't own anything initially
std::unordered_map<std::string, bool> BuyHoldStrategy::calculateInitialBought() {
    std::unordered_map<std::string, bool> temp;
    for (std::string ticker : tickers) {
        temp[ticker] = false;
    }
    return temp; // Create new map and pass it to bought
}
// Stupid strategy to buy if not bought
void BuyHoldStrategy::calculateSignals(Event* event) {
    if (event->getType() == "MarketEvent") {
        this->bars->updateBars();
        for (std::string ticker : tickers) {
            if (bought[ticker] == false) {
                SignalEvent* signal = new SignalEvent(ticker, this->bars->getTimestamp(), "LONG");
                events->push(signal);
                bought[ticker] = true;
            }
        }
    }
}