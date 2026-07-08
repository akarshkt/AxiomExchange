#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H
#include "./Orderbook.h"
// #include "./ProcessResult.h"
#include "./Ringbuffer.h"
class MatchingEngine{
    public:
    Orderbook orderbook;
    Logger logger;
    Ringbuffer ringbuffer;
    public:
     MatchingEngine(size_t capacity);
    void cancelOrder(OrderId orderId);
    ProcessResult processOrder(Order &order);
    Orderbook& getOrderbook();
    Ringbuffer& getRingbuffer();

};

#endif