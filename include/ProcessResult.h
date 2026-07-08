#include <vector>
#include "./Trade.h"
#include "./ExecutionReport.h"
struct ProcessResult
{
    std::vector<Trade> trades;

    std::vector<ExecutionReport> reports;

    void processTrade(Trade trade,Order& order,size_t quantity){
        trades.push_back(trade);
        ExecutionReport report(order.orderId,order.userId,order.orderStatus,quantity,quantity,order.remainingQuantity);
        
    }
    void processOriginalOrder(Order& order,size_t quantity){
        ExecutionReport report(order.orderId,order.userId,order.orderStatus,quantity,order.remainingQuantity,order.originalQuantity-order.remainingQuantity);
        
    }
};