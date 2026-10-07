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
private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;

public:
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }

};
