#pragma once

#include "CoreMinimal.h"
#include "HAL/Platform.h"
#include "UObject/ObjectMacros.h"
#include "WeaponType.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    E_None UMETA(DisplayName = "None"),
    E_Rifle UMETA(DisplayName = "Rifle"),
    E_Pistol UMETA(DisplayName = "Pistol")
};