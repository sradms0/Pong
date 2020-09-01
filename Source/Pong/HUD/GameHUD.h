// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/** HUD for displaying display game info within widgets in game */
UCLASS()
class PONG_API AGameHUD final : public AHUD
{
	GENERATED_BODY()

public:
    /** Initializes score widget-blueprint class. */
    AGameHUD();

    /** Creates the score widget and adds it to the viewport. */
    virtual void BeginPlay() override;

private:
    /** Displays the scores of both the player and AI */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Scores", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> ScoresWidgetClass;
    
    /** Contains newly created widgets to add to the viewport */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Scores", meta = (AllowPrivateAccess = "true"))
    class UUserWidget* CurrentWidget;
};
