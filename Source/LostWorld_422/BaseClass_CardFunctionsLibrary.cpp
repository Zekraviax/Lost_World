#include "BaseClass_CardFunctionsLibrary.h"

#include "BaseClass_EntityInBattle.h"
#include "LostWorld_422GameStateBase.h"


// Function index definitions
#define NOTHING 0
#define DRAW_CARDS 1
#define DEAL_DAMAGE 2
//#define GUN_DOWN 0
//#define SHOCKWAVE 1
//#define SUDDEN_INSPIRATION 2
//#define ESSENCE_RECYCLING 2
//#define RECALL 4
//#define ROLLING_QUAKE 5


//-------------------- Base Functions --------------------//
// Sets default values
ABaseClass_CardFunctionsLibrary::ABaseClass_CardFunctionsLibrary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseClass_CardFunctionsLibrary::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeCardFunctions();
}

// Called every frame
void ABaseClass_CardFunctionsLibrary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


//-------------------- Function Initializations --------------------//
void ABaseClass_CardFunctionsLibrary::InitializeCardFunctions()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize ability functions."));

	CardFunctions[NOTHING] = &ABaseClass_CardFunctionsLibrary::CardFunction_Nothing;
	CardFunctions[DRAW_CARDS] = &ABaseClass_CardFunctionsLibrary::CardFunction_DrawCards;
	CardFunctions[DEAL_DAMAGE] = &ABaseClass_CardFunctionsLibrary::CardFunction_DealDamage;
	//CardFunctions[GUN_DOWN] = &ABaseClass_CardFunctionsLibrary::Gun_Down;
	//CardFunctions[SHOCKWAVE] = &ABaseClass_CardFunctionsLibrary::Shockwave;
	//CardFunctions[SUDDEN_INSPIRATION] = &ABaseClass_CardFunctionsLibrary::Sudden_Inspiration;
	//CardFunctions[ESSENCE_RECYCLING] = &ABaseClass_CardFunctionsLibrary::Essence_Recycling;
	//CardFunctions[RECALL] = &ABaseClass_CardFunctionsLibrary::Recall;
	//CardFunctions[ROLLING_QUAKE] = &ABaseClass_CardFunctionsLibrary::Rolling_Quake;


	UE_LOG(LogTemp, Warning, TEXT("Successfully initialized ability functions."));
}



//-------------------- Card Functions --------------------//
void ABaseClass_CardFunctionsLibrary::CardFunction_Nothing()
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Function: Nothing"));
}

void ABaseClass_CardFunctionsLibrary::CardFunction_DrawCards()
{
	//UE_LOG(LogTemp, Warning, TEXT("Execute Function: Draw Cards"));

	//int32 DrawValue = 0;

	//for (int i = 0; i < DrawValue; i++)
	//{
	//	if (LocalCardReference.Controller->CardsInDeck.Num() > 0) {
	//		LocalCardReference.Controller->CardsInHand.Add(LocalCardReference.Controller->CardsInDeck[0]);

	//		// Set ownership
	//		if (!LocalCardReference.Controller->CardsInHand[0].Owner) {
	//		LocalCardReference.Controller->CardsInHand.Last().Owner = LocalCardReference.Controller;
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
	//		}
	//		if (!LocalCardReference.Controller->CardsInHand[0].Controller) {
	//		LocalCardReference.Controller->CardsInHand.Last().Controller = LocalCardReference.Controller;
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
	//		}

	//		LocalCardReference.Controller->CardsInDeck.RemoveAt(0);
	//	}
	//}

	//LocalCardReference.Controller->UpdateCardIndicesInAllZones();
	//LocalCardReference.Controller->UpdateCardWidgets();
}

void ABaseClass_CardFunctionsLibrary::CardFunction_DealDamage()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Function: Deal Damage"));

	//int32 DamageValue = 0

	//for (int i = 0; i < LocalCardReference.CurrentTargets.Num(); i++)
	//{
	//	int32 OldHealthValue = LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value;
	//	LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value -= DamageValue;

	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + LocalCardReference.CurrentTargets[i]->EntityBaseData.DisplayName)));
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
	//}
}

