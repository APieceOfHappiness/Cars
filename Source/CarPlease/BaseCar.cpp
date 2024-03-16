// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCar.h"

ABaseCar::ABaseCar() {
	UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh* CylinderMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Создание частей машины
	this->Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	this->Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	this->Person = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Person"));
	this->Wheel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel1"));
	this->Wheel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel2"));
	this->Wheel3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel3"));
	this->Wheel4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel4"));
	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	this->Hinge1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hinge1"));
	this->Hinge2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hinge2"));
	this->Hinge3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hinge3"));
	this->Hinge4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hinge4"));

	this->WheelAxis1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("WheelAxis1"));
	this->WheelAxis2 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("WheelAxis2"));
	this->WheelAxis3 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("WheelAxis3"));
	this->WheelAxis4 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("WheelAxis4"));

	this->HingeSuspension1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("HingeSuspension1"));
	this->HingeSuspension2 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("HingeSuspension2"));
	this->HingeSuspension3 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("HingeSuspension3"));
	this->HingeSuspension4 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("HingeSuspension4"));

	this->Body->SetStaticMesh(CubeMesh);
	this->Person->SetStaticMesh(CubeMesh);
	this->Wheel1->SetStaticMesh(CylinderMesh);
	this->Wheel2->SetStaticMesh(CylinderMesh);
	this->Wheel3->SetStaticMesh(CylinderMesh);
	this->Wheel4->SetStaticMesh(CylinderMesh);
	this->Hinge1->SetStaticMesh(CubeMesh);
	this->Hinge2->SetStaticMesh(CubeMesh);
	this->Hinge3->SetStaticMesh(CubeMesh);
	this->Hinge4->SetStaticMesh(CubeMesh);

	// Выключение коллизий
	this->Hinge1->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Hinge2->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Hinge3->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Hinge4->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Wheel1->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Wheel2->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Wheel3->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Wheel4->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Body->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	this->Person->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);

	this->Hinge1->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Hinge2->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Hinge3->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Hinge4->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Wheel1->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Wheel2->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Wheel3->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Wheel4->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Body->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	this->Person->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);

	this->StartPosition = FVector(0.f, 0.f, 500.f);
	//UE_LOG(LogTemp, Warning, TEXT("Mesh Location: %s"), *start_position.ToString());
	this->Body->SetRelativeLocation(this->StartPosition);

	this->Person->AttachToComponent(this->Body, FAttachmentTransformRules::KeepWorldTransform);
	this->Person->SetWorldLocation(this->StartPosition + FVector(0.f, 30.f, 100.f));
	this->Camera->AttachToComponent(this->Body, FAttachmentTransformRules::KeepWorldTransform);
	this->Camera->SetWorldLocation(this->StartPosition + FVector(0, -300, 300));
	this->WheelAxis1->SetWorldLocation(this->StartPosition + FVector(100.f, 60.f, -50.f));
	this->WheelAxis2->SetWorldLocation(this->StartPosition + FVector(-100.f, 60.f, -50.f));
	this->WheelAxis3->SetWorldLocation(this->StartPosition + FVector(100.f, -60.f, -50.f));
	this->WheelAxis4->SetWorldLocation(this->StartPosition + FVector(-100.f, -60.f, -50.f));

	this->HingeSuspension1->SetWorldLocation(this->StartPosition + FVector(100.f, 60.f, -50.f));
	this->HingeSuspension2->SetWorldLocation(this->StartPosition + FVector(-100.f, 60.f, -50.f));
	this->HingeSuspension3->SetWorldLocation(this->StartPosition + FVector(100.f, -60.f, -50.f));
	this->HingeSuspension4->SetWorldLocation(this->StartPosition + FVector(-100.f, -60.f, -50.f));

	this->Hinge1->SetWorldLocation(this->StartPosition + FVector(100.f, 60.f, -50.f));
	this->Hinge2->SetWorldLocation(this->StartPosition + FVector(-100.f, 60.f, -50.f));
	this->Hinge3->SetWorldLocation(this->StartPosition + FVector(100.f, -60.f, -50.f));
	this->Hinge4->SetWorldLocation(this->StartPosition + FVector(-100.f, -60.f, -50.f));

	this->Wheel1->SetWorldLocation(this->StartPosition + FVector(100.f, 60.f, -50.f));
	this->Wheel2->SetWorldLocation(this->StartPosition + FVector(-100.f, 60.f, -50.f));
	this->Wheel3->SetWorldLocation(this->StartPosition + FVector(100.f, -60.f, -50.f));
	this->Wheel4->SetWorldLocation(this->StartPosition + FVector(-100.f, -60.f, -50.f));

	this->Camera->SetWorldRotation(FQuat(FRotator(0, 90, 0)));
	this->Wheel1->SetWorldRotation(FQuat(FRotator(90, 0, 0)));
	this->Wheel2->SetWorldRotation(FQuat(FRotator(90, 0, 0)));
	this->Wheel3->SetWorldRotation(FQuat(FRotator(90, 0, 0)));
	this->Wheel4->SetWorldRotation(FQuat(FRotator(90, 0, 0)));

	this->Body->SetWorldScale3D(FVector(1.f, 2.f, 0.5f));
	this->Person->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	this->Wheel1->SetWorldScale3D(FVector(0.7f, 0.7f, 0.3f));
	this->Wheel2->SetWorldScale3D(FVector(0.7f, 0.7f, 0.3f));
	this->Wheel3->SetWorldScale3D(FVector(0.7f, 0.7f, 0.3f));
	this->Wheel4->SetWorldScale3D(FVector(0.7f, 0.7f, 0.3f));

	this->Hinge1->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	this->Hinge2->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	this->Hinge3->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	this->Hinge4->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	this->Body->SetSimulatePhysics(true);
	this->Wheel1->SetSimulatePhysics(true);
	this->Wheel2->SetSimulatePhysics(true);
	this->Wheel3->SetSimulatePhysics(true);
	this->Wheel4->SetSimulatePhysics(true);

	this->Hinge1->SetSimulatePhysics(true);
	this->Hinge2->SetSimulatePhysics(true);
	this->Hinge3->SetSimulatePhysics(true);
	this->Hinge4->SetSimulatePhysics(true);

	this->WheelAxis1->ComponentName1.ComponentName = "Hinge1";
	this->WheelAxis1->ComponentName2.ComponentName = "Wheel1";
	this->HingeSuspension1->ComponentName1.ComponentName = "Body";
	this->HingeSuspension1->ComponentName2.ComponentName = "Hinge1";

	this->WheelAxis2->ComponentName1.ComponentName = "Hinge2";
	this->WheelAxis2->ComponentName2.ComponentName = "Wheel2";
	this->HingeSuspension2->ComponentName1.ComponentName = "Body";
	this->HingeSuspension2->ComponentName2.ComponentName = "Hinge2";

	this->WheelAxis3->ComponentName1.ComponentName = "Hinge3";
	this->WheelAxis3->ComponentName2.ComponentName = "Wheel3";
	this->HingeSuspension3->ComponentName1.ComponentName = "Body";
	this->HingeSuspension3->ComponentName2.ComponentName = "Hinge3";

	this->WheelAxis4->ComponentName1.ComponentName = "Hinge4";
	this->WheelAxis4->ComponentName2.ComponentName = "Wheel4";
	this->HingeSuspension4->ComponentName1.ComponentName = "Body";
	this->HingeSuspension4->ComponentName2.ComponentName = "Hinge4";

	this->WheelAxis1->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->WheelAxis1->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	this->WheelAxis1->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0.f);

	this->WheelAxis2->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->WheelAxis2->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	this->WheelAxis2->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0.f);

	this->WheelAxis3->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->WheelAxis3->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	this->WheelAxis3->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0.f);

	this->WheelAxis4->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->WheelAxis4->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	this->WheelAxis4->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0.f);

	this->WheelAxis1->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis1->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis1->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	this->WheelAxis2->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis2->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis2->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	this->WheelAxis3->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis3->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis3->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	this->WheelAxis4->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis4->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->WheelAxis4->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	this->WheelAxis1->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	this->WheelAxis2->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	this->WheelAxis3->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	this->WheelAxis4->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);

	// Амортизация
	this->WheelAxis1->SetAngularVelocityDrive(false, true);
	this->WheelAxis2->SetAngularVelocityDrive(false, true);
	this->WheelAxis3->SetAngularVelocityDrive(false, true);
	this->WheelAxis4->SetAngularVelocityDrive(false, true);

	this->HingeSuspension1->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->HingeSuspension1->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	this->HingeSuspension1->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 30.f);

	this->HingeSuspension2->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->HingeSuspension2->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	this->HingeSuspension2->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 30.f);

	this->HingeSuspension3->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->HingeSuspension3->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	this->HingeSuspension3->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 30.f);

	this->HingeSuspension4->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);
	this->HingeSuspension4->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	this->HingeSuspension4->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 30.f);

	this->HingeSuspension1->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, 30.0f);
	this->HingeSuspension1->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->HingeSuspension1->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	this->HingeSuspension2->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, 30.0f);
	this->HingeSuspension2->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->HingeSuspension2->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	this->HingeSuspension3->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->HingeSuspension3->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->HingeSuspension3->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	this->HingeSuspension4->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->HingeSuspension4->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	this->HingeSuspension4->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);

	this->HingeSuspension1->SetLinearPositionDrive(false, false, true);
	this->HingeSuspension2->SetLinearPositionDrive(false, false, true);
	this->HingeSuspension3->SetLinearPositionDrive(false, false, true);
	this->HingeSuspension4->SetLinearPositionDrive(false, false, true);

	this->HingeSuspension1->SetLinearVelocityDrive(false, false, true);
	this->HingeSuspension2->SetLinearVelocityDrive(false, false, true);
	this->HingeSuspension3->SetLinearVelocityDrive(false, false, true);
	this->HingeSuspension4->SetLinearVelocityDrive(false, false, true);

	this->HingeSuspension1->SetLinearDriveParams(2000.f, 50.f, 0.f);
	this->HingeSuspension2->SetLinearDriveParams(2000.f, 50.f, 0.f);
	this->HingeSuspension3->SetLinearDriveParams(2000.f, 50.f, 0.f);
	this->HingeSuspension4->SetLinearDriveParams(2000.f, 50.f, 0.f);

	// Трение
	this->WheelAxis1->SetAngularOrientationDrive(true, false);
	this->WheelAxis2->SetAngularOrientationDrive(true, false);
	this->WheelAxis3->SetAngularOrientationDrive(true, false);
	this->WheelAxis4->SetAngularOrientationDrive(true, false);

	this->WheelAxis1->SetAngularDriveParams(0.f, 5.f, 0.f);
	this->WheelAxis2->SetAngularDriveParams(0.f, 5.f, 0.f);
	this->WheelAxis3->SetAngularDriveParams(0.f, 5.f, 0.f);
	this->WheelAxis4->SetAngularDriveParams(0.f, 5.f, 0.f);

	// Подготовка к повороту
	this->HingeSuspension1->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	this->HingeSuspension2->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	this->HingeSuspension3->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
	this->HingeSuspension4->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);

	this->HingeSuspension1->SetAngularOrientationDrive(true, false);
	this->HingeSuspension2->SetAngularOrientationDrive(true, false);
	this->HingeSuspension3->SetAngularOrientationDrive(true, false);
	this->HingeSuspension4->SetAngularOrientationDrive(true, false);

	this->HingeSuspension1->SetAngularVelocityDrive(true, false);
	this->HingeSuspension2->SetAngularVelocityDrive(true, false);
	this->HingeSuspension3->SetAngularVelocityDrive(true, false);
	this->HingeSuspension4->SetAngularVelocityDrive(true, false);

	this->HingeSuspension1->SetAngularDriveParams(99999999.f, 99999999.f, 0.f);
	this->HingeSuspension2->SetAngularDriveParams(99999999.f, 99999999.f, 0.f);
	this->HingeSuspension3->SetAngularDriveParams(99999999.f, 99999999.f, 0.f);
	this->HingeSuspension4->SetAngularDriveParams(99999999.f, 99999999.f, 0.f);
	// ---------------------------------
	//hinge_suspension1->SetAngularOrientationTarget(FRotator(0., 30., 0.f));
	//hinge_suspension2->SetAngularOrientationTarget(FRotator(0., 30., 0.f));

	//hinge_suspension1->SetAngularVelocityTarget(FVector(0., 0., 30.f));
	//hinge_suspension2->SetAngularVelocityTarget(FVector(0., 0., 30.f));
}

