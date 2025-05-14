#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "Data.h"
#include "Global.h"
#include "Event.h"
class DataHandler {
protected:
    int timestamp = 0;
public:
    virtual ~DataHandler() = default;
    int getTimestamp() const;
    virtual Day* getLatestData(std::string symbol) = 0;
    virtual void updateBars() = 0;
    virtual std::queue<Event*>* getEventQueue() const = 0;
};

class HistoricDataHandler : public DataHandler {
    // Timestamp is days since start of historic data
    std::queue<Event*>* events;
    std::unordered_map<std::string, Day>* latestData; // Contains the current bars
    // std::vector<std::string>* symbolList; // Unneeded
    bool continueBacktest = true;
public:
    HistoricDataHandler();
    std::queue<Event*>* getEventQueue() const override;
    void setEventQueue(std::queue<Event*> *events);
    Day* getLatestData(std::string symbol) override;
    void updateBars() override;
};
#endif
