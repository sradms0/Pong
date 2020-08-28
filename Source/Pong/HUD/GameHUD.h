// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API AGameHUD final : public AHUD
{
	GENERATED_BODY()

public:
    AGameHUD();
    
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Scores", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> ScoresWidgetClass;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Scores", meta = (AllowPrivateAccess = "true"))
    class UUserWidget* CurrentWidget;
};
