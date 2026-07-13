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
    Orderbook& book=engine.getOrderbook();
    Logger& logger=engine.getLogger();
    Ringbuffer& tradeLog=engine.getRingbuffer();
    Order buy=makeBuy(1,100,100,TimeInForce::GTC);
    Order sell=makeSell(2,100,100,TimeInForce::GTC);
    
    void SetUp() override{
        // engine.processOrder(buy);
        // engine.processOrder(sell);
    
    }
};

TEST_F(TradeBookFixture,CompleteMatchTradeOccurs_LIMIT){
     ProcessResult buyResult =engine.processOrder(buy);
    ProcessResult sellResult= engine.processOrder(sell);
    EXPECT_EQ(buyResult.trades.size(),0);
    EXPECT_EQ(sellResult.trades.size(),1);
    
    EXPECT_EQ(tradeLog.size(),1);
    EXPECT_EQ(tradeLog.returnTrade().buyer,1);
    EXPECT_EQ(tradeLog.returnTrade().seller,2);
    EXPECT_EQ(tradeLog.returnTrade().buyOrderId,buy.orderId);
    EXPECT_EQ(tradeLog.returnTrade().sellOrderId,sell.orderId);
}
TEST_F(TradeBookFixture,PartialMatchTradeOccurs_LIMIT){
    Order partialBuy=makeBuy(1,100,100,TimeInForce::GTC);
    Order partialSell=makeSell(2,20,100,TimeInForce::GTC);
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
TEST_F(TradeBookFixture,NoMatchTradeOccurs_LIMIT){
    Order partialBuy=makeBuy(1,100,100,TimeInForce::GTC);
    Order partialSell=makeSell(2,100,110,TimeInForce::GTC);
    ProcessResult repBuyPartial=engine.processOrder(partialBuy);
    ProcessResult repSellPartial=engine.processOrder(partialSell);
    Trade curTrade=tradeLog.returnTrade();
    EXPECT_EQ(curTrade,Trade{});
    EXPECT_EQ(tradeLog.size(),0);
}
TEST_F(TradeBookFixture,CompleteMatchTradeOccurs_MARKET){
    Order Sell=makeSell(2,100,100,TimeInForce::GTC);
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
    Order Buy=makeBuy(1,100,100,TimeInForce::GTC);
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
TEST_F(TradeBookFixture,OneOrderExecutesManyTradesFirstBuy){
    Order buy=makeBuy(1,100,100,TimeInForce::GTC);

    Order sell1=makeSell(2,10,100,TimeInForce::GTC);
    Order sell2=makeSell(2,10,100,TimeInForce::GTC);
    Order sell3=makeSell(2,10,100,TimeInForce::GTC);
    Order sell4=makeSell(2,10,100,TimeInForce::GTC);
    Order sell5=makeSell(2,10,100,TimeInForce::GTC);
    ProcessResult report=engine.processOrder( buy);    
    ProcessResult report1=engine.processOrder(sell1);
    ProcessResult report2=engine.processOrder(sell2);
    ProcessResult report3=engine.processOrder(sell3);
    ProcessResult report4=engine.processOrder(sell4);
    ProcessResult report5=engine.processOrder(sell5);  
    
    EXPECT_EQ(report.trades.size(),0);
    EXPECT_EQ(report.reports.size(),1);
    EXPECT_EQ(report1.trades.size(),1);
    EXPECT_EQ(report2.trades.size(),1);
    EXPECT_EQ(report3.trades.size(),1);
    EXPECT_EQ(report4.trades.size(),1);
    EXPECT_EQ(report5.trades.size(),1);
    EXPECT_EQ(report1.reports.size(),2);
    EXPECT_EQ(report2.reports.size(),2);
    EXPECT_EQ(report3.reports.size(),2);
    EXPECT_EQ(report4.reports.size(),2);
    EXPECT_EQ(report5.reports.size(),2);
}
TEST_F(TradeBookFixture,OneOrderExecutesManyTradesLastSell){
    
    Order buy=makeBuy(1,100,100,TimeInForce::GTC);
    Order sell1=makeSell(2,10,100,TimeInForce::GTC);
    Order sell2=makeSell(2,10,100,TimeInForce::GTC);
    Order sell3=makeSell(2,10,100,TimeInForce::GTC);
    Order sell4=makeSell(2,10,100,TimeInForce::GTC);
    Order sell5=makeSell(2,10,100,TimeInForce::GTC);
    ProcessResult report1=engine.processOrder(sell1);
    ProcessResult report2=engine.processOrder(sell2);
    ProcessResult report3=engine.processOrder(sell3);
    ProcessResult report4=engine.processOrder(sell4);
    ProcessResult report5=engine.processOrder(sell5);  
    ProcessResult report=engine.processOrder( buy);    
    
    EXPECT_EQ(report.trades.size(),5);
    EXPECT_EQ(report.reports.size(),6);
    EXPECT_EQ(report1.trades.size(),0);
    EXPECT_EQ(report2.trades.size(),0);
    EXPECT_EQ(report3.trades.size(),0);
    EXPECT_EQ(report4.trades.size(),0);
    EXPECT_EQ(report5.trades.size(),0);
    EXPECT_EQ(report1.reports.size(),1);
    EXPECT_EQ(report2.reports.size(),1);
    EXPECT_EQ(report3.reports.size(),1);
    EXPECT_EQ(report4.reports.size(),1);
    EXPECT_EQ(report5.reports.size(),1);
}
TEST_F(TradeBookFixture,TwoMarketOrdersCannotMatch){
    Order buyMarket=makeMarketBuy(1,100);
    Order sellMarket=makeMarketSell(2,100);
    ProcessResult repBuy=engine.processOrder( buyMarket);
    ProcessResult repSell=engine.processOrder(sellMarket);
    EXPECT_EQ(repBuy.reports.size(),1);
    EXPECT_EQ(repSell.reports.size(),1);
    EXPECT_EQ(repBuy.trades.size(),0);
    EXPECT_EQ(repSell.trades.size(),0);
    Trade trade=tradeLog.returnTrade();
    EXPECT_EQ(trade,Trade{});
}
TEST_F(TradeBookFixture,MarketOrderDonotGoInTheBooks){
    Order buyMarket=makeMarketBuy(1,100);
    Order sellMarket=makeMarketSell(2,100);
    ProcessResult repBuy=engine.processOrder( buyMarket);
    ProcessResult repSell=engine.processOrder(sellMarket);
    EXPECT_EQ(repBuy.reports.size(),1);
    EXPECT_EQ(repSell.reports.size(),1);
    EXPECT_EQ(repBuy.trades.size(),0);
    EXPECT_EQ(repSell.trades.size(),0);
    Trade trade=tradeLog.returnTrade();
    EXPECT_EQ(trade,Trade{});
    EXPECT_THROW(book.orderLookup(buyMarket.orderId), std::runtime_error);
    EXPECT_THROW(book.orderLookup(sellMarket.orderId), std::runtime_error);
}
TEST_F(TradeBookFixture,IOCOrdersDonotGoInBook){
     Order buy=makeBuy(1,100,100,TimeInForce::GTC);
     Order buy2=makeBuy(1,50,100,TimeInForce::GTC);
     Order sell=makeMarketSell(2,200);
     ProcessResult buyRep=engine.processOrder( buy);
     ProcessResult buyRep2=engine.processOrder(buy2);
     ProcessResult sellRep=engine.processOrder(sell);
   
     EXPECT_THROW(book.orderLookup(buy.orderId),std::runtime_error);
     EXPECT_THROW(book.orderLookup(buy2.orderId),std::runtime_error);
     EXPECT_THROW(book.orderLookup(sell.orderId),std::runtime_error);
     
     EXPECT_EQ(sellRep.trades.size(),2);
}
TEST_F(TradeBookFixture,FOKDoesnotExecuteIfNotFill){
     Order buy=makeBuy(1,100,100,TimeInForce::GTC);
     Order buy2=makeBuy(1,50,100,TimeInForce::GTC);
     Order sell=makeSell(2,200,100,TimeInForce::FOK);
    //  sell.timeInForce=TimeInForce::FOK;
    //  std::cout<<(sell.timeInForce==TimeInForce::FOK?"FOK":"Not FOK")<<std::endl;
     ProcessResult buyRep=engine.processOrder( buy);
     ProcessResult buyRep2=engine.processOrder(buy2);
     ProcessResult sellRep=engine.processOrder(sell);
   
    //  EXPECT_THROW(book.orderLookup(buy.orderId),std::runtime_error);
    //  EXPECT_THROW(book.orderLookup(buy2.orderId),std::runtime_error);
     EXPECT_EQ(book.orderLookup(buy2.orderId).orderStatus,OrderStatus::NEW);
     EXPECT_THROW(book.orderLookup(sell.orderId),std::runtime_error);
     
     EXPECT_EQ(sellRep.trades.size(),0);
     EXPECT_EQ(sellRep.reports.size(),1);
}
