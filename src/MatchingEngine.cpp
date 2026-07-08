#include "../include/MatchingEngine.h"

// Orderbook orderbook;
MatchingEngine::MatchingEngine(size_t capacity) : ringbuffer(capacity) {
   
}
ProcessResult MatchingEngine::processOrder(Order &order)
{
   
   ProcessResult res = orderbook.matchOrder(order);
   ringbuffer.pushListOfTrades(res.trades);
   return res;
}
void MatchingEngine::cancelOrder(OrderId orderId)
{
    orderbook.cancelOrder(orderId);
}

// public:
Orderbook& MatchingEngine::getOrderbook()
{
    return orderbook;
}
Ringbuffer& MatchingEngine::getRingbuffer(){
    return ringbuffer;
}
// };