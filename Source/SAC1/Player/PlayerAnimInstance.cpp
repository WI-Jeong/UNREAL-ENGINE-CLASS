// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAnimType = EPlayerAnimType::Default;

	mOnGround = false;

	mFallRecoveryAdditive = 0.f; 

	mAttackEnable = true;

	mAttackIndex = 0;

	mFallLandPositon = 0.14f;

	mCanJump = true;

}
void UPlayerAnimInstance::AttackT()
{
	//공격 가능 상태가 true이고 현재 공격 몽타주가 재생가능해야한다.
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]))
		return;

	//공격불가능상태로 만들어준다.
	mAttackEnable = false;

	//공격모션을 처음부터 재생시킬 수 잇도록한다.
	Montage_SetPosition(mAttackMontage[mAttackIndex], 0.f);

	//몽타주를 재생시킨다.
	Montage_Play(mAttackMontage[mAttackIndex]);

	//배열.num() 배열의 수
	mAttackIndex = (mAttackIndex + 1) % mAttackMontage.Num();

	 
}

void UPlayerAnimInstance::Jump()
{
	if (Montage_IsPlaying(mFallRecovery))
	{
		mFallRecoveryAdditive = 0.f;
		Montage_Stop(0.1f, mFallRecovery);
	}

	mCanJump = false;

	/*if (mAnimType == EPlayerAnimType::Fall)
	{
	   mFallRecoveryAdditive = 0.f;

	   if (Montage_IsPlaying(mFallRecovery))
		  Montage_Stop(0.1f, mFallRecovery);
	}*/
	
	mAnimType = EPlayerAnimType::Jump;

}

bool UPlayerAnimInstance::CanJump()
{
	return mCanJump;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	//부모클래스의 NativeInitializeAnimation()함수를 먼저호출해준다.
	//Super: 부모클래스를 의미한다.

	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Cast: 언리얼에서 제공하는 안전한 형변환 함수이다.
	// 언리얼 클래스들은 반드시 cast 함수를 이용해서 형변환해야한다.
	APlayerCharacter*Player=Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 판단한다.
   // nullptr일 경우 유효한 객체가 아니다.
	if (IsValid(Player)) 
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement(); 

		if (IsValid(Movement)) 
		{
			mMoveSpeed = Movement->Velocity.Length(); 

			mOnGround = Movement->IsMovingOnGround();

			//mFallRecoveryAdditive = 0.f;

			/*
			* 1. 땅을 밟고 있는 상태가 아니다.
			* 2. 현재 동작하는 애니메이션이 점프가 아니다.
			* 3. 현재 동작하는 애니메이션이 Fall이 아니다.
			* 
			*/

			if (!mOnGround && mAnimType != EPlayerAnimType::Fall &&
				mAnimType != EPlayerAnimType::Jump)
			{
				mAnimType = EPlayerAnimType::Fall;
			}

			//Default 상태가 아닐 경우 공격 불가능 상태로 만들어준다.
			if (mAnimType != EPlayerAnimType::Default)
			{
				mAttackEnable = false;
			}

			//땅을 밝고 있는 상태이고 에니메이션이 fall일 경우 이제 막 땅을 밟게 되었다는 것이므로
			//공격을 활성화한다.
			if (mOnGround && mAnimType == EPlayerAnimType::Fall)
			{
				mAttackEnable = true;
			}
		}
	}

	//check는 C++의 assert기능이다.
	//check괄호 안의 내용이 false일 경우 에러를 발생시킨다.
	//check(Player != nullptr); 

	//checkf는 에러 발생시 메세지를 만들어 줄 수 있다.
	//checkf(Player != nullptr, TEXT("Player Cast Failed"));

}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::AnimNotify_TransitionFall()
{
	mAnimType = EPlayerAnimType::Fall;
}

void UPlayerAnimInstance::AnimNotify_FallLandEnd()
{
	
	mAnimType = EPlayerAnimType::Default;

	mFallRecoveryAdditive = 1.f;

	//현재 몽타주가 재생되고 있는지 판단한다.
	if (!Montage_IsPlaying(mFallRecovery))
	{
		//리커버리 모션을 처음부터 재생시킬 수 있도록 한다.
		Montage_SetPosition(mFallRecovery, 0.f);

		//몽타주를 재생시킨다.
		Montage_Play(mFallRecovery);

	}

	mCanJump = true;

	LOG(TEXT("FALL LAND"));

}

void UPlayerAnimInstance::AnimNotify_JumpRecoveryEnd()
{
	mFallRecoveryAdditive = 0.f;
}


void UPlayerAnimInstance::AnimNotify_Attack() 
{
	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 판단한다.
   // nullptr일 경우 유효한 객체가 아니다.
	if (IsValid(Player))
	{
		Player->Attack1();
	}
}


void UPlayerAnimInstance::AnimNotify_Attack2()
{
	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 판단한다.
   // nullptr일 경우 유효한 객체가 아니다.
	if (IsValid(Player))
	{
		Player->Attack2();
	}
}

//
void UPlayerAnimInstance::AnimNotify_Attack3()
{
	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 판단한다.
   // nullptr일 경우 유효한 객체가 아니다.
	if (IsValid(Player))
	{
		Player->Attack3();
	}
}
//
void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackIndex = 0;
}

void UPlayerAnimInstance::AnimNotify_TeleportEnd()
{
	mAttackEnable = true;
	mAnimType = EPlayerAnimType::Default;

	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 판단한다.
   // nullptr일 경우 유효한 객체가 아니다.
	if (IsValid(Player))
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (IsValid(Movement))
		{
			Movement->MaxWalkSpeed = 600.f;
		}

	}
}
