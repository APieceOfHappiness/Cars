// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Entity.h"
#include "CoreMinimal.h"
#include "BaseCar.h"
#include "EvolutionProcessor.h"
#include "CarAI.generated.h"

/**
 * 
 */

enum { DEAD, ALIVE };

UCLASS()
class CARPLEASE_API ACarAI : public ABaseCar, public Entity
{
	GENERATED_BODY()
public:
	ACarAI() = default;
	void InitializeObject(FVector Loc, EvolutionProcessor* Brain, int* still_alive);
	float Fitness() override;

private:
	bool MayThink = false;
	int* still_alive = nullptr;
	bool State = ALIVE;
	float Coins = 0.f;


protected: 
	EvolutionProcessor* Brain;

	bool IsDead() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
