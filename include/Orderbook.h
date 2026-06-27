#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <map>
#include <vector>
#include "Order.h"
#include <algorithm>
class Orderbook{

    std::map<Price,std::vector<Order>> asks;
    std::map<Price,std::vector<Order>> bids;

    void addOrder(Order order);
    void removeOrder(Order order);
    void matchOrder(Order order1);
    Order findOrder(Order order);

};

#endif
