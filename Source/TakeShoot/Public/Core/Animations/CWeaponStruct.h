// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CWeaponStruct.generated.h"

USTRUCT(BlueprintType)
struct TAKESHOOT_API FWeaponDetails
{
	GENERATED_USTRUCT_BODY()

public:	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float WeaponDurability;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int MagAmount;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int AmmoAmount; 
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool isDirty; 
	
	FWeaponDetails()
	{
		WeaponDurability = 100.0f;
		MagAmount = 0;
		AmmoAmount = 0;
		isDirty = false;
	}
};



UENUM(BlueprintType)
enum class CurrentWeapon : uint8
{
	E_FreeHand = 0 UMETA(DisplayName="FreeHand"),
	E_Sword    = 1 UMETA(DisplayName="Sword")
};

UENUM(BlueprintType)
enum class CurrentTeam : uint8
{
	E_NoTeamSleceted = 0 UMETA(DisplayName="NoTeamSelected"),
	E_Team1			 = 1 UMETA(DisplayName="Team1"),
	E_Team2			 = 2 UMETA(DisplayName="Team2")
};