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
// struct ExecutionReport
// {
//     std::once_flag initializationFlag;
//     OrderId orderId;

//     OrderStatus status;

//     Quantity originalQuantity;

//     Quantity remainingQuantity;

//     std::vector<Trade> trades;
//     void setOrderId(OrderId orderId)
//     {
//         this->orderId=orderId;
//     }
//     void processTrade(Trade trade){
//         std::call_once(initializationFlag, &ExecutionReport::setOrderId, this);

//         trades.push_back(trade);
//         remainingQuantity-=trade.quantity;
//         if(remainingQuantity==0)
//         status=OrderStatus::FILLED;
//         else
//         status=OrderStatus::PARTIALLY_FILLED;
//     }
// };
#endif