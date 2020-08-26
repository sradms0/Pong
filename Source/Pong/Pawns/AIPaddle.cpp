// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPaddle.h"
#include "Kismet/GameplayStatics.h"
#include "Pong/Actors/Ball.h"
#include "Pong/PongGameModeBase.h"

void AAIPaddle::BeginPlay()
{
    Super::BeginPlay();
}

AAIPaddle::AAIPaddle()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAIPaddle::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APongGameModeBase* GameModeRef = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameModeRef == nullptr)
    {
        return;
    }
    
    BallRef = GameModeRef->GetBallRef();
    if (BallRef == nullptr)
    {
        return;
    }

    const FVector BallVelocity = BallRef->GetVelocity();
    float TargetZ = 0.0f;
    float InterpSpeed = Speed;
    if (BallVelocity.X > 0)
    {
        TargetZ = BallRef->GetActorLocation().Z;
    }
    else
    {
        InterpSpeed *= 2;
    }
    
    const FVector Target = FVector(850, 10, TargetZ);
    const FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), Target, DeltaSeconds, InterpSpeed);
    SetActorLocation(NewLocation, true);
}
