// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameModeBase.h"
#include "Pong/Actors/Ball.h"
#include "Pong/HUD/GameHUD.h"
#include "Kismet/KismetMathLibrary.h"

APongGameModeBase::APongGameModeBase():Super()
{
	HUDClass = AGameHUD::StaticClass();
}

void APongGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    SpawnBall(GenerateRandomDirection());
}

ABall* APongGameModeBase::GetBallRef()
{
    return BallRef;
}

int32 APongGameModeBase::GetAIScore()
{
	return AIScore;
}

int32 APongGameModeBase::GetPlayerScore()
{
	return AIScore;
}

void APongGameModeBase::SetScore(bool IsLeftGoal)
{
	float RespawnDirection;
	
	if (IsLeftGoal)
	{
		AIScore++;
		RespawnDirection = -1.0f;
	}
	else
	{
		PlayerScore++;
		RespawnDirection = 1.0f;
	}

	SpawnBall(RespawnDirection);
}

void APongGameModeBase::SpawnBall(float InitialDirection)
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

	Direction = InitialDirection;
    
	GetWorld()->GetTimerManager().SetTimer(InitialBallVelocityTimerHandle, this, &APongGameModeBase::InitializeBallVelocity, InitialBallVelocityDelay, false);
}

float APongGameModeBase::GenerateRandomDirection()
{
    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();
	
    return UKismetMathLibrary::SignOfFloat(RandomStream.FRandRange(-1.0f, 1.0f));
}

void APongGameModeBase::InitializeBallVelocity()
{
    UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(BallRef->GetRootComponent());
    Root->SetPhysicsLinearVelocity(FVector(Direction * BallSpeed, 0, 0), true);
}
