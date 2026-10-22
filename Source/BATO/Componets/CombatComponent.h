// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/Class.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"

#include "CombatComponent.generated.h"


class UWeaponData;
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATO_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWeaponData> WeaponData;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentWeapon(AWeapon* lastWeapon);
private:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<TSubclassOf<AWeapon>> DefaultWeapons;
	AWeapon* SpawnWeapon(TSubclassOf<AWeapon> weaponToSpawn) const;

	UPROPERTY(Replicated)
	TArray<AWeapon*> Inventory;
	UPROPERTY(ReplicatedUsing = OnRep_CurrentWeapon)
	AWeapon* CurrentWeapon;

	void SelectItem(int inventoryItemIndex);

public:	
	void Initial_Fire_Weapon_Pressed();
	void Initial_Fire_Weapon_Released();

	void Initial_Aim_Weapon_Pressed();
	void Initial_Aim_Weapon_Released();

	void Initial_Cycle_Weapon_Pressed();
	void Initial_Reload_Weapon_Pressed();

	void SpawnInventory();
	void DestroyInventory();
};
