// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UMG/UMG_CharacterSelector.h"

#include "Core/Character/CCharacterSelectorPawn.h"
#include "Net/UnrealNetwork.h"


void UUMG_CharacterSelector::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (CharacterSelectorPawnRef != nullptr)
	{
		if (FakeButton_Team1 != nullptr)
		{
			if (FakeButton_Team1->IsHovered())
			{
				CharacterSelectorPawnRef->Team1SelectionHovvered = true;
				CharacterSelectorPawnRef->Team2SelectionHovvered = false;
				CharacterSelectorPawnRef->ReadyHovvered = false;
			}
			else
			{
				CharacterSelectorPawnRef->Team1SelectionHovvered = false;
			}

		}

		if (FakeButton_Team2 != nullptr)
		{
			if (FakeButton_Team2->IsHovered())
			{
				CharacterSelectorPawnRef->Team2SelectionHovvered = true;
				CharacterSelectorPawnRef->Team1SelectionHovvered = false;
				CharacterSelectorPawnRef->ReadyHovvered = false;
			}
			else
			{
				CharacterSelectorPawnRef->Team2SelectionHovvered = false;
			}
		}

		if (FakeButton_Ready != nullptr)
		{
			if (FakeButton_Ready->IsHovered())
			{
				CharacterSelectorPawnRef->ReadyHovvered = true;
			}else
			{
				CharacterSelectorPawnRef->ReadyHovvered = false;
			}
		}
		
	}

	if (!CharacterSelectorPawnRef)
	{
		UE_LOG(LogTemp,Warning,TEXT("CHARACTER YOK"));
		CharacterSelectorPawnRef = Cast<ACCharacterSelectorPawn>(GetOwningPlayer()->GetPawn());
	}
	
}

void UUMG_CharacterSelector::NativeConstruct()
{
	Super::NativeConstruct();
	CharacterSelectorPawnRef = Cast<ACCharacterSelectorPawn>(GetOwningPlayer()->GetPawn());
	GetOwningPlayer()->SetShowMouseCursor(true);

	TXT_MaxPlayerReachedTeam1->SetVisibility(ESlateVisibility::Hidden);
	TXT_JoinedTeam1->SetVisibility(ESlateVisibility::Hidden);

	TXT_MaxPlayerReachedTeam2->SetVisibility(ESlateVisibility::Hidden);
	TXT_JoinedTeam2->SetVisibility(ESlateVisibility::Hidden);

	FakeButton_Ready->SetVisibility(ESlateVisibility::Hidden);
	TXT_Ready->SetVisibility(ESlateVisibility::Hidden);
}

void UUMG_CharacterSelector::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUMG_CharacterSelector,player1selectedCount);
	DOREPLIFETIME(UUMG_CharacterSelector,player2selectedCount);
	DOREPLIFETIME(UUMG_CharacterSelector,ReadyPlayer);
}

FReply UUMG_CharacterSelector::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	//Join Team
	if (CharacterSelectorPawnRef != nullptr)
	{
		if (CharacterSelectorPawnRef->PawnCurrentTeam == CurrentTeam::E_NoTeamSleceted)
		{
			if (CharacterSelectorPawnRef->Team1SelectionHovvered)
			{
				if (player1selectedCount < MaxPlayer)
				{
					CharacterSelectorPawnRef->CallTeamSeleciton(CurrentTeam::E_Team1);
					TXT_JoinedTeam1->SetVisibility(ESlateVisibility::Visible);
					TXT_MaxPlayerReachedTeam1->SetVisibility(ESlateVisibility::Hidden);
					TXT_MaxPlayerReachedTeam2->SetVisibility(ESlateVisibility::Hidden);
					FakeButton_Ready->SetVisibility(ESlateVisibility::Visible);
				}else
				{
					UE_LOG(LogTemp,Warning,TEXT("Max Player Reached For Team 1"));
					TXT_MaxPlayerReachedTeam1->SetVisibility(ESlateVisibility::Visible);
				}
			}
			if (CharacterSelectorPawnRef->Team2SelectionHovvered)
			{
				if (player2selectedCount < MaxPlayer)
				{
					CharacterSelectorPawnRef->CallTeamSeleciton(CurrentTeam::E_Team2);
					TXT_JoinedTeam2->SetVisibility(ESlateVisibility::Visible);
					TXT_MaxPlayerReachedTeam1->SetVisibility(ESlateVisibility::Hidden);
					TXT_MaxPlayerReachedTeam2->SetVisibility(ESlateVisibility::Hidden);
					FakeButton_Ready->SetVisibility(ESlateVisibility::Visible);
				}else
				{
					UE_LOG(LogTemp,Warning,TEXT("Max Player Reached For Team 2"));
					TXT_MaxPlayerReachedTeam2->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}

	//Change Current Team
	if (CharacterSelectorPawnRef != nullptr)
	{
		if (CharacterSelectorPawnRef->PawnCurrentTeam == CurrentTeam::E_Team1)
		{
			if (CharacterSelectorPawnRef->Team2SelectionHovvered)
			{
				if (player2selectedCount < MaxPlayer)
				{
					CharacterSelectorPawnRef->LeaveTeamSelection(CurrentTeam::E_Team1);
					CharacterSelectorPawnRef->DoOnce = false;
					CharacterSelectorPawnRef->CallTeamSeleciton(CurrentTeam::E_Team2);
					TXT_JoinedTeam2->SetVisibility(ESlateVisibility::Visible);
					TXT_JoinedTeam1->SetVisibility(ESlateVisibility::Hidden);
					TXT_MaxPlayerReachedTeam1->SetVisibility(ESlateVisibility::Hidden);
					TXT_MaxPlayerReachedTeam2->SetVisibility(ESlateVisibility::Hidden);
					FakeButton_Ready->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					TXT_MaxPlayerReachedTeam2->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
		if (CharacterSelectorPawnRef->PawnCurrentTeam == CurrentTeam::E_Team2)
		{
			if (CharacterSelectorPawnRef->Team1SelectionHovvered)
			{
				if (player1selectedCount < MaxPlayer)
				{
					CharacterSelectorPawnRef->LeaveTeamSelection(CurrentTeam::E_Team2);
					CharacterSelectorPawnRef->DoOnce = false;
					CharacterSelectorPawnRef->CallTeamSeleciton(CurrentTeam::E_Team1);
					TXT_JoinedTeam1->SetVisibility(ESlateVisibility::Visible);
					TXT_JoinedTeam2->SetVisibility(ESlateVisibility::Hidden);
					TXT_MaxPlayerReachedTeam1->SetVisibility(ESlateVisibility::Hidden);
					TXT_MaxPlayerReachedTeam2->SetVisibility(ESlateVisibility::Hidden);
					FakeButton_Ready->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					TXT_MaxPlayerReachedTeam1->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}


	if (CharacterSelectorPawnRef != nullptr)
	{
		if (CharacterSelectorPawnRef->ReadyHovvered)
		{
			if (CharacterSelectorPawnRef->PawnCurrentTeam!=CurrentTeam::E_NoTeamSleceted)
			{
				UE_LOG(LogTemp,Warning,TEXT("Ready Selected Call Event"));
				CharacterSelectorPawnRef->Ready(CharacterSelectorPawnRef->PawnCurrentTeam);
				TXT_Ready->SetVisibility(ESlateVisibility::Visible);
			
			}
		}
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}






