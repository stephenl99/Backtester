#pragma once
#include <unordered_map>
#include "DataHandler.h"

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void calculateSignals(Event* event) = 0; // Determines the moves
};
class BuyHoldStrategy : public Strategy {
    public:
    DataHandler* bars; // DH to caculate bars
    std::queue<Event *> * events; // Event queue
    std::unordered_map<std::string, bool>* bought = calculateInitialBought(); // Maps each security to whether we own it
    explicit BuyHoldStrategy(DataHandler* dh);
    std::unordered_map<std::string, bool>* calculateInitialBought(); // Get initial portfolio
    void calculateSignals(Event* event); //
};

