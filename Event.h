
#ifndef EVENT_H
#define EVENT_H
class Event {
    public:
    std::string type;
    std::string getType() const;
    void setType(std::string type);
};

class MarketEvent : public Event {
public:
    MarketEvent();
};

class SignalEvent : public Event {
private:
    std::string symbol;
    int timeStamp;
    std::string signalType;
public:
    SignalEvent(std::string symbol, int timeStamp, std::string signalType);

    std::string getSignalType();
    std::string getSymbol();
};

class OrderEvent : public Event {
private:
    std::string symbol;
    std::string orderType;
    int quantity;
    bool buy; // If true buy, if false sell
public:
    OrderEvent(std::string symbol, std::string orderType, int quantity, bool buy);

    std::string getTicker();

    int getQuantity();

    bool getDirection();
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
    FillEvent(std::string symbol, int timestamp, int quantity, std::string exchange, bool buy, double cost);
    double getCommission() const;
    bool getDirection();

    std::string getTicker();

    int getQuantity();
};
#endif //EVENT_H
