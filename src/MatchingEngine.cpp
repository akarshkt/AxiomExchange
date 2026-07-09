#include "../include/MatchingEngine.h"

// Orderbook orderbook;
MatchingEngine::MatchingEngine(size_t capacity) : ringbuffer(capacity) {
   
}
ProcessResult MatchingEngine::processOrder(Order &order)
{
   
   logger.logOrder(order);
   Order copy=order;
   ProcessResult res = orderbook.matchOrder(order);
   ringbuffer.pushListOfTrades(res.trades);
   if(copy.orderStatus!=order.orderStatus || copy.remainingQuantity!=order.remainingQuantity) 
   logger.logOrder(order);
   std::cout<<"Size"<<res.reports.size()<<std::endl;
   for(auto& it:res.reports){
    std::cout<<it.orderId<<"   ";
    if(it.orderId !=order.orderId){
        Order logOrder=orderbook.orderLookup(it.orderId);
        std::cout<<logOrder.orderId<<"   ";
        logger.logOrder(logOrder);
        
    }
   }
   logger.logTrades(res.trades);
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