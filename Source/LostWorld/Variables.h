#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Variables.generated.h"


// Forward declarations
class AActorGridTile;


// ---------------------------------------- Enums ---------------------------------------- //

// -------------------------------- Levels
UENUM(BlueprintType)
enum class EFloorLayouts : uint8
{
	FourSquares
};


// -------------------------------- Cards
UENUM(BlueprintType)
enum class ECardTypes : uint8
{
	Spell,
	Summon,
	Technique,
	Command,
	Shout
};


UENUM(BlueprintType)
enum class ECardTargets : uint8
{
	AnySingleEntity,
};


UENUM(BlueprintType)
enum class ECardFunctions : uint8
{
	TestFunctionOne,
};


// ---------------------------------------- Structs ---------------------------------------- //
USTRUCT(BlueprintType)
struct LOSTWORLD_API FIntVector2D
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y;

	// Default constructor
	FIntVector2D()
	{
		X = 0;
		Y = 0;
	}

	// Creates and initializes a new instance with the specified coordinates.
	FIntVector2D(int32 InX, int32 InY)
	{
		X = InX;
		Y = InY;
	}

	// Comparator
	FORCEINLINE bool operator==(const FIntVector2D& OtherStruct) const
	{
		return X == OtherStruct.X &&
			Y == OtherStruct.Y;
	}
};


// -------------------------------- Cards
USTRUCT(BlueprintType)
struct LOSTWORLD_API FCard
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int BaseCost; // Use a different variable for the total cost (the cost after any changes to the base cost.)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	TArray<ECardTypes> CardTypes; // Card types should be added to the array in the order that they're written on the card.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	FString Description; // Describes the cards functions to the player.

	// For each function that requires different targets, the game will add an entry to the stack.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Functions)
	TMap<ECardFunctions, ECardTargets> StackEntries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CalculatedVariables)
	int TotalCost;

	// Default constructor
	FCard()
	{
		DisplayName = "Default Card";
		BaseCost = 1;
		CardTypes.Add(ECardTypes::Spell);
		Description = "This is a default description.";
		TotalCost = 1;
		StackEntries.Add(ECardFunctions::TestFunctionOne, ECardTargets::AnySingleEntity);
	}
};


// -------------------------------- Entities
USTRUCT(BlueprintType)
struct LOSTWORLD_API FEntityBaseStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumHealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumManaPoints;

	// Increases damage dealt by physical attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Strength;

	// Default constructor
	FEntityBaseStats()
	{
		MaximumHealthPoints = 10;
		MaximumManaPoints = 10;
		Strength = 1;
	}
};


