// Fill out your copyright notice in the Description page of Project Settings.


#include "SAC1GameInstance.h"

USAC1GameInstance::USAC1GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerTable(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'"));

	if (PlayerTable.Succeeded())
		mPlayerDataTable = PlayerTable.Object;



	static ConstructorHelpers::FObjectFinder<UDataTable>	ItemTable(TEXT("/Script/Engine.DataTable'/Game/Data/DT_Item.DT_Item'"));

	if (ItemTable.Succeeded())
		mItemDataTable = ItemTable.Object;


}

void USAC1GameInstance::Init()
{
	Super::Init();
}

const FPlayerDataTable* USAC1GameInstance::FindPlayerData(const FName& Name)
{
	return mPlayerDataTable->FindRow<FPlayerDataTable>(Name, TEXT(""));
}

const FItemTable* USAC1GameInstance::FindItemData(const FName& Name)
{
	return mItemDataTable->FindRow<FItemTable>(Name, TEXT(""));
}
