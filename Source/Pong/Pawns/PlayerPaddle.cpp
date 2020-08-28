// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"

void APlayerPaddle::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("Move"), this, &APlayerPaddle::CalculateMoveInput);
}

APlayerPaddle::APlayerPaddle()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlayerPaddle::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    Move();
}

void APlayerPaddle::Move()
{
    AddActorLocalOffset(MoveDirection, true);
    SetColliderLinearVelocity(MoveDirection);
}

void APlayerPaddle::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(0, 0, Value * Speed * GetWorld()->DeltaTimeSeconds);
}

