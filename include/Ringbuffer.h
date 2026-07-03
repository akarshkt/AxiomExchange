#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class Ringbuffer
{
private:
    std::vector<T> trades;
    size_t tail = 0;
    size_t head = 0;
    size_t capacity;
    size_t count = 0;

public:
    Ringbuffer(size_t n) : capacity(n)
    {
        trades.resize(n);
    }

    void push(T trade)
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

    void print()
    {
        std::cout<<"Printing Once"<<std::endl;
        if (count == 0)
        {
            std::cout << "Buffer Empty\n";
            return;
        }
        size_t current = head;
        for (size_t i = 0; i < count; ++i)
        {

            std::cout << trades[current].getTradeId() << " " ;
            current = (current + 1) % capacity;
        }
        std::cout << "\n";
    }
};

#endif
