// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelect.h"
#include "../UI/CharacterSelectGameMode.h"   
#include "../SAC1GameInstance.h"

// Sets default values
APlayerSelect::APlayerSelect()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//mCameraRigTime = 5.f;
	//mCameraRigAddTime = 0.f;
	//mCameraTransition = false;
	//mCameraRigPlayDir = 1.f;

	//mSelectJob = EPlayerJob::None;
}

// Called when the game starts or when spawned
void APlayerSelect::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerSelect::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	//FHitResult	result;

	//bool Collision = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel10,
	//	false, result);

	//if (Collision)
	//{
	//	USkeletalMeshComponent* MeshCom = nullptr;

	//	if (IsValid(mCursorPickActor) && mCursorPickActor != result.GetActor())
	//	{
	//		//result.GetActor()->Tags
	//		MeshCom = mCursorPickActor->GetComponentByClass<USkeletalMeshComponent>();

	//		if (IsValid(MeshCom))
	//		{
	//			MeshCom->SetRenderCustomDepth(false);
	//		}
	//	}

	//	mCursorPickActor = result.GetActor();

	//	MeshCom = mCursorPickActor->GetComponentByClass<USkeletalMeshComponent>();

	//	if (IsValid(MeshCom))
	//	{
	//		MeshCom->SetRenderCustomDepth(true);
	//	}
	//}

	//else if (IsValid(mCursorPickActor))
	//{
	//	USkeletalMeshComponent* MeshCom = mCursorPickActor->GetComponentByClass<USkeletalMeshComponent>();

	//	if (IsValid(MeshCom))
	//	{
	//		MeshCom->SetRenderCustomDepth(false);
	//	}

	//	mCursorPickActor = nullptr;
	//}

	//if (mCameraTransition)
	//{
	//	mCameraRigAddTime += DeltaTime * mCameraRigPlayDir;

	//	if (mCameraRigAddTime >= mCameraRigTime)
	//	{
	//		mCameraRigAddTime = mCameraRigTime;
	//		mCameraTransition = false;
	//	}

	//	else if (mCameraRigAddTime <= 0.f)
	//	{
	//		mCameraRigAddTime = 0.f;
	//		mCameraTransition = false;
	//	}

	//	float	RigRatio = mCameraRigAddTime / mCameraRigTime;

	//	mCameraRigRail->CurrentPositionOnRail = RigRatio;
	//}
}

// Called to bind functionality to input
void APlayerSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction(TEXT("Select"), EInputEvent::IE_Pressed,
	//	this, &APlayerSelect::Pick);
}

void APlayerSelect::Pick()
{
	//// GameMode를 얻어온다.
	//ACharacterSelectGameMode* GameMode = GetWorld()->GetAuthGameMode<ACharacterSelectGameMode>();

	//if (IsValid(mCursorPickActor))
	//{
	//	mSelectActor = mCursorPickActor;
	//	LOG(TEXT("Tag : %s"), *mSelectActor->Tags[0].ToString());

	//	if (mSelectActor->Tags[0] == TEXT("Knight"))
	//	{
	//		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(mKnightCamera,
	//			mCameraRigTime, EViewTargetBlendFunction::VTBlend_Cubic);
	//		mSelectJob = EPlayerJob::Knight;
	//	}

	//	else if (mSelectActor->Tags[0] == TEXT("Archer"))
	//		mSelectJob = EPlayerJob::Archer;

	//	else if (mSelectActor->Tags[0] == TEXT("Magicion"))
	//	{
	//		mSelectJob = EPlayerJob::Magicion;
	//		mCameraTransition = true;
	//		mCameraRigPlayDir = 1.f;
	//	}

	//	GameMode->EnableStartButton(true);

	//	if (!mCameraTransitionTimerHandle.IsValid())
	//	{
	//		// Actor클래스는 GetWorldTimerManager() 함수를 지원해주고 있지만
	//		// 다른 클래스에서는 지원하지 않을 수 있기 때문에
	//		// GetWorld()->GetTimerManager() 로 접근한다.
	//		GetWorld()->GetTimerManager().SetTimer(mCameraTransitionTimerHandle, this,
	//			&APlayerSelect::CameraTransitionTimer, mCameraRigTime);
	//	}
	//}

	//else
	//{
	//	if (mSelectJob == EPlayerJob::Magicion)
	//	{
	//		mCameraRigPlayDir = -1.f;
	//		mCameraTransition = true;
	//	}

	//	else if (mSelectJob == EPlayerJob::Knight)
	//	{
	//		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this,
	//			mCameraRigTime, EViewTargetBlendFunction::VTBlend_Cubic);
	//	}

	//	GameMode->EnableStartButton(false);
	//	GameMode->SetCharacterInfo(false);
	// 
	//}

	//USAC1GameInstance* GameInst = GetWorld()->GetGameInstance<USAC1GameInstance>();

	//GameInst->SetPlayerJob(mSelectJob);

}
//
//void APlayerSelect::CameraTransitionTimer()
//{
//	//// GameMode를 얻어온다.    
//	//ACharacterSelectGameMode* GameMode = GetWorld()->GetAuthGameMode<ACharacterSelectGameMode>();
//
//	//GameMode->SetCharacterInfo(false);
//
//	//GetWorld()->GetTimerManager().ClearTimer(mCameraTransitionTimerHandle);
//
//	//switch (mSelectJob)
//	//{
//	//case EPlayerJob::Knight:
//	//	GameMode->SetCharacterInfo(true, TEXT("Knight"), mKnightMtrl);
//	//	break;
//	//case EPlayerJob::Archer:
//	//	break;
//	//case EPlayerJob::Magicion:
//	//	GameMode->SetCharacterInfo(true, TEXT("Magicion"), mMagicionMtrl);
//	//	break;
//	//}
//}
