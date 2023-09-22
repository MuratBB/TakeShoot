// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../CMainCharacterBase.h"
#include "CMainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TAKESHOOT_API UCMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	bool IsMoving;
	
	UPROPERTY()
	ACMainCharacterBase* CharacterRef;

	UPROPERTY(BlueprintReadOnly)
	CurrentWeapon MyCurrentWeapon;


public:
	APawn * OwningPawn;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
