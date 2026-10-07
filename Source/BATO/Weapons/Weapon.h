#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UObject/ObjectMacros.h"
#include "UObject/ObjectPtr.h"
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

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;

};
