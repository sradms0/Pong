// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameModeBase.h"
#include "Actors/Ball.h"
#include "Kismet/KismetMathLibrary.h"

void APongGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    SpawnBall();
}

void APongGameModeBase::SpawnBall()
{
    UObject* BallActorToSpawn = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/Blueprints/BP_Ball.BP_Ball")));
    UBlueprint* GeneratedBPBall = Cast<UBlueprint>(BallActorToSpawn);
    UClass* BallClassToSpawn = BallActorToSpawn->StaticClass();
    if (BallClassToSpawn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("No Ball class to spawn from"));
        return;
    }
    BallRef = GetWorld()->SpawnActor<ABall>(GeneratedBPBall->GeneratedClass, FVector(10, 0, 0), FRotator());

    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();
    Direction = UKismetMathLibrary::SignOfFloat(RandomStream.FRandRange(-1.0f, 1.0f));
    
    UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(BallRef->GetRootComponent());
    Root->SetPhysicsLinearVelocity(FVector(Direction * BallSpeed, 0, 0), true);
}
