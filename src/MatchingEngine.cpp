#include "../include/MatchingEngine.h"

    Orderbook orderbook;

    void MatchingEngine::processOrder(Order &order){
        orderbook.matchOrder(order);
    }
    // public:
    Orderbook MatchingEngine::getOrderbook(){
        return orderbook;
    }
// };