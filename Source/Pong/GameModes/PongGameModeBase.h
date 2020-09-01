// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

class ABall;
class APaddleBase;

/**
 * Default mode for two player pong game: player vs AI
 */
UCLASS()
class PONG_API APongGameModeBase final : public AGameModeBase
{
	GENERATED_BODY()

protected:
    /** Spawns paddles and ball */
    virtual void BeginPlay() override;

public:
    /** Initializes game HUD */
    APongGameModeBase();

    /**
     * Gives ball access to actors that need data about the current ball.
     * @return the current balls address
     */
    ABall* GetBallRef() const;

    /**
     * Sets the players score based on a a left or right goal.
     * @param IsLeftGoal - Whether or not a boundary is a left or right goal
     */
    void SetScore(bool IsLeftGoal);

    /**
     * Gives the AIs score for the game HUD to access.
     * @return The AIs current score
     */
    UFUNCTION(BlueprintCallable, Category = "Scores")
    int32 GetAIScore() const;
    
    /**
     * Gives the player's score for the game HUD to access.
     * @return The player's current score
     */
    UFUNCTION(BlueprintCallable, Category = "Scores")
    int32 GetPlayerScore() const;

private:
    /** Reference the current ball; updates after every ball spawn */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References", meta = (AllowPrivateAccess = "true"))
    ABall* BallRef;

    /** Delay for ball movement after ball is spawned */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float InitialBallVelocityDelay = 1.0f;

    /** Initial ball direction (player side, to the left) */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float Direction = -1;

    /** Ball spawning location; center of the map by default */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Locations", meta = (AllowPrivateAccess = "true"))
    FVector BallSpawnLocation = FVector(0, 0, 0);
    
    /** Player spawning location; left and centered of the map by default */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Locations", meta = (AllowPrivateAccess = "true"))
    FVector PlayerPaddleSpawnLocation = FVector(-850, 10, 0);
    
    /** AI spawning location; right and centered of the map by default */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Locations", meta = (AllowPrivateAccess = "true"))
    FVector AIPaddleSpawnLocation = FVector(850, 10, 0);
 
    /** Default ball speed when spawned */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball Movement", meta = (AllowPrivateAccess = "true"))
    float BallSpeed = 1400.0f;

    /** Track the player's score */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    int32 PlayerScore = 0;
 
    /** Track the AIs score */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    int32 AIScore = 0;

    /** Timer for delaying ball velocity after spawning */
    FTimerHandle InitialBallVelocityTimerHandle;

    /**
     * Spawns the ball in the beginning of the game and after destroyed from passing a goal.
     * @param InitialDirection - Direction of the balls velocity after spawning
     */
    void SpawnBall(const float InitialDirection);

    /** Create the player's paddle. */
    void SpawnPlayerPaddle();
    
    /** Create the AIs paddle. */
    void SpawnAIPaddle();

    /**
     * Helper for generating actor blueprints
     * @param BPPath - Path reference of the blueprint
     * @return The generated blueprint to be spawned
     */
    UBlueprint* GenerateBlueprintForSpawn(const TCHAR* BPPath) const;

    /**
     * Generates the ball blueprint.
     * @return The generated ball blueprint to be spawned
     */
    UBlueprint* GenerateBallBlueprintForSpawn() const;
    
    /**
     * Generates the player blueprint.
     * @return The generated player blueprint to be spawned
     */
    UBlueprint* GeneratePlayerPaddleBlueprintForSpawn() const;
    
    /**
     * Generates the AI blueprint.
     * @return The generated AI blueprint to be spawned
     */
    UBlueprint* GenerateAIPaddleBlueprintForSpawn() const;

    /* Generates a random direction for the balls velocity after spawning. */
    static float GenerateRandomDirection();

    /* Moves the ball after spawning. */
    void InitializeBallVelocity() const;
};

