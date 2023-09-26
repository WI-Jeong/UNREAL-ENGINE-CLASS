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
	//class UCharacterSelectWidget �������� ����� �װ� �θ�� �̰� ����ǵ�
	//�� ������� class UCharacterWidget���� ����� ��°..�̰� �̸��� �� ������ߢ�


public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void BeginPlay()	override;
	virtual void Tick(float DeltaTime)	override;

	
};
