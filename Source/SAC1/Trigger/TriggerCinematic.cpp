// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCinematic.h"

ATriggerCinematic::ATriggerCinematic()
{
	PrimaryActorTick.bCanEverTick = true;

	mSequenceActor = nullptr;

}

void ATriggerCinematic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerCinematic::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(mSequence))
	{
		if (!IsValid(mSequencePlayer))
		{
			mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mSequence, mSetting, mSequenceActor);

			mSequencePlayer->OnFinished.AddDynamic(this, &ATriggerCinematic::SequenceFinish);
		}
		// �����Ų��.
		if (!mSequencePlayer->IsPlaying())
			mSequencePlayer->Play();

	}
}

void ATriggerCinematic::SequenceFinish()
{
}
