// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tqueue.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TQueue_H__
#define __TQueue_H__

#include <stdexcept>

const int DefaultMemSize = 1024; // стандартный размер памяти для очереди

template<typename T>
class TQueue {
protected:
    T* pMem; // указатель на массив элементов
    size_t MemSize; // размер памяти для СД
    size_t DataCount; // количество элементов в СД
    size_t Head; // индекс начала очереди
    size_t Tail; // индекс конца очереди

    int GetNextIndex(int index) const // получить следующий индекс
    {
        return (index + 1) % MemSize;
    }

public:
    explicit TQueue(size_t Size = DefaultMemSize) : MemSize(Size), Head(0), Tail(0), DataCount(0)
    {
        if (Size == 0) {
            throw std::invalid_argument("Queue size must be greater than 0");
        }
        pMem = new T[MemSize];
    }

    TQueue(const TQueue& other) : MemSize(other.MemSize), Head(other.Head), 
                                   Tail(other.Tail), DataCount(other.DataCount)
    {
        pMem = new T[MemSize];
        for (size_t i = 0; i < MemSize; ++i) {
            pMem[i] = other.pMem[i];
        }
    }

    ~TQueue()
    {
        delete[] pMem;
    }

    TQueue& operator=(const TQueue& other)
    {
        if (this != &other) {
            delete[] pMem;
            
            MemSize = other.MemSize;
            Head = other.Head;
            Tail = other.Tail;
            DataCount = other.DataCount;
            
            pMem = new T[MemSize];
            for (size_t i = 0; i < MemSize; ++i) {
                pMem[i] = other.pMem[i];
            }
        }
        return *this;
    }

    size_t size() const
    {
        return DataCount;
    }

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
        if (IsFull()) {
            throw std::overflow_error("Queue is full");
        }
        
        pMem[Tail] = val;
        Tail = GetNextIndex(Tail);
        DataCount++;
    }

    T Pop()
    {
        if (IsEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        
        T value = pMem[Head];
        Head = GetNextIndex(Head);
        DataCount--;
        return value;
    }

    T& Front()
    {
        if (IsEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return pMem[Head];
    }

    const T& Front() const
    {
        if (IsEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return pMem[Head];
    }

    void Clear()
    {
        Head = 0;
        Tail = 0;
        DataCount = 0;
    }
};

#endif