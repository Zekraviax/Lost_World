#include "BaseClass_PlayerController.h"

#include "EngineUtils.h"
#include "BaseClass_DefaultPawn.h"
#include "BaseClass_GridTile.h"
#include "BaseClass_Widget_Minimap.h"
#include "WidgetComponent_MinimapRoom.h"
#include "Components/SceneComponent.h"


void ABaseClass_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup proper mouse controls
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	ClickEventKeys.Add(EKeys::RightMouseButton);

	// Mouse Up event for when players drag, and then let go of cards
	InputComponent->BindAction("MouseLeftClicked", IE_Pressed, this, &ABaseClass_PlayerController::CustomOnLeftMouseButtonUpEvent);

	// Keyboard controls
	InputComponent->BindAction("MoveNorth", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveNorth);
	InputComponent->BindAction("MoveEast", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveEast);
	InputComponent->BindAction("MoveSouth", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveSouth);
	InputComponent->BindAction("MoveWest", IE_Pressed, this, &ABaseClass_PlayerController::PlayerMoveWest);

	ControlMode = E_Player_ControlMode::E_Move;
}


void ABaseClass_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create the Level HUD widget
	if (!Level_HUD_Widget && Level_HUD_Class) {
		Level_HUD_Widget = CreateWidget<UBaseClass_HUD_Level>(GetWorld(), Level_HUD_Class);
		Level_HUD_Widget->AddToViewport();
	}

	// Add some cards to the players' collection
	FString ContextString;
	FCardBase* Card_Shock = CardsTable->FindRow<FCardBase>("Shock", ContextString, true);
	FCardBase* Card_SuddenInspiration = CardsTable->FindRow<FCardBase>("SuddenInspiration", ContextString, true);
	FCardBase* Card_BloodRecycling = CardsTable->FindRow<FCardBase>("BloodRecycling", ContextString, true);
	FCardBase* Card_Annihilate = CardsTable->FindRow<FCardBase>("Annihilate", ContextString, true);
	FCardBase* Card_RollingQuake = CardsTable->FindRow<FCardBase>("RollingQuake", ContextString, true);

	for (int i = 0; i < 6; i++) {
		CurrentCollection.Add(*Card_Shock);
	}
	for (int i = 0; i < 2; i++) {
		CurrentCollection.Add(*Card_SuddenInspiration);
	}
	CurrentCollection.Add(*Card_BloodRecycling);
	CurrentCollection.Add(*Card_Annihilate);
	CurrentCollection.Add(*Card_RollingQuake);

	ManualBeginPlay();
}


void ABaseClass_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABaseClass_PlayerController::ManualBeginPlay()
{
	// Create the player EntityInBattle
	if (EntityInBattle_Class) {
		UWorld* const World = GetWorld();
		FActorSpawnParameters SpawnParameters;

		EntityInBattleRef = World->SpawnActor<ABaseClass_EntityInBattle>(EntityInBattle_Class, SpawnParameters);
		EntityInBattleRef->EntityBaseData = CurrentEntityData;
		EntityInBattleRef->PlayerControllerRef = this;

		EntityInBattleRef->EntityBaseData.GameOverOnDeath.GameOverOnDeath = true;

		// Set Camera Target
		FViewTargetTransitionParams Params;
		SetViewTarget(EntityInBattleRef, Params);
		EntityInBattleRef->Camera->SetActive(true);

		// Move player to first tile
		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;
			if (FoundTile->PlayerRestPointReference && FoundTile->X_Coordinate == 0 && FoundTile->Y_Coordinate == 0) {
				FoundTile->MinimapRoomReference->SetColour();
				break;
			}
		}
	}

	// Generate Level
	Level_HUD_Widget->Minimap->GenerateLevel();
}


