// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleBase.h"
#include "Pong/Actors/Ball.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APaddleBase::APaddleBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Collider;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);
}
