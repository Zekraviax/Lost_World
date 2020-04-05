// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "WidgetComponent_RoomEncounter.generated.h"


UCLASS()
class LOSTWORLD_422_API UWidgetComponent_RoomEncounter : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(meta = (BindWidget))
	UButton* InteractButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EncounterLabel;

// ------------------------- Encounter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter")
	F_Level_Room EncounterData;

// Base Variables
// --------------------------------------------------

// ------------------------- Encounter
	UFUNCTION(BlueprintCallable)
	void SelectedEncounter();
};