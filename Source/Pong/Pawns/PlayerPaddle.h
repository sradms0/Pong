// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pong/Pawns/PaddleBase.h"
#include "PlayerPaddle.generated.h"

/** An paddle for a human player in pong. */
UCLASS()
class PONG_API APlayerPaddle final : public APaddleBase
{
	GENERATED_BODY()

protected:
	/** Initializes root collider sprite components. */
    virtual void BeginPlay() override;
    
    /**
     * Sets control of paddle with use of a mouse.
     * This allows the player to give the paddle non-constant velocity.
     * @param PlayerInputComponent - The input component to bind movement to the Z-axis
     */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
    /** Ensures that tick functions run, so paddle movement can update. */
    APlayerPaddle();

    /** Calls Move to update paddle movement */
    virtual void Tick(float DeltaSeconds) override;

private:
    /** Contains paddles updated velocity; calculated through CalculateMoveInput */
    FVector MoveDirection;
    
    /** Changes the paddles offset and velocity based on MoveDirection. */
    virtual void Move() override;
    
    /**
     * Updates MoveDirection, so that the paddle is able to move through the Z-axis.
     * @param Value - The difference between the paddles final and initial location
     */
    void CalculateMoveInput(float Value);
};
