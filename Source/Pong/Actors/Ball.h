// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class APaddleBase;
class USphereComponent;
class UPaperSpriteComponent;

/**
 * A ball used to play in a game of Pong.
 * This interacts with boundary and paddle actors.
 * Custom collisions are enforced through HitPaddle and HitBall methods, changing its velocity.
 */
UCLASS()
class PONG_API ABall final : public AActor
{
	GENERATED_BODY()
	
public:	
	/**
	 * Constructor.
	 * Initializes root container and sprite
	 */
	ABall();

	/**
	 * Detects overlapping actors, meant for APaddleBase and ABoundary classes.
	 * @param OverlappedComp - Primitive root component of Ball
	 * @param OtherActor - Overlapping actor: either boundary or paddle
	 * @param OtherComp - Primitive root component of other overlapping actor
	 * @param OtherBodyIndex - Index of mesh to overlapping actor (multi-overlap is expected to be none, so will be -1)
	 * @param bFromSweep - If collision detected from current to intended location (only setting velocity, so is false)
	 * @param SweepResult - What the ball 'hit' (not used)
	 */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

protected:
	/** Delegates OnComponentBeginOverlap to OnBeginOverlap */
	virtual void BeginPlay() override;

private:
	/** Root component for balls collision detection */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	/** 2D representation of ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* Sprite;

	/**
	 * Changes ball velocity after hitting a paddle.
	 * @param Paddle - Paddle the ball collided with
	 */
	void HitPaddle(APaddleBase* Paddle) const;

	/** Changes ball velocity after hitting a boundary */
	void HitBoundary() const;

	/**
	 * Calculates balls new Z velocity component after hitting paddle; called within HitPaddle.
	 * @param CurrentSphereVelocity - The linear velocity of the root collider primitive
	 * @param PaddleVelocityZ - The paddles Z velocity component to determine angle of the ball
	 * @return The balls new Z velocity component
	 */
	static float CalculateHitPaddleVelocityZ(const FVector CurrentSphereVelocity, const float PaddleVelocityZ);

	/** 
	 * Handles fringe case of ball colliding with a paddle and boundary, calling HitBoundary.
	 * Without this, a paddle will have priority of hitting the ball, throwing the ball out of top/bottom boundaries.
	 */
	void AssertPaddleAndBoundaryHit() const;
};
