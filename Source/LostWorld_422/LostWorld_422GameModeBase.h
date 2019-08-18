// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"

#include "LostWorld_422GameModeBase.generated.h"

// Forward Declarations
class ABaseClass_EntityInBattle;
class ABaseClass_CardFunctionsLibrary;


// Enums
//--------------------------------------------------

// Card Base Variables
UENUM(BlueprintType)
enum class E_Card_Types : uint8
{
	E_Summon			UMETA(DisplayName = "Summon"),
	E_Spell				UMETA(DisplayName = "Spell"),
	E_Technique			UMETA(DisplayName = "Technique"),
};

UENUM(BlueprintType)
enum class E_Card_Elements : uint8
{
	E_Fire				UMETA(DisplayName = "Fire"),
	E_Water				UMETA(DisplayName = "Water"),
	E_Air				UMETA(DisplayName = "Air"),
	E_Earth				UMETA(DisplayName = "Earth"),
	E_Light				UMETA(DisplayName = "Light"),
	E_Arcane			UMETA(DisplayName = "Arcane"),
	E_Cosmic			UMETA(DisplayName = "Cosmic"),
	E_Divine			UMETA(DisplayName = "Divine")
};

// Card Technical Functions
UENUM(BlueprintType)
enum class E_Card_Functions : uint8
{
	E_Nothing						UMETA(DisplayName = "Nothing"),
	E_Deal_X_Damage					UMETA(DisplayName = "Deal X Damage"),
	E_Draw_X_Cards					UMETA(DisplayName = "Draw X Cards"),
	E_Add_Status_Effect				UMETA(DisplayName = "Add Status Effect To Targets"),
	E_Change_Current_Mana			UMETA(DisplayName = "Change Target's Current Mana"),
	E_Change_Maximum_Mana			UMETA(DisplayName = "Change Target's Maximum Mana"),
	E_Change_Current_Health			UMETA(DisplayName = "Change Target's Current Health"),
	E_Change_Maximum_Health			UMETA(DisplayName = "Change Target's Maximum Health"),
	E_Create_Card					UMETA(DisplayName = "Create A Card"),
	E_Search_Zone					UMETA(DisplayName = "Search Zone (Hand/Deck/Graveyard)"),
	E_Modal_Choose_One				UMETA(DisplayName = "Choose-One Effect"),						// Choose one-or-more function effects
};

UENUM(BlueprintType)
enum class E_Card_Rules : uint8
{
	// Card Types
	E_Rule_CardType_Spell_Cards					UMETA(DisplayName = "Card Type: Spells"),
	E_Rule_CartType_Summon_Cards				UMETA(DisplayName = "Card Type: Summons"),
	E_Rule_CardType_Technique_Cards				UMETA(DisplayName = "Card Type: Techniques"),
	// Card Zones
	E_Rule_Zone_Hand							UMETA(DisplayName = "Zone: Hand"),
	E_Rule_Zone_Deck							UMETA(DisplayName = "Zone: Deck"),
	E_Rule_Zone_Graveyard						UMETA(DisplayName = "Zone: Graveyard"),
	// Set Numbers
	E_Rule_FixedInteger_Zero					UMETA(DisplayName = "Fixed Integer: 0"),
	E_Rule_FixedInteger_One						UMETA(DisplayName = "Fixed Integer: 1"),
	E_Rule_FixedInteger_Two						UMETA(DisplayName = "Fixed Integer: 2"),
	E_Rule_FixedInteger_Three					UMETA(DisplayName = "Fixed Integer: 3"),
	E_Rule_FixedInteger_Four					UMETA(DisplayName = "Fixed Integer: 4"),
	E_Rule_FixedInteger_Five					UMETA(DisplayName = "Fixed Integer: 5"),
	E_Rule_FixedInteger_Six						UMETA(DisplayName = "Fixed Integer: 6"),
	E_Rule_FixedInteger_Seven					UMETA(DisplayName = "Fixed Integer: 7"),
	E_Rule_FixedInteger_Eight					UMETA(DisplayName = "Fixed Integer: 8"),
	E_Rule_FixedInteger_Nine					UMETA(DisplayName = "Fixed Integer: 9"),
	E_Rule_FixedInteger_Ten						UMETA(DisplayName = "Fixed Integer: 10"),
	// Variable Numbers
	E_Rule_VariableInteger_Current_Power		UMETA(DisplayName = "Variable Integer: Current Power"),
	E_Rule_VariableInteger_Random_Number		UMETA(DisplayName = "Variable Integer: Random Number (0 - 10)"),
	// Miscellaneoous Functions
	E_Rule_Draw_Chosen_Card						UMETA(DisplayName = "Miscellaneous: Draw Chosen Card"),
	// Targets
	E_Rule_Target_CastTarget					UMETA(DisplayName = "Target: Cast Target"),
	E_Rule_Target_Self							UMETA(DisplayName = "Target: Self"),
};