void ABaseCar::InitializeObject(FVector Loc) {
	this->StartPosition = Loc;
	this->Body->SetRelativeLocation(Loc);

	this->WheelAxis1->SetWorldLocation(Loc + FVector(100.f, 60.f, -50.f));
	this->WheelAxis2->SetWorldLocation(Loc + FVector(-100.f, 60.f, -50.f));
	this->WheelAxis3->SetWorldLocation(Loc + FVector(100.f, -60.f, -50.f));
	this->WheelAxis4->SetWorldLocation(Loc + FVector(-100.f, -60.f, -50.f));

	this->HingeSuspension1->SetWorldLocation(Loc + FVector(100.f, 60.f, -50.f));
	this->HingeSuspension2->SetWorldLocation(Loc + FVector(-100.f, 60.f, -50.f));
	this->HingeSuspension3->SetWorldLocation(Loc + FVector(100.f, -60.f, -50.f));
	this->HingeSuspension4->SetWorldLocation(Loc + FVector(-100.f, -60.f, -50.f));

	this->Hinge1->SetWorldLocation(Loc + FVector(100.f, 60.f, -50.f));
	this->Hinge2->SetWorldLocation(Loc + FVector(-100.f, 60.f, -50.f));
	this->Hinge3->SetWorldLocation(Loc + FVector(100.f, -60.f, -50.f));
	this->Hinge4->SetWorldLocation(Loc + FVector(-100.f, -60.f, -50.f));

	this->Wheel1->SetWorldLocation(Loc + FVector(100.f, 60.f, -50.f));
	this->Wheel2->SetWorldLocation(Loc + FVector(-100.f, 60.f, -50.f));
	this->Wheel3->SetWorldLocation(Loc + FVector(100.f, -60.f, -50.f));
	this->Wheel4->SetWorldLocation(Loc + FVector(-100.f, -60.f, -50.f));
}

