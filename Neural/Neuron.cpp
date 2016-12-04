#include "stdafx.h"
#include "Neuron.h"

Mismatch_exception::Mismatch_exception(std::string _Str) : Str(_Str)
{
}

const char * Mismatch_exception::What()
{
	return Str.c_str();
}

Neuron::Neuron(int _Dim, std::vector<TYPE> _W, std::function<TYPE(std::vector<TYPE>&, std::vector<TYPE>&)> _SF, std::function<TYPE(TYPE)> _AF)
{
	Dimension = _Dim;
	Wheights = _W;
	SummateFunc = _SF;
	ActivateFunc = _AF;
}

std::vector<TYPE> Neuron::GetWeights()
{
	return Wheights;
}

void Neuron::SetWeights(std::vector<TYPE> NewWeightes)
{
	if (NewWeightes.size() != Dimension+1)
	{
		throw Mismatch_exception("Yup, mismatch");
	}
	Wheights = NewWeightes;
}

TYPE Neuron::Process(std::vector<TYPE> Input)
{
	return ActivateFunc(SummateFunc(Input, Wheights));
}
