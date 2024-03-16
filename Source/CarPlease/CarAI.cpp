// Fill out your copyright notice in the Description page of Project Settings.


#include "CarAI.h"

void ACarAI::InitializeObject(FVector Loc, EvolutionProcessor* Brain, int* still_alive) {
	this->ABaseCar::InitializeObject(Loc);
	this->still_alive = still_alive;
	if (this->still_alive) {
		(*this->still_alive)++;
	}
	if (this->Brain) {
		delete this->Brain;
	}
	this->Brain = Brain;
}

void ACarAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->State == ALIVE) {
		if (this->ReactionTimer == 0) {
			std::vector<float> EnvInfo = this->GetEnvInfo();
			std::vector<float> Decision = this->Brain->MakeADecision(EnvInfo);
			//UE_LOG(LogTemp, Warning, TEXT("size: %d"), EnvInfo.size());
			//UE_LOG(LogTemp, Warning, TEXT("env_info: %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f"), EnvInfo[0], EnvInfo[1], EnvInfo[2], EnvInfo[3], EnvInfo[4], EnvInfo[5], EnvInfo[6], EnvInfo[7], EnvInfo[8], EnvInfo[9], EnvInfo[10]);
			UE_LOG(LogTemp, Warning, TEXT("env_info: %f, %f, %f, %f, %f, %f"), EnvInfo[0], EnvInfo[1], EnvInfo[2], EnvInfo[3], EnvInfo[4], EnvInfo[5]);
			//UE_LOG(LogTemp, Warning, TEXT("decision: %f, %f"), Decision[0], Decision[1]);

			//if (Decision[0] > 0) {
			//	this->Drive(500000.f * Decision[1]);
			//}
			if (this->MayThink) {
				this->Drive(500000.f);

				if (Decision[0] < -1) {
					Decision[0] = -1;
				}
				else if (Decision[0] > 1) {
					Decision[0] = 1;
				}
				this->Turn(Decision[0] * this->AngleLimit);
			}

			//if (Decision[0] > 0) {
			//	this->Turn(Decision[1] * this->AngleLimit);
			//}
		}
		this->ReactionTimer++;
		if (this->ReactionTimer == this->ReactionSpeed) {
			this->ReactionTimer = 0;
			this->MayThink = true;
		}

		if (!this->TicksForLiving) {
			this->State = DEAD;
			if (this->still_alive) {
				(*this->still_alive)--;
			}
			this->Brain = nullptr;
		}
		this->TicksForLiving--;
	}
}

bool ACarAI::IsDead() {
	return this->State;
}


float ACarAI::Fitness()
{
	//return this->Coins + (this->StartPosition - this->Body->GetComponentLocation()).Size();
	return this->Coins + (this->Body->GetComponentLocation().Y - this->StartPosition.Y);
}

void ACarAI::BeginPlay()
{
	Super::BeginPlay();
	EvolutionProcessor* brain = new EvolutionProcessor();
	brain->InitializeWeights(6, 1);
	this->InitializeObject(this->StartPosition, brain, nullptr);
}
