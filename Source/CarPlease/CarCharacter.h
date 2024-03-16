// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCar.h"
#include "CarCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CARPLEASE_API ACarCharacter : public ABaseCar
{
	GENERATED_BODY()

protected:
	void MoveForward(float Axis);

	void MoveLeftRight(float Axis);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
};
