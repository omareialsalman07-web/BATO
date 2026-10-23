#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/Pawn.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"
#include "WeaponType.h"

#include "Weapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class BATO_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType;

	virtual void OnRep_Owner() override;

	UPROPERTY(EditAnywhere, Category = "Weapon|Aim")
	float AimFieldOfView;
private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;

	void SetMeshVisibilities(APawn* OwningPawn) const;
public:
	const USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	const USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }

	void AttachToCharacter(AActor* Character) const;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetAimFOV() const { return AimFieldOfView; }
};
