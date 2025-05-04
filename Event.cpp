#include<string>
#include "Event.h"
#include <utility>

std::string Event::getType() const {
        return type;
}
void Event::setType(std::string type) {
    this->type = std::move(type);
}

MarketEvent::MarketEvent() {
    setType("MarketEvent");
}
SignalEvent::SignalEvent(std::string symbol, int timeStamp, std::string signalType) {
    setType("SignalEvent");
    this->symbol = std::move(symbol);
    this->timeStamp = timeStamp;
    this->signalType = std::move(signalType);
}

OrderEvent::OrderEvent(std::string symbol, std::string orderType, int quantity, bool buy) {
    setType("OrderEvent");
    this->symbol = std::move(symbol);
    this->orderType = std::move(orderType);
    this->quantity = quantity;
    this->buy = buy;
}


FillEvent::FillEvent(std::string symbol, int timestamp, int quantity, bool buy, double cost) {
    setType("FillEvent");
    this->symbol = std::move(symbol);
    this->timestamp = timestamp;
    this->quantity = quantity;
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
