// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Trigger.h"
#include "DoorOpenTrigger.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ADoorOpenTrigger : public ATrigger
{
	GENERATED_BODY()

public:
	ADoorOpenTrigger();


protected:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
	class ALevelSequenceActor* LevelSequenceActor;

	UPROPERTY(VisibleAnywhere)
	class ULevelSequence* LevelSequence;

	UPROPERTY(VisibleAnywhere)
	class ULevelSequencePlayer* LevelSequencePlayer;


protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;



};
