// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pong/Pawns/PaddleBase.h"
#include "AIPaddle.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API AAIPaddle final : public APaddleBase
{
	GENERATED_BODY()

protected:
    void BeginPlay() override;
    
public:
    AAIPaddle();

    void Tick(float DeltaSeconds) override;
    
    
private:
    
};
