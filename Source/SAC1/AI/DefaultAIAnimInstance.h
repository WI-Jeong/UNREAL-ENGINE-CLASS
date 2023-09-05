// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "DefaultAIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API UDefaultAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDefaultAIAnimInstance();

public:

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

	virtual void NativePostEvaluateAnimation();

	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();

	
};
