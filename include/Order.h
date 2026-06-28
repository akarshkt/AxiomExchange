#ifndef ORDER_H
#define ORDER_H

#include <cstdint>
#include <math.h>
#include <time.h>
#include <chrono>
using OrderId = uint64_t;
using UserId = uint64_t;
using AssetId = uint64_t;
using Timestamp = uint64_t;
using Price = int64_t;
using Quantity = uint32_t;
enum class Side{
	BUY,
	SELL
};

enum class OrderType{
	MARKET,
	LIMIT,
	STOP
};



struct Order{

	OrderId orderId;
	OrderType orderType;
	Side side;
	Price price;
	UserId userId;
	AssetId assetId;
	Quantity originalQuantity;
	Quantity remainingQuantity;
	Timestamp timestamp;
	Order(UserId userId,OrderType ordertype, AssetId assetId,Quantity originalQuantity, Side side,Price price );
	 bool operator==(const Order& other) const
    {
        return orderId == other.orderId;
    }
};
#endif
