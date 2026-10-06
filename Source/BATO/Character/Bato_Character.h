// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"
#include "Bato_Character.generated.h"

UCLASS()
class BATO_API ABato_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABato_Character();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)	
	TObjectPtr<class USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere)	
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)	
	TObjectPtr<class UCameraComponent> FirstPersonCamera;
};
