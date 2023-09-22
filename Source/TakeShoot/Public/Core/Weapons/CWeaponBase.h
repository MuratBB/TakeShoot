// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ACMainCharacterBase;

#include "Core/Animations/CWeaponStruct.h"
#include "GameFramework/Actor.h"
#include "CWeaponBase.generated.h"

UCLASS()
class TAKESHOOT_API ACWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WeaponMesh;
	
	
public:	
	// Sets default values for this actor's properties
	ACWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FWeaponDetails WeaponDetails;

	UPROPERTY(BlueprintReadOnly)
	ACMainCharacterBase* OwnerPlayer;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<UAnimMontage*> Attack_Shoot_Animations;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
