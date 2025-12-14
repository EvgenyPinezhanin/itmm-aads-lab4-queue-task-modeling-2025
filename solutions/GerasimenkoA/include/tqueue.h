// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tqueue.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TQueue_H__
#define __TQueue_H__

#include <cstddef>      
#include <stdexcept>    
#include <utility> 

using namespace std;

const size_t DefaultMemSize = 1024; // стандартный размер памяти для очереди

template<typename T>
class TQueue {
protected:
    T* pMem;            // указатель на массив элементов
    size_t MemSize;     // размер памяти для СД
    size_t DataCount;   // количество элементов в СД
    size_t Head;        // индекс начала очереди
    size_t Tail;        // индекс конца очереди

    size_t GetNextIndex(size_t index) const noexcept // получить следующий индекс
    {
        return (index + 1) % MemSize;
    }

public:
    explicit TQueue(size_t Size = DefaultMemSize) : MemSize(Size), Head(0), Tail(0), DataCount(0)
    {
        if (MemSize == 0) throw out_of_range("Queue size should be greater than zero.");
        pMem = new T[MemSize]();
    }

    TQueue(TQueue&& other) noexcept :
        pMem(other.pMem), MemSize(other.MemSize), DataCount(other.DataCount),
        Head(other.Head), Tail(other.Tail)
    {
        other.pMem = nullptr;
        other.MemSize = 0;
        other.DataCount = 0;
        other.Head = 0;
        other.Tail = 0;
    }

    ~TQueue()
    {
        if (pMem != nullptr) {
            delete[] pMem;
            pMem = nullptr;
        }
        
    }

    TQueue& operator=(TQueue&& other) noexcept 
    {
        if (this != &other) {
            delete[] pMem;
            pMem = other.pMem;
            MemSize = other.MemSize;
            DataCount = other.DataCount;
            Head = other.Head;
            Tail = other.Tail;

            other.pMem = nullptr;
            other.MemSize = 0;
            other.DataCount = 0;
            other.Head = other.Tail = 0;
        }
        return *this;
    }


    size_t size() const { return DataCount; }

    bool IsEmpty() const 
    {
        return DataCount == 0;
    }

    bool IsFull() const
    {
        return DataCount == MemSize;
    }

    void Push(const T& val)
    {
        if (IsFull()) throw out_of_range("Queue overflow.");
        pMem[Tail] = val;
        Tail = GetNextIndex(Tail);
        ++DataCount;
    }

    T Pop()
    {
        if (IsEmpty()) throw out_of_range("Queue underflow.");
        T tmp = pMem[Head];
        Head = GetNextIndex(Head);
        --DataCount;
        return tmp;
    }

    /*void clear() noexcept {
        if (pMem != nullptr) {
            delete[] pMem;
            pMem = nullptr;
        }
        DataCount = 0;
        Head = 0;
        Tail = 0;
    }*/

    
};

#endif
