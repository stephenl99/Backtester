
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include "DataHandler.h"
#include "Event.h"

class Portfolio {
    public:
    virtual ~Portfolio() = default;

    virtual void updateSignal(Event* event) = 0;
    virtual void updateFill(Event* event) = 0;
};

class NaivePortfolio : public Portfolio {
private:
    HistoricDataHandler* dataHandler; // Historic for now, update later for more data handlers
    int startDate; // start date starting at 0
    double initialCapital;
    std::vector<std::string> relevantTickers;
    std::vector<std::unordered_map<std::string, int>> allPositions = initAllPositions();
    std::unordered_map<std::string, int> currentPositions = initCurrentPositions();
    std::vector<std::unordered_map<std::string, int>> allHoldings = initAllHoldings();
    std::unordered_map<std::string, int> currentHoldings = initCurrentHoldings();
public:
    NaivePortfolio(HistoricDataHandler* dh, std::queue<Event>* events, int startTimestamp = 0, double initialCapital = 10000.0, std::vector<std::string> relevantTickers);
    std::vector<std::unordered_map<std::string, int>> initAllPositions() const;
    std::unordered_map<std::string, int> initCurrentPositions();
    std::vector<std::unordered_map<std::string, int>> initAllHoldings();
    std::unordered_map<std::string, int> initCurrentHoldings();
    void updateTime(Event* event);
    void updatePositionsFill(FillEvent* fillEvent);
    void updateHoldingsFill(FillEvent* fillEvent);
    OrderEvent* generateOrder(SignalEvent* signal, int quantity = 100);
    // void createDataframe() // TBD IF ACTUALLY WANT TO DO

};


#endif //PORTFOLIO_H
