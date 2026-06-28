#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <map>
#include <vector>
#include "Order.h"
#include <algorithm>
class Orderbook{
    public:
    std::map<Price,std::vector<Order>> asks;
    std::map<Price,std::vector<Order>> bids;

    void addOrder(Order &order);
    void cancelOrder(OrderId orderId);
    void matchOrder(Order &order);
    public:
    Order orderLookup(OrderId orderId);
    void removeOrder(OrderId orderId, Side side);

};

#endif