float ABaseCar::GetDistToTheClosestObject(float Angle) {
	FHitResult OutHit;

	FVector Start = this->Body->GetComponentLocation();
	FVector ForwardVector = this->Camera->GetForwardVector();

	FQuat RotationQuat = FQuat(FRotator(0.0f, Angle, 0.0f));
	ForwardVector = RotationQuat.RotateVector(ForwardVector);

	FVector End = Start + ForwardVector * this->RayLen;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredComponent(this->Body);

	bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

	if (IsHit) {
		FVector ColLoc= OutHit.ImpactPoint;
		//UE_LOG(LogTemp, Warning, TEXT("start: %f, %f, %f"), start.X, start.Y, start.Z);
		//UE_LOG(LogTemp, Warning, TEXT("col_loc: %f, %f, %f"), col_loc.X, col_loc.Y, col_loc.Z);
		return (ColLoc - Start).Size() / this->RayLen;
	}
	return 1.f;
}

std::vector<float> ABaseCar::GetEnvInfo() {
	std::vector<float> EnvInfo;

	//for (int angle = 0; angle < 360; angle += 45) {
	//	EnvInfo.push_back(this->GetDistToTheClosestObject(angle));
	//}
	//EnvInfo.push_back((this->Body->GetRightVector()).X);
	//EnvInfo.push_back((this->Body->GetRightVector()).Y);
	//EnvInfo.push_back((this->Body->GetRightVector()).Z);
	//return EnvInfo;

	for (int angle = -60; angle <= 60; angle += 30) {
		EnvInfo.push_back(this->GetDistToTheClosestObject(angle));
	}
	//EnvInfo.push_back((this->Body->GetRightVector()).X);
	//EnvInfo.push_back((this->Body->GetRightVector()).Y);
	//EnvInfo.push_back((this->Body->GetRightVector()).Z);
	EnvInfo.push_back((500 - this->TicksForLiving) / 500);
	return EnvInfo;
}

