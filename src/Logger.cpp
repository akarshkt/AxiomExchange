#include "../include/Logger.h"
#include <iostream>
#include <fstream> // Required for file operations
#include <string>
#include "../include/Order.h"

void appendTradesLogToFile(const std::string &filename, Trade &trade)
{
    // Open the file with the std::ios::app flag
    std::ofstream file(filename, std::ios::app);

    // Always check if the file opened successfully
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    file << trade.getTradeId() << "  "
         << trade.buyer << "  " << trade.buyOrderId
         << "  " << trade.seller << "  "
         << trade.sellOrderId << "  "
         << trade.executionPrice << "  "
         << trade.quantity << "  "
         << (formatNanosecondTimestamp(trade.timestamp)) << "\n";
}
void appendOrderLogToFile(const std::string &filename, Order &order)
{

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    file << order.orderId
         << "  " << (order.orderType == OrderType::MARKET ? "Market" : (OrderType::LIMIT == order.orderType ? "LIMIT" : "STOP")) << "  "
         << order.originalQuantity << "  "
         << order.remainingQuantity << "  "
         << order.price << "  "
         << (order.side == Side::BUY ? "BUY" : "SELL") << "  "
         << (formatNanosecondTimestamp(order.timestamp)) << "  "
         << order.userId << "  "
         << order.orderStatus << "\n";
}
Logger::Logger(size_t capacity) : totalTradeLog(capacity), ringbuffer(capacity) {}
void Logger::print()
{
    ringbuffer.print();
}
void Logger::writeToDisk(Trade &trade, EVENT event)
{
    appendTradesLogToFile("trades.txt", trade);
}
void Logger::writeToDisk(Order &order, EVENT event)
{
    if (event == EVENT::CANCEL)
        appendOrderLogToFile("cancels.txt", order);
    else if (event == EVENT::ORDER)
        appendOrderLogToFile("orders.txt", order);
}

void Logger::logTrade(Trade &trade)
{
    ringbuffer.push(trade);
    writeToDisk(trade, EVENT::TRADE);
}
void Logger::logOrder(Order &order)
{
    writeToDisk(order, EVENT::ORDER);
}
void Logger::logCancelOrder(Order &order)
{
    writeToDisk(order, EVENT::CANCEL);
}
Ringbuffer<Trade>& Logger::getRingBuffer(){
    return ringbuffer;
}
size_t Logger::getSizeofRingbuffer(){
    return ringbuffer.size();
}
