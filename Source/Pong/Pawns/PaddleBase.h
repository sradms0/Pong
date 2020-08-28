// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddleBase.generated.h"

class ABall;
class APongGameModeBase;
class UBoxComponent;
class UPaperSpriteComponent;

UCLASS(Abstract)
class PONG_API APaddleBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddleBase();
	
	FVector GetColliderLinearVelocity() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float", meta = (BlueprintProtected))
	float Speed = 1000.0f;

	APongGameModeBase* GameModeRef;
	
	ABall* BallRef;

	virtual void BeginPlay() override;

	virtual void Move();
	
	void SetColliderLinearVelocity(const FVector Velocity) const;

private:
	UPrimitiveComponent* PrimitiveRootComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Collider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* Sprite;
};
