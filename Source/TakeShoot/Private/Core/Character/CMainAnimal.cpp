// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/CMainAnimal.h"


// Sets default values
ACMainAnimal::ACMainAnimal()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACMainAnimal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACMainAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACMainAnimal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

