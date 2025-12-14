// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Пинежанин Е.С.
//
// Тестирование модели вычислительного центра

#include <iostream>
#include <random>
#include <locale.h>
#include "tcomputecentermodel.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	size_t CountCycles = 100000;
	size_t QueueSize = 16;
	double q1 = 0.25;
	double q2 = 0.35;
	srand(5);
	TComputeCenterModel model(CountCycles, QueueSize, q1, q2);
	model.Model();

	std::cout << "Тест\n";

	model.PrintResult();

	return 0;
}
