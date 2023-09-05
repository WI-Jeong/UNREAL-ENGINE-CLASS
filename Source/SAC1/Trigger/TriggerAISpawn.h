// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trigger.h"
#include "TriggerAISpawn.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ATriggerAISpawn : public ATrigger
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr< USpringArmComponent> mSpringArm;

protected:
	virtual void TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
};
