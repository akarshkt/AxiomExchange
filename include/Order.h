#ifndef ORDER_H
#define ORDER_H

#include <cstdint>
#include <math.h>
#include <time.h>
#include <chrono>
#include <list>
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
enum class TimeInForce
{
    GTC,
    IOC,
    FOK,
    DAY
};
enum class OrderStatus{
	NEW,
	PARTIALLY_FILLED,
	FILLED,
	CANCELLED,
	EXPIRED,
	REJECTED
};
inline std::ostream& operator<<(std::ostream& os, const OrderStatus& status) {
    switch (status) {
        case OrderStatus::NEW:              os << "NEW"; break;
        case OrderStatus::PARTIALLY_FILLED: os << "PARTIALLY_FILLED"; break;
        case OrderStatus::FILLED:           os << "FILLED"; break;
        case OrderStatus::CANCELLED:        os << "CANCELLED"; break;
        case OrderStatus::EXPIRED:          os << "EXPIRED"; break;
        case OrderStatus::REJECTED:         os << "REJECTED"; break;
        default:                            os << "UNKNOWN"; break;
    }
    return os;
}
struct Order{

	OrderId orderId;
	OrderType orderType;
	TimeInForce timeInForce;
	Side side;
	Price price;
	UserId userId;
	AssetId assetId;
	Quantity originalQuantity;
	Quantity remainingQuantity;
	Timestamp timestamp;
	OrderStatus orderStatus;
	Order(UserId userId,OrderType ordertype,TimeInForce timeInForce, AssetId assetId,Quantity originalQuantity, Side side,Price price );
	 bool operator==(const Order& other) const
    {
        return orderId == other.orderId;
    }
	void setOrderStatus(OrderStatus orderStatus);
};
struct OrderLocation{
	Side side;
	Price price;
	std::list<Order> :: iterator it;
};

#endif
