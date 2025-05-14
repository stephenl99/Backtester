
#include "ExecutionHandler.h"


NoLatencyExecutionHandler::NoLatencyExecutionHandler(DataHandler* dataHandler) {
    this->eventQueue = dataHandler->getEventQueue();
    this->dataHandler = dataHandler;
}
// Converts Order into fill
void NoLatencyExecutionHandler::ExecuteOrder(Event* event) const {
    if (event->getType() == "ORDER") {
        OrderEvent* orderEvent = static_cast<OrderEvent*>(event);
        FillEvent* fillEvent = new FillEvent(orderEvent->getTicker(), dataHandler->getTimestamp(), orderEvent->getQuantity(), "ARCA", orderEvent->getDirection(), 0.0); // Initialize cost to 0.0
        eventQueue->push(fillEvent);
    }
}
