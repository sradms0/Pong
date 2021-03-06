// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleBase.h"
#include "Pong/Actors/Ball.h"
#include "Pong/GameModes/PongGameModeBase.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APaddleBase::APaddleBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Collider;
    PrimitiveRootComponent = Cast<UPrimitiveComponent>(RootComponent);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);
}

FVector APaddleBase::GetColliderLinearVelocity() const
{
	return PrimitiveRootComponent->GetPhysicsLinearVelocity();
}

void APaddleBase::SetColliderLinearVelocity(const FVector Velocity) const
{
	return PrimitiveRootComponent->SetPhysicsLinearVelocity(Velocity);
}

void APaddleBase::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void APaddleBase::Move() {}