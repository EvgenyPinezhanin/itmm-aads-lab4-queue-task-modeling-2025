// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tcomputecentermodel.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TComputeCenterModel_H__
#define __TComputeCenterModel_H__

#include <vector>

#include <tqueue.h>

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

  //Геттеры для тестов
  size_t GetCountCycles() const noexcept { return CountCycles; }
  size_t GetQueueSize() const noexcept { return QueueSize; }
  double GetQ1() const noexcept { return q1; }
  double GetQ2() const noexcept { return q2; }
  size_t GetCountTasks() const noexcept { return CountTasks; }
  size_t GetCountFailure() const noexcept { return CountFailure; }
  size_t GetCountAvrCycles() const noexcept { return CountAvrCycles; }
  size_t GetCountStall() const noexcept { return CountStall; }

};

#endif
