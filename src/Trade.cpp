#include "../include/Trade.h"

Trade::Trade(OrderId buyOrderId,
        OrderId sellOrderId,
        UserId buyer,
        UserId seller,
        Price executionPrice,
        Quantity quantity,
        Timestamp timestamp
        )
        :
        
        buyOrderId(buyOrderId),
        sellOrderId(sellOrderId),
        buyer(buyer),
        seller(seller),
        executionPrice(executionPrice),
        quantity(quantity),
        timestamp(timestamp),
        tradeId(rand())
        {}

TradeId Trade::getTradeId(){
    return tradeId;
}