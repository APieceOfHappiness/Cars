// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <vector>
#include <Entity.h>
#include "CoreMinimal.h"

/**
 * 
 */
class CARPLEASE_API EvolutionProcessor
{

	std::vector<std::vector<float>> Weights;

public:
	EvolutionProcessor() = default;
	EvolutionProcessor(EvolutionProcessor* Brain);

	void InitializeWeights(int LenIn, int LenOut);

	std::vector<float> MakeADecision(std::vector<float>& Genom) const;

	void Mutate();

	static void Cross(EvolutionProcessor* Brain1, EvolutionProcessor* Brain2);

	int Size(int axis) const;

	std::vector<std::vector<float>>& GetWeights();
};
