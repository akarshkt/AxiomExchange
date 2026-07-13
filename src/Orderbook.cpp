#include "../include/Orderbook.h"
#include <iostream>
void Orderbook::addOrder(Order& order)
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
    orderIndex.erase(orderId);
}
// void Orderbook::removeOrder(Order* order)
// {
    
//     auto &book = order->side == Side::BUY ? bids : asks;

//     book[order->price].erase(order);
//     orderIndex.erase(order->orderId);
// }
void Orderbook::cancelOrder(OrderId orderId)
{

    auto loc = orderIndex[orderId];
    auto &book = loc.side == Side::BUY ? bids : asks;

    (loc.it)->setOrderStatus(OrderStatus::CANCELLED);
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
    return *(loc.it);
    
}
ExecutionPlan Orderbook::matchOrderLimit(Order &order)
{

    ExecutionPlan plan;
    if (order.side == Side::BUY)
    {
     
        for (auto it = asks.begin();it!=asks.end() && it->first <= order.price;)
        {
            
                auto &orders = it->second;
                for (auto orderIt = orders.begin();
                     orderIt != orders.end();)
                {
                    Quantity traded =
                        std::min(order.remainingQuantity,
                                 (orderIt)->remainingQuantity);

                plan.process(orderIt,traded);
                   orderIt++;
                    
                }
           
            if (orders.empty())
             it = asks.erase(it);
          else
              ++it;
        }
    }
    else
    {
        for (auto it=bids.begin();it!=bids.end() && it->first>=order.price;)
        {
            
                auto &orders = it->second;

                for (auto orderIt = orders.begin();
                     orderIt != orders.end();)
                {
                    Quantity traded =
                        std::min(order.remainingQuantity,
                                 (orderIt)->remainingQuantity);

                      plan.process(orderIt,traded);
                      orderIt++;
                }
            if (orders.empty())
            it = bids.erase(it);
            else
            ++it;
        }
    }
        return plan;
}

ExecutionPlan Orderbook::matchOrderMarket(Order &order)
{
     ExecutionPlan plan;
     
    if (order.side == Side::BUY)
    {
      
        for (auto it = asks.begin();it!=asks.end();)
        {

            auto &orders = it->second;

            for (auto orderIt = orders.begin();
                 orderIt != orders.end();)
            {
                Quantity traded =
                    std::min(order.remainingQuantity,
                             (orderIt)->remainingQuantity);

                 plan.process(orderIt,traded);
                   orderIt++;
            }
            if (orders.empty())
             it = asks.erase(it);
          else
              ++it;
        }
      
    }
    else
    {
     
        for (auto it = bids.rbegin(); it != bids.rend();)
        {

            auto &orders = it->second;

            for (auto orderIt = orders.begin();
                 orderIt != orders.end();)
            {
                Quantity traded =
                    std::min(order.remainingQuantity,
                             (orderIt)->remainingQuantity);

                plan.process(orderIt,traded);
                   orderIt++;
                
            }
              
        if (orders.empty())
           bids.erase(std::next(it).base()); 
         else
         ++it;
       }
    }
     
         return plan;
}
// void Orderbook::matchOrderStop(Order &order){

// }

ExecutionPlan Orderbook::matchOrder(Order &order)
{
    OrderType tempOrderType = order.orderType;
    // ExecutionPlan plan;
    if (tempOrderType == OrderType::LIMIT )
        return matchOrderLimit(order);
    else if (tempOrderType == OrderType::MARKET )
        return matchOrderMarket(order);


    
    // else
    //     matchOrderStop(order);
    // std::cout<<temp.trades.size();
    // return temp;
}