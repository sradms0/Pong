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

public:
    APongGameModeBase();
    
    ABall* GetBallRef();
    
    void SetScore(bool IsLeftGoal);

    UFUNCTION(BlueprintCallable, Category = "Scores")
    int32 GetAIScore();
    
    UFUNCTION(BlueprintCallable, Category = "Scores")
    int32 GetPlayerScore();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References", meta = (AllowPrivateAccess = "true"))
    ABall* BallRef;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float InitialBallVelocityDelay = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float Direction = -1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float BallSpeed = 1400.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    int32 PlayerScore = 0;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    int32 AIScore = 0;

    FTimerHandle InitialBallVelocityTimerHandle;
    
    void SpawnBall(float InitialDirection);
    
    float GenerateRandomDirection();
    
    void InitializeBallVelocity();
    
};


