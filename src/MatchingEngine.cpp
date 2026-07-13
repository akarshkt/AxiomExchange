#include "../include/MatchingEngine.h"
#include "../include/ExecutionPlan.h"
// Orderbook orderbook;
MatchingEngine::MatchingEngine(size_t capacity) : ringbuffer(capacity)
{
}
ProcessResult MatchingEngine::executePlan(ExecutionPlan& plan,Order& order){
    ProcessResult res;
    res.processOriginalOrder(order,order.remainingQuantity);
    if((order.timeInForce==TimeInForce::FOK && order.originalQuantity==plan.totalMatched)||
       (order.timeInForce != TimeInForce::FOK))
   { for(auto &it:plan.fills){
        
        Trade trade;
        if(order.side==Side::BUY)
        trade=Trade(
            order.orderId,  
             it.restingOrder->orderId,
             order.userId,
            it.restingOrder->userId,
            it.price,
            it.quantity,
            getTimestamp()
        );
        else
        trade=Trade(
            it.restingOrder->orderId,
            order.orderId,  
            it.restingOrder->userId,
            order.userId,
            it.price,
            it.quantity,
            getTimestamp()
        );
        res.processTrade(trade,order,it.quantity);
        order.remainingQuantity-=it.quantity;
        it.restingOrder->remainingQuantity-=it.quantity;
        // if(it.restingOrder->remainingQuantity==0)
        // it.restingOrder->setOrderStatus(OrderStatus::FILLED);
        // else
        // it.restingOrder->setOrderStatus(OrderStatus::PARTIALLY_FILLED);

        if(it.restingOrder->remainingQuantity==0)
        orderbook.removeOrder(it.restingOrder->orderId);
    }
    // if(plan.totalMatched==order.remainingQuantity)
    // order.setOrderStatus(OrderStatus::FILLED);
    // else
    // order.setOrderStatus(OrderStatus::PARTIALLY_FILLED);
    if(order.timeInForce==TimeInForce::GTC && order.orderStatus!=OrderStatus::FILLED && order.orderStatus!=OrderStatus::CANCELLED)
    orderbook.addOrder(order);
}else{
    order.setOrderStatus(OrderStatus::CANCELLED);
}
    return res;
}
ProcessResult MatchingEngine::processOrder(Order& order)
{

    // logger.logOrder(order);
    
    // OrderStatus originalOrderStatus=order.orderStatus;
    // Quantity originalRemainingQuantity=order.remainingQuantity;
    ExecutionPlan plan = orderbook.matchOrder(order);
    // for(auto it:plan.fills){
    //     std::cout<<it.restingOrder->orderId<<"  "<<std::endl;
    // }
    ProcessResult res=executePlan(plan,order);
        ringbuffer.pushListOfTrades(res.trades);
        // std::cout<<res.trades.size()<<std::endl;
    // if (originalOrderStatus != order.orderStatus || originalRemainingQuantity != order.remainingQuantity)
    //     logger.logOrder(order);
    // for (auto &it : res.reports)
    // {
    //     if (it.orderId != order->orderId)
    //     {
    //         Order* logOrder = orderbook.orderLookup(it.orderId);
        
    //         // logger.logOrder(logOrder);
    //         if(logOrder->remainingQuantity==0)
    //         orderbook.removeOrder(logOrder->orderId);
    //     }
     
    // }
    // logger.logTrades(res.trades);
    return res;
}
void MatchingEngine::cancelOrder(OrderId orderId)
{
    orderbook.cancelOrder(orderId);
}

// public:
Orderbook &MatchingEngine::getOrderbook()
{
    return orderbook;
}
Ringbuffer &MatchingEngine::getRingbuffer()
{
    return ringbuffer;
}
Logger &MatchingEngine::getLogger()
{
    return logger;
}
// };