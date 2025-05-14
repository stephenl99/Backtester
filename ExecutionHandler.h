

#ifndef EXECUTIONHANDLER_H
#define EXECUTIONHANDLER_H
#include <queue>

#include "Event.h"
#include"DataHandler.h"
//I think i must include data handler in order to access current time in datahandler, as opposed to actual current time

class ExecutionHandler {
public:
    virtual ~ExecutionHandler() = default;

private:
    virtual void executeOrder(Event* event) = 0;
};

class NoLatencyExecutionHandler : public ExecutionHandler {
    std::queue<Event *>* eventQueue;
    DataHandler *dataHandler;
public:
    NoLatencyExecutionHandler(DataHandler* dataHandler);
    void ExecuteOrder(Event *event) const;
};


#endif //EXECUTIONHANDLER_H
