#include "Strategy.h"

BuyHoldStrategy::BuyHoldStrategy(DataHandler* dh, std::queue<Event*> events) {
    this->bars = dh;
    this->events = events;
}
// Sets each bought value to false since we don't own anything initially
std::unordered_map<std::string, bool> BuyHoldStrategy::calculateInitialBought() {
    for (std::string ticker : tickers) {
        this->bought[ticker] = false;
    }
    return this->bought;
}
// Stupid strategy to buy if not bought
void BuyHoldStrategy::calculateSignals(Event* event) {
    if (event->getType() == "MarketEvent") {
        this->bars->updateBars();
        for (std::string ticker : tickers) {
            if (bought[ticker] == false) {
                SignalEvent* signal = new SignalEvent(ticker, this->bars->getTimestamp(), "LONG");
                events.push(signal);
                bought[ticker] = true;
            }
        }
    }
}