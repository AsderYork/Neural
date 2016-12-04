#include "stdafx.h"
#include "TeachingGround.h"

TeachingEngine::TeachingEngine(float _LR, float _E, int _AE, Neuron* _TN, int _DIM) : LerningRate(_LR), EPSILON(_E), AlowedSteps(_AE), TestedNeuron(_TN)
{
	Dimension = _DIM;
	TmpGen = 0;
}

void TeachingEngine::SetLF(std::function<float(TYPE, TYPE)> _LF)
{
	LossFunc = _LF;
}

void TeachingEngine::SetLERF(std::function<std::vector<TYPE>(std::vector<TYPE>, std::vector<TestExpect>, std::vector<TYPE>, std::function<float(TYPE, TYPE)>)> _LERF)
{
	LerningFunc = _LERF;
}

void TeachingEngine::RegisterTest(TestExpect Test)
{
	/*Так как смещение у нас записано в нулевой позиции, во входном векторе всегда должна быть единица
	Но в целом вызывающий код об этом думать не должен. Потому мы просто добавляем в начало массива ввода эту единицу*/
	std::vector<TYPE> AugInput = { 1 };
	for (int i = 0; i < Test.Input.size(); i++) { AugInput.push_back(Test.Input[i]); }

	TestExpect AugTest(AugInput,Test.Result);

	Cases.push_back(AugTest);
}

float TeachingEngine::DoGeneration()
{
	float Error = 0;
	do {
		Error = 0;
		if (AlowedSteps - TmpGen <= 0)		{return 0.0f;}
		printf("So now we're on a %i generation. Only %i remains!\n", TmpGen, AlowedSteps - TmpGen);

		printf("|TESTNUM  |");
		for (int i = 0; i < Dimension; i++) {
			printf("VAL#%-5i|", i + 1);
		}
		printf("X|PREDICTED|RESULT   |DIFF     |\n");

		std::vector<TYPE> Results;
		//Отрисовка и заполнение результатов
		for (int i = 0; i < Cases.size(); i++)
		{
			printf("|%-9i", i);
			for (int j = 0; j < Dimension;j++)
			{
				printf("|%- 9.4f", Cases[i].Input[j + 1]);
			}
			printf("|X|%- 9.4f|", Cases[i].Result);

			Results.push_back(TestedNeuron->Process(Cases[i].Input));
			printf("%- 9.4f|", Results[i]);
			printf("%- 9.4f|", Cases[i].Result - Results[i]);

			printf("\n");
		}

		for (int i = 0; i < Results.size(); i++)
		{
			Error += LossFunc(Cases[i].Result, Results[i]);
		}
		printf("ERROR:%- 9.4f\n", Error);

		std::vector<TYPE> NewWeights;

		std::vector<TYPE> TmpWeights = TestedNeuron->GetWeights();


		printf("[LERNING] This is weights we allready have\n");
		for (int i = 0; i < TmpWeights.size(); i++) { printf("|W#%-7i", i); }
		printf("|\n");
		for (int i = 0; i < TmpWeights.size(); i++) { printf("|%- 9.4f", TmpWeights[i]); }
		printf("|\n");




		printf("[LerningSpeed:%-9.6f] This is the differences in weights we apply\n", LerningRate);
		NewWeights = LerningFunc(TmpWeights, Cases, Results, LossFunc);
		for (int i = 0; i < NewWeights.size(); i++)
		{
			NewWeights[i] *= LerningRate;
		}
		for (int i = 0; i < TmpWeights.size(); i++) { printf("|%- 9.4f", NewWeights[i]); }
		printf("|\n");

		for (int i = 0; i < NewWeights.size(); i++)
		{
			TmpWeights[i] += NewWeights[i];
		}

		TestedNeuron->SetWeights(TmpWeights);
		TmpGen++;
	} while (abs(Error) > abs(EPSILON));
	return 0.0f;
}
