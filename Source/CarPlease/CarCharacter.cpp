// Fill out your copyright notice in the Description page of Project Settings.


#include "CarCharacter.h"

void ACarCharacter::MoveLeftRight(float Axis) {
	if (Controller != NULL) {
		if (Axis != 0) {
			this->CurAngle += Axis / 30;
			if (this->CurAngle > this->AngleLimit) {
				this->CurAngle = this->AngleLimit;
			}
			else if (this->CurAngle < -this->AngleLimit) {
				this->CurAngle = -this->AngleLimit;
			}
		}
		else {
			this->CurAngle = 0;
		}
	}
	this->Turn(this->CurAngle);
}

void ACarCharacter::MoveForward(float Axis) {
	if (Axis > 0) {
		this->Drive(50000.f);
	}
	else if (Axis < 0) {
		this->Drive(-50000.f);
	}
}

void ACarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACarCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ACarCharacter::MoveLeftRight);
}

void ACarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->ReactionTimer == 0) {
		std::vector<float> EnvInfo = this->GetEnvInfo();
		UE_LOG(LogTemp, Warning, TEXT("env_info: %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f"), EnvInfo[0], EnvInfo[1], EnvInfo[2], EnvInfo[3], EnvInfo[4], EnvInfo[5], EnvInfo[6], EnvInfo[7], EnvInfo[8], EnvInfo[9], EnvInfo[10]);
	}
	this->ReactionTimer++;
	if (this->ReactionTimer == this->ReactionSpeed) {
		this->ReactionTimer = 0;
	}
}
