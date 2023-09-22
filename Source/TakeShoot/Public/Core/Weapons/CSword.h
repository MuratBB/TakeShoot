// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CWeaponBase.h"
#include "CSword.generated.h"

UCLASS()
class TAKESHOOT_API ACSword : public ACWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACSword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
