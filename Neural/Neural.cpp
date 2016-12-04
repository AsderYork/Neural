// Neural.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include "TeachingGround.h"
#include <conio.h>

int main()
{
	auto SumFunc = [](std::vector<TYPE> I, std::vector<TYPE> W) ->TYPE {
		TYPE Return=0;
		for (int i = 0; i < W.size(); i++)
		{
			Return += W[i] * I[i];
		 }
		return Return;			 
	};


	auto Clamp = [](TYPE I) ->TYPE {if (I > 0) { return 1.0f; } return 0.0f; };
	std::vector<TYPE> W = { 1,1,1 };
	Neuron NE(2,W,SumFunc, Clamp);
	TeachingEngine TE(0.4f,0.001f, 100, &NE, 2);


	TE.RegisterTest(TestExpect({ 0,0 }, 0));
	TE.RegisterTest(TestExpect({ 1,0 }, 0));
	TE.RegisterTest(TestExpect({ 0,1 }, 0));
	TE.RegisterTest(TestExpect({ 1,1 }, 1));

	auto LossFunc = [](TYPE PRED, TYPE RES) -> float {return PRED - RES;};
	TE.SetLF(LossFunc);

	auto LerningFunc = [](std::vector<TYPE> W, std::vector<TestExpect> T, std::vector<TYPE> R, std::function<float(TYPE, TYPE)> LF)
		->std::vector<TYPE> {

		std::vector<TYPE> DeltaWeights;
		//«абиваем все нул€ми, что бы потом с этим сумировать
		for (int i = 0; i < W.size(); i++)		{ DeltaWeights.push_back(0);}

		TYPE TestError = 0;
		for (int i = 0; i < R.size(); i++)
		{
			TestError = LF(T[i].Result, R[i]);

			for (int j = 0; j < W.size(); j++)
			{
				DeltaWeights[j] += TestError*T[i].Input[j];
			}
		}

		return DeltaWeights;
	};

	TE.SetLERF(LerningFunc);
	TE.DoGeneration();

	char C;
	C = _getch();
    return 0;
}

