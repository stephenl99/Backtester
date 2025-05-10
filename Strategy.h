#pragma once
#include <unordered_map>
#include "DataHandler.h"


class Strategy {
public:
    virtual ~Strategy() = default;

    virtual std::unordered_map<std::string, bool> calculate_symbols() = 0;
};
class BuyHoldStrategy : public Strategy {
    public:
    DataHandler* bars;
    std::queue<MarketEvent> events;
    BuyHoldStrategy(DataHandler* dh, std::queue<MarketEvent> eventQueue);
    std::unordered_map<std::string, bool> calculate_initial_bought();
    std::unordered_map<std::string, bool> calculate_symbols() override;
};

