#include "BattleHistory_Base.h"


// Sets default values
ABattleHistory_Base::ABattleHistory_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABattleHistory_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleHistory_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

