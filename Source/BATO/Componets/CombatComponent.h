// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATO_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

protected:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	void Initial_Fire_Weapon_Pressed();
	void Initial_Fire_Weapon_Released();

	void Initial_Aim_Weapon_Pressed();
	void Initial_Aim_Weapon_Released();

	void Initial_Cycle_Weapon_Pressed();
	void Initial_Reload_Weapon_Pressed();
};
