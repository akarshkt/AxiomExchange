#ifndef TRADELOGS_H
#define TRADELOGS_H
#include <cstddef>
#include <vector>
#include <iostream>
#include "Trade.h"
#include "Ringbuffer.h"
#include "./utils/TimeUtils.h"
enum struct EVENT{
    ORDER,
    CANCEL,
    TRADE,
    ERROR
};
class Logger
{
private:
    size_t totalTradeLog;
    Ringbuffer<Trade> ringbuffer;

public:
    Logger(size_t capacity);
    void logTrade(Trade &trade);
    void logOrder(Order &order);
    void logCancelOrder(Order &order);
    void writeToDisk(Trade &trade,EVENT event);
    void writeToDisk(Order &order,EVENT event);
    void print();
};

#endif
