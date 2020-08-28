// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pong/Pawns/PaddleBase.h"
#include "PlayerPaddle.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APlayerPaddle final : public APaddleBase
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
    APlayerPaddle();

    virtual void Tick(float DeltaSeconds) override;

private:
    FVector MoveDirection;
    
    virtual void Move() override;
    
    void CalculateMoveInput(float Value);
    
};
