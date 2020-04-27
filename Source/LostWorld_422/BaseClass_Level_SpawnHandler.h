#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseClass_LevelRoom.h"

#include "BaseClass_Level_SpawnHandler.generated.h"

UCLASS()
class LOSTWORLD_422_API ABaseClass_Level_SpawnHandler : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
// Initializer
// --------------------------------------------------
	// Sets default values for this actor's properties
	ABaseClass_Level_SpawnHandler();

// Base Variables
// --------------------------------------------------

// ------------------------- Constructors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Constructors")
	TSubclassOf<ABaseClass_LevelRoom> TestOne_Room_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Constructors")
	ABaseClass_LevelRoom* Room_Reference;

// ------------------------- Rooms

// Functions
// --------------------------------------------------
	UFUNCTION()
	ABaseClass_LevelRoom* SpawnNewRoom(TSubclassOf<ABaseClass_LevelRoom> RoomToSpawnClass, FVector WorldLocation, FRotator WorldRotation, ABaseClass_LevelRoom* PreviousRoomReference);

};