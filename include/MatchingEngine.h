#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include "./Orderbook.h"
class MatchingEngine{
    Orderbook orderbook;
    public:
    void processOrder(Order &order);
    Orderbook getOrderbook();
};

#endif