// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CarAI.h"
#include "EvolutionProcessor.h"
#include "CarGen.generated.h"

UCLASS()
class CARPLEASE_API ACarGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarGen();
protected:
	int EpochCnt = 1;
	int GenerationCnt = 1;

	int RepCnt = 1;
	int CurRep = 0;

	// every car in generation has the link of this variable
	int still_alive = 0; 

	virtual void BeginPlay() override;
	std::vector<EvolutionProcessor*> Brains;
	std::vector<ACarAI*> Entities;
	std::vector<float> Fitness;

public:	
	void SpawnGeneration(int size);
	void FinishSimulation();
	void StartSimulation();
	void Selection(int NumComp);
	void Mutate(float probability);
	void Cross(float probability);

	bool WaitingForEverybodyToDie();

	virtual void Tick(float DeltaTime) override;
};
