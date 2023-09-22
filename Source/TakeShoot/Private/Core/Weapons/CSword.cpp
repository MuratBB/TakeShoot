// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Weapons/CSword.h"

// Sets default values
ACSword::ACSword()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACSword::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

