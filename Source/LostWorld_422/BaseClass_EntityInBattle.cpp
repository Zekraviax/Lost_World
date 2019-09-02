// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_EntityInBattle.h"

#include "BaseClass_EntityInWorld.h"
#include "BaseClass_PlayerController.h"
#include "LostWorld_422GameStateBase.h"

// Sets default values
ABaseClass_EntityInBattle::ABaseClass_EntityInBattle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//FAttachmentTransformRules AttachRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	//StaticMesh->AttachToComponent(RootComponent, AttachRules);
	//SpringArm->AttachToComponent(StaticMesh, AttachRules);
	//Camera->AttachToComponent(SpringArm, AttachRules);
	StaticMesh->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ABaseClass_EntityInBattle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseClass_EntityInBattle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseClass_EntityInBattle::CustomOnBeginMouseOverEvent(UPrimitiveComponent * TouchedComponent)
{

}

void ABaseClass_EntityInBattle::Debug_CreateDefaultDeck()
{
	for (int i = 0; i < 10; i++)
	{
		ALostWorld_422GameModeBase* LocalGameModeRef = (ALostWorld_422GameModeBase*)GetWorld()->GetAuthGameMode();
		FString ContextString;
		TArray<FName> RowNames = LocalGameModeRef->CardDataTableRef->GetRowNames();
		CardsInDeck.Add(*LocalGameModeRef->CardDataTableRef->FindRow<FCardBase>(RowNames[1], ContextString));

		CardsInDeck[i].Controller = this;
		CardsInDeck[i].Owner = this;
		CardsInDeck[i].ZoneIndex = i;
	}
}

void ABaseClass_EntityInBattle::Begin_Battle()
{
	int32 RandIndex;

	// Draw seven cards at random
	for (int i = 0; i < 7; i++)
	{
		RandIndex = FMath::RandRange(0, CardsInDeck.Num() - 1);
		CardsInHand.Add(CardsInDeck[RandIndex]);

		// Set Indices
		CardsInHand[i].ZoneIndex = i;

		// Set Ownership
		if (!CardsInHand[i].Controller)
			CardsInHand[i].Controller = this;
		if (!CardsInHand[i].Owner)
			CardsInHand[i].Owner = this;

		CardsInDeck.RemoveAt(RandIndex);
	}

	UpdateCardIndicesInAllZones();
}

void ABaseClass_EntityInBattle::UpdateCardWidgets()
{
	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	if (EntityBaseData.IsPlayerControllable && GameStateRef->SortedTurnOrderList[0] == this)
	{
		for (int i = 0; i < CardsInHand.Num(); i++)
		{
			if (i == 0)
				PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(true, CardsInHand[i]);
			else
				PlayerControllerRef->Battle_HUD_Widget->CreatePlayerCardsInHandWidgets(false, CardsInHand[i]);
		}
	}
}

void ABaseClass_EntityInBattle::Begin_Turn()
{
	UpdateCardIndicesInAllZones();
	UpdateCardWidgets();

	if (!EntityBaseData.IsPlayerControllable) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("IsPlayerControllable: False"));
		AI_CastRandomCard();
	}
}

void ABaseClass_EntityInBattle::UpdateCardIndicesInAllZones()
{
	for (int i = 0; i < CardsInHand.Num(); i++)
		CardsInHand[i].ZoneIndex = i;
	
	for (int j = 0; j < CardsInGraveyard.Num(); j++)
		CardsInGraveyard[j].ZoneIndex = j;

	for (int k = 0; k < CardsInDeck.Num(); k++)
		CardsInDeck[k].ZoneIndex = k;
}

void ABaseClass_EntityInBattle::AI_CastRandomCard()
{
	// Get random card in hand
	int32 RandCardIndex = FMath::RandRange(0, CardsInHand.Num() - 1);
	FCardBase RandCard = CardsInHand[RandCardIndex];
	TArray<ABaseClass_EntityInBattle*> RandTargetsArray;

	// Set targets
	for (int i = 0; i < RandCard.FunctionsWithRules.Num(); i++) {
		if (RandCard.FunctionsWithRules[i].Rules.Contains(E_Card_Rules::E_Rule_Target_Self)) {
			RandCard.CurrentTargets.Add(this);
		}
		else if (RandCard.FunctionsWithRules[i].Rules.Contains(E_Card_Rules::E_Rule_Target_CastTarget)) {
			for (TActorIterator<ABaseClass_EntityInBattle> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
				ABaseClass_EntityInBattle* FoundEntity = *ActorItr;

				if (FoundEntity->EntityBaseData.IsPlayerControllable) {
					RandTargetsArray.Add(FoundEntity);
				}
			}
			RandCard.CurrentTargets.Add(RandTargetsArray[FMath::RandRange(0, RandTargetsArray.Num() - 1)]);
		}
	}

	// Cast card
	if (!GameModeRef)
		GameModeRef = Cast<ALostWorld_422GameModeBase>(GetWorld()->GetAuthGameMode());

	GameModeRef->CardFunctionLibraryReference->AddCardFunctionsToTheStack(RandCard);

	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	GameStateRef->EntityEndOfTurn();
}