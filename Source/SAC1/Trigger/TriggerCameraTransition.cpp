// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCameraTransition.h"
#include "../Camera/CameraTransitionPoint.h"
#include "../Player/PlayerCharacter.h"

ATriggerCameraTransition::ATriggerCameraTransition()
{

	PrimaryActorTick.bCanEverTick = true;

	mTransitionIndex = -1;

	mTransitionTime = 3.f;
	mTransitionTimeAdd = 0.f;

}

void ATriggerCameraTransition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if (mTransitionIndex != -1)
	{
		mTransitionTimeAdd += DeltaTime;

		if (mTransitionTimeAdd >= mTransitionTime + 0.2f )
		{

			mTransitionTimeAdd = 0.f;
			++mTransitionIndex;

			if (mTransitionIndex == mTransitionPointArray.Num())
			{
				mTransitionIndex = -1;
				mPlayerController->SetViewTargetWithBlend(mOriginTarget, mTransitionTime,
					EViewTargetBlendFunction::VTBlend_EaseInOut, 2.f, false);
			}

			else
			{

				mPlayerController->SetViewTargetWithBlend(mTransitionPointArray[mTransitionIndex], mTransitionTime,
					EViewTargetBlendFunction::VTBlend_EaseInOut, 2.f, false);
			}


		}

	}



}

void ATriggerCameraTransition::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (mTransitionPointArray.Num() == 0)
		return;

	// PlayerController를 얻어온다.
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (IsValid(PlayerCharacter))
	{
		mPlayerController = PlayerCharacter->GetController<APlayerController>();

		if (IsValid(mPlayerController))
		{
			//FViewTargetTransitionParams	param;
			//PlayerController->SetViewTarget(mTransitionPointArray[0], param);

			mOriginTarget = OtherActor;

			mTransitionIndex = 0;
			mTransitionTimeAdd = 0.f;

			mPlayerController->SetViewTargetWithBlend(mTransitionPointArray[mTransitionIndex], mTransitionTime,
				EViewTargetBlendFunction::VTBlend_EaseInOut, 2.f, false);

		}
	}
}
