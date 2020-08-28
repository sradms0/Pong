// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameModeBase.h"
#include "Pong/Actors/Ball.h"
#include "Pong/Pawns/PlayerPaddle.h"
#include "Pong/Pawns/AIPaddle.h"
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
    SpawnPlayerPaddle();
    SpawnAIPaddle();
}

ABall* APongGameModeBase::GetBallRef() const
{
    return BallRef;
}

int32 APongGameModeBase::GetAIScore() const
{
	return AIScore;
}

int32 APongGameModeBase::GetPlayerScore() const
{
	return AIScore;
}

void APongGameModeBase::SetScore(const bool IsLeftGoal)
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

void APongGameModeBase::SpawnBall(const float InitialDirection)
{
    UBlueprint* GeneratedBPBall = GenerateBallBlueprintForSpawn();
    if (GeneratedBPBall == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("No Ball class to spawn from"));
        return;
    }
    BallRef = GetWorld()->SpawnActor<ABall>(GeneratedBPBall->GeneratedClass, BallSpawnLocation, FRotator());
	Direction = InitialDirection;
	GetWorld()->GetTimerManager().SetTimer(InitialBallVelocityTimerHandle, this,
	                                       &APongGameModeBase::InitializeBallVelocity, InitialBallVelocityDelay, false
	                                       );
}

void APongGameModeBase::SpawnPlayerPaddle()
{
	UBlueprint* GeneratedBPPlayerPaddle = GeneratePlayerPaddleBlueprintForSpawn();
	if (GeneratedBPPlayerPaddle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No PlayerPaddle class to spawn from"));
		return;
	}

	GetWorld()->SpawnActor<APlayerPaddle>(
		GeneratedBPPlayerPaddle->GeneratedClass, PlayerPaddleSpawnLocation, FRotator(0, 0, 0)
	);
}

void APongGameModeBase::SpawnAIPaddle()
{
	UBlueprint* GeneratedBPPlayerPaddle = GenerateAIPaddleBlueprintForSpawn();
	if (GeneratedBPPlayerPaddle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No AIPaddle class to spawn from"));
		return;
	}

	GetWorld()->SpawnActor<AAIPaddle>(
		GeneratedBPPlayerPaddle->GeneratedClass, AIPaddleSpawnLocation, FRotator(0, 0, 0)
	);
}

UBlueprint* APongGameModeBase::GenerateBlueprintForSpawn(const TCHAR* BPPath) const
{
	UObject* ActorToSpawn = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr, BPPath));
	UBlueprint* GeneratedBP = Cast<UBlueprint>(ActorToSpawn);
	UClass* ClassToSpawn = ActorToSpawn->StaticClass();
	return ClassToSpawn ? GeneratedBP : nullptr;
}

UBlueprint* APongGameModeBase::GenerateBallBlueprintForSpawn() const
{
    return GenerateBlueprintForSpawn(TEXT("/Game/Blueprints/BP_Ball"));
}

UBlueprint* APongGameModeBase::GeneratePlayerPaddleBlueprintForSpawn() const
{
    return GenerateBlueprintForSpawn(TEXT("/Game/Blueprints/BP_PlayerPaddle"));
}

UBlueprint* APongGameModeBase::GenerateAIPaddleBlueprintForSpawn() const
{
    return GenerateBlueprintForSpawn(TEXT("/Game/Blueprints/BP_AIPaddle"));
}

float APongGameModeBase::GenerateRandomDirection()
{
    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();
    return UKismetMathLibrary::SignOfFloat(RandomStream.FRandRange(-1.0f, 1.0f));
}

void APongGameModeBase::InitializeBallVelocity() const
{
    UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(BallRef->GetRootComponent());
    Root->SetPhysicsLinearVelocity(FVector(Direction * BallSpeed, 0, 0), true);
}
