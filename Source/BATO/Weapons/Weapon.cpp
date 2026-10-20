
#include "Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "BATO/Interfaces/PlayerInterface.h"
#include "GameFramework/Pawn.h"
#include "Templates/Casts.h"
#include "UObject/Linker.h"

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
	AttachToOwner();
}

void AWeapon::SetMeshVisisbilty() const
{
	if(GetInstigator()->IsLocallyControlled())
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

void AWeapon::AttachToOwner() const
{
	APawn* OwningPawn = GetInstigator();
	if(!IsValid(OwningPawn) || !OwningPawn->Implements<UPlayerInterface>()) return;

	SetMeshVisisbilty();
	IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(OwningPawn);

	FName GripPoint = PlayerInterface->GetWeaponAttachedPoint(WeaponType);
	Mesh1P->AttachToComponent(PlayerInterface->GetMesh1P(),  FAttachmentTransformRules::KeepRelativeTransform, GripPoint);
	Mesh3P->AttachToComponent(PlayerInterface->GetMesh3P(),  FAttachmentTransformRules::KeepRelativeTransform, GripPoint);

}
