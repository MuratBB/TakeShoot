// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CMainGameModeBase.h"
#include "..\..\Public\Core\CMainCharacterBase.h"




ACMainGameModeBase::ACMainGameModeBase()
{
	DefaultPawnClass = ACMainCharacterBase::StaticClass();
}

