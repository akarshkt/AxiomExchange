// TEST(MatchingEngine, InsertBuyOrder)
// {
//     MatchingEngine engine;

//     Order order(
//         1,
//         OrderType::LIMIT,
//         1,
//         100,
//         Side::BUY,
//         100
//     );

//     engine.processOrder(order);

//     EXPECT_EQ(engine.getOrderBook().bids.size(),1);
// }