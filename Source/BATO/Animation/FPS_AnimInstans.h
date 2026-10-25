// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BatoAnimInstance.h"
#include "BATO/Data/WeaponData.h"

#include "FPS_AnimInstans.generated.h"


UCLASS()
class BATO_API UFPS_AnimInstans : public UBatoAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:

	UPROPERTY(BlueprintReadOnly)
	FPlayerAnims CurrentAnims;
};
