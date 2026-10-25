// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BatoAnimInstance.h"
#include "BATO/Data/WeaponData.h"
#include "Math/MathFwd.h"
#include "UObject/ObjectMacros.h"

#include "TPS_AnimInstans.generated.h"


UCLASS()
class BATO_API UTPS_AnimInstans : public UBatoAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	FPlayerAnims CurrentAnims;

	UPROPERTY(BlueprintReadOnly)
	float AO_Pitch;

	UPROPERTY(BlueprintReadOnly)
	FTransform FABRIK_SocketTransform;

	UPROPERTY(BlueprintReadOnly)
	bool bHasCurrentWeapon;
};
