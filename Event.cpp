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
    int timeStamp;
    std::string signalType;


    public:
    SignalEvent(std::string symbol, int timwStamp, std::string signalType) {
        setType("SignalEvent");
        this->symbol = std::move(symbol);
        this->timeStamp = timeStamp;
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

class FillEvent : public Event {
    private:
    std::string symbol;
    int timestamp;
    std::string exchange;
    int quantity;
    bool buy;
    double cost;
    double commission;
    public:
    FillEvent(std::string symbol, int timestamp, int quantity, bool buy, double cost) {
        setType("FillEvent");
        this->symbol = std::move(symbol);
        this->timestamp = timestamp;
        this->quantity = quantity;
        this->buy = buy;
        this->cost = cost;
    }
    double getCommission() {
        double temp = 1.3;
        if (quantity <= 500) {
            temp = std::max(temp, .013 * quantity);
        } else {
            temp = std::max(temp, .008 * quantity);
        }
        return temp;
    }
};
