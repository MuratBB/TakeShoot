// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CBaseGameState.generated.h"


class UUMG_CharacterSelector;

UCLASS()
class TAKESHOOT_API ACBaseGameState : public AGameStateBase
{
	GENERATED_BODY()
public:

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	TArray<UUserWidget*> FoundedWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUMG_CharacterSelector> WBPCharacterSelectorRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> CharacterSelectorPawnRef;

	UPROPERTY()
	TArray<AActor*> FoundedActor;

protected:
	UFUNCTION()
	void StartGame();

	UPROPERTY()
	bool DoOnce = true;
};
