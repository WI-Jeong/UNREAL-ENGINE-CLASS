// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SACPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ASACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASACPlayerController();

protected:
	TObjectPtr<AActor> mCursorPickActor;
	//TSubclassOf¿¡¼­ TObjectPtr·Î ¹Ù²Þ

protected:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ChangePickOutLine(int32 StencilValue);
	
};
