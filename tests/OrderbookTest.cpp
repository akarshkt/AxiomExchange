#include <gtest/gtest.h>

#include "../include/Orderbook.h"
#include "../include/MatchingEngine.h"
#include "./utils/TestUtils.h"
class OrderBookFixture : public ::testing::Test
{
protected:
   
    MatchingEngine engine;
    Orderbook& book; // A clean reference alias

    OrderBookFixture() 
        : engine(10000), 
          book(engine.getOrderbook()) // Perfectly fast, completely safe link
    {}

    Order  buy=makeBuy(1,100,100);
    Order  sell=makeSell(2,100,100);
    

    void SetUp() override
    {
       
    }

    void TearDown() override
    {
        // Runs after every test
    }
};
TEST_F(OrderBookFixture, AddSingleBuyOrder)
{
   
GTEST_SKIP() << "Market orders not implemented yet.";
    engine.processOrder(buy);

    EXPECT_EQ(book.bids.size(), 1);
    EXPECT_EQ(book.asks.size(), 0);
    EXPECT_EQ(book.bids[100].size(), 1);
    EXPECT_EQ(book.bids[100].begin()->orderId, buy.orderId);
    EXPECT_EQ(book.bids[100].begin()->price, 100);
    EXPECT_EQ(book.bids[100].begin()->remainingQuantity, 100);
};

TEST_F(OrderBookFixture, PartialOrderFill)
{
    GTEST_SKIP() << "Market orders not implemented yet.";
    Order orderCounter=makeSell(2,20,100);
    // Order order2=makeSell(2,20,100);
    engine.processOrder(buy);
    engine.processOrder(orderCounter);
    Orderbook testBook=engine.getOrderbook();
    EXPECT_EQ(testBook.bids[100].begin()->remainingQuantity, 80);
}

TEST_F(OrderBookFixture,CompleteOrderFill){
    GTEST_SKIP() << "Market orders not implemented yet.";
    engine.processOrder(buy);
    engine.processOrder(sell);
    Orderbook testBook=engine.getOrderbook();
    EXPECT_EQ(testBook.bids[100].size(),0);
    EXPECT_EQ(testBook.asks[100].size(),0);
}