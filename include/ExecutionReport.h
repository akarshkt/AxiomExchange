#ifndef MATCHRESULT_H
#define MATCHRESULT_H
#include <vector>
#include "./Trade.h"
#include <mutex>


struct ExecutionReport
{
    OrderId orderId;

    UserId userId;

    OrderStatus status;

    Quantity lastExecutedQuantity;

    Quantity cumulativeExecutedQuantity;

    Quantity remainingQuantity;
    ExecutionReport(OrderId orderId,
        UserId userId,
        OrderStatus orderStatus,
        size_t quantity,
        size_t remainingQuantity,
        size_t cumulativeQuantity
        )
        {
        this->orderId=orderId;
        this->userId=userId;
        this->status=orderStatus;
        this->lastExecutedQuantity=quantity;
        this->remainingQuantity=remainingQuantity;
        this->cumulativeExecutedQuantity=cumulativeQuantity;
    };

};
#endif