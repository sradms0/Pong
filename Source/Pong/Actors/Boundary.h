// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boundary.generated.h"

class APongGameModeBase;
class UBoxComponent;

/**
 * A boundary to deflect or act as a goal
 * This interacts with a ball actor.
 */
UCLASS()
class PONG_API ABoundary final : public AActor
{
	GENERATED_BODY()

protected:
	/** Sets a game mode reference and delegates OnComponentBeginOverlap to OnOverlapBegin */
	virtual void BeginPlay() override;
	
public:	
	/**
	 * Constructor.
	 * Initializes root container. 
	 */
	ABoundary();

	/**
	 * Detects overlapping ABall actor.
	 * If this boundary is a goal, the game mode destroys the ball.
	 * @param OverlappedComp - Primitive root component of boundary
	 * @param OtherActor - Overlapping ball actor
	 * @param OtherComp - Primitive root component of ball
	 * @param OtherBodyIndex - Index of mesh to overlapping ball (multi-overlap is expected to be none, so will be -1)
	 * @param bFromSweep - If collision detected from current to intended location (only setting velocity, so is false)
	 * @param SweepResult - What the boundary 'hit' (not used)
	 */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	
private:
	/** Root component for collision detection */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Bounds;

	/** Determines if player can score */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boundary Type", meta = (AllowPrivateAccess = "true"))
	bool IsGoal = false;

	/** Determines which player scored */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boundary Type", meta = (AllowPrivateAccess = "true"))
	bool IsLeftGoal = false;

	/** Deletes ball when overlapping a goal */
	APongGameModeBase* GameModeRef;
};