// This struct should only contain variables that are relevant to all types of entities:
// Players, normal enemies, boss enemies, summons, and NPCs(?)
USTRUCT(BlueprintType)
struct LOSTWORLD_API FEntity
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	// All entities will have a Deck variable, even if they don't use it in gameplay.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCard> Deck;

	FEntity()
	{
		DisplayName = "Default Jim";
		Deck.Add(FCard());
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FEnemyEntity : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntity EntityData;

	// Experience points given to the player when defeated.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExperiencePoints;

	FEnemyEntity()
	{
		ExperiencePoints = 1;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FEncounter : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EnemyDataTableRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumFloor;

	FEncounter()
	{
		EnemyDataTableRowName = "TestEncounterOne";
		MinimumFloor = 1;
		MaximumFloor = 1;
	}

	FORCEINLINE bool operator==(const FEncounter& OtherStruct) const
	{
		return this->EnemyDataTableRowName == OtherStruct.EnemyDataTableRowName &&
				this->MinimumFloor == OtherStruct.MinimumFloor &&
				this->MaximumFloor == OtherStruct.MaximumFloor;
	}
};


// -------------------------------- Levels
USTRUCT(BlueprintType)
struct LOSTWORLD_API FCorridorDataAsStruct
{
	GENERATED_BODY()

	// Each corridor grid tile coordinate.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntVector2D> GridTileCoordinates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActorGridTile*> GridTilesInCorridor;

	FORCEINLINE bool operator==(const FCorridorDataAsStruct& OtherStruct) const
	{
		return this->GridTileCoordinates == OtherStruct.GridTileCoordinates &&
				this->GridTilesInCorridor == OtherStruct.GridTilesInCorridor;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FRoomDataAsStruct
{
	GENERATED_BODY()

	// The lengths and widths should not exceed the dimensions of the floor.
	// These values are the minimum and maximum possible sizes of a room (not the coordinates.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumWidth;

	// These Boundary variables are generated by the level generator functions
	// and shouldn't be assigned in any JSON files.
	// Except for the bottom left Boundary, which will always be 1,1.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomLeftBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomRightBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopLeftBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopRightBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActorGridTile*> GridTilesInRoom;

	FRoomDataAsStruct()
	{
		MinimumLength = 3;
		MinimumWidth = 3;
		MaximumLength = 4;
		MaximumWidth = 4;
		BottomLeftBoundary = FIntVector2D(1, 1);
		BottomRightBoundary = FIntVector2D(1, 1);
		TopLeftBoundary = FIntVector2D(1, 1);
		TopRightBoundary = FIntVector2D(1, 1);
	}

	FORCEINLINE bool operator==(const FRoomDataAsStruct& OtherStruct) const
	{
		return this->MinimumLength == OtherStruct.MinimumLength &&
			this->MinimumWidth == OtherStruct.MinimumWidth &&
			this->MaximumLength == OtherStruct.MaximumLength &&
			this->MaximumWidth == OtherStruct.MaximumWidth &&
			this->BottomLeftBoundary == OtherStruct.BottomLeftBoundary &&
			this->BottomRightBoundary == OtherStruct.BottomRightBoundary &&
			this->TopLeftBoundary == OtherStruct.TopLeftBoundary &&
			this->TopRightBoundary == OtherStruct.TopRightBoundary &&
			this->GridTilesInRoom == OtherStruct.GridTilesInRoom;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FFloorDataAsStruct
{
	GENERATED_BODY()

	// The north-south dimension will be called 'Length' and 'X'.
	// This is the minimum size of the map in tiles.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumLength;

	// The east-west dimension will be called 'Width' and 'Y'.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinimumWidth;

	// This is the maximum size of the map in tiles.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaximumWidth;

	// These Boundary variables are generated by the level generator functions
	// and shouldn't be assigned in any JSON files.
	// Except for the bottom left Boundary, which will be the zero point of the level.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomLeftBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D BottomRightBoundary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopLeftBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntVector2D TopRightBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFloorLayouts Layout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomDataAsStruct> RoomDataAsStructsArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCorridorDataAsStruct> CorridorDataAsStructsArray;

	FFloorDataAsStruct()
	{
		MinimumLength = 18;
		MinimumWidth = 18;
		MaximumLength = 28;
		MaximumWidth = 28;
		BottomLeftBoundary = FIntVector2D(1, 1);
		BottomRightBoundary = FIntVector2D(1, 1);
		TopLeftBoundary = FIntVector2D(1, 1);
		TopRightBoundary = FIntVector2D(1, 1);
		Layout = EFloorLayouts::FourSquares;
		RoomDataAsStructsArray = { FRoomDataAsStruct(),
									FRoomDataAsStruct(),
									FRoomDataAsStruct(),
									FRoomDataAsStruct() };
		CorridorDataAsStructsArray = { FCorridorDataAsStruct(),
									FCorridorDataAsStruct(),
									FCorridorDataAsStruct(),
									FCorridorDataAsStruct(), };
	}

	FORCEINLINE bool operator==(const FFloorDataAsStruct& OtherStruct) const
	{
		return this->MinimumLength == OtherStruct.MinimumLength &&
			this->MinimumWidth == OtherStruct.MinimumWidth &&
			this->MaximumLength == OtherStruct.MaximumLength &&
			this->MaximumWidth == OtherStruct.MaximumWidth &&
			this->BottomLeftBoundary == OtherStruct.BottomLeftBoundary &&
			this->BottomRightBoundary == OtherStruct.BottomRightBoundary &&
			this->TopLeftBoundary == OtherStruct.TopLeftBoundary &&
			this->TopRightBoundary == OtherStruct.TopRightBoundary &&
			this->Layout == OtherStruct.Layout &&
			this->RoomDataAsStructsArray == OtherStruct.RoomDataAsStructsArray &&
			this->CorridorDataAsStructsArray == OtherStruct.CorridorDataAsStructsArray;
	}
};


USTRUCT(BlueprintType)
struct LOSTWORLD_API FLevelDataAsStruct
{
	GENERATED_BODY()

	// If true, the floor count will increment by +1 and
	// the stairs will appear to climb upward.
	// If false, then the opposite will be the case.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StairsGoUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEncounter> Encounters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFloorDataAsStruct FloorDataAsStruct;

	FLevelDataAsStruct()
	{
		StairsGoUp = true;
		Encounters.Add(FEncounter());
	}

	FORCEINLINE bool operator==(const FLevelDataAsStruct& OtherStruct) const
	{
		return this->StairsGoUp == OtherStruct.StairsGoUp &&
			this->FloorDataAsStruct == OtherStruct.FloorDataAsStruct &&
			this->Encounters == OtherStruct.Encounters;
	}
};


// -------------------------------- Boiler-plate code
class LOSTWORLD_API Variables
{
public:
	Variables();
	~Variables();

// ---------------------------------------- Constants ---------------------------------------- //
	// The size of a GridTile in Unreal Engine units.
	int GridTileWidth = 100;
	int GridTileLength = 100;
};
