// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCinematic.h"

ATriggerCinematic::ATriggerCinematic()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void ATriggerCinematic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerCinematic::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATriggerCinematic::SequenceFinish()
{
}
