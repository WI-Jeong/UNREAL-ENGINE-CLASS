// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Camera/CameraShakeBase.h"
#include "HitCameraShake.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API UHitCameraShake : public UCameraShakeBase
{
	GENERATED_BODY()

public:
	UHitCameraShake(const FObjectInitializer& ObjectInitializer);
	
};
