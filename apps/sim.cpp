#include "../include/MatchingEngine.h"
#include <iostream>
#include <fstream>
#include <string>
size_t loadConfigCapacity(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Warning: config.txt not found. Defaulting to 10000.\n";
        return 10000;
    }
    size_t capacity = 10000;
    file >> capacity;
    return capacity;
}
int32_t main()
{
    size_t capacity = loadConfigCapacity("./config.txt");

    std::cout << "Starting Exchange Simulator with Trade Log Capacity: " << capacity << "\n";

    // 2. Pass it down to the engine
    MatchingEngine engine(capacity);
    // auto start = std::chrono::steady_clock::now();
    Order order1(1, OrderType::LIMIT, 2, 10, Side::BUY, 20);
    Order order2(2, OrderType::LIMIT, 2, 10, Side::BUY, 25);
    Order order3(3, OrderType::LIMIT, 2, 10, Side::BUY, 30);
    Order order4(4, OrderType::LIMIT, 2, 10, Side::BUY, 35);
    Order order5(5, OrderType::LIMIT, 2, 10, Side::BUY, 40);
    Order order6(6, OrderType::LIMIT, 2, 81, Side::BUY, 40);
    Order order7(7, OrderType::LIMIT, 2, 10, Side::SELL, 20);
    Order order8(8, OrderType::LIMIT, 2, 10, Side::SELL, 25);
    Order order9(9, OrderType::LIMIT, 2, 5, Side::SELL, 30);
    engine.processOrder(order1);
    engine.processOrder(order2);
    engine.processOrder(order3);
    engine.processOrder(order4);
    engine.processOrder(order5);
    engine.processOrder(order6);
    engine.processOrder(order7);
    engine.processOrder(order8);
    engine.processOrder(order9);
    engine.cancelOrder(order6.orderId);

    // auto end = std::chrono::steady_clock::now();
    // std::cout<<(end-start)/10;
    // Orderbook orderbook=engine.getOrderbook();
    // for(auto &it:orderbook.asks){
    //     for(auto &ti:it.second){
    //         std::cout<<it.first<<"  "<<ti.remainingQuantity<<"   "<<ti.originalQuantity<<"   "<<ti.userId<<std::endl;
    //     }
    // }
    // for(auto &it:orderbook.bids){
    //     for(auto &ti:it.second){
    //          std::cout<<it.first<<"  "<<ti.remainingQuantity<<"   "<<ti.originalQuantity<<"   "<<ti.userId<<std::endl;
    //     }
    // }
    // Logger& logger = engine.getOrderbook().getLogger();
    // logger.print();
}