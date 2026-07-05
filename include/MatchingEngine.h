#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include "./Orderbook.h"
class MatchingEngine{
    Orderbook orderbook;
    public:
    MatchingEngine(size_t capacity);
    void cancelOrder(OrderId orderId);
    void processOrder(Order &order);
    Orderbook& getOrderbook();
};

#endif