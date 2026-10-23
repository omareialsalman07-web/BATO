
#include "Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "BATO/Interfaces/PlayerInterface.h"
#include "CoreGlobals.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"
#include "Templates/Casts.h"
#include "UObject/Linker.h"
#include "UObject/Object.h"
#include "UObject/UObjectBaseUtility.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bNetUseOwnerRelevancy = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh1P");
	RootComponent = Mesh1P;
	Mesh1P->CastShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh3P");
	Mesh3P->SetupAttachment(Mesh1P);
	Mesh3P->CastShadow = true;
	Mesh3P->bReceivesDecals = false;
	Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

	Mesh1P->SetHiddenInGame(true);
	Mesh3P->SetHiddenInGame(true);

	AimFieldOfView = 65.0f;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnRep_Owner()
{
	Super::OnRep_Owner();

	//AttachToOwner();
	/*UE_LOG(LogTemp, Warning, TEXT("Owner Rep | New Owner: %s"), *GetNameSafe(GetInstigator()));*/
}

void AWeapon::SetMeshVisibilities(APawn* OwningPawn) const
{
	if (OwningPawn->IsLocallyControlled())
	{
		Mesh1P->SetHiddenInGame(false);
		Mesh3P->SetHiddenInGame(true);
	}
	else
	{
		Mesh1P->SetHiddenInGame(true);
		Mesh3P->SetHiddenInGame(false);
	}
}

void AWeapon::AttachToCharacter(AActor* Character) const
{
	APawn* CharacterPawn = Cast<APawn>(Character);
	if (!IsValid(CharacterPawn) || !CharacterPawn->Implements<UPlayerInterface>()) return;
	
	SetMeshVisibilities(CharacterPawn);
	
	IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(CharacterPawn);
	if(!PlayerInterface) return;

	const FName AttachPoint = PlayerInterface->GetWeaponAttachedPoint(WeaponType);
	USkeletalMeshComponent* PawnMesh1P = PlayerInterface->GetMesh1P();
	USkeletalMeshComponent* PawnMesh3P = PlayerInterface->GetMesh3P();
	
	Mesh1P->AttachToComponent(PawnMesh1P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	Mesh3P->AttachToComponent(PawnMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);

}
