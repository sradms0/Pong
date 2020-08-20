// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddleBase.generated.h"

class ABall;
class UBoxComponent;
class UPaperSpriteComponent;

UCLASS(Abstract)
class PONG_API APaddleBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddleBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float", meta = (BlueprintProtected))
	float Speed = 10.0f;

	ABall* BallRef;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Collider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprite", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* Sprite;
};
