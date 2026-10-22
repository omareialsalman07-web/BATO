// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/NameTypes.h"
#include "BATO/Weapons/WeaponType.h"
#include "UObject/ObjectMacros.h"

#include "WeaponData.generated.h"

class UBlendSpace;
class UAnimSequence;

USTRUCT(BlueprintType)
struct FPlayerAnims
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> IdleAnim = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> AimIdleAnim = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> CrouchIdleAnim = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UAnimSequence> WalkAnim = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UAnimSequence> SprintAnim = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset_Hip;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset_Aim;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> Strafe_Standing;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> Strafe_Crouching;
};

UCLASS()
class BATO_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Weapons")
	TMap<EWeaponType, FName> GripPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TMap<EWeaponType, FPlayerAnims> FPS_Anims;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	TMap<EWeaponType, FPlayerAnims> TPS_Anims;
};
