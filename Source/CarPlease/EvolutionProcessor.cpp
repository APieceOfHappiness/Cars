// Fill out your copyright notice in the Description page of Project Settings.


#include "EvolutionProcessor.h"


void EvolutionProcessor::Cross(EvolutionProcessor* Brain1, EvolutionProcessor* Brain2) {
	if (Brain1 == Brain2) {
		return;
	}
	int rand_i = FMath::RandRange(0, Brain1->Size(1) - 1);
	int rand_j = FMath::RandRange(0, Brain1->Size(1) - 1);
	if (rand_j > rand_i) {
		int temp = rand_i;
		int rand_i = rand_j;
		int rand_j = temp;
	}
	for (int i = rand_i; i <= rand_j; i++) {
		for (int j = 0; j < Brain1->Size(0); ++j) {
			float temp = Brain1->GetWeights()[j][i];
			Brain1->GetWeights()[j][i] = Brain2->GetWeights()[j][i];
			Brain2->GetWeights()[j][i] = temp;
		}
	}
}

EvolutionProcessor::EvolutionProcessor(EvolutionProcessor* Brain)
{
	//UE_LOG(LogTemp, Warning, TEXT("Start---------- %d"), Brain->Size(-1));

	//UE_LOG(LogTemp, Warning, TEXT("Was: %f, %f"), Brain.Weights[0][0], this->Weights[0][0]);
	this->Weights.resize(Brain->Size(0), std::vector<float>(Brain->Size(1)));
	for (int i = 0; i < Brain->Size(0); i++) {
		for (int j = 0; j < Brain->Size(1); j++) {
			this->Weights[i][j] = Brain->GetWeights()[i][j];
		}
	}
}

void EvolutionProcessor::InitializeWeights(int LenIn, int LenOut)
{
	float MinValue = -1.0f;
	float MaxValue = 1.0f;

	this->Weights.resize(LenOut, std::vector<float>(LenIn)); // увеличиваем размер вектора, но не инициализируем элементы

	// заполняем элементы вектора случайными значениями
	for (int i = 0; i < LenOut; i++) {
		for (int j = 0; j < LenIn; j++) {
			this->Weights[i][j] = FMath::FRandRange(MinValue, MaxValue);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Is: %f, %f, %f, %f, %f, %f"), this->Weights[0][0], this->Weights[0][1], this->Weights[0][2], this->Weights[0][3], this->Weights[0][4], this->Weights[0][5]);
	//UE_LOG(LogTemp, Warning, TEXT("Size of weights: %d"), this->Weights.size());
}

std::vector<float> EvolutionProcessor::MakeADecision(std::vector<float>& Genom) const 
{
	std::vector<float> Answer;

	float MinValue = -1.0f;
	float MaxValue = 1.0f;

	for (int OutPutNum = 0; OutPutNum < this->Weights.size(); ++OutPutNum) {
		float Out = 0;
		for (int InPutNum = 0; InPutNum < Genom.size(); ++InPutNum) {
			Out += Genom[InPutNum] * this->Weights[OutPutNum][InPutNum];
		}
		Answer.push_back(Out);
	}
	return Answer;
}

void EvolutionProcessor::Mutate()
{
	FRandomStream RandomStream(FMath::Rand());
	int rand_i = FMath::RandRange(0, this->Weights.size() - 1);
	int rand_j = FMath::RandRange(0, this->Weights[0].size() - 1);
	this->Weights[rand_i][rand_j] += FMath::FRandRange(-0.1, 0.1);
}

int EvolutionProcessor::Size(int axis = -1) const
{
	if (axis == 0) {
		return this->Weights.size();
	}
	else if ((axis == 1) && (this->Weights.size() > 0)) {
		return this->Weights[0].size();
	}
	else if (axis == -1) {
		if (this->Weights.size() > 0) {
			return 0;
		}
		else {
			return this->Weights.size() * this->Weights[0].size();
		}
	}
	return -1;
}

std::vector<std::vector<float>>& EvolutionProcessor::GetWeights()
{
	return this->Weights;
}
