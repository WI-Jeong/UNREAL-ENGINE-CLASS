// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpenTrigger.h"

ADoorOpenTrigger::ADoorOpenTrigger()
{

	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<ULevelSequence> LS(TEXT("/Script/LevelSequence.LevelSequence'/Game/LevelSequence/LS_Door.LS_Door'"));
	if (LS.Succeeded())
	{
		LevelSequence = LS.Object;
	}

}

void ADoorOpenTrigger::BeginPlay()
{
	Super::BeginPlay();

	FMovieSceneSequencePlaybackSettings Settings;
	Settings.bAutoPlay = false;
	Settings.bPauseAtEnd = true;
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, Settings, LevelSequenceActor);
}

void ADoorOpenTrigger::Tick(float DeltaTime)
{
}

void ADoorOpenTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->Play();
	}
}

void ADoorOpenTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->PlayReverse();
	}
}
