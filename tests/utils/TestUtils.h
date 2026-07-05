#include "../include/Order.h"
#include "../include/Orderbook.h"

Order makeBuy(int id,int qty,int price);
Order makeSell(int id,int qty,int price);
Order makeMarketBuy(int id,int qty,int price);
Order makeMarketSell(int id,int qty,int price);
// void expectBookEmpty(const Orderbook&);
// void expectBidLevels(const Orderbook&, size_t);
// void expectAskLevels(const Orderbook&, size_t);