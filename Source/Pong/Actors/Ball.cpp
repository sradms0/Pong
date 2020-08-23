// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
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
		APaddleBase* Paddle = Cast<APaddleBase>(OtherActor);
		if (Paddle)
		{
			HitPaddle(Paddle);
		}
	}
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);
}

void ABall::HitPaddle(APaddleBase* Paddle) const
{
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	
	const float PaddleVelocityZ = Paddle->GetColliderLinearVelocity().Z;
	const float NewSphereVelocityZ = (PaddleVelocityZ / RandomStream.FRandRange(2.0f, 3.0f))
										+ RandomStream.FRandRange(-200.0f, 200.0f);

	UPrimitiveComponent* SpherePrimitive = Cast<UPrimitiveComponent>(Sphere);
	const FVector CurrentSphereVelocity = SpherePrimitive->GetPhysicsLinearVelocity();
	
	SpherePrimitive->SetPhysicsLinearVelocity(
		FVector(CurrentSphereVelocity.X * -1, CurrentSphereVelocity.Y, NewSphereVelocityZ)
	);	
}
