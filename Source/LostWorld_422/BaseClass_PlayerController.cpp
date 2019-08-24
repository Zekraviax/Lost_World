// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseClass_PlayerController.h"

#include "EngineUtils.h"
#include "BaseClass_DefaultPawn.h"


ABaseClass_PlayerController::ABaseClass_PlayerController()
{
	// Construct Player EntityInWorld
	//static ConstructorHelpers::FObjectFinder<UBlueprint>EntityInBattleBlueprintConstruct(TEXT("Blueprint'/Game/Blueprint_EntityInBattle.Blueprint_EntityInBattle'"));

	//if (EntityInBattleBlueprintConstruct.Object) {
	//	EntityInBattle_Class = (UClass*)EntityInBattleBlueprintConstruct.Object->GeneratedClass;
	//}
}

void ABaseClass_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup proper mouse controls
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	ClickEventKeys.Add(EKeys::RightMouseButton);

	// Mouse Up event for when players let go of cards
	//if(GetPawn())
	InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &ABaseClass_PlayerController::CustomOnLeftMouseButtonUpEvent);
}

void ABaseClass_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create the battle HUD widget
	if (!Battle_HUD_Widget && Battle_HUD_Class)
	{
		Battle_HUD_Widget = CreateWidget<UBaseClass_HUD_Battle>(GetWorld(), Battle_HUD_Class);
		Battle_HUD_Widget->AddToViewport();
	}

	// Create the player EntityInWorld
	if (!EntityInBattleRef && EntityInBattle_Class)
	{
		UWorld* const World = GetWorld(); // get a reference to the world
		FActorSpawnParameters SpawnParameters;
		EntityInBattleRef = World->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_Class, SpawnParameters);
		EntityInBattleRef->EntityBaseData = CurrentEntityData;
		EntityInBattleRef->PlayerControllerRef = this;

		// Set Camera Target
		FViewTargetTransitionParams Params;
		SetViewTarget(EntityInBattleRef, Params);
		EntityInBattleRef->Camera->SetActive(true);
	}
}

void ABaseClass_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseClass_PlayerController::CustomOnLeftMouseButtonUpEvent()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Mouse Button Up"));

	// Get any actors under cursor
	FHitResult HitResult(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, HitResult);

	if (HitResult.GetActor())
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hit Actor: " + HitResult.GetActor()->GetName()));

	// Delete CardDrag widget
	if (CurrentDragCardRef)
	{
		//CurrentDragCardRef->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Card Widget Destroyed: " + CurrentDragCardRef->CardData.DisplayName));

		if (Cast<ABaseClass_EntityInBattle>(HitResult.GetActor()) && CurrentDragCardRef->CardData.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_CastTarget) 
			|| CurrentDragCardRef->CardData.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_Self))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Find Target"));

			// Set rudimentary targets based on cast mode
			if (CurrentDragCardRef->CardData.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_Target_CastTarget))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Cast Card: " + CurrentDragCardRef->CardData.DisplayName + " on Target: " + HitResult.GetActor()->GetName()));
				CurrentDragCardRef->CardData.CurrentTargets.Add(Cast<ABaseClass_EntityInBattle>(HitResult.GetActor()));
			}

			CurrentDragCardRef->CastCard();

			// Remove card from hand and add to graveyard
			for (int i = 0; i < CurrentDragCardRef->CardData.Controller->CardsInHand.Num(); i++)
			{
				//
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("CardInHand Index: " + FString::FromInt(CurrentDragCardRef->CardData.Controller->CardsInHand[i].ZoneIndex) + "  /  Cast Card Index: " + FString::FromInt(CurrentDragCardRef->CardData.ZoneIndex))));

				if (CurrentDragCardRef->CardData.Controller->CardsInHand[i].ZoneIndex == CurrentDragCardRef->CardData.ZoneIndex)
				{
					CurrentDragCardRef->CardData.Controller->CardsInHand.RemoveAt(i);
					CurrentDragCardRef->CardData.Controller->CardsInGraveyard.Add(CurrentDragCardRef->CardData);
					break;
				}
			}

			for (int j = 0; j < CurrentDragCardRef->CardData.Controller->CardsInHand.Num(); j++)
			{
				if (j == 0)
					Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(true, CurrentDragCardRef->CardData.Controller->CardsInHand[j]);
				else
					Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(false, CurrentDragCardRef->CardData.Controller->CardsInHand[j]);
			}
		}

		CurrentDragCardRef->RemoveFromParent();
	}
}