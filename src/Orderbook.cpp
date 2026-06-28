#include "../include/Orderbook.h"
#include <iostream>

std::map<Price, std::vector<Order>> asks;
std::map<Price, std::vector<Order>> bids;

void Orderbook::addOrder(Order &order)
{
    if (order.side == Side::BUY)
    {
        bids[order.price].push_back(order);
    }
    else
        asks[order.price].push_back(order);
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

    for (auto &it : asks)
    {
        for (auto &ti : it.second)
        {
            if (ti.orderId == orderId)
            {
                it.second.erase(std::remove(it.second.begin(), it.second.end(), ti), it.second.end());
                break;
            }
        }
    }
    for (auto &it : bids)
    {
        for (auto &ti : it.second)
        {
            if (ti.orderId == orderId)
            {
                it.second.erase(std::remove(it.second.begin(), it.second.end(), ti), it.second.end());
                break;
            }
        }
    }
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

void Orderbook::matchOrder(Order &order)
{
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
