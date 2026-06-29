#include "../include/MatchingEngine.h"
#include <iostream>

int32_t main(){
    MatchingEngine engine;
    Order order1(1,OrderType::LIMIT,2,10,Side::BUY,20);
    Order order2(2,OrderType::LIMIT,2,10,Side::BUY,25);
    Order order3(3,OrderType::LIMIT,2,10,Side::BUY,30);
    Order order4(4,OrderType::LIMIT,2,10,Side::BUY,35);
    Order order5(5,OrderType::LIMIT,2,10,Side::BUY,40);
    Order order6(6,OrderType::LIMIT,2,81,Side::BUY,40);
    Order order7(7,OrderType::LIMIT,2,10,Side::SELL,20);
    Order order8(8,OrderType::LIMIT,2,10,Side::SELL,25);
    Order order9(9,OrderType::LIMIT,2,5,Side::SELL,30);
    engine.processOrder(order1);
    engine.processOrder(order2);
    engine.processOrder(order3);
    engine.processOrder(order4);
    engine.processOrder(order5);
    engine.processOrder(order6);
    engine.processOrder(order7);
    engine.processOrder(order8);
    engine.processOrder(order9);
    engine.cancelOrder(order6.orderId);
    Orderbook orderbook=engine.getOrderbook();
    for(auto &it:orderbook.asks){
        for(auto &ti:it.second){
            std::cout<<it.first<<"  "<<ti.remainingQuantity<<"   "<<ti.originalQuantity<<"   "<<ti.userId<<std::endl;
        }
    }
    for(auto &it:orderbook.bids){
        for(auto &ti:it.second){
             std::cout<<it.first<<"  "<<ti.remainingQuantity<<"   "<<ti.originalQuantity<<"   "<<ti.userId<<std::endl;
        }
    }
}