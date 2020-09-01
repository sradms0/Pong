// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddleBase.generated.h"

class ABall;
class APongGameModeBase;
class UBoxComponent;
class UPaperSpriteComponent;

/**
 * Interface for a pong paddle.
 * Used for initializing default functionality for player and AI.
 */
UCLASS(Abstract)
class PONG_API APaddleBase : public APawn
{
	GENERATED_BODY()

public:
	/** Initializes root collider sprite components */
	APaddleBase();

	/**
	 * Calculates and provides linear velocity of primitive collider.
	 * @return The vector of the colliders movement
	 */
	FVector GetColliderLinearVelocity() const;

protected:
	/** Default paddle speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float", meta = (BlueprintProtected))
	float Speed = 1000.0f;

	/** Gives access to ball reference */
	APongGameModeBase* GameModeRef;

	/** Track balls movement (used for AI)*/
	ABall* BallRef;

	/** Initializes GameModeRef. */
	virtual void BeginPlay() override;

	/** Controls paddle movement; determined by derived paddles. */
	virtual void Move();

	/** Update primitive collider velocity (used for player). */
	void SetColliderLinearVelocity(const FVector Velocity) const;

private:
	/* Primitive for root collider to access and update its linear velocity */
	UPrimitiveComponent* PrimitiveRootComponent;

	/** Root component for paddles collision detection */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Collider;
	
	/** 2D representation of paddle */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* Sprite;
};