// ------------------------- Controls
void ABaseClass_PlayerController::CustomOnLeftMouseButtonUpEvent()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Mouse Button Up"));

	// Get any actors under cursor
	FHitResult HitResult(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, HitResult);

	if (HitResult.GetActor())
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Hit Actor: " + HitResult.GetActor()->GetName()));

	// Delete CardDrag widget
	if (CurrentDragCardRef && Battle_HUD_Widget)
	{
		//CurrentDragCardRef->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Card Widget Destroyed: " + CurrentDragCardRef->CardData.DisplayName));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Find Target"));

		// Set rudimentary targets based on cast mode
		if (Cast<ABaseClass_EntityInBattle>(HitResult.GetActor()) && CurrentDragCardRef->CardData.SimpleTargetsOverride == E_Card_SetTargets::E_AnyTarget)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Cast Card: " + CurrentDragCardRef->CardData.DisplayName + " on Target: " + HitResult.GetActor()->GetName()));
			CurrentDragCardRef->CardData.CurrentTargets.Add(Cast<ABaseClass_EntityInBattle>(HitResult.GetActor()));

		} else if (CurrentDragCardRef->CardData.SimpleTargetsOverride == E_Card_SetTargets::E_Self) {
			CurrentDragCardRef->CardData.CurrentTargets.Add(CurrentDragCardRef->CardData.Controller);

		} else if (!(Cast<ABaseClass_EntityInBattle>(HitResult.GetActor())) && CurrentDragCardRef->CardData.SimpleTargetsOverride == E_Card_SetTargets::E_AnyTarget) {
			CurrentDragCardRef->RemoveFromParent();
			CurrentDragCardRef = NULL;
			return;
		}

		if (!CurrentDragCardRef->CardData.Controller) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error: No Controller"));
		} else {
			//// Mana Check
			//if (CurrentDragCardRef->CardData.ManaCost != -255) {
			//	if (EntityInBattleRef->EntityBaseData.ManaValues.X_Value >= CurrentDragCardRef->CardData.ManaCost) {
			//		EntityInBattleRef->EntityBaseData.ManaValues.X_Value -= CurrentDragCardRef->CardData.ManaCost;
			//	} else {
			//		CurrentDragCardRef->RemoveFromParent();
			//		CurrentDragCardRef = NULL;
			//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error: Failed to cast card"));
			//		return;
			//	}
			//	CurrentDragCardRef->CastCard();
			//} else {
			//	if (!SpendManaWidget_Reference && SpendManaWidget_Class) {
			//		SpendManaWidget_Reference = CreateWidget<UBaseClass_Widget_SpentMana>(GetWorld(), SpendManaWidget_Class);

			//		SpendManaWidget_Reference->CardReference = CurrentDragCardRef;
			//		SpendManaWidget_Reference->OnWidgetCreated();
			//		SpendManaWidget_Reference->AddToViewport();
			//	}
			//}

			if (CurrentDragCardRef->CardData.AbilitiesAndConditions[0].AbilityConditions.Contains(E_Card_AbilityConditions::E_CastingCost_X)) {
				//if (!SpendManaWidget_Reference && SpendManaWidget_Class) {
				//	SpendManaWidget_Reference = CreateWidget<UBaseClass_Widget_SpentMana>(GetWorld(), SpendManaWidget_Class);

				//	SpendManaWidget_Reference->CardReference = CurrentDragCardRef;
				//	SpendManaWidget_Reference->OnWidgetCreated();
				//	SpendManaWidget_Reference->AddToViewport();
				//}
			} else {
				if (EntityInBattleRef->EntityBaseData.ManaValues.X_Value >= CurrentDragCardRef->CardData.ManaCost) {
					if (CurrentDragCardRef->CardData.ManaCost >= 1) {
						EntityInBattleRef->EntityBaseData.ManaValues.X_Value -= CurrentDragCardRef->CardData.ManaCost;
					}
				} else {
					CurrentDragCardRef->RemoveFromParent();
					CurrentDragCardRef = NULL;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error: Failed to cast card"));
					return;
				}
				CurrentDragCardRef->CastCard();
			}

			// Remove card from hand and add to graveyard
			for (int i = 0; i < CurrentDragCardRef->CardData.Controller->CardsInHand.Num(); i++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("CardInHand Index: " + FString::FromInt(CurrentDragCardRef->CardData.Controller->CardsInHand[i].ZoneIndex) + "  /  Cast Card Index: " + FString::FromInt(CurrentDragCardRef->CardData.ZoneIndex))));

				if (CurrentDragCardRef->CardData.Controller->CardsInHand.IsValidIndex(i) && CurrentDragCardRef->CardData.Controller->CardsInHand[i].ZoneIndex == CurrentDragCardRef->CardData.ZoneIndex) {
					CurrentDragCardRef->CardData.Controller->CardsInHand.RemoveAt(i);
					CurrentDragCardRef->CardData.Controller->CardsInGraveyard.Add(CurrentDragCardRef->CardData);
				}
			}

			for (int j = 0; j < CurrentDragCardRef->CardData.Controller->CardsInHand.Num() - 1; j++)
			{
				if (j == 0)
					Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(true, CurrentDragCardRef->CardData.Controller->CardsInHand[j]);
				else
					Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(false, CurrentDragCardRef->CardData.Controller->CardsInHand[j]);
			}

			CurrentDragCardRef->CardData.Controller->UpdateCardIndicesInAllZones();
			CurrentDragCardRef->CardData.Controller->UpdateCardWidgets();

			CurrentDragCardRef->RemoveFromParent();
			CurrentDragCardRef = NULL;
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveNorth()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Move North"));

		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile->IsValidLowLevel()) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate + 1 && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate) {
					MoveToTile(FoundTile);
					FoundTile->OnPlayerEnterTile();
					break;
				}
			}
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveEast()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Move East"));

		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile->IsValidLowLevel()) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate + 1) {
					MoveToTile(FoundTile);
					FoundTile->OnPlayerEnterTile();
					break;
				}
			}
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveSouth()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Move South"));

		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile->IsValidLowLevel()) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate - 1 && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate) {
					MoveToTile(FoundTile);
					FoundTile->OnPlayerEnterTile();
					break;
				}
			}
		}
	}
}


