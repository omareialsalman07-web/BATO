// Fill out your copyright notice in the Description page of Project Settings.


#include "BatoAnimInstance.h"
#include "BATO/Character/Bato_Character.h"
#include "BATO/Componets/CombatComponent.h"
#include "BATO/Weapons/Weapon.h"
#include "CoreGlobals.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"
#include "Math/Color.h"
#include "UObject/Linker.h"
#include "UObject/Object.h"


void UBatoAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    BatoCharacter = Cast<ABato_Character>(TryGetPawnOwner());
}

void UBatoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!IsValid(BatoCharacter)) 
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't get BatoCharacter from owning pawn"));
        return;
    }
    
    CombatCompenent = BatoCharacter->GetCombatComponent();
    if (!IsValid(CombatCompenent)) return;

    CurrentWeapon = CombatCompenent->GetCurrentWeapon();
    if (!IsValid(CurrentWeapon)) return;
    
    CurrentWeaponType = CurrentWeapon->GetWeaponType();
    bAim = CombatCompenent->GetIsAim();
}
