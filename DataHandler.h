#pragma once
#include "Main.h"
#include "Data.h"
class DataHandler {
public:
    virtual ~DataHandler() = default;

    virtual Day getLatestData(std::string symbol, int timestamp) = 0;
    virtual void updateBars(int timestamp) = 0;
};

class HistoricDataHandler : public DataHandler {
    // Timestamp is days since start of historic data
    Day getLatestData(std::string symbol, int timestamp) override;
    void updateBars(int timestamp) override;
};