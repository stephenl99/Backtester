#include<string>
#include "Event.h"

std::string Event::getType() const {
        return type;
}
void Event::setType(std::string type) {
    this->type = std::move(type);
}
MarketEvent::MarketEvent() {
    setType("MARKET");
}
SignalEvent::SignalEvent(std::string symbol, int timeStamp, std::string signalType) {
    setType("SIGNAL");
    this->symbol = std::move(symbol);
    this->timeStamp = timeStamp;
    this->signalType = std::move(signalType);
}
std::string SignalEvent::getSignalType() {
    return this->signalType;
}
std::string SignalEvent::getSymbol() {
    return this->symbol;
}
OrderEvent::OrderEvent(std::string symbol, std::string orderType, int quantity, bool buy) {
    setType("ORDER");
    this->symbol = std::move(symbol);
    this->orderType = std::move(orderType);
    this->quantity = quantity;
    this->buy = buy;
}
std::string OrderEvent::getTicker() {
    return this->symbol;
}
int OrderEvent::getQuantity() {
    return this->quantity;
}
bool OrderEvent::getDirection() {
    return this->buy;
}

FillEvent::FillEvent(std::string symbol, int timestamp, int quantity, std::string exchange, bool buy, double cost) {
    setType("FILL");
    this->symbol = std::move(symbol);
    this->timestamp = timestamp;
    this->quantity = quantity;
    this->exchange = exchange;
    this->buy = buy;
    this->cost = cost;
    this->commission = getCommission();
}
double FillEvent::getCommission() const {
    double temp = 1.3;
    if (quantity <= 500) {
        temp = std::max(temp, .013 * quantity);
    } else {
        temp = std::max(temp, .008 * quantity);
    }
    return temp;
}
bool FillEvent:: getDirection() {
    return buy;
}
std::string FillEvent:: getTicker() {
    return symbol;
}
int FillEvent:: getQuantity() {
    return quantity;
}