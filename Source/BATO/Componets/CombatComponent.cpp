
#include "CombatComponent.h"
#include "BATO/Weapons/Weapon.h"
#include "CoreGlobals.h"
#include "Engine/Engine.h"
#include "BATO/Data/WeaponData.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"
#include "Templates/Casts.h"
#include "Templates/SubclassOf.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"
#include "UObject/UObjectBaseUtility.h"

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

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, Inventory);
	DOREPLIFETIME(UCombatComponent, CurrentWeapon);
}

void UCombatComponent::OnRep_CurrentWeapon(AWeapon* lastWeapon)
{	
	if(!IsValid(CurrentWeapon)) return;
	CurrentWeapon->AttachToCharacter(GetOwner());
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
	if(GetOwner()->GetLocalRole() < ROLE_Authority) return;

	for(const TSubclassOf<AWeapon>& weaponClass : DefaultWeapons) 
	{
		AWeapon* WeaponToSpawn = SpawnWeapon(weaponClass);
		Inventory.AddUnique(WeaponToSpawn);
	}

	SelectItem(0);
}

void UCombatComponent::DestroyInventory()
{
	// TODO: Destroy the inventory once we have one.
}

AWeapon* UCombatComponent::SpawnWeapon(TSubclassOf<AWeapon> weaponToSpawn) const
{
	if(!IsValid(weaponToSpawn)) return nullptr;

	AActor* OwningActor = GetOwner();
	if (!IsValid(OwningActor)) return nullptr;
	if (OwningActor->GetLocalRole() < ROLE_Authority) return nullptr;
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = Cast<APawn>(OwningActor);
	SpawnInfo.Owner = OwningActor;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	return GetWorld()->SpawnActor<AWeapon>(weaponToSpawn, SpawnInfo);
}

void UCombatComponent::SelectItem(int inventoryItemIndex)
{
	inventoryItemIndex = inventoryItemIndex % 1; // to make from 0 to 1
	if(Inventory.Num() > inventoryItemIndex)
	{
		CurrentWeapon = Inventory[inventoryItemIndex];
		CurrentWeapon->AttachToCharacter(GetOwner());
	}
}

