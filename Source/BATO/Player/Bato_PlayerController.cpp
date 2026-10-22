// Fill out your copyright notice in the Description page of Project Settings.


#include "Bato_PlayerController.h"

#include "Engine/Engine.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputTriggers.h"
#include "Math/Color.h"
#include "Math/MathFwd.h"
#include "UObject/CoreNetTypes.h"
#include "UObject/ObjectPtr.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BATO/Character/Bato_Character.h"
#include "Net/UnrealNetwork.h"

void ABato_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(!IsValid(GetLocalPlayer())) return;

    UEnhancedInputLocalPlayerSubsystem* Subsystem  = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

    if(IsValid(Subsystem))
    {
        Subsystem->AddMappingContext(BatoIMC, 0);
    }
}

void ABato_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    UEnhancedInputComponent* BatoInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    BatoInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
    BatoInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
    BatoInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,&ThisClass::Input_Jump);
    BatoInputComponent->BindAction(CroutchAction, ETriggerEvent::Started, this,&ThisClass::Input_Crouch);
    BatoInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this,&ThisClass::Input_SprintStart);
     BatoInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this,&ThisClass::Input_SprintEnd);

      BatoInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Started, this,&ThisClass::Input_Fire_Weapon_Pressed);
      BatoInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Completed, this,&ThisClass::Input_Fire_Weapon_Released);

      BatoInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Started, this,&ThisClass::Input_Aim_Weapon_Pressed);
      BatoInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Completed, this,&ThisClass::Input_Aim_Weapon_Released);

      BatoInputComponent->BindAction(CycleAction, ETriggerEvent::Started, this,&ThisClass::Input_Cycle_Weapon_Pressed);
      BatoInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this,&ThisClass::Input_Reload_Weapon_Pressed);
}

void ABato_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(ABato_PlayerController, bSprint, COND_SkipOwner);
}

void ABato_PlayerController::Server_Sprint_Implementation(bool bPressed)
{
    bSprint = bPressed;
}

void ABato_PlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
    FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

    FRotator YawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

    FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    TObjectPtr<APawn> ControlledPawn = GetPawn();
    if(IsValid(ControlledPawn))
    {
        ControlledPawn->AddMovementInput(ForwardVector, InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightVector, InputAxisVector.X);
    }
}

void ABato_PlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
    FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    
    TObjectPtr<APawn> ControlledPawn = GetPawn();
    if(IsValid(ControlledPawn))
    {
        ControlledPawn->AddControllerPitchInput(InputAxisVector.Y);
        ControlledPawn->AddControllerYawInput(InputAxisVector.X);
    }
}

void ABato_PlayerController::Input_Jump()
{
    ACharacter* ControlledCharacter = GetCharacter();
    if(!ControlledCharacter) return;

    if(ControlledCharacter->IsCrouched())
    {
        ControlledCharacter->UnCrouch();
    }
    else
    {
        ControlledCharacter->Jump();
    }
}

void ABato_PlayerController::Input_Crouch()
{
    ACharacter* ControlledCharacter = GetCharacter();
    if(!ControlledCharacter) return;

    if(ControlledCharacter->IsCrouched())
    {
        ControlledCharacter->UnCrouch();
    }
    else
    {
        ControlledCharacter->Crouch();

        ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; // To avoid sprinting on uncrouting (in case we crouch from sprint and we are not holding sprint key)
    }
}

void ABato_PlayerController::Input_SprintStart()
{
    Sprint(true);
    Server_Sprint(true);
}

void ABato_PlayerController::Input_SprintEnd()
{
    Sprint(false);
    Server_Sprint(false);
}

void ABato_PlayerController::Sprint(bool bPressed)
{
    bSprint = bPressed;

    if(bSprint)
    {
        ACharacter* ControlledCharacter = GetCharacter();
        if(!ControlledCharacter) return;
        
        if(ControlledCharacter->IsCrouched())
        {
            ControlledCharacter->UnCrouch();
        }
    
        ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
    else 
    {
        ACharacter* ControlledCharacter = GetCharacter();
        if(!ControlledCharacter) return;

        if(!ControlledCharacter->IsCrouched())
        {
            ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
        }
    }
}

void ABato_PlayerController::Input_Fire_Weapon_Pressed()
{
    ABato_Character* ControlledBatoCharacter = Cast<ABato_Character>(GetCharacter());
    if(ControlledBatoCharacter) 
    {
        ControlledBatoCharacter->Input_Fire_Weapon_Pressed();
    }
}

void ABato_PlayerController::Input_Fire_Weapon_Released()
{
    ABato_Character* ControlledBatoCharacter = Cast<ABato_Character>(GetCharacter());
    if(ControlledBatoCharacter) 
    {
        ControlledBatoCharacter->Input_Fire_Weapon_Released();
    }
}

void ABato_PlayerController::Input_Aim_Weapon_Pressed()
{
    ABato_Character* ControlledBatoCharacter = Cast<ABato_Character>(GetCharacter());
    if(ControlledBatoCharacter) 
    {
        ControlledBatoCharacter->Input_Aim_Weapon_Pressed();
    }
}

void ABato_PlayerController::Input_Aim_Weapon_Released()
{
    ABato_Character* ControlledBatoCharacter = Cast<ABato_Character>(GetCharacter());
    if(ControlledBatoCharacter) 
    {
        ControlledBatoCharacter->Input_Aim_Weapon_Released();
    }
}

void ABato_PlayerController::Input_Cycle_Weapon_Pressed()
{
    ABato_Character* ControlledBatoCharacter = Cast<ABato_Character>(GetCharacter());
    if(ControlledBatoCharacter) 
    {
        ControlledBatoCharacter->Input_Cycle_Weapon_Pressed();
    }
}

void ABato_PlayerController::Input_Reload_Weapon_Pressed()
{
    ABato_Character* ControlledBatoCharacter = Cast<ABato_Character>(GetCharacter());
    if(ControlledBatoCharacter) 
    {
        ControlledBatoCharacter->Input_Reload_Weapon_Pressed();
    }
}
