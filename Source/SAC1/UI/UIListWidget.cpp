// Fill out your copyright notice in the Description page of Project Settings.


#include "UIListWidget.h"
#include "../SAC1GameInstance.h"
//#include "ItemData.h"

void UUIListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mList = Cast<UListView>(GetWidgetFromName(TEXT("List")));

    USAC1GameInstance* GameInst = GetWorld()->GetGameInstance<USAC1GameInstance>();

    if (IsValid(GameInst))
    {
        TArray<FItemTable*> ItemArray;
        GameInst->GetAllItemData<FItemTable>(ItemArray);

        int32   Count = ItemArray.Num();

        for (int32 i = 0; i < Count * 10; ++i)
        {
           // UItemData* ItemData = NewObject<UItemData>();

            //ItemData->SetItemInfo(ItemArray[i % 3]);

           // mList->AddItem(ItemData);
        }
    }


    else
    {
        LOG(TEXT("GetGameInstance Failed"));
    }

    mList->OnItemClicked().AddUObject<UUIListWidget>(this, &UUIListWidget::ItemClick);
    //mList->OnItemDoubleClicked()
    mList->OnItemIsHoveredChanged().AddUObject<UUIListWidget>(this, &UUIListWidget::ItemHovered);

}

void UUIListWidget::ItemClick(UObject* Obj)
{
}

void UUIListWidget::ItemHovered(UObject* Obj, bool Hovered)
{
}
