#pragma once
#include "Main.h"
#include "Data.h"
class DataHandler {
public:
    virtual ~DataHandler() = default;

    virtual Day getLatestData(std::string symbol, int timestamp) = 0;
    virtual void updateBars(int timestamp) = 0;
};
