#include "../include/Orderbook.h"
#include <iostream>

// Orderbook::Orderbook(size_t capacity) : {}//logger(capacity)

//logger& Orderbook::get//logger()
// {
//     return //logger;
// };
void Orderbook::addOrder(Order &order)
{
    Price price = order.price;

    auto &book = (order.side == Side::BUY ? bids : asks);
    book[price].push_back(order);
    orderIndex[order.orderId] = {order.side, price, --(book[price].end())};
    //logger.logOrder(order);
}
void Orderbook::removeOrder(OrderId orderId, Side side)
{
    auto &book = (side == Side::BUY) ? bids : asks;

    for (auto &[price, orders] : book)
    {
        for (auto it = orders.begin(); it != orders.end(); ++it)
        {

            if (it->orderId == orderId)
            {
                std::cout << "ORDER REMOVED  " << std::endl;
                std::cout << "DELETED :" << it->userId << "   " << it->price << "   " << it->originalQuantity << std::endl;

                orders.erase(it);
                return;
            }
        }
    }
}
void Orderbook::cancelOrder(OrderId orderId)
{

    auto loc = orderIndex[orderId];
    auto &book = loc.side == Side::BUY ? bids : asks;

    loc.it->orderStatus = OrderStatus::CANCELLED;
    // //logger.logCancelOrder(*(loc.it));
    book[loc.price].erase(loc.it);
}

Order Orderbook::orderLookup(OrderId orderId)
{
    for (auto &it : bids)
    {
        for (auto &ti : it.second)
        {
            if (ti.orderId == orderId)
            {
                return ti;
            }
        }
    }

    for (auto &it : asks)
    {
        for (auto &ti : it.second)
        {
            if (ti.orderId == orderId)
            {
                return ti;
            }
        }
    }
    Order order1(1, OrderType::MARKET, 2, 10, Side::BUY, 20);
    return order1;
}
ProcessResult Orderbook::matchOrderLimit(Order &order)
{
    ProcessResult processResult;
    size_t beforeMatchRemainingQuantity=order.remainingQuantity;
    if (order.side == Side::BUY)
    {
        bool val = true;
        for (auto &it : asks)
        {
            if (it.first <= order.price)
            {
                auto &orders = it.second;

                for (auto orderIt = orders.begin();
                     orderIt != orders.end();)
                {
                    Quantity traded =
                        std::min(order.remainingQuantity,
                                 orderIt->remainingQuantity);

                    order.remainingQuantity -= traded;
                    orderIt->remainingQuantity -= traded;
                    // Timestamp currTimestamp=;
                    Trade newTrade(order.orderId, orderIt->orderId, order.userId, orderIt->userId, it.first, traded, getTimestamp());
                    //logger.logTrade(newTrade);
                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt->setOrderStatus(OrderStatus::FILLED);
                        //logger.logOrder(*orderIt);       // Log FIRST while memory is valid
                        processResult.processTrade(newTrade,*orderIt,traded);
                        orderIt = orders.erase(orderIt); // Erase SECOND
                    }
                    else
                    {
                        orderIt->setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                        //logger.logOrder(*orderIt); // Log FIRST
                        processResult.processTrade(newTrade,*orderIt,traded);
                        ++orderIt;                 // Advance SECOND
                    }
                   
                    if (order.remainingQuantity == 0)
                    {
                        order.setOrderStatus(OrderStatus::FILLED);
                        val = false;
                        processResult.processOriginalOrder(order,traded);
                        break;
                    }
                    else
                    {
                        order.setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                        //logger.logOrder(order);
                    }
                }
            }
        }
        if (val)
        {
            if(beforeMatchRemainingQuantity!=order.remainingQuantity)
            processResult.processOriginalOrder(order,beforeMatchRemainingQuantity-order.remainingQuantity);
            addOrder(order);
        }
        return processResult;
    }
    else
    {
        bool val = true;
        for (auto &it : bids)
        {
            if (it.first >= order.price)
            {
                auto &orders = it.second;

                for (auto orderIt = orders.begin();
                     orderIt != orders.end();)
                {
                    Quantity traded =
                        std::min(order.remainingQuantity,
                                 orderIt->remainingQuantity);

                    order.remainingQuantity -= traded;
                    orderIt->remainingQuantity -= traded;
                    Trade newTrade( orderIt->orderId,order.orderId, orderIt->userId, order.userId, it.first, traded, getTimestamp());
                    // //logger.logTrade(newTrade);
                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt->setOrderStatus(OrderStatus::FILLED);
                        //logger.logOrder(*orderIt);       // Log FIRST while memory is valid
                        orderIt = orders.erase(orderIt); // Erase SECOND
                    }
                    else
                    {
                        orderIt->setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                        //logger.logOrder(*orderIt); // Log FIRST
                        ++orderIt;                 // Advance SECOND
                    }
                     processResult.processTrade(newTrade,*orderIt,traded);
                    if (order.remainingQuantity == 0)
                    {
                        order.setOrderStatus(OrderStatus::FILLED);
                        val = false;
                        processResult.processOriginalOrder(order,traded);
                        break;
                    }
                    else
                    {
                        order.setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                        // //logger.logOrder(order);
                    }
                }
            }
        }
        if (val)
        {
            if(beforeMatchRemainingQuantity!=order.remainingQuantity)
            processResult.processOriginalOrder(order,beforeMatchRemainingQuantity-order.remainingQuantity);
            addOrder(order);
        }
    }
    return processResult;
}

