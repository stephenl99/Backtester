#include<string>
#include <utility>
class Event {
    private:
        std::string type;
    public:
    std::string getType() {
        return type;
    }
    void setType(std::string type) {
        this->type = std::move(type);
    }
};

class MarketEvent : public Event {
    public:
    MarketEvent() {
        setType("MarketEvent");
    }
};

class SignalEvent : public Event {
    private:
        std::string symbol;
        int day;
        std::string signalType;


    public:
    SignalEvent(std::string symbol, int day, std::string signalType) {
        setType("SignalEvent");
        this->symbol = std::move(symbol);
        this->day = day;
        this->signalType = std::move(signalType);
    }
};

class OrderEvent : public Event {
private:
    std::string symbol;
    std::string orderType;
    int quantity;
    bool buy; // If true buy, if false sell


public:
    OrderEvent(std::string symbol, std::string orderType, int quantity, bool buy) {
        setType("OrderEvent");
        this->symbol = std::move(symbol);
        this->orderType = std::move(orderType);
        this->quantity = quantity;
        this->buy = buy;
    }
};