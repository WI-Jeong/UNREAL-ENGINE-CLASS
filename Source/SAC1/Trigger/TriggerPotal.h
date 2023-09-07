// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trigger.h"
#include "TriggerPotal.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ATriggerPotal : public ATrigger
{
	GENERATED_BODY()

public:
	ATriggerPotal();

protected:
	UPROPERTY(Category = Component,VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent>	mParticle;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName	mTransitionName;

protected:
	virtual void TriggerOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	
};
