#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

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

	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;

	virtual void OnRep_Owner() override;
private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;

	void SetMeshVisibilities(APawn* OwningPawn) const;

public:
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }

	void AttachToOwner() const; // This should be called after setup the onwing
};
