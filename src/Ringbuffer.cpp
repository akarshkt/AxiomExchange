#include "../include/Ringbuffer.h"

void Ringbuffer::push(Trade& trade)
{
    trades[tail] = trade;
    tail = (tail + 1) % capacity;
    if (count < capacity)
    {
        count++;
    }
    else
    {
        head = (head + 1) % capacity;
    }
}
void Ringbuffer::pushListOfTrades(std::vector<Trade>& trades){
    for(auto &it:trades)
    {
        push(it);
    }
};
void Ringbuffer::print()
{
    std::cout << "Printing Once" << std::endl;
    if (count == 0)
    {
        std::cout << "Buffer Empty\n";
        return;
    }
    size_t current = head;
    for (size_t i = 0; i < count; ++i)
    {

        std::cout << trades[current].getTradeId() << " ";
        current = (current + 1) % capacity;
    }
    std::cout << "\n";
}
Trade Ringbuffer::returnTrade()
{
    return trades[((tail-1) % capacity + capacity) % capacity];
}
size_t Ringbuffer::size()
{
    return count;
}
std::vector<Trade> &Ringbuffer::getTrades()
{
    return trades;
};