// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Weapons/CWeaponBase.h"

#include "..\..\..\Public\Core\CMainCharacterBase.h"

// Sets default values
ACWeaponBase::ACWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Weapon"));
	WeaponMesh->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void ACWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ACMainCharacterBase>(GetNetOwningPlayer());
	
}

// Called every frame
void ACWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

