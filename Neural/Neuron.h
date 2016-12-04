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
	/*���������� ������ �������
	� ����� ������ �� ��������� �������� ��� ������� ������� ������� �����. � ������ ����������� �������
	����� �� ������� ������ ������� ������� �����. �� ��� ��� ��� ������ �����*/
	int Dimension;

	//����. �� �� ���������. � �������� ����. ������� ���������
	std::vector<TYPE> Wheights;

	/*����������� �������. 
	������ �������� - ������ �������� ��������
	������ �������� - ������ �����.
	������ �������� - ��������.
	���������� ���� �����*/
	std::function<TYPE(std::vector<TYPE>&, std::vector<TYPE>&)> SummateFunc;

	/*������������� �������. ��� ��� ������: ��������� ��������� ����������� �-��� � ���������� ������� �����������*/
	std::function<TYPE(TYPE)> ActivateFunc;

	
	

public:

	//������ ��������� �������������� ����
	Neuron(int _Dim,
		std::vector<TYPE> _W,
		std::function<TYPE(std::vector<TYPE>&, std::vector<TYPE>&)> _SF,
		std::function<TYPE(TYPE)> _AF);

	std::vector<TYPE> GetWeights();
	void SetWeights(std::vector<TYPE> NewWeightes);

	/*�������� �-���. �������� ������ ����� ������ � ��������� ��������*/
	TYPE Process(std::vector<TYPE> Input);


};