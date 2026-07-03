#include "../include/TradeLogs.h"
#include <iostream>
#include <fstream> // Required for file operations
#include <string>
void appendLogToFile(const std::string& filename, Trade &trade) {
    // Open the file with the std::ios::app flag
    std::ofstream file(filename, std::ios::app);

    // Always check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    // Write your message followed by a newline
    file << trade.getTradeId()<<"  "<< trade.buyer<<"  "<<trade.buyOrderId<<"  "<< trade.seller<<"  "<<trade.sellOrderId<<"  "<< trade.executionPrice<<"  "<<trade.quantity<<"  "<< trade.timestamp<<"\n";

    // File closes automatically when the function ends and 'file' goes out of scope
}
TradeLogs::TradeLogs(size_t capacity) : totalTradeLog(capacity), ringbuffer(capacity) {
    
}

void TradeLogs::print() {
    ringbuffer.print();
}
void TradeLogs::writeToDisk(Trade trade){
    appendLogToFile("log.txt",trade);
}
void TradeLogs::logTrade(Trade trade) {
    ringbuffer.push(trade);
    writeToDisk(trade);
}
