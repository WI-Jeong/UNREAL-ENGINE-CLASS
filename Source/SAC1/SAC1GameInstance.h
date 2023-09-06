// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "SAC1GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API USAC1GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USAC1GameInstance();

private:
	//UDataTable*
	TObjectPtr<UDataTable> mPlayerDataTable;

public:
	virtual void Init();

public:
	const FPlayerDataTable* FindPlayerData(const FName& Name);
	
};
