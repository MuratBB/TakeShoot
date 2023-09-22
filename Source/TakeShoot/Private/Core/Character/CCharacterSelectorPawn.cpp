// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/CCharacterSelectorPawn.h"
#include "UnrealWidgetFwd.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACCharacterSelectorPawn::ACCharacterSelectorPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACCharacterSelectorPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACCharacterSelectorPawn::CallTeamSeleciton(CurrentTeam CurrentTeam)
{
	if (!DoOnce)
	{
		DoOnce = true;
		TeamSelectionServer(CurrentTeam);
	}
}

void ACCharacterSelectorPawn::LeaveTeamSelection(CurrentTeam CurrentTeam)
{
	LeaveTeamServer(CurrentTeam);
}

void ACCharacterSelectorPawn::Ready(CurrentTeam CurrentTeam)
{
	ReadyServer(CurrentTeam);
}

void ACCharacterSelectorPawn::ReadyClient_Implementation(CurrentTeam CurrentTeam)
{
	if (CurrentTeam != CurrentTeam::E_NoTeamSleceted)
	{
		if (!DoOnceReady)
		{
			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(),FoundedWidget,WidgetClassRef);
		
			for (UUserWidget* Widget : FoundedWidget)
			{
				UUMG_CharacterSelector* WidgetRef = Cast<UUMG_CharacterSelector>(Widget);
				WidgetRef->ReadyPlayer = WidgetRef->ReadyPlayer + 1;
				DoOnceReady = true;
			}
		}
	
	}
}

void ACCharacterSelectorPawn::ReadyServer_Implementation(CurrentTeam CurrentTeam)
{
	ReadyClient(CurrentTeam);
}

void ACCharacterSelectorPawn::LeaveTeamClient_Implementation(CurrentTeam CurrentTeam)
{
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(),FoundedWidget,WidgetClassRef);

	UE_LOG(LogTemp,Warning,TEXT("Index Founded : %d") , FoundedWidget.Num());

	//If Team 1 Selected
	if (CurrentTeam == CurrentTeam::E_Team1)
	{
		for (UUserWidget* Widget : FoundedWidget)
		{
			UUMG_CharacterSelector* WidgetRef = Cast<UUMG_CharacterSelector>(Widget);
			WidgetRef->player1selectedCount = WidgetRef->player1selectedCount - 1;
			PawnCurrentTeam = CurrentTeam::E_Team1;
		}
	}

	//If Team 2 Selected
	if (CurrentTeam == CurrentTeam::E_Team2)
	{
		for (UUserWidget* Widget : FoundedWidget)
		{
			UUMG_CharacterSelector* WidgetRef = Cast<UUMG_CharacterSelector>(Widget);
			WidgetRef->player2selectedCount = WidgetRef->player2selectedCount - 1;
			PawnCurrentTeam = CurrentTeam::E_Team2;
		}
	}
}

void ACCharacterSelectorPawn::LeaveTeamServer_Implementation(CurrentTeam CurrentTeam)
{
	LeaveTeamClient(CurrentTeam);
}

void ACCharacterSelectorPawn::TeamSelectionClient_Implementation(CurrentTeam CurrentTeam)
{
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(),FoundedWidget,WidgetClassRef);

	UE_LOG(LogTemp,Warning,TEXT("Index Founded : %d") , FoundedWidget.Num());

	//If Team 1 Selected
	if (CurrentTeam == CurrentTeam::E_Team1)
	{
		for (UUserWidget* Widget : FoundedWidget)
		{
			UUMG_CharacterSelector* WidgetRef = Cast<UUMG_CharacterSelector>(Widget);
			WidgetRef->player1selectedCount = WidgetRef->player1selectedCount + 1;
			PawnCurrentTeam = CurrentTeam::E_Team1;
		}
	}

	//If Team 2 Selected
	if (CurrentTeam == CurrentTeam::E_Team2)
	{
		for (UUserWidget* Widget : FoundedWidget)
		{
			UUMG_CharacterSelector* WidgetRef = Cast<UUMG_CharacterSelector>(Widget);
			WidgetRef->player2selectedCount = WidgetRef->player2selectedCount + 1;
			PawnCurrentTeam = CurrentTeam::E_Team2;
		}
	}
}

void ACCharacterSelectorPawn::TeamSelectionServer_Implementation(CurrentTeam CurrentTeam)
{
	TeamSelectionClient(CurrentTeam);
}

// Called every frame
void ACCharacterSelectorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACCharacterSelectorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

