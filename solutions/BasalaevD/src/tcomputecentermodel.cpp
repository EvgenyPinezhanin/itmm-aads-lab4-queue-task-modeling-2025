// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tcomputecentermodel.cpp
//
// Copyright (c) Пинежанин Е.С.

#include "tcomputecentermodel.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

TComputeCenterModel::TComputeCenterModel(size_t _CountCycles, size_t _QueueSize, 
                                         double _q1, double _q2)
    : CountCycles(_CountCycles), QueueSize(_QueueSize), q1(_q1), q2(_q2),
      TaskQueue(_QueueSize), CountTasks(0), CountFailure(0), 
      CountAvrCycles(0), CountStall(0)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void TComputeCenterModel::SetParameters(size_t _CountCycles, size_t _QueueSize, 
                                        double _q1, double _q2)
{
    CountCycles = _CountCycles;
    QueueSize = _QueueSize;
    q1 = _q1;
    q2 = _q2;
    
    TaskQueue = TQueue<size_t>(QueueSize);
    CountTasks = 0;
    CountFailure = 0;
    CountAvrCycles = 0;
    CountStall = 0;
}

void TComputeCenterModel::Model()
{
    size_t totalTaskTime = 0;
    size_t tasksCompleted = 0;
    size_t taskProcessingTime = 0;
    bool isProcessing = false;
    
    TaskQueue = TQueue<size_t>(QueueSize);
    CountTasks = 0;
    CountFailure = 0;
    CountAvrCycles = 0;
    CountStall = 0;
    
    for (size_t cycle = 0; cycle < CountCycles; ++cycle) {
        double randVal = static_cast<double>(std::rand()) / RAND_MAX;
        if (randVal < q1) {
            CountTasks++;
            
            if (!TaskQueue.IsFull()) {
                size_t taskTime = 1 + static_cast<size_t>((1.0 - q2) * 4);
                if (taskTime < 1) taskTime = 1;
                TaskQueue.Push(taskTime);
            } else {
                CountFailure++;
            }
        }
        
        if (isProcessing) {
            taskProcessingTime--;
            
            if (taskProcessingTime == 0) {
                isProcessing = false;
                tasksCompleted++;
            }
        }
        
        if (!isProcessing && !TaskQueue.IsEmpty()) {
            taskProcessingTime = TaskQueue.Pop();
            isProcessing = true;
            totalTaskTime += taskProcessingTime;
        } else if (!isProcessing) {
            CountStall++;
        }
    }
    
    CountAvrCycles = tasksCompleted > 0 ? totalTaskTime / tasksCompleted : 0;
}

void TComputeCenterModel::PrintResult() const
{
    std::cout << "=== Результаты моделирования ===\n";
    std::cout << "Параметры модели:\n";
    std::cout << "  Количество тактов: " << CountCycles << "\n";
    std::cout << "  Размер очереди: " << QueueSize << "\n";
    std::cout << "  Интенсивность потока задач (q1): " << q1 << "\n";
    std::cout << "  Производительность процессора (q2): " << q2 << "\n\n";
    
    std::cout << "Статистика:\n";
    std::cout << "  Всего поступило задач: " << CountTasks << "\n";
    std::cout << "  Отказов в обслуживании: " << CountFailure << "\n";
    std::cout << "  Тактов простоя: " << CountStall << "\n";
    std::cout << "  Среднее время выполнения задачи: " << CountAvrCycles << " тактов\n\n";
    
    std::cout << "Вероятностные характеристики:\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "  Вероятность отказа: " << GetFailureProbability() << "\n";
    std::cout << "  Вероятность простоя: " << GetStallProbability() << "\n";
    std::cout << "  Среднее время в системе: " << GetAverageTaskTime() << " тактов\n";
    std::cout << "===============================\n";
}

double TComputeCenterModel::GetFailureProbability() const
{
    return CountTasks > 0 ? static_cast<double>(CountFailure) / CountTasks : 0.0;
}

double TComputeCenterModel::GetStallProbability() const
{
    return static_cast<double>(CountStall) / CountCycles;
}

double TComputeCenterModel::GetAverageTaskTime() const
{
    return static_cast<double>(CountAvrCycles);
}