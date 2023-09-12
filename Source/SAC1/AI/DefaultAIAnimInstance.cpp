// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIAnimInstance.h"
#include "AIPawn.h"

UDefaultAIAnimInstance::UDefaultAIAnimInstance()
{
	mAnimType = EAIAnimType::Idle;
}

void UDefaultAIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UDefaultAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UDefaultAIAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UDefaultAIAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UDefaultAIAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UDefaultAIAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UDefaultAIAnimInstance::AnimNotify_Attack()
{

}

void UDefaultAIAnimInstance::AnimNotify_AttackEnd()
{

}
