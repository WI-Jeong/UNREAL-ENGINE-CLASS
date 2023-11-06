// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIAnimInstance.h"
#include "AIPawn.h"
#include "AIController.h"

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

	AAIController* Controller = Cast<AAIController>(TryGetPawnOwner()->GetController());

	if (IsValid(Controller))
	{
		AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (IsValid(Target))
		{
			FDamageEvent	DmgEvent;
			Target->TakeDamage(10.f, DmgEvent, Controller, TryGetPawnOwner());
		}
	}

}

void UDefaultAIAnimInstance::AnimNotify_AttackEnd()
{
	AAIPawn* AIPawn = Cast< AAIPawn>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 판단한다.
   // nullptr일 경우 유효한 객체가 아니다.
	if (IsValid(AIPawn))
	{
		AIPawn->SetAttackEnd(true);
	}
}

void UDefaultAIAnimInstance::AnimNotify_InteractionkEnd()
{
	AAIPawn* AIPawn = Cast< AAIPawn>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 판단한다.
   // nullptr일 경우 유효한 객체가 아니다.
	if (IsValid(AIPawn))
	{
		AIPawn->SetInteractionEnd(true);
	}
}
