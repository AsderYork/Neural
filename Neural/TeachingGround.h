#pragma once
#include "stdafx.h"
#include "Neuron.h"

/*Тестовые ожидания. По-сути это и есть "Эксперемент". Он состоит из входного вектора и значения, которое мы ожидаем в итоге*/
struct TestExpect
{
	std::vector<TYPE> Input;
	TYPE Result;

	TestExpect(std::vector<TYPE> _Input, TYPE _Result) : Input(_Input), Result(_Result) {}
};

class TeachingEngine
{
private:
	std::vector<TestExpect> Cases;
	float LerningRate;
	int Dimension;

	float EPSILON;

	int AlowedSteps;
	int TmpGen;

	Neuron* TestedNeuron;

	/*Целевая цункция. Отражает успешность нейрона на данном проходе по всем эксперементам
	Возвращает она значение float, которое чем ближе к нулю, тем лучше
	Первый параметр - массив предсказанных значений первым
	Второй параметр - массив результатов
	Само собой элементы массивов должны соответствовать одним и тем же тестам*/
	//std::function<float(std::vector<TYPE>, std::vector<TYPE>)> TargetFunc;

	/*Функция потери. Отражает успешность нейрона на данном эксперементе
	Возвращает она значение float, которое чем ближе к нулю, тем лучше
	Первый параметр - Предсказанное значение
	Второй параметр - Полученный результат*/
	std::function<float(TYPE,TYPE)> LossFunc;

	/*Обучающая ф-ция.
	Первый параметр - веса
	Второй параметр - Тесты
	Третий параметр - Результаты
	Четвертый параметр - Функция потери
	Ну а возвращает она новые веса
	*/
	std::function<std::vector<TYPE>(std::vector<TYPE>, std::vector<TestExpect>, std::vector<TYPE>, std::function<float(TYPE, TYPE)>)> LerningFunc;

public:
	TeachingEngine(float _LR, float _E, int _AE, Neuron* _TN, int _DIM);

	void SetLF(std::function<float(TYPE, TYPE)> _LF);
	void SetLERF(std::function<std::vector<TYPE>(std::vector<TYPE>, std::vector<TestExpect>, std::vector<TYPE>, std::function<float(TYPE, TYPE)>)> _LERF);

	void RegisterTest(TestExpect Test);

	float DoGeneration();
};