#pragma once
#include "Main.h"
#include "Data.h"
class DataHandler {
public:
    virtual Day getLatestData(std::string symbol, int numDays) = 0;
    virtual void updateBars() = 0;
};
