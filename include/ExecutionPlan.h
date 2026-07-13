#ifndef EXECUTIONPLAN_H
#define EXECUTIONPLAN_H
#include <vector>
#include "./Order.h"
struct PlannedExecution
{
    std::list<Order>::iterator  restingOrder;
    Quantity quantity;
    Price price;

    PlannedExecution(std::list<Order>::iterator order,Quantity quantity,Price price){
        this->restingOrder=order;
        this->quantity=quantity;
        this->price=price;
    }
};

struct ExecutionPlan
{
    std::vector<PlannedExecution> fills;

    Quantity totalMatched = 0;

    void process(std::list<Order>::iterator order,Quantity traded){
        PlannedExecution ex(order,traded,order->price);
        fills.push_back(ex);
    }
};

#endif