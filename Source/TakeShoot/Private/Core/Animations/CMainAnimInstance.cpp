// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Core/Animations/CMainCharacterAnimInstance.h"

#include "../../../Public/Core/CMainCharacterBase.h"

void UCMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();

	CharacterRef = Cast<ACMainCharacterBase>(OwningPawn);
}

void UCMainCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningPawn)
	{
		return;
	}
	if (OwningPawn)
	{
		//Get Current Weapon
		//MyCurrentWeapon = CharacterRef->CurrentWeapon;
		
		//İsMoving
		IsMoving = (OwningPawn->GetVelocity().SizeSquared() > 3);
	}

	

}
