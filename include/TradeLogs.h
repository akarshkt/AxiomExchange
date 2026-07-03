#ifndef TRADELOGS_H
#define TRADELOGS_H
#include <cstddef>
#include <vector>
#include <iostream>
#include "Trade.h"
#include "Ringbuffer.h"

class TradeLogs
{
private:
    size_t totalTradeLog;
    Ringbuffer<Trade> ringbuffer;

public:
    TradeLogs(size_t capacity);
    void logTrade(Trade trade);
    void writeToDisk(Trade trade);
    void print();   
};

#endif