UENUM(BlueprintType)
enum class E_Card_UserSelectModes : uint8
{
	E_Cast				UMETA(DisplayName = "Cast From Hand"),
	E_Select			UMETA(DisplayName = "Select From CardSelector Widget"),
};

UENUM(BlueprintType)
enum class E_Card_UserSelectFunctions : uint8
{
	E_Draw_Card,
	E_Discard_Card,
};

// Modes for casting on a target, not specifically the spells' target
UENUM(BlueprintType)
enum class E_Card_TargetModes : uint8
{
	E_Self,
	E_SingleEntity,
	E_AllEntities,
	E_SingleEnemy,
	E_AllEnemies,
};


// Structs
//--------------------------------------------------

// Base
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FIntVector2D
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X_Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y_Value;

	// Default Constructor
	FIntVector2D() {}

	FIntVector2D(int32 SetX, int32 SetY)
	{
		X_Value = SetX;
		Y_Value = SetY;
	}
};

// Cards and Card Functions
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FCardFunctionAndRules
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Data")
	E_Card_Functions Function;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Data")
	TArray<E_Card_Rules> Rules;

	FCardFunctionAndRules()
	{
		Function = E_Card_Functions::E_Deal_X_Damage;
		Rules.Add(E_Card_Rules::E_Rule_FixedInteger_Seven);
	}
};

USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FCardBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	int32 ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Card_Types Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	TArray<E_Card_Elements> Elements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	UTexture2D* Art;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functions")
	TArray<FCardFunctionAndRules> FunctionsWithRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 ZoneIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	E_Card_UserSelectModes CurrentSelectMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	ABaseClass_EntityInBattle* Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	TArray<ABaseClass_EntityInBattle*> CurrentTargets;

	FCardBase()
	{
		DisplayName = "Default";
		ManaCost = 1;
		Type = E_Card_Types::E_Spell;
		Elements.Add(E_Card_Elements::E_Fire);
		Art = NULL;
		Description = "Blank.";
		ZoneIndex = -1;
		CurrentSelectMode = E_Card_UserSelectModes::E_Cast;
		Owner = NULL;
		Controller = NULL;
	}
};

// Entities
USTRUCT(BlueprintType)
struct LOSTWORLD_422_API FEntityBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	FIntVector2D HealthValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	FIntVector2D ManaValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	bool IsPlayerControllable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
	TArray<FCardBase> CurrentDeck;

	FEntityBase()
	{
		DisplayName = "Default";
		HealthValues = FIntVector2D(10, 10);
		ManaValues = FIntVector2D(5, 5);
		IsPlayerControllable = false;
	}
};

// Default
USTRUCT()
struct LOSTWORLD_422_API FTestStruct
{
	GENERATED_BODY();
};

UCLASS()
class LOSTWORLD_422_API ALostWorld_422GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	// Card Data Table Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Technical")
	FDataTableRowHandle CardDataTableRowRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Technical")
	UDataTable* CardDataTableRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data - Technical")
	ABaseClass_CardFunctionsLibrary* CardFunctionLibraryReference;
};
