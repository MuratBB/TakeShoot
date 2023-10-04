// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/CCharacterSelectorPawn.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
ACCharacterSelectorPawn::ACCharacterSelectorPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACCharacterSelectorPawn::removeTeamWidget()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	UE_LOG(LogTemp,Warning,TEXT("Remove All Widget %hhd ") , PawnCurrentTeam);
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

