// Fill out your copyright notice in the Description page of Project Settings.


#include "Boundary.h"
#include "Components/BoxComponent.h"
#include "Pong/PongGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABoundary::ABoundary()
{
	PrimaryActorTick.bCanEverTick = false;

	Bounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounds"));
	RootComponent = Bounds;
}

void ABoundary::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (!IsGoal)
		{
			return;
		}

		GameModeRef->SetScore(IsLeftGoal);
		OtherActor->Destroy();
	}
}

void ABoundary::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeRef = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	Bounds->OnComponentBeginOverlap.AddDynamic(this, &ABoundary::OnOverlapBegin);
}

