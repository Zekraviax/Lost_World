// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "BaseClass_CardFunctionsLibrary.h"
#include "BaseClass_WidgetComponent_Stats.h"
#include "LostWorld_422GameModeBase.h"

#include "BaseClass_EntityInBattle.generated.h"

// Forward Declarations
class ABaseClass_EntityInWorld;
class ABaseClass_PlayerController;
class ALostWorld_422GameStateBase;

// Entity In Battle:
// A class that handles the functions of an entity in battle.
// Handles entity variables such as health and mana, current cards, etc.
// Represented in the world by an EntityInWorld actor.	

UCLASS()
class LOSTWORLD_422_API ABaseClass_EntityInBattle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_EntityInBattle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	FEntityBase EntityBaseData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	TArray<FCardBase> CardsInDeck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	TArray<FCardBase> CardsInHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	TArray<FCardBase> CardsInGraveyard;

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	// UI in World Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* EntityStats_WidgetComponent;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ABaseClass_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ALostWorld_422GameModeBase* GameModeRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ALostWorld_422GameStateBase* GameStateRef;

// ------------------------- Widgets
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_WidgetComponent_Stats* EntityStats_WidgetComponent_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_WidgetComponent_Stats> EntityStats_WidgetComponent_Class;

// ------------------------- Timers
	UPROPERTY()
	FTimerHandle EndTurn_TimerHandle;

// Functions
// --------------------------------------------------

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void CustomOnBeginMouseOverEvent(UPrimitiveComponent* TouchedComponent);

// ------------------------- Deck
	UFUNCTION()
	void Debug_CreateDefaultDeck();

	UFUNCTION(BlueprintImplementableEvent)
	void ShuffleCardsInDeck_BP();

// ------------------------- Components
	UFUNCTION()
	void ResetStatsWidget();

// ------------------------- Battle
	UFUNCTION()
	void Begin_Battle();

	UFUNCTION()
	void Begin_Turn();

	UFUNCTION()
	void UpdateCardWidgets();

	UFUNCTION()
	void UpdateCardIndicesInAllZones();

// ------------------------- AI
	UFUNCTION()
	void AI_CastRandomCard();

	UFUNCTION()
	void AI_EndTurnDelay();
};