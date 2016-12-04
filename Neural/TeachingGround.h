#pragma once
#include "stdafx.h"
#include "Neuron.h"

/*�������� ��������. ��-���� ��� � ���� "�����������". �� ������� �� �������� ������� � ��������, ������� �� ������� � �����*/
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

	/*������� �������. �������� ���������� ������� �� ������ ������� �� ���� �������������
	���������� ��� �������� float, ������� ��� ����� � ����, ��� �����
	������ �������� - ������ ������������� �������� ������
	������ �������� - ������ �����������
	���� ����� �������� �������� ������ ��������������� ����� � ��� �� ������*/
	//std::function<float(std::vector<TYPE>, std::vector<TYPE>)> TargetFunc;

	/*������� ������. �������� ���������� ������� �� ������ ������������
	���������� ��� �������� float, ������� ��� ����� � ����, ��� �����
	������ �������� - ������������� ��������
	������ �������� - ���������� ���������*/
	std::function<float(TYPE,TYPE)> LossFunc;

	/*��������� �-���.
	������ �������� - ����
	������ �������� - �����
	������ �������� - ����������
	��������� �������� - ������� ������
	�� � ���������� ��� ����� ����
	*/
	std::function<std::vector<TYPE>(std::vector<TYPE>, std::vector<TestExpect>, std::vector<TYPE>, std::function<float(TYPE, TYPE)>)> LerningFunc;

public:
	TeachingEngine(float _LR, float _E, int _AE, Neuron* _TN, int _DIM);

	void SetLF(std::function<float(TYPE, TYPE)> _LF);
	void SetLERF(std::function<std::vector<TYPE>(std::vector<TYPE>, std::vector<TestExpect>, std::vector<TYPE>, std::function<float(TYPE, TYPE)>)> _LERF);

	void RegisterTest(TestExpect Test);

	float DoGeneration();
};