// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pong/Pawns/PaddleBase.h"
#include "AIPaddle.generated.h"

/** An AI paddle opponent for pong. */
UCLASS()
class PONG_API AAIPaddle final : public APaddleBase
{
	GENERATED_BODY()

protected:
	/** Initializes root collider sprite components */
    virtual void BeginPlay() override;
    
public:
    /** Ensures that tick functions run to track balls movement */
    AAIPaddle();

    /** Calls Move to update movement in regards to ball location */
    virtual void Tick(float DeltaSeconds) override;
    
private:
    /** 
     * Tracks balls location, updating position of this paddle.
     * The paddle location returns to the center of the board if the ball is moving away from it.
     */
    virtual void Move() override;
};
