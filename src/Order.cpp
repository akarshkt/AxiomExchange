#include "../include/Order.h"

Timestamp getTimestamp(){
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    
}
Order::Order(UserId userId,
             OrderType ordertype,
             AssetId assetId,
             Quantity originalQuantity,
             Side side,
             Price price
            )
    : 
      userId(userId),
      orderType(ordertype),
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
    this->assetId = assetId;
    this->originalQuantity = originalQuantity;
    this->remainingQuantity = originalQuantity;
    this->side = side;
}