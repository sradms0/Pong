// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Pong/Actors/Boundary.h"
#include "Pong/Pawns/PaddleBase.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Sphere;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);
}

void ABall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AssertPaddleAndBoundaryHit();
		
		ABoundary* Boundary = Cast<ABoundary>(OtherActor);
		APaddleBase* Paddle = Cast<APaddleBase>(OtherActor);
		if (Paddle)
		{
			HitPaddle(Paddle);
		}
		else if (Boundary)
		{
			HitBoundary();
		}
	}
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);
}

void ABall::HitPaddle(APaddleBase* Paddle) const
{
	UPrimitiveComponent* SpherePrimitive = Cast<UPrimitiveComponent>(Sphere);
	const FVector CurrentSphereVelocity = SpherePrimitive->GetPhysicsLinearVelocity();
	const float NewBallVelocityZ = CalculateHitPaddleVelocityZ(CurrentSphereVelocity, Paddle->GetColliderLinearVelocity().Z);
	SpherePrimitive->SetPhysicsLinearVelocity(
		FVector(CurrentSphereVelocity.X * -1.0f, CurrentSphereVelocity.Y, NewBallVelocityZ)
	);
	const FVector NewBallVelocity = SpherePrimitive->GetPhysicsLinearVelocity();
}

void ABall::HitBoundary() const
{
	UPrimitiveComponent* SpherePrimitive = Cast<UPrimitiveComponent>(Sphere);
	const FVector CurrentSphereVelocity = SpherePrimitive->GetPhysicsLinearVelocity();
	SpherePrimitive->SetPhysicsLinearVelocity(
		FVector(CurrentSphereVelocity.X, CurrentSphereVelocity.Y, CurrentSphereVelocity.Z* -1.0f)
	);
}

float ABall::CalculateHitPaddleVelocityZ(const FVector CurrentSphereVelocity, const float PaddleVelocityZ)
{
	return !FMath::Abs(PaddleVelocityZ) ? CurrentSphereVelocity.Z :
			FMath::Sqrt(FMath::Square(PaddleVelocityZ) + FMath::Square(CurrentSphereVelocity.X)) 
			* (PaddleVelocityZ / FMath::Abs(PaddleVelocityZ))
			* 0.4f;
}


void ABall::AssertPaddleAndBoundaryHit() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	if (OverlappingActors.Num() > 1)
	{
		HitBoundary();
	}
}
