#ifndef TRADE_H
#define TRADE_H
#include "./Order.h"
using TradeId = uint64_t;
class Trade
{
    public:
    TradeId tradeId;
    OrderId buyOrderId;
    OrderId sellOrderId;
    UserId buyer;
    UserId seller;
    Price executionPrice;
    Quantity quantity;
    Timestamp timestamp;

public:
    Trade() = default;
    bool operator==(const Trade& other) const {
        return tradeId == other.tradeId && 
               quantity == other.quantity && 
               executionPrice == other.executionPrice ;
    }

public:
    TradeId getTradeId();
    Trade(
         OrderId buyOrderId,
         OrderId sellOrderId,
         UserId buyer, 
         UserId seller, 
         Price executionPrice, 
         Quantity quantity, 
         Timestamp timestamp
        );
};

#endif