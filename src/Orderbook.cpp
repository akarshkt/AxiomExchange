#include "../include/Orderbook.h"
#include <iostream>

std::map<Price, std::list<Order>> asks;
std::map<Price, std::list<Order>> bids;
std::unordered_map<OrderId,OrderLocation> orderIndex;
void Orderbook::addOrder(Order &order)
{
    Price price=order.price;
    Side side=order.side;
    if (side == Side::BUY)
    {
        bids[price].emplace_back(order);
        orderIndex[order.orderId]={side,price,  --(bids[price].end())};
    }
    else{
        asks[price].push_back(order);
        orderIndex[order.orderId]={side,price,  --(asks[price].end())};
    }
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

    auto loc=orderIndex[orderId];
    auto& book=loc.side==Side::BUY?bids:asks;
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
void Orderbook::matchOrderLimit(Order &order){
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

                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt = orders.erase(orderIt);
                    }
                    else
                    {
                        ++orderIt;
                    }

                    if (order.remainingQuantity == 0)
                      { val=false; break;}
                }
            }
        }
        if (val)
            addOrder(order);
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

                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt = orders.erase(orderIt);
                    }
                    else
                    {
                        ++orderIt;
                    }

                    if (order.remainingQuantity == 0)
                      { val=false; break;}
                }
            }
        }
        if (val)
            addOrder(order);
    }

}

void Orderbook::matchOrderMarket(Order &order){
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

                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt = orders.erase(orderIt);
                    }
                    else
                    {
                        ++orderIt;
                    }

                    if (order.remainingQuantity == 0)
                      { val=false; break;}
                }
            
        }
        if (val)
           addOrder(order);
          
    }
    else
    {
        bool val = true;
        for (auto &it : bids)
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

                    if (orderIt->remainingQuantity == 0)
                    {
                        orderIt = orders.erase(orderIt);
                    }
                    else
                    {
                        ++orderIt;
                    }

                    if (order.remainingQuantity == 0)
                      { val=false; break;}
                }
            
        }
        if (val)
            addOrder(order);
          
    }
}
// void Orderbook::matchOrderStop(Order &order){

// }
void Orderbook::matchOrder(Order &order)
{
    OrderType tempOrderType=order.orderType;
    if(tempOrderType==OrderType::LIMIT)
        matchOrderLimit(order);
    else if(tempOrderType==OrderType::MARKET)
        matchOrderMarket(order);
    // else
    //     matchOrderStop(order);
}