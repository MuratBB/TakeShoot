 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/CWeaponStruct.h"
#include "GameFramework/Character.h"
#include "Camera/CameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/CSword.h"
#include "CMainCharacterBase.generated.h"

 UCLASS()
class TAKESHOOT_API ACMainCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponenet;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* FPSSpringArmComponenet;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class ACWeaponBase> WeaponRef;

	UPROPERTY(EditAnywhere)
	ACSword* SwordRef;
	
public:
	// Sets default values for this character's properties
	ACMainCharacterBase();

	UPROPERTY()
	float RunSpeed;
	float WalkSpeed;
	float WeaponWalkSpeed;
	
	
	UPROPERTY()
	CurrentWeapon CurrentWeapon;

	UPROPERTY(BlueprintReadWrite , VisibleAnywhere)
	UChildActorComponent* Weapon;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartJump();
	void StopJump();
	void StartCrouch();
	void StopCrouch();
	void StartRun();
	void StopRun();


	//Weapon
	UFUNCTION()
	void TakeFreehand();

	UFUNCTION()
	void TakeSword();
};
