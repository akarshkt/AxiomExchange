#include "./utils/TestUtils.h"

Order makeBuy(
    int id,
    int qty,
    int price
)
{
    return Order(
        id,
        OrderType::LIMIT,
        1,
        qty,
        Side::BUY,
        price
    );
}

Order makeSell(
    int id,
    int qty,
    int price
)
{
    return Order(
        id,
        OrderType::LIMIT,
        1,
        qty,
        Side::SELL,
        price
    );
}
Order makeMarketBuy(
    int id,
    int qty,
    int price
)
{
    return Order(
        id,
        OrderType::MARKET,
        1,
        qty,
        Side::BUY,
        price
    );
}

Order makeMarketSell(
    int id,
    int qty,
    int price
)
{
    return Order(
        id,
        OrderType::MARKET,
        1,
        qty,
        Side::SELL,
        price
    );
}