ProcessResult Orderbook::matchOrderMarket(Order &order)
{
    ProcessResult processResult;
    size_t beforeMatchRemainingQuantity=order.remainingQuantity;
    if (order.side == Side::BUY)
    {
        bool val = true;
        for (auto &it : asks)
        {

            auto &orders = it.second;

            for (auto orderIt = orders.begin();
                 orderIt != orders.end();)
            {
                Quantity traded =
                    std::min(order.remainingQuantity,
                             orderIt->remainingQuantity);

                order.remainingQuantity -= traded;
                orderIt->remainingQuantity -= traded;
                Trade newTrade(order.orderId, orderIt->orderId, order.userId, orderIt->userId, it.first, traded, getTimestamp());
                ////logger.logTrade(newTrade);
                if (orderIt->remainingQuantity == 0)
                {
                    orderIt->setOrderStatus(OrderStatus::FILLED);
                    ////logger.logOrder(*orderIt);       // Log FIRST while memory is valid
                     processResult.processTrade(newTrade,*orderIt,traded);
                    orderIt = orders.erase(orderIt); // Erase SECOND
                }
                else
                {
                    orderIt->setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                    //logger.logOrder(*orderIt); // Log FIRST
                     processResult.processTrade(newTrade,*orderIt,traded);
                    ++orderIt;                 // Advance SECOND
                }

                if (order.remainingQuantity == 0)
                {
                    order.orderStatus = OrderStatus::FILLED;
                    //logger.logOrder(order);
                    processResult.processOriginalOrder(order,traded);
                    val = false;
                    break;
                }
                else
                {
                    order.orderStatus = OrderStatus::PARTIALLY_FILLED;
                    //logger.logOrder(order);
                }
            }
        }
        if (val)
        {
             if(beforeMatchRemainingQuantity!=order.remainingQuantity)
            processResult.processOriginalOrder(order,beforeMatchRemainingQuantity-order.remainingQuantity);
            

            cancelOrder(order.orderId);
        }
    }
    else
    {
        bool val = true;
        for (auto it = bids.rbegin(); it != bids.rend(); it++)
        {

            auto &orders = it->second;

            for (auto orderIt = orders.begin();
                 orderIt != orders.end();)
            {
                Quantity traded =
                    std::min(order.remainingQuantity,
                             orderIt->remainingQuantity);

                order.remainingQuantity -= traded;
                orderIt->remainingQuantity -= traded;
                Trade newTrade(orderIt->orderId, order.orderId, orderIt->userId, order.userId, it->first, traded, getTimestamp());
                //logger.logTrade(newTrade);
                if (orderIt->remainingQuantity == 0)
                {
                    orderIt->setOrderStatus(OrderStatus::FILLED);
                    //logger.logOrder(*orderIt);       // Log FIRST while memory is valid
                     processResult.processTrade(newTrade,*orderIt,traded);
                    orderIt = orders.erase(orderIt); // Erase SECOND
                }
                else
                {
                    orderIt->setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                     processResult.processTrade(newTrade,*orderIt,traded);
                    //logger.logOrder(*orderIt); // Log FIRST
                    ++orderIt;                 // Advance SECOND
                }

                if (order.remainingQuantity == 0)
                {
                    order.orderStatus = OrderStatus::FILLED;
                    //logger.logOrder(order);
                    processResult.processOriginalOrder(order,traded);
                    val = false;
                    break;
                }
                else
                {
                    order.orderStatus = OrderStatus::PARTIALLY_FILLED;
                    //logger.logOrder(order);
                }
            }
        }
        if (val)
        {
         if(beforeMatchRemainingQuantity!=order.remainingQuantity)
            processResult.processOriginalOrder(order,beforeMatchRemainingQuantity-order.remainingQuantity);
            
            cancelOrder(order.orderId);
        }
    }
    return processResult;
}
// void Orderbook::matchOrderStop(Order &order){

// }
ProcessResult Orderbook::matchOrder(Order &order)
{
    OrderType tempOrderType = order.orderType;
    ProcessResult temp;
    if (tempOrderType == OrderType::LIMIT)
        temp= matchOrderLimit(order);
    else if (tempOrderType == OrderType::MARKET)
        return matchOrderMarket(order);
    // else
    //     matchOrderStop(order);
    return temp;
}