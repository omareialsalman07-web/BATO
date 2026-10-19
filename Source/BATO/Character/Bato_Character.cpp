// Fill out your copyright notice in the Description page of Project Settings.


#include "Bato_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BATO/Componets/CombatComponent.h"
#include "BATO/Data/WeaponData.h"


ABato_Character::ABato_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MovementState.bCanCrouch = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(SpringArm);
	FirstPersonCamera->bUsePawnControlRotation = false;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh1P");
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	CombatComponent->SetIsReplicated(true);
}

void ABato_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABato_Character::PossessedBy(AController *NewController)
{
	Super::PossessedBy(NewController);

	if(IsValid(CombatComponent)) {
		CombatComponent->SpawnInventory();
	}
}


void ABato_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABato_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
	
void ABato_Character::Input_Fire_Weapon_Pressed()
{
	CombatComponent->Initial_Fire_Weapon_Pressed();
}

void ABato_Character::Input_Fire_Weapon_Released()
{
	CombatComponent->Initial_Fire_Weapon_Released();
}

void ABato_Character::Input_Aim_Weapon_Pressed()
{
	CombatComponent->Initial_Aim_Weapon_Pressed();
}

void ABato_Character::Input_Aim_Weapon_Released()
{
	CombatComponent->Initial_Aim_Weapon_Released();
}

void ABato_Character::Input_Cycle_Weapon_Pressed()
{
	CombatComponent->Initial_Cycle_Weapon_Pressed();
}

void ABato_Character::Input_Reload_Weapon_Pressed()
{
	CombatComponent->Initial_Reload_Weapon_Pressed();
}

FName ABato_Character::GetWeaponAttachedPoint(const EWeaponType &WeaponType)
{
	checkf(CombatComponent->WeaponData, TEXT("Please fill out weapon data"));
	return *CombatComponent->WeaponData->GripPoints.Find(WeaponType);
}