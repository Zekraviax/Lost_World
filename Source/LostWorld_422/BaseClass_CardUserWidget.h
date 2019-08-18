// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"

#include "BaseClass_CardUserWidget.generated.h"

// Forward Declarations
class ABaseClass_PlayerController;


UCLASS()
class LOSTWORLD_422_API UBaseClass_CardUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// NativeTick override
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	// Card
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	FCardBase CardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data - Technical")
	int32 IndexInZone;

	// Function variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Functions")
	bool IsDragging;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Functions")
	ABaseClass_PlayerController* LocalPlayerControllerRef;

	UPROPERTY()
	ALostWorld_422GameModeBase* GameModeRef;

	// Mouse Events
	UFUNCTION(BlueprintCallable)
	void OnMouseButtonDownEvent(UBaseClass_CardUserWidget* CardDragWidgetInstance);

	UFUNCTION()
	void CastCard();

	//UFUNCTION()
	//void SetCardTargets();
};
