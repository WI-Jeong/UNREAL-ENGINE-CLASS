// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "VideoPlayerBase.generated.h"

UCLASS()
class SAC1_API AVideoPlayerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVideoPlayerBase();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent>	mRoot;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMediaSoundComponent>	mMediaSound; 


	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMediaPlayer>	mMediaPlayer;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMediaSource>	mMediaSource;


	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool mAutoPlay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(Blueprintcallable)
	void PlayVideo();


};
