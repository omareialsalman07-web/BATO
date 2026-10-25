// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_AnimInstans.h"
#include "BATO/Character/Bato_Character.h"
#include "BATO/Componets/CombatComponent.h"


void UFPS_AnimInstans::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void UFPS_AnimInstans::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if(!IsValid(BatoCharacter)) return;
    if (!IsValid(CombatCompenent) || !IsValid(CombatCompenent->WeaponData)) return;

    FPlayerAnims* fpsAnims = CombatCompenent->WeaponData->FPS_Anims.Find(CurrentWeaponType);
    if(fpsAnims)
        CurrentAnims = *fpsAnims;
}
