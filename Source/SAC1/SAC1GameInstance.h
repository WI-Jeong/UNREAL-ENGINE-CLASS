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
	//데이터 테이블의 에셋 타입은 UDataTable
	//UDataTable*
	TObjectPtr<UDataTable> mPlayerDataTable;
	TObjectPtr<UDataTable>	mItemDataTable;

public:
	virtual void Init();

public:
	const FPlayerDataTable* FindPlayerData(const FName& Name);
	const FItemTable* FindItemData(const FName& Name);

	template <typename T>
	void GetAllItemData(TArray<T*>& ItemArray)
	{
		mItemDataTable->GetAllRows<T>(TEXT(""), ItemArray);
	}
	
};
