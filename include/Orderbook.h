#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <map>
#include <unordered_map>
#include <list>
#include "Order.h"
#include <algorithm>
class Orderbook{
    public:
    std::map<Price,std::list<Order>> asks;
    std::map<Price,std::list<Order>> bids;
    std::unordered_map<OrderId,OrderLocation> orderIndex;
    void addOrder(Order &order);
    void cancelOrder(OrderId orderId);
    void matchOrder(Order &order);
    void matchOrderLimit(Order &order);
    void matchOrderMarket(Order &order);
    void matchOrderStop(Order &order);
    public:
    Order orderLookup(OrderId orderId);
    void removeOrder(OrderId orderId, Side side);

};

#endif
