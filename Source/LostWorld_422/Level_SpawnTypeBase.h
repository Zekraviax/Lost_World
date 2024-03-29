#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"

#include "Level_SpawnTypeBase.generated.h"


// Forward Declarations
class UWidgetComponent_MinimapRoom;
class UBaseClass_Widget_Minimap;
class ABaseClass_GridTile;
class ABaseClass_LevelRoom;
class ABaseClass_EntityInBattle;


UCLASS()
class LOSTWORLD_422_API ALevel_SpawnTypeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevel_SpawnTypeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_LevelRoom> LevelRoom_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetComponent_MinimapRoom> MinimapRoom_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent_MinimapRoom* MinimapRoom_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseClass_GridTile> GridTile_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABaseClass_GridTile* GridTile_Actor;

// ------------------------- Minimap
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseClass_Widget_Minimap* PlayerMinimapReference;

// ------------------------- References
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* EnemyFormationsTable;

// ------------------------- Map
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABaseClass_GridTile*> GridTilesArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UWidgetComponent_MinimapRoom*> FullMinimapRoomArray;

// ------------------------- Gameplay
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentFloor = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FloorsRequiredForBoss;

// Functions
// --------------------------------------------------

// ------------------------- Base Class Functions
	virtual void RunLevelGeneratorFunction();
};
