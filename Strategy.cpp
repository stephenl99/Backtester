#include "Strategy.h"

BuyHoldStrategy::BuyHoldStrategy(DataHandler* dh, std::queue<MarketEvent> eventQueue) {
    this->bars = dh;
    this->events = eventQueue;
}