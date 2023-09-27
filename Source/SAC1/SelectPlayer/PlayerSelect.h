// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerSelect.generated.h"

UCLASS()
class SAC1_API APlayerSelect : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerSelect();

private:
	TObjectPtr<AActor>	mCursorPickActor;
	TObjectPtr<AActor>	mSelectActor;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACameraRig_Rail>	mCameraRigRail;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACameraActor>	mKnightCamera;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float		mCameraRigTime;

	float		mCameraRigAddTime;
	float		mCameraRigPlayDir; 

	bool		mCameraTransition;

	EPlayerJob	mSelectJob;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Pick();

};
