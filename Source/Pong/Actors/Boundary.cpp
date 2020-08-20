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

void ABoundary::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

