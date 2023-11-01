// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "UIListWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API UUIListWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UListView* mList;

public:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void ItemClick(UObject* Obj);
	UFUNCTION()
	void ItemHovered(UObject* Obj, bool Hovered);
	
};
