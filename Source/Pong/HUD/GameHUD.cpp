// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Blueprint/UserWidget.h"

AGameHUD::AGameHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget>ScoresObj(TEXT("/Game/Blueprints/UI/WBP_Scores"));
    ScoresWidgetClass = ScoresObj.Class;
}

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if (ScoresWidgetClass == nullptr)
    {
        return;
    }
    
    CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), ScoresWidgetClass);
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->AddToViewport();
    }
}
