#pragma once
#include "stdafx.h"

typedef float TYPE;

class Mismatch_exception : public std::exception
{
	private:
	std::string Str;
public:
	Mismatch_exception(std::string _Str);
	const char* What();
};

class Neuron
{
private:
	/*Количество входов нейрона
	К слову теперь мы сохраняем смещение как нулевой элемент массива весов. А значит размерность нейрона
	будет на единицу меньше размера массива весов. Но как раз под размер входа*/
	int Dimension;

	//Веса. Мы их сохраняем. И смещение тоже. Нулевым элементом
	std::vector<TYPE> Wheights;

	/*Сумматорная функция. 
	Первый параметр - массив входящих значений
	Второй параметр - массив весов.
	Третий параметр - Смещение.
	Возвращает одно число*/
	std::function<TYPE(std::vector<TYPE>&, std::vector<TYPE>&)> SummateFunc;

	/*Активационная функция. Тут все просто: принимает результат сумматорной ф-ции и возвращает уровень возбуждения*/
	std::function<TYPE(TYPE)> ActivateFunc;

	
	

public:

	//Просто заполняет соответсвующие поля
	Neuron(int _Dim,
		std::vector<TYPE> _W,
		std::function<TYPE(std::vector<TYPE>&, std::vector<TYPE>&)> _SF,
		std::function<TYPE(TYPE)> _AF);

	std::vector<TYPE> GetWeights();
	void SetWeights(std::vector<TYPE> NewWeightes);

	/*Основная ф-ция. Проводит данные через нейрон и вычисляет значение*/
	TYPE Process(std::vector<TYPE> Input);


};