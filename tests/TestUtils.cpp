#include "./utils/TestUtils.h"

Order makeBuy(
    int id,
    int qty,
    int price,
    TimeInForce timeInForce
)
{
    return Order(
        id,
        OrderType::LIMIT,
        timeInForce,
        1,
        qty,
        Side::BUY,
        price
    );
}

Order makeSell(
    int id,
    int qty,
    int price,
    TimeInForce timeInForce
)
{
    return Order(
        id,
        OrderType::LIMIT,
        timeInForce,
        1,
        qty,
        Side::SELL,
        price
    );
}
Order makeMarketBuy(
    int id,
    int qty
   
)
{
    return Order(
        id,
        OrderType::MARKET,
        TimeInForce::IOC,
        1,
        qty,
        Side::BUY,
        0
    );
}

Order makeMarketSell(
    int id,
    int qty
)
{
    return Order(
        id,
        OrderType::MARKET,
        TimeInForce::IOC,
        1,
        qty,
        Side::SELL,
        0
    );
}
