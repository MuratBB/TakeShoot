// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Animations/CWeaponStruct.h"
#include "Core/UMG/UMG_CharacterSelector.h"
#include "GameFramework/Character.h"
#include "CCharacterSelectorPawn.generated.h"

UCLASS()
class TAKESHOOT_API ACCharacterSelectorPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacterSelectorPawn();
	
	UPROPERTY()
	bool Team1SelectionHovvered;

	UPROPERTY()
	bool Team2SelectionHovvered;

	UPROPERTY()
	bool ReadyHovvered;
	
	UFUNCTION()
	void CallTeamSeleciton(CurrentTeam CurrentTeam);

	UFUNCTION()
	void LeaveTeamSelection(CurrentTeam CurrentTeam);

	UFUNCTION()
	void Ready(CurrentTeam CurrentTeam);
	
	UPROPERTY()
	bool DoOnce = false;

	UPROPERTY()
	bool DoOnceReady = false;
	
	UPROPERTY(BlueprintReadOnly)
	CurrentTeam PawnCurrentTeam = CurrentTeam::E_NoTeamSleceted;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(NetMulticast,Reliable)
	void TeamSelectionClient(CurrentTeam CurrentTeam);

	UFUNCTION(Server,Reliable)
	void TeamSelectionServer(CurrentTeam CurrentTeam);

	UFUNCTION(NetMulticast,Reliable)
	void LeaveTeamClient(CurrentTeam CurrentTeam);

	UFUNCTION(Server,Reliable)
	void LeaveTeamServer(CurrentTeam CurrentTeam);

	UFUNCTION(NetMulticast,Reliable)
	void ReadyClient(CurrentTeam CurrentTeam);

	UFUNCTION(Server,Reliable)
	void ReadyServer(CurrentTeam CurrentTeam);
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UUserWidget* BPCharacterSelectorWidget;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UUMG_CharacterSelector> WidgetClassRef;
	
	UPROPERTY()
	TArray<UUserWidget*> FoundedWidget;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
