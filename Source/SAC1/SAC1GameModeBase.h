// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
//#include "DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "SAC1GameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SAC1_API ASAC1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASAC1GameModeBase();

private:
	TObjectPtr<UDataTable>	mAIDataTable;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;

public:
	const FAIDataTable* FindAIData(const FName& Name);
};
