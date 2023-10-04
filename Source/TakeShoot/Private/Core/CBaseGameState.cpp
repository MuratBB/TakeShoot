// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CBaseGameState.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Core/Character/CCharacterSelectorPawn.h"
#include "Kismet/GameplayStatics.h"

class UUMG_CharacterSelector;

void ACBaseGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	if (DoOnce)
	{
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(),FoundedWidget,WBPCharacterSelectorRef);
		for (UUserWidget* Widgets : FoundedWidget)
		{
			UUMG_CharacterSelector* CharacterSelector =  Cast<UUMG_CharacterSelector>(Widgets);
			if (CharacterSelector->ReadyPlayer >= 4)
			{
				StartGame();
				break;
			}
		}
	}
}

void ACBaseGameState::StartGame()
{
	UE_LOG(LogTemp,Warning,TEXT("GameStarted Workd"));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),CharacterSelectorPawnRef,FoundedActor);
	for (AActor* OutActor : FoundedActor)
	{
		ACCharacterSelectorPawn* X = Cast<ACCharacterSelectorPawn>(OutActor);
		X->BPCharacterSelectorWidget->RemoveFromParent();
	}
}
