#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <map>
#include <unordered_map>
#include <list>
#include "Order.h"
#include <algorithm>
#include "Trade.h"
#include "Logger.h"
#include "./utils/TimeUtils.h"
class Orderbook
{
    Logger logger;

public:
    Orderbook(size_t capacity);
    std::map<Price, std::list<Order>> asks;
    std::map<Price, std::list<Order>> bids;
    std::unordered_map<OrderId, OrderLocation> orderIndex;
    void addOrder(Order &order);
    void cancelOrder(OrderId orderId);
    void matchOrder(Order &order);
    void matchOrderLimit(Order &order);
    void matchOrderMarket(Order &order);
    void matchOrderStop(Order &order);
    Logger& getLogger();
    Order orderLookup(OrderId orderId);
    void removeOrder(OrderId orderId, Side side);
};

#endif
