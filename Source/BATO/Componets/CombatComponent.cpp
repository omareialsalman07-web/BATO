
#include "CombatComponent.h"
#include "Engine/Engine.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::Initial_Fire_Weapon_Pressed()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, "Fire Weapon Pressed", false);
	}
}

void UCombatComponent::Initial_Fire_Weapon_Released()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, "Fire Weapon Releaced", false);
	}
}

void UCombatComponent::Initial_Aim_Weapon_Pressed()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, "Aim Weapon Pressed", false);
	}
}

void UCombatComponent::Initial_Aim_Weapon_Released()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, "Aim Weapon Released", false);
	}
}

void UCombatComponent::Initial_Cycle_Weapon_Pressed()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, "Cycle Weapon Pressed", false);
	}
}

void UCombatComponent::Initial_Reload_Weapon_Pressed()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, "Reload Weapon Pressed", false);
	}
}

