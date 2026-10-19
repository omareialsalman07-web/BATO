// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"

#include "CombatComponent.generated.h"


class UWeaponData;

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

private:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeapon> DefaultWeapon;
	AWeapon* SpawnWeapon(TSubclassOf<AWeapon> weaponToSpawn) const;

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
