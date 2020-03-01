// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "BaseClass_CardUserWidget.h"
#include "BaseClass_Widget_DeckBuilder.h"
#include "LostWorld_422GameModeBase.h"

#include "BaseClass_HUD_Level.generated.h"


UCLASS()
class LOSTWORLD_422_API UBaseClass_HUD_Level : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* EncounterList_ScrollBox;

// ------------------------- Widgets
	// Deck Builder Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UBaseClass_Widget_DeckBuilder> DeckBuilder_Class;

	// Deck Builder Instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	UBaseClass_Widget_DeckBuilder* DeckBuilderRef;

// ------------------------- Room Features
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Features")
	TArray<E_LevelRoom_EncounterTypes> EncounterList;

// Functions
// --------------------------------------------------

// ------------------------- Widgets
	UFUNCTION(BlueprintCallable)
	void OpenDeckBuilder();
};
