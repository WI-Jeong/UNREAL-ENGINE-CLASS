// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelect.h"

// Sets default values
APlayerSelect::APlayerSelect()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCameraRigTime = 5.f;
	mCameraRigAddTime = 0.f;
	mCameraTransition = false;

	mSelectJob = EPlayerJob::None;
}

// Called when the game starts or when spawned
void APlayerSelect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FHitResult	result;

	bool Collision = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel10,
		false, result);

	if (Collision)
	{
		USkeletalMeshComponent* MeshCom = nullptr;

		if (IsValid(mCursorPickActor) && mCursorPickActor != result.GetActor())
		{
			//result.GetActor()->Tags
			MeshCom = mCursorPickActor->GetComponentByClass<USkeletalMeshComponent>();

			if (IsValid(MeshCom))
			{
				MeshCom->SetRenderCustomDepth(false);
			}
		}

		mCursorPickActor = result.GetActor();

		MeshCom = mCursorPickActor->GetComponentByClass<USkeletalMeshComponent>();

		if (IsValid(MeshCom))
		{
			MeshCom->SetRenderCustomDepth(true);
		}
	}

	else if (IsValid(mCursorPickActor))
	{
		USkeletalMeshComponent* MeshCom = mCursorPickActor->GetComponentByClass<USkeletalMeshComponent>();

		if (IsValid(MeshCom))
		{
			MeshCom->SetRenderCustomDepth(false);
		}

		mCursorPickActor = nullptr;
	}

	/*if (mCameraTransition)
	{
		mCameraRigAddTime += DeltaTime * mCameraRigPlayDir;

		if (mCameraRigAddTime >= mCameraRigTime)
		{
			mCameraRigAddTime = mCameraRigTime;
			mCameraTransition = false;
		}

		else if (mCameraRigAddTime <= 0.f)
		{
			mCameraRigAddTime = 0.f;
			mCameraTransition = false;
		}

		float	RigRatio = mCameraRigAddTime / mCameraRigTime;

		mCameraRigRail->CurrentPositionOnRail = RigRatio;
	}*/



}

// Called to bind functionality to input
void APlayerSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Select"),EInputEvent::IE_Pressed,this,&APlayerSelect::Pick);

}

void APlayerSelect::Pick()
{
	if (IsValid(mCursorPickActor))
	{
		mSelectActor = mCursorPickActor;
		LOG(TEXT("Tag : %s"), *mSelectActor->Tags[0].ToString());
		//Tags[0].ToString()); 로 안끝내고 Tags[0];로 끝내면 간접정보 잘못되었다고 오류남.

		if (mSelectActor->Tags[0] == TEXT("Knight"))
		{
			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(mKnightCamera,
				mCameraRigTime, EViewTargetBlendFunction::VTBlend_Cubic);
			mSelectJob = EPlayerJob::Knight;
		}

		else if (mSelectActor->Tags[0] == TEXT("Archer"))
			mSelectJob = EPlayerJob::Archer;

		else if (mSelectActor->Tags[0] == TEXT("Magicion"))
		{
			mSelectJob = EPlayerJob::Magicion;
			mCameraTransition = true;
			//mCameraRigPlayDir = 1.f;
		}

		//GameMode->EnableStartButton(true);
	}

	else
	{
		if (mSelectJob == EPlayerJob::Magicion)
		{
			//mCameraRigPlayDir = -1.f;
			mCameraTransition = true;
		}

		else if (mSelectJob == EPlayerJob::Knight)
		{
			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this,
				mCameraRigTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}

		//GameMode->EnableStartButton(false);
	}
}

