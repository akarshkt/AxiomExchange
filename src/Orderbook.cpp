#include "../include/Orderbook.h"

class OrderBook{
    std::map<Price,std::vector<Order>> asks;
    std::map<Price,std::vector<Order>> bids;

    void addOrder(Order order){
        if(order.side==Side::BUY){
            bids[order.price].push_back(order);
        }
        else
        asks[order.price].push_back(order);
    }
    void removeOrder(OrderId orderId){
        
        for(auto &it:asks){
            for(auto &ti:it.second){
                if(ti.orderId==orderId){
                    it.second.erase(std::remove(it.second.begin(),it.second.end(),ti),it.second.end());
                    break;
                }
            }
        }
        for(auto &it:asks){
            for(auto &ti:it.second){
                if(ti.orderId==orderId){
                    it.second.erase(std::remove(it.second.begin(),it.second.end(),ti),it.second.end());
                    break;
                }
            }
        }
    }
    Order findOrder(OrderId orderId){
         for(auto &it:asks){
            for(auto &ti:it.second){
                if(ti.orderId==orderId){
                   return ti;
                }
            }
        }
        for(auto &it:asks){
            for(auto &ti:it.second){
                if(ti.orderId==orderId){
                   return ti;
                }
            }
        }
    }
};