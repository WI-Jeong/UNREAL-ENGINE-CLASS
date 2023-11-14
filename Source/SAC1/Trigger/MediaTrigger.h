// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Trigger.h"
#include "MediaTrigger.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API AMediaTrigger : public ATrigger
{
	GENERATED_BODY()

public:
	AMediaTrigger();

protected:
	virtual void TriggerOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);


	
};