//void ABaseClass_CardFunctionsLibrary::Gun_Down()
//{
//	int32 DamageValue = 7;
//	int32 OldHealthValue = LocalCardReference.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;
//	LocalCardReference.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value -= DamageValue;
//
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + LocalCardReference.CurrentTargets[0]->EntityBaseData.DisplayName)));
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(LocalCardReference.CurrentTargets[00]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
//}
//
//void ABaseClass_CardFunctionsLibrary::Shockwave()
//{
//	for (int i = 0; i < LocalCardReference.CurrentTargets.Num(); i++)
//	{
//		int32 DamageValue = 1;
//		int32 OldHealthValue = LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value;
//		LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value -= DamageValue;
//
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + LocalCardReference.CurrentTargets[i]->EntityBaseData.DisplayName)));
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(LocalCardReference.CurrentTargets[i]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
//	}
//}
//
//void ABaseClass_CardFunctionsLibrary::Sudden_Inspiration()
//{
//	int32 DrawValue = 2;
//
//	for (int i = 0; i < DrawValue; i++)
//	{
//		if (LocalCardReference.Controller->CardsInDeck.Num() > 0) {
//			LocalCardReference.Controller->CardsInHand.Add(LocalCardReference.Controller->CardsInDeck[0]);
//
//			// Set ownership
//			//LocalCardReference.Controller->CardsInHand.Last().Owner = LocalCardReference.Controller;
//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
//
//			LocalCardReference.Controller->CardsInHand.Last().Controller = LocalCardReference.Controller;
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
//
//			LocalCardReference.Controller->CardsInDeck.RemoveAt(0);
//		}
//	}
//
//	LocalCardReference.Controller->UpdateCardIndicesInAllZones();
//	LocalCardReference.Controller->UpdateCardWidgets();
//}
//
//void ABaseClass_CardFunctionsLibrary::Essence_Recycling()
//{
//	int32 DrawValue = 2;
//	int32 DamageValue = 2;
//
//	int32 OldHealthValue = LocalCardReference.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;
//	LocalCardReference.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value -= DamageValue;
//
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + LocalCardReference.CurrentTargets[0]->EntityBaseData.DisplayName)));
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(LocalCardReference.CurrentTargets[00]->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
//
//	for (int i = 0; i < DrawValue; i++)
//	{
//		if (LocalCardReference.Controller->CardsInDeck.Num() > 0) {
//			LocalCardReference.Controller->CardsInHand.Add(LocalCardReference.Controller->CardsInDeck[0]);
//
//			// Set ownership
//			//LocalCardReference.Controller->CardsInHand.Last().Owner = LocalCardReference.Controller;
//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Owner"));
//
//			LocalCardReference.Controller->CardsInHand.Last().Controller = LocalCardReference.Controller;
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Card Controller"));
//
//			LocalCardReference.Controller->CardsInDeck.RemoveAt(0);
//		}
//	}
//
//	LocalCardReference.Controller->UpdateCardIndicesInAllZones();
//	LocalCardReference.Controller->UpdateCardWidgets();
//}
//
//void ABaseClass_CardFunctionsLibrary::Recall() 
//{
//	TSubclassOf<class UBaseClass_Widget_ZoneSearch> ZoneSearchWidget_Class = Cast<ALostWorld_422GameModeBase>(GetWorld()->GetAuthGameMode())->ZoneSearchWidget_Class;
//	UBaseClass_Widget_ZoneSearch* ZoneSearchWidget_Reference = CreateWidget<UBaseClass_Widget_ZoneSearch>(GetWorld(), ZoneSearchWidget_Class);
//	ZoneSearchWidget_Reference->PopulateWidget(LocalCardReference.Controller->CardsInDeck, 1, E_ZoneSearch_Functions::E_DrawCards, E_Card_Zones::E_Deck);
//	ZoneSearchWidget_Reference->AddToViewport();
//}
//
//void ABaseClass_CardFunctionsLibrary::Rolling_Quake()
//{
//	int32 DamageValue = 2;
//	int32 OldHealthValue = 0;
//	ABaseClass_EntityInBattle* Target;
//
//	for (int i = 0; i < LocalCardReference.ManaCost; i++) {
//		Target = LocalCardReference.CurrentTargets[FMath::RandRange(0, LocalCardReference.CurrentTargets.Num() - 1)];
//
//		OldHealthValue = Target->EntityBaseData.HealthValues.X_Value;
//		Target->EntityBaseData.HealthValues.X_Value -= DamageValue;
//
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Target: " + Target->EntityBaseData.DisplayName)));
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Damage: " + FString::FromInt(DamageValue) + "  /  New Health Value: " + FString::FromInt(Target->EntityBaseData.HealthValues.X_Value) + "  /  Old Health Value: " + FString::FromInt(OldHealthValue))));
//
//	}
//}

//-------------------- Execute Functions --------------------//
void ABaseClass_CardFunctionsLibrary::ExecuteCardFunctions()
{
	int32 CardFunctionIndex = 0;

	// Get GameState
	if (!GameStateRef)
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Searching for function to execute."));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (TEXT("Card Targets: ") + FString::FromInt(LocalCardReference.CurrentTargets.Num())));


	// Valid range check
	if (CardFunctionIndex > CARD_FUNCTIONS_COUNT || CardFunctionIndex < 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Failed Execution"));
		return;
	}

	(this->* (CardFunctions[CardFunctionIndex]))();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Successful Execution"));

	GameStateRef->TheStack.RemoveAt(0);

	if (GameStateRef->TheStack.Num() > 0) {
		GetWorldTimerManager().SetTimer(StackTimerHandle, this, &ABaseClass_CardFunctionsLibrary::ExecuteCardFunctions, 2.f);
	}
}


void ABaseClass_CardFunctionsLibrary::AddCardFunctionsToTheStack(FCardBase Card)
{
	FCardBase NewStackEntry;
	NewStackEntry.Art = Card.Art;
	NewStackEntry.Controller = Card.Controller;
	NewStackEntry.DisplayName = Card.DisplayName;
	NewStackEntry.Elements = Card.Elements;
	NewStackEntry.ManaCost = Card.ManaCost;
	NewStackEntry.Owner = Card.Owner;
	NewStackEntry.Type = Card.Type;

	// Get GameState
	if (GameStateRef->IsValidLowLevel())
		GameStateRef = GetWorld()->GetGameState<ALostWorld_422GameStateBase>();

	for (int i = 0; i < Card.AbilitiesAndConditions.Num(); i++) {
		NewStackEntry.Description = Card.Description;
		NewStackEntry.CurrentTargets = Card.CurrentTargets;
		NewStackEntry.AbilitiesAndConditions.Add(Card.AbilitiesAndConditions[i]);
		GameStateRef->TheStack.Add(NewStackEntry);
	}

	// Start timer for the stack
	GetWorldTimerManager().SetTimer(StackTimerHandle, this, &ABaseClass_CardFunctionsLibrary::ExecuteCardFunctions, 2.f);
}


//void ABaseClass_CardFunctionsLibrary::SetCardTargets()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Set Card Targets"));
//}


//int32 ABaseClass_CardFunctionsLibrary::ReturnIntValueFromRules()
//{
//	// Return Fixed Integers
//	if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_One))
//		return 1;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Two))
//		return 2;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Three))
//		return 3;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Four))
//		return 4;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Five))
//		return 5;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Six))
//		return 6;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Seven))
//		return 7;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Eight))
//		return 8;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Nine))
//		return 9;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_FixedInteger_Ten))
//		return 10;
//	// Calculate and return variable integers
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_VariableInteger_Current_Power))
//		return LocalCardReference.Controller->EntityBaseData.ManaValues.X_Value;
//	else if (LocalCardReference.FunctionsWithRules[0].Rules.Contains(E_Card_Rules::E_Rule_VariableInteger_Random_Number))
//		return FMath::RandRange(0, 10);
//	else
//		return 0;
//}