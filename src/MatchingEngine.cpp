#include "../include/MatchingEngine.h"

    Orderbook orderbook;

    void MatchingEngine::processOrder(Order &order){
        orderbook.matchOrder(order);
    }
    void MatchingEngine::cancelOrder(OrderId orderId){
        orderbook.cancelOrder(orderId);
    }
    // public:
    Orderbook MatchingEngine::getOrderbook(){
        return orderbook;
    }
// };