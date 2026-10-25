// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_AnimInstans.h"
#include "BATO/Character/Bato_Character.h"
#include "BATO/Componets/CombatComponent.h"
#include "UObject/Object.h"

void UTPS_AnimInstans::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void UTPS_AnimInstans::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if(!IsValid(BatoCharacter)) return;
    if (!IsValid(CombatCompenent) || !IsValid(CombatCompenent->WeaponData)) return;

    FPlayerAnims* tpsAnims = CombatCompenent->WeaponData->TPS_Anims.Find(CurrentWeaponType);
    if(tpsAnims)
        CurrentAnims = *tpsAnims;

    AO_Pitch = BatoCharacter->GetFixedAO_Pitch();
    FABRIK_SocketTransform = BatoCharacter->Get_FABRIK_SocketTransform();
    bHasCurrentWeapon = BatoCharacter->GetCombatComponent()->HasCurrentWeapon();
}

