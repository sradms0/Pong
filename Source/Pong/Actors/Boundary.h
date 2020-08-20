// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boundary.generated.h"

class APongGameModeBase;
class UBoxComponent;

UCLASS()
class PONG_API ABoundary : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	ABoundary();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Bounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boundary Type", meta = (AllowPrivateAccess = "true"))
	bool IsGoal = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boundary Type", meta = (AllowPrivateAccess = "true"))
	bool IsLeftGoal = false;

	APongGameModeBase* GameModeRef;
};