// Called when the game starts or when spawned
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();
	this->InitializeObject(this->StartPosition);
}

void ABaseCar::Drive(float Power)
{
	FVector RightVector = this->Body->GetRightVector();
	//for (UStaticMeshComponent* Wheel : { this->Wheel1, this->Wheel2 }) {
	//	FRotator target_rotation = FRotator::MakeFromEuler(FVector(-rotation_direction.Y, rotation_direction.Z, rotation_direction.X) * Power);
	//	UE_LOG(LogTemp, Warning, TEXT("target_rotation: %f %f %f"), target_rotation.Yaw, target_rotation.Roll, target_rotation.Pitch);
	//	Wheel->SetRelativeRotation(FQuat(FRotator(90.0f, 0.0f, 0.0f)));
	//}

	//UE_LOG(LogTemp, Warning, TEXT("target_rotation: %f %f %f"), this->Camera->GetForwardVector().X, this->Camera->GetForwardVector().Y, this->Camera->GetForwardVector().Z);
	//this->Body->AddImpulse((this->Camera->GetForwardVector() + FVector(0.f, 0.f, 0.1f))* Power / 5);
	this->Wheel1->AddAngularImpulse(FVector(-RightVector.Y, RightVector.X, RightVector.Z) * Power);
	this->Wheel2->AddAngularImpulse(FVector(-RightVector.Y, RightVector.X, RightVector.Z) * Power);
}

void ABaseCar::Turn(float Angle)
{
	if (Angle > this->AngleLimit) {
		Angle = this->AngleLimit;
	}
	else if (Angle < -this->AngleLimit) {
		Angle = -this->AngleLimit;
	}
	this->HingeSuspension1->SetAngularOrientationTarget(FRotator(0., Angle, 0.f));
	this->HingeSuspension2->SetAngularOrientationTarget(FRotator(0., Angle, 0.f));

	this->HingeSuspension1->SetAngularVelocityTarget(FVector(0., 0., Angle));
	this->HingeSuspension2->SetAngularVelocityTarget(FVector(0., 0., Angle));
	
	//UE_LOG(LogTemp, Warning, TEXT("decision: %f"), Angle);
}



