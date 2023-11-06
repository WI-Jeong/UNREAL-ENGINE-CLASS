// Fill out your copyright notice in the Description page of Project Settings.


#include "HitCameraShake.h"
#include "PerlinNoiseCameraShakePattern.h"

UHitCameraShake::UHitCameraShake(const FObjectInitializer& ObjectInitializer) :
	UCameraShakeBase(ObjectInitializer)
{
	bSingleInstance = false;

	UPerlinNoiseCameraShakePattern* Pattern = CreateDefaultSubobject<UPerlinNoiseCameraShakePattern>(TEXT("Shake"));

	SetRootShakePattern(Pattern);

	Pattern->LocationAmplitudeMultiplier = 10.f;
	Pattern->LocationFrequencyMultiplier = 10.f;

	Pattern->Y.Amplitude = 50.f;
	Pattern->Y.Frequency = 50.f;


}
