// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tcomputecentermodel.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TComputeCenterModel_H__
#define __TComputeCenterModel_H__

#include <vector>

#include "tqueue.h"

class TComputeCenterModel {
private:
  size_t CountCycles; // количество тактов имитации
  size_t QueueSize; // размер очереди задач
  double q1; // Интенсивность потока задач (вероятность появления новой задачи)
  double q2; // Производительность процессора (вероятность выполнения задачи)

  TQueue<size_t> TaskQueue;

  size_t CountTasks; // количество поступивших в вычислительную систему заданий
  size_t CountFailure; // количество отказов в обслуживании заданий из-за переполнения очереди
  size_t CountAvrCycles; // среднее количество тактов выполнения задания
  size_t CountStall; // количество тактов простоя процессора из-за отсутствия в очереди заданий

public:
  TComputeCenterModel(size_t _CountCycles = 100, size_t _QueueSize = 10, double _q1 = 0.5, double _q2 = 0.5);

  void SetParameters(size_t _CountCycles = 100, size_t _QueueSize = 10, double _q1 = 0.5, double _q2 = 0.5);

  void Model(); // запуск моделирования

  void PrintResult() const; // вывод в консоль результатов моделирования
  
  // Геттеры для тестирования
  size_t GetCountTasks() const { return CountTasks; }
  size_t GetCountFailure() const { return CountFailure; }
  size_t GetCountStall() const { return CountStall; }
  size_t GetCountAvrCycles() const { return CountAvrCycles; }
  double GetFailureProbability() const;
  double GetStallProbability() const;
  double GetAverageTaskTime() const;
};

#endif