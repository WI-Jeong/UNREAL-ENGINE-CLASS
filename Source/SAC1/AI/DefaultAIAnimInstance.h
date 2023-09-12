// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "DefaultAIAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EAIAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Skill1,
	Skill2,
	Skill3
};

/**
 * 
 */
UCLASS()
class SAC1_API UDefaultAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDefaultAIAnimInstance();

protected:
	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAIAnimType	mAnimType;

public:
	void ChangeAnim(EAIAnimType Type)
	{
		mAnimType = Type;
	}

public:

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

	virtual void NativePostEvaluateAnimation();

	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();


public:
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	
};
