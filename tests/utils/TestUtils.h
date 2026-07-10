#include "../include/Order.h"
#include "../include/Orderbook.h"

Order makeBuy(int id,int qty,int price,TimeInForce timeInForce);
Order makeSell(int id,int qty,int price,TimeInForce timeInForce);
Order makeMarketBuy(int id,int qty);
Order makeMarketSell(int id,int qty);
// void expectBookEmpty(const Orderbook&);
// void expectBidLevels(const Orderbook&, size_t);
// void expectAskLevels(const Orderbook&, size_t);