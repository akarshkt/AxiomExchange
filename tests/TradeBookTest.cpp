#include <gtest/gtest.h>
#include "../include/MatchingEngine.h"
#include "../include/Orderbook.h"
#include "../include/Logger.h"
#include "./utils/TestUtils.h"
class TradeBookFixture : public :: testing :: Test {
    protected:
    size_t capacity=10000;
    MatchingEngine engine;
    Orderbook& book;
    TradeBookFixture() 
    : engine(10000), 
    book(engine.getOrderbook()) // Perfectly fast, completely safe link
    {}
    Logger& logger=book.getLogger();
    Ringbuffer<Trade>& tradeLog=logger.getRingBuffer();
    Order buy=makeBuy(1,100,100);
    Order sell=makeSell(2,100,100);
    void SetUp() override{
        engine.processOrder(buy);
        engine.processOrder(sell);
    }
};

TEST_F(TradeBookFixture,CompleteMatchTradeOccurs){
   
    EXPECT_EQ(tradeLog.returnTrade().buyer,1);
    EXPECT_EQ(tradeLog.returnTrade().seller,2);
    EXPECT_EQ(tradeLog.returnTrade().buyOrderId,buy.orderId);
    EXPECT_EQ(tradeLog.returnTrade().sellOrderId,sell.orderId);
}
TEST_F(TradeBookFixture,PartialMatchTradeOccurs){
    Order partialBuy=makeBuy(1,100,100);
    Order partialSell=makeSell(2,20,100);
    engine.processOrder(partialBuy);
    engine.processOrder(partialSell);
    Trade curTrade=tradeLog.returnTrade();
    EXPECT_EQ(curTrade.buyer,1);
    EXPECT_EQ(curTrade.seller,2);
    EXPECT_EQ(curTrade.buyOrderId,partialBuy.orderId);
    EXPECT_EQ(curTrade.sellOrderId,partialSell.orderId);
    EXPECT_EQ(curTrade.quantity,20);
    EXPECT_EQ(tradeLog.size(),2);

}

