// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ObjectPtr.h"

#include "Bato_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class BATO_API ABato_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> BatoIMC;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CroutchAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump();
	void Input_Crouch();
	void Input_SprintStart();
	void Input_SprintEnd();

};
