
#include "CombatComponent.h"
#include "BATO/Weapons/Weapon.h"
#include "Engine/Engine.h"
#include "BATO/Data/WeaponData.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Templates/Casts.h"
#include "UObject/Object.h"

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

AWeapon* UCombatComponent::SpawnWeapon(TSubclassOf<AWeapon> weaponToSpawn) const
{
	if(!IsValid(weaponToSpawn)) return nullptr;

	APawn* Owner = Cast<APawn>(GetOwner());
	if(!IsValid(Owner)) return nullptr;
	if(Owner->GetLocalRole() < ROLE_Authority) return nullptr; // spawn only from the server

	UWorld* World = GetWorld();
	if(!World) return nullptr;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = Owner;
	SpawnInfo.Owner = Owner;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return World->SpawnActor<AWeapon>(weaponToSpawn, SpawnInfo);
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

void UCombatComponent::SpawnInventory()
{
	AWeapon* newWeapon = SpawnWeapon(DefaultWeapon);
}

void UCombatComponent::DestroyInventory()
{
	// TODO: Destroy the inventory once we have one.
}

