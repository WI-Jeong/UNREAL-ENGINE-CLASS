// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoPlayerBase.h"

// Sets default values
AVideoPlayerBase::AVideoPlayerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mMediaSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSound"));

	SetRootComponent(mRoot);

	mMediaSound->SetupAttachment(mRoot); 

	mRoot->bVisualizeComponent = true;

	mAutoPlay = true;

}

// Called when the game starts or when spawned
void AVideoPlayerBase::BeginPlay()
{
	Super::BeginPlay();

	if (mAutoPlay)
	{
		mMediaPlayer->OpenSource(mMediaSource);
		mMediaPlayer->Play();
	}

	
}

// Called every frame
void AVideoPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVideoPlayerBase::PlayVideo()
{
}

