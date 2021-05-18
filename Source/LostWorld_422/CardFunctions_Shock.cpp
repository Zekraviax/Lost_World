#include "CardFunctions_Shock.h"

#include "BaseClass_EntityInBattle.h"


void ACardFunctions_Shock::RunCardAbilityFunction(FStackEntry StackEntry)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Execute Card Function: Shock"));

	int32 DamageValue = StackEntry.Card.AbilitiesAndConditions[0].BaseDamage;
	//int32 OldHealthValue = StackEntry.Card.CurrentTargets[0]->EntityBaseData.HealthValues.X_Value;

	Cast<ABaseClass_EntityInBattle>(StackEntry.Card.CurrentTargets[0])->Event_DamageIncoming(DamageValue, StackEntry.Card.Elements[0], E_Card_DamageTypes::E_Magical);
}