// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tcomputecentermodel.cpp
//
// Copyright (c) Пинежанин Е.С.

#include <tcomputecentermodel.h>

#include <iostream>
#include <cstdlib>

using namespace std;

double GetRandomValue() // вернуть случайное значение от 0.0 до 1.0
{
	return static_cast<double>(rand()) / RAND_MAX;
}

TComputeCenterModel::TComputeCenterModel(size_t _CountCycles, size_t _QueueSize, double _q1, double _q2):
	CountCycles(_CountCycles), 
	QueueSize(_QueueSize), 
	q1(_q1), q2(_q2), 
	TaskQueue(_QueueSize), 
	CountTasks(0), 
	CountFailure(0), 
	CountAvrCycles(0), 
	CountStall(0) {}

void TComputeCenterModel::SetParameters(size_t _CountCycles, size_t _QueueSize, double _q1, double _q2)
{
	CountCycles = _CountCycles;
	QueueSize = _QueueSize;
	q1 = _q1; q2 = _q2;

	CountTasks = 0;
	CountFailure = 0;
	CountAvrCycles = 0;
	CountStall = 0;

	TaskQueue.~TQueue<size_t>();
	new(&TaskQueue) TQueue<size_t>(QueueSize);
	//TaskQueue = TQueue<size_t>(QueueSize); //Иначе крашится при перезаписи, ибо нет реализации оператора =
}

void TComputeCenterModel::Model()
{
	size_t Сts = 0;			//завершенная задача
	size_t TotalCycles = 0; //общее кол-во циклов на текущую задачу 
	size_t CyclesByOne = 0; //кол-во циклов на задачу
	bool busy = false;

	for (size_t i = 0; i < CountCycles; ++i) {
		//Появление задачи с шансом q1
		if (GetRandomValue() < q1) {
			if (TaskQueue.IsFull()) {
				++CountFailure;
			}
			else {
				TaskQueue.Push(1);
				++CountTasks;
			}
		}
		
		if (!busy) {
			if (!TaskQueue.IsEmpty()) {
				TaskQueue.Pop();
				busy = true;
				CyclesByOne = 0;
			}
			else {
				++CountStall;
			}
		}
		if (busy) {
			++CyclesByOne;
			//Завершение задачи с шансом q2
			if (GetRandomValue() < q2) {
				++Сts;
				TotalCycles += CyclesByOne;
				busy = false;
				CyclesByOne = 0;
			}
		}
	}

	if (Сts > 0) {
		CountAvrCycles = static_cast<size_t>(TotalCycles / Сts);
	}
	else { CountAvrCycles = 0; }
}

void TComputeCenterModel::PrintResult() const
{
	cout << "Result\n";
	cout << "CountCycles:    " << CountCycles << '\n';
	cout << "QueueSize:      " << QueueSize << '\n';
	cout << "q1:             " << q1 << '\n';
	cout << "q2:             " << q2 << '\n';
	cout << "CountTasks:     " << CountTasks << '\n';
	cout << "CountFailure:   " << CountFailure << '\n';
	cout << "CountAvrCycles: " << CountAvrCycles << '\n';
	cout << "CountStall:     " << CountStall << '\n';

}
