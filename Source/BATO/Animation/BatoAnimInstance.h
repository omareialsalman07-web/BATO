// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BATO/Weapons/WeaponType.h"
#include "UObject/ObjectMacros.h"

#include "BatoAnimInstance.generated.h"

class ABato_Character;

UCLASS()
class BATO_API UBatoAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	ABato_Character* BatoCharacter;

	UPROPERTY(BlueprintReadOnly)
	EWeaponType CurrentWeaponType;

	UPROPERTY(BlueprintReadOnly)
	bool bAim;

	class UCombatComponent* CombatCompenent;
	const class AWeapon* CurrentWeapon;
};