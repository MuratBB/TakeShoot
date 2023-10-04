// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Core/CBaseGameState.h"
class ACCharacterSelectorPawn;
#include "UMG_CharacterSelector.generated.h"

/**
 * 
 */
UCLASS()
class TAKESHOOT_API UUMG_CharacterSelector : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
		
	UPROPERTY(BlueprintReadOnly,Replicated)
	int32 player1selectedCount = 0;

	UPROPERTY(BlueprintReadOnly,Replicated)
	int32 player2selectedCount = 0;

	UPROPERTY(BlueprintReadOnly,Replicated)
	int32 ReadyPlayer = 0;
	
	UPROPERTY(BlueprintReadOnly)
	int32 MaxPlayer = 2;
	
	UPROPERTY()
	ACCharacterSelectorPawn* CharacterSelectorPawnRef;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UBorder* FakeButton_Team1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UBorder* FakeButton_Team2;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* TXT_MaxPlayerReachedTeam1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* TXT_JoinedTeam1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* TXT_MaxPlayerReachedTeam2;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* TXT_JoinedTeam2;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UBorder* FakeButton_Ready;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* TXT_Ready;
};
