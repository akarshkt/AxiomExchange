#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include "./Trade.h"

class Ringbuffer
{
private:
    std::vector<Trade> trades;
    size_t tail = 0;
    size_t head = 0;
    size_t capacity;
    size_t count = 0;

public:
    Ringbuffer(size_t n) : capacity(n)
    {
        trades.resize(n);
    }

    void push(Trade trade);
    void pushListOfTrades(std::vector<Trade>& trades);
    void print();


    Trade returnTrade();
    size_t size();
    std::vector<Trade>& getTrades();
   
};

#endif
