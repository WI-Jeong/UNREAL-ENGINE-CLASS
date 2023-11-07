// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Trigger.h"
#include "TriggerCameraTransition.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ATriggerCameraTransition : public ATrigger
{
	GENERATED_BODY()

public:
	ATriggerCameraTransition();

protected:
	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class ACameraTransitionPoint*>	mTransitionPointArray;

	int32		mTransitionIndex;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		mTransitionTime;

	float		mTransitionTimeAdd;

	class APlayerController* mPlayerController;


	AActor* mOriginTarget;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	virtual void TriggerOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	
};
