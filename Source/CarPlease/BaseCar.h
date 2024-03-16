// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <vector>

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Components/CapsuleComponent.h"
#include "BaseCar.generated.h"


UCLASS()
class CARPLEASE_API ABaseCar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int TicksForLiving = 500;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Body;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Person;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Wheel1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Wheel2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Wheel3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Wheel4;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Hinge1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Hinge2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Hinge3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UStaticMeshComponent* Hinge4;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* WheelAxis1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* WheelAxis2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* WheelAxis3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* WheelAxis4;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* HingeSuspension1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* HingeSuspension2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* HingeSuspension3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyParts")
		UPhysicsConstraintComponent* HingeSuspension4;

	int ReactionSpeed = 5;

	int ReactionTimer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		float AngleBack = 1; // ???

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		float AngleFront = 1; // ???

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		FVector StartPosition = FVector(0.f, 0.f, 150.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		float RayLen = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		float AngleLimit = 10.f;
	float CurAngle = 0.f;

	void Drive(float Power);

	void Turn(float Angle);

public:
	std::vector<float> GetEnvInfo();
	float GetDistToTheClosestObject(float Angle);
	void InitializeObject(FVector Loc);
	// Called every frame
};
