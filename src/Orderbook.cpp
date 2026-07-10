#include "../include/Orderbook.h"
#include <iostream>

void Orderbook::addOrder(Order &order)
{
    Price price = order.price;

    auto &book = (order.side == Side::BUY ? bids : asks);
    book[price].push_back(order);
    orderIndex[order.orderId] = {order.side, price, --(book[price].end())};
    //logger.logOrder(order);
}
void Orderbook::removeOrder(OrderId orderId)
{
    auto loc = orderIndex[orderId];
    auto &book = loc.side == Side::BUY ? bids : asks;

    book[loc.price].erase(loc.it);
}
void Orderbook::cancelOrder(OrderId orderId)
{

    auto loc = orderIndex[orderId];
    auto &book = loc.side == Side::BUY ? bids : asks;

    loc.it->orderStatus = OrderStatus::CANCELLED;
    book[loc.price].erase(loc.it);
}

Order& Orderbook::orderLookup(OrderId orderId)
{
    // auto loc=orderIndex[orderId];
    // auto &book = loc.side == Side::BUY ? bids : asks;
    // return *loc.it;
    auto it = orderIndex.find(orderId);

    if (it == orderIndex.end())
    throw std::runtime_error("Order not found");
        // return ;

    auto &loc = it->second;
    return *loc.it;
    
}
ProcessResult Orderbook::matchOrderLimit(Order &order)
{
    ProcessResult processResult;
    size_t beforeMatchRemainingQuantity=order.remainingQuantity;
     bool val = true;
    if (order.side == Side::BUY)
    {
     
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
                    Trade newTrade(order.orderId, orderIt->orderId, order.userId, orderIt->userId, it.first, traded, getTimestamp());
                   
                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt->setOrderStatus(OrderStatus::FILLED);
                        processResult.processTrade(newTrade,*orderIt,traded);
                        orderIt = orders.erase(orderIt); 
                    }
                    else
                    {
                        orderIt->setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                        processResult.processTrade(newTrade,*orderIt,traded);
                        ++orderIt;               
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
                    }
                }
            }
        }
       
    }
    else
    {
       
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
                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt->setOrderStatus(OrderStatus::FILLED);
                        processResult.processTrade(newTrade,*orderIt,traded);
                        orderIt = orders.erase(orderIt); 
                    }
                    else
                    {
                        orderIt->setOrderStatus(OrderStatus::PARTIALLY_FILLED);
                        processResult.processTrade(newTrade,*orderIt,traded);
                        ++orderIt;                 
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
                    }
                }
            }
        }
       
        
    }
    if (val)
        {
            if(beforeMatchRemainingQuantity!=order.remainingQuantity)
            processResult.processOriginalOrder(order,beforeMatchRemainingQuantity-order.remainingQuantity);
            if(order.timeInForce==TimeInForce::GTC)
            addOrder(order);
            else if(order.timeInForce == TimeInForce::IOC)
            order.orderStatus=OrderStatus::CANCELLED;
        }
         if(order.remainingQuantity==order.originalQuantity)
        processResult.processOriginalOrder(order,beforeMatchRemainingQuantity);
        
        return processResult;
}

ProcessResult Orderbook::matchOrderMarket(Order &order)
{
    ProcessResult processResult;
    size_t beforeMatchRemainingQuantity=order.remainingQuantity;
      bool val = true;
    if (order.side == Side::BUY)
    {
      
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
      
    }
    else
    {
     
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
       
    }
     if (val)
        {
             if(beforeMatchRemainingQuantity!=order.remainingQuantity)
            processResult.processOriginalOrder(order,beforeMatchRemainingQuantity-order.remainingQuantity);
            

            // cancelOrder(order.orderId);
        }
        if(order.remainingQuantity==order.originalQuantity)
        processResult.processOriginalOrder(order,beforeMatchRemainingQuantity);
        return processResult;
}
// void Orderbook::matchOrderStop(Order &order){

// }

ProcessResult Orderbook::matchOrder(Order &order)
{
    OrderType tempOrderType = order.orderType;
    TimeInForce timeInForce=order.timeInForce;
    // ProcessResult temp;
    
    if (tempOrderType == OrderType::LIMIT )
        return matchOrderLimit(order);
    else if (tempOrderType == OrderType::MARKET )
        return matchOrderMarket(order);


    
    // else
    //     matchOrderStop(order);
    // std::cout<<temp.trades.size();
    // return temp;
}