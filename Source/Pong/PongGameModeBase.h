// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

class ABall;
class APaddleBase;

/**
 * 
 */
UCLASS()
class PONG_API APongGameModeBase final : public AGameModeBase
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    APongGameModeBase();
    
    ABall* GetBallRef() const;
    
    void SetScore(bool IsLeftGoal);

    UFUNCTION(BlueprintCallable, Category = "Scores")
    int32 GetAIScore() const;
    
    UFUNCTION(BlueprintCallable, Category = "Scores")
    int32 GetPlayerScore() const;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References", meta = (AllowPrivateAccess = "true"))
    ABall* BallRef;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float InitialBallVelocityDelay = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float Direction = -1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Locations", meta = (AllowPrivateAccess = "true"))
    FVector BallSpawnLocation = FVector(0, 0, 0);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Locations", meta = (AllowPrivateAccess = "true"))
    FVector PlayerPaddleSpawnLocation = FVector(-850, 10, 0);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Locations", meta = (AllowPrivateAccess = "true"))
    FVector AIPaddleSpawnLocation = FVector(850, 10, 0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float BallSpeed = 1400.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    int32 PlayerScore = 0;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    int32 AIScore = 0;

    FTimerHandle InitialBallVelocityTimerHandle;
    
    void SpawnBall(const float InitialDirection);
    
    void SpawnPlayerPaddle();
    
    void SpawnAIPaddle();

    UBlueprint* GenerateBlueprintForSpawn(const TCHAR* BPPath) const;

    UBlueprint* GenerateBallBlueprintForSpawn() const;
    
    UBlueprint* GeneratePlayerPaddleBlueprintForSpawn() const;
    
    UBlueprint* GenerateAIPaddleBlueprintForSpawn() const;

    static float GenerateRandomDirection();
    
    void InitializeBallVelocity() const;
};

