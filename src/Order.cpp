#include "../include/Order.h"
#include "../include/utils/TimeUtils.h"

Order::Order(UserId userId,
             OrderType ordertype,
             TimeInForce timeInForce,
             AssetId assetId,
             Quantity originalQuantity,
             Side side,
             Price price
            )
    : 
      userId(userId),
      orderType(ordertype),
      timeInForce(timeInForce),
      assetId(assetId),
      originalQuantity(originalQuantity),
      side(side),
      price(price)
{
    this->timestamp=getTimestamp();
    this->orderId=random();
    this->userId=userId;
    this->price=price;
    this->orderType = ordertype;
    this->timeInForce = timeInForce;
    this->assetId = assetId;
    this->originalQuantity = originalQuantity;
    this->remainingQuantity = originalQuantity;
    this->side = side;
    this->orderStatus=OrderStatus::NEW;

    
}

void Order::setOrderStatus(OrderStatus orderStatus){
    this->orderStatus=orderStatus;
}