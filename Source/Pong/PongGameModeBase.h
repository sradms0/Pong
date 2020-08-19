// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

class ABall;

/**
 * 
 */
UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References", meta = (AllowPrivateAccess = "true"))
    ABall* BallRef;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float Direction = -1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float BallSpeed = 1400.0f;

    void SpawnBall();
};


