#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LostWorld_422GameModeBase.h"
#include "BaseClass_GridTile.h"
#include "BaseComponent_Room_Tile.h"
#include "BaseComponent_Room_SpawnPoint.h"
#include "WidgetComponent_RoomEncounter.h"
#include "Lostworld_422GameInstanceBase.h"

#include "BaseClass_LevelRoom.generated.h"

// Forward Declarations
class ABaseClass_Level_SpawnHandler;



UCLASS()
class LOSTWORLD_422_API ABaseClass_LevelRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseClass_LevelRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Base Variables
// --------------------------------------------------

// ------------------------- Room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	F_Level_Room RoomData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<F_Level_Room> EncountersList;

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room Components")
	TArray<UBaseComponent_Room_Tile*> SceneCoordinateComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room Components")
	TArray<UBaseComponent_Room_SpawnPoint*> RoomSpawnSceneComponents;

// ------------------------- Constructor Classes (?)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	TSubclassOf<ABaseClass_EntityInBattle> EntityInBattle_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constructors")
	ABaseClass_EntityInBattle* EntityInBattle_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	TSubclassOf<UWidgetComponent_RoomEncounter> RoomEncounter_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constructors")
	UWidgetComponent_RoomEncounter* RoomEncounter_Widget;


// Functions
// --------------------------------------------------

// ------------------------- Setup
	UFUNCTION(BlueprintCallable)
	void SpawnAdjacentRoom();

	UFUNCTION()
	void SpawnEnemyFormation(F_LevelRoom_EnemyFormation EnemyFormation);

	UFUNCTION(BlueprintCallable)
	void PlayerEnterRoom();
};