// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"
#include "BATO/Interfaces/PlayerInterface.h"

#include "Bato_Character.generated.h"

class UCombatComponent;

UCLASS()
class BATO_API ABato_Character : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ABato_Character();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController *NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCombatComponent> CombatComponent;
	
private:
	UPROPERTY(VisibleAnywhere)	
	TObjectPtr<class USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere)	
	TObjectPtr<class USpringArmComponent> SpringArm;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)	
	TObjectPtr<class UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DefaultFieldOfView;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAim(bool bAim);
public:
	void Input_Fire_Weapon_Pressed();
	void Input_Fire_Weapon_Released();

	void Input_Aim_Weapon_Pressed();
	void Input_Aim_Weapon_Released();

	void Input_Cycle_Weapon_Pressed();
	void Input_Reload_Weapon_Pressed();

	virtual FName GetWeaponAttachedPoint(const EWeaponType &WeaponType) override;
	virtual USkeletalMeshComponent * GetMesh1P() const override;
	virtual USkeletalMeshComponent * GetMesh3P() const override;

	UFUNCTION(BlueprintCallable)
	float GetFixedAO_Pitch() const;
};
