// Fill out your copyright notice in the Description page of Project Settings.


#include "Bato_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputTriggers.h"
#include "Math/Color.h"
#include "Math/MathFwd.h"
#include "UObject/ObjectPtr.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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
    ACharacter* ControlledCharacter = GetCharacter();
    if(!ControlledCharacter) return;

    if(ControlledCharacter->IsCrouched())
    {
        ControlledCharacter->UnCrouch();
    }

    ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ABato_PlayerController::Input_SprintEnd()
{
    ACharacter* ControlledCharacter = GetCharacter();
    if(!ControlledCharacter) return;

    if(!ControlledCharacter->IsCrouched())
    {
        ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}
