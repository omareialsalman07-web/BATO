// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/NameTypes.h"
#include "BATO/Weapons/WeaponType.h"

#include "UObject/ObjectMacros.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class BATO_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Weapons")
	TMap<EWeaponType, FName> GripPoints;
};
