// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterSelectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ACharacterSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACharacterSelectGameMode();

private:
	TSubclassOf<UUserWidget>	mCharacterUIClass;
	TObjectPtr<class UCharacterSelectWidget>	mCharacterWidget;
	//class UCharacterSelectWidget 위젯먼저 만들고 그걸 부모로 이걸 만든건데
	//내 마음대로 class UCharacterWidget으로 만들면 어째..이거 이름도 잘 지켜줘야쥥


public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;

	
};
