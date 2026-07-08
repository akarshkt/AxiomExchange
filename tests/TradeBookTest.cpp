#include <gtest/gtest.h>
#include "../include/MatchingEngine.h"
#include "../include/Orderbook.h"
#include "../include/Logger.h"
#include "./utils/TestUtils.h"
#include "../include/Ringbuffer.h"
class TradeBookFixture : public :: testing :: Test {
    protected:
    size_t capacity=10000;
    MatchingEngine engine;
    
    TradeBookFixture() 
    : engine(10000)
    // Perfectly fast, completely safe link
    {}
    Orderbook& book=engine.orderbook;
    Logger& logger=engine.logger;
    Ringbuffer& tradeLog=engine.getRingbuffer();
    Order buy=makeBuy(1,100,100);
    Order sell=makeSell(2,100,100);
    
    void SetUp() override{
        // engine.processOrder(buy);
        // engine.processOrder(sell);
    
    }
};

TEST_F(TradeBookFixture,CompleteMatchTradeOccurs_LIMIT){
    ProcessResult buyResult =engine.processOrder(buy);
    ProcessResult sellResult= engine.processOrder(sell);
    // std::cout<<sellResult.reports.size()<<std::endl;
    EXPECT_EQ(buyResult.trades.size(),0);
    EXPECT_EQ(sellResult.trades.size(),1);
    
    EXPECT_EQ(tradeLog.size(),1);
    EXPECT_EQ(tradeLog.returnTrade().buyer,1);
    EXPECT_EQ(tradeLog.returnTrade().seller,2);
    EXPECT_EQ(tradeLog.returnTrade().buyOrderId,buy.orderId);
    EXPECT_EQ(tradeLog.returnTrade().sellOrderId,sell.orderId);
}
TEST_F(TradeBookFixture,PartialMatchTradeOccurs_LIMIT){
    Order partialBuy=makeBuy(1,100,100);
    Order partialSell=makeSell(2,20,100);
    ProcessResult repBuyPartial=engine.processOrder(partialBuy);
    ProcessResult repSellPartial=engine.processOrder(partialSell);
    Trade curTrade=tradeLog.returnTrade();
    EXPECT_EQ(curTrade.buyer,1);
    EXPECT_EQ(curTrade.seller,2);
    EXPECT_EQ(curTrade.buyOrderId,partialBuy.orderId);
    EXPECT_EQ(curTrade.sellOrderId,partialSell.orderId);
    EXPECT_EQ(curTrade.quantity,20);
    EXPECT_EQ(tradeLog.size(),1);

}
TEST_F(TradeBookFixture,CompleteMatchTradeOccurs_MARKET){
    Order Sell=makeSell(2,100,100);
    Order marketBuy=makeMarketBuy(1,100);
    ProcessResult repSell=engine.processOrder(Sell);
    ProcessResult repMarketBuy=engine.processOrder(marketBuy);
    Trade curTrade=tradeLog.returnTrade();
    EXPECT_EQ(curTrade.buyer,1);
    EXPECT_EQ(curTrade.seller,2);
    EXPECT_EQ(curTrade.buyOrderId,marketBuy.orderId);
    EXPECT_EQ(curTrade.sellOrderId,Sell.orderId);
    EXPECT_EQ(curTrade.quantity,100);
}
TEST_F(TradeBookFixture,PartialMatchTradeOccurs_MARKET){
    Order Buy=makeBuy(1,100,100);
    Order partialMarketSell=makeMarketSell(2,20);
    ProcessResult repBuy=engine.processOrder(Buy);
    ProcessResult repMarketSell=engine.processOrder(partialMarketSell);
    Trade curTrade=tradeLog.returnTrade();
    EXPECT_EQ(curTrade.buyer,1);
    EXPECT_EQ(curTrade.seller,2);
    EXPECT_EQ(curTrade.buyOrderId,Buy.orderId);
    EXPECT_EQ(curTrade.sellOrderId,partialMarketSell.orderId);
    EXPECT_EQ(curTrade.quantity,20);
    EXPECT_EQ(tradeLog.size(),1);

}
TEST_F(TradeBookFixture,NoOrdersAvailableToBuy_MARKET){
  
    Order marketBuy=makeMarketBuy(1,100);
    ProcessResult repMarketBuy=engine.processOrder(marketBuy);
    Trade curTrade=tradeLog.returnTrade();

    EXPECT_EQ(curTrade,Trade{});
    EXPECT_EQ(repMarketBuy.trades.size(),0);
    EXPECT_EQ(repMarketBuy.reports.size(),1);
}