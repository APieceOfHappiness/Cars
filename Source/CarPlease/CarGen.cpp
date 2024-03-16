// Fill out your copyright notice in the Description page of Project Settings.


#include "CarGen.h"
#include "Math/UnrealMathUtility.h"


ACarGen::ACarGen() {
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void ACarGen::BeginPlay()
{
	Super::BeginPlay();
	this->SpawnGeneration(this->GenerationCnt);
	this->StartSimulation();
}

void ACarGen::FinishSimulation() {
	// TODO:
	if (this->Entities.empty()) {
		return;
	}
	if (this->CurRep == 0) {
		this->Fitness.clear();
		this->Fitness.resize(this->GenerationCnt, 0);
	}
	for (int i = 0; i < this->GenerationCnt; ++i) {
		this->Fitness[i] += this->Entities[i]->Fitness() / this->RepCnt;
		this->Entities[i]->Destroy();
	}
	this->Entities.clear();
	this->CurRep++;
	if (this->CurRep == this->RepCnt) {
		this->CurRep = 0;
	}
}

void ACarGen::StartSimulation() {
	int shift = 5000;
	FVector StartPosition = GetActorLocation() + FVector(0.f, 0.f, 130);
	//FVector StartPosition = GetActorLocation() + FVector(-this->GenerationCnt * shift / 2, 500.f, 300.f);
	for (int i = 0; i < this->GenerationCnt; ++i) {
		this->Entities.push_back(GetWorld()->SpawnActor<ACarAI>(FVector(i * 100.f, i * 100.f, -20000.f), FRotator::ZeroRotator));
		//StartPosition = FVector(StartPosition.X + shift, StartPosition.Y, StartPosition.Z);
		this->Entities.back()->InitializeObject(StartPosition, this->Brains[i], &this->still_alive);
	}

	if (this->Fitness.size()) {
		//UE_LOG(LogTemp, Warning, TEXT("Fitness: %f, %f, %f, %f, %f"), this->Fitness[0], this->Fitness[1], this->Fitness[2], this->Fitness[3], this->Fitness[4]);
	}
}

void ACarGen::SpawnGeneration(int size) {
	for (int i = 0; i < size; ++i) {
		this->Brains.push_back(new EvolutionProcessor());
		this->Brains.back()->InitializeWeights(6, 1);
		UE_LOG(LogTemp, Warning, TEXT("1STEP: %d"), this->Brains.back()->Size(-1));
	}

	//EvolutionProcessor* BrainTemp = new EvolutionProcessor();
	//BrainTemp->InitializeWeights(11, 4);
	//this->Brains.push_back(new EvolutionProcessor(BrainTemp));
	//for (int i = 0; i < size - 1; ++i) {
	//	this->Brains.push_back(new EvolutionProcessor(BrainTemp));
	//	//UE_LOG(LogTemp, Warning, TEXT("1STEP: %d"), this->Brains.back()->Size(-1));
	//}
}

void ACarGen::Selection(int NumComp) {
	std::vector<EvolutionProcessor*> NewGeneration;
	int RandomIdx;
	int MaxIdx;
	float MeanFitness = 0;
	for (int i = 0; i < this->GenerationCnt; ++i) {

		MaxIdx = FMath::RandRange(0, this->GenerationCnt - 1);
		for (int CompIdx = 0; CompIdx < NumComp - 1; ++CompIdx) {
			RandomIdx = FMath::RandRange(0, this->GenerationCnt - 1);
			if (this->Fitness[RandomIdx] > this->Fitness[MaxIdx]) {
				MaxIdx = RandomIdx;
			}
		}
		MeanFitness += this->Fitness[i];
		//UE_LOG(LogTemp, Warning, TEXT("2STEP: %f"), this->Fitness[MaxIdx]);
		NewGeneration.push_back(new EvolutionProcessor(this->Brains[MaxIdx]));
	}
	MeanFitness /= this->GenerationCnt;
	UE_LOG(LogTemp, Warning, TEXT("MeanFitness: %f"), MeanFitness);

	// LOOOOK CAREFULLL
	this->Brains.clear();
	std::copy(NewGeneration.begin(), NewGeneration.end(), this->Brains.begin());
}

bool ACarGen::WaitingForEverybodyToDie()
{
	return !static_cast<bool>(this->still_alive);
	//return false;
}

void ACarGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("what %d"), this->still_alive);
	if (this->WaitingForEverybodyToDie()) {
		// It fills fitness vector
		this->FinishSimulation();
		//UE_LOG(LogTemp, Warning, TEXT("EEEEEEEEEEEE"));
		if (this->CurRep == 0) {
			this->Selection(10);
		}
		//this->Mutate(0.1);
		//this->Cross(0.8);
		this->StartSimulation();
	}
}

void ACarGen::Mutate(float probability) {
	for (int i = 0; i < this->GenerationCnt; ++i) {
		if (FMath::FRandRange(0, 1) < probability) {
			this->Brains[i]->Mutate();
		}
	}
}

void ACarGen::Cross(float probability) {
	for (int i = 0; i < this->GenerationCnt; ++i) {
		if (FMath::FRandRange(0, 1) < probability) {
			EvolutionProcessor::Cross(this->Brains[i], this->Brains[FMath::RandRange(0, this->GenerationCnt - 1)]);
		}
	}
}



// Called every frame