void ABaseClass_PlayerController::PlayerMoveWest()
{
	if (ControlMode == E_Player_ControlMode::E_Move) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Move West"));

		for (TObjectIterator<ABaseClass_GridTile> Itr; Itr; ++Itr) {
			ABaseClass_GridTile* FoundTile = *Itr;

			if (FoundTile->IsValidLowLevel()) {
				if (FoundTile->X_Coordinate == EntityInBattleRef->X_Coordinate && FoundTile->Y_Coordinate == EntityInBattleRef->Y_Coordinate - 1) {
					MoveToTile(FoundTile);
					FoundTile->OnPlayerEnterTile();
					break;
				}
			}
		}
	}
}


// ------------------------- Gameplay
void ABaseClass_PlayerController::BeginBattle()
{
	if (Level_HUD_Widget)
		Level_HUD_Widget->SetVisibility(ESlateVisibility::Collapsed);

	// Create the Battle HUD widget
	if (Battle_HUD_Widget) {
		Battle_HUD_Widget->SetVisibility(ESlateVisibility::Visible);
	} else if (Battle_HUD_Class && !Battle_HUD_Widget) {
		Battle_HUD_Widget = CreateWidget<UBaseClass_HUD_Battle>(GetWorld(), Battle_HUD_Class);
		Battle_HUD_Widget->AddToViewport();
	}
}


void ABaseClass_PlayerController::ExitBattle()
{
	if (Battle_HUD_Widget)
		Battle_HUD_Widget->SetVisibility(ESlateVisibility::Collapsed);

	// Create the Level HUD widget
	if (Level_HUD_Widget) {
		Level_HUD_Widget->SetVisibility(ESlateVisibility::Visible);
	} else if (Level_HUD_Class && !Level_HUD_Widget) {
		Level_HUD_Widget = CreateWidget<UBaseClass_HUD_Level>(GetWorld(), Level_HUD_Class);
		Level_HUD_Widget->AddToViewport();
	}

	// Restore the players' MP, but not HP


	ControlMode = E_Player_ControlMode::E_Move;
	Level_HUD_Widget->Minimap->UpdateMinimap(CurrentLocationInLevel);
}


void ABaseClass_PlayerController::MoveToTile(ABaseClass_GridTile* TileReference)
{
	// Set Player's Entity location
	EntityInBattleRef->SetActorLocation(TileReference->PlayerRestPointReference->GetComponentLocation());
	EntityInBattleRef->X_Coordinate = TileReference->X_Coordinate;
	EntityInBattleRef->Y_Coordinate = TileReference->Y_Coordinate;
	CurrentLocationInLevel = TileReference;

	CurrentRoom = TileReference->RoomReference;

	Level_HUD_Widget->Minimap->UpdateMinimap(TileReference);
}