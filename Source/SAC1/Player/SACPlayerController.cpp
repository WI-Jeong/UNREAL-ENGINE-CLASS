// Fill out your copyright notice in the Description page of Project Settings.


#include "SACPlayerController.h"

ASACPlayerController::ASACPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;



	//여기까지 이제 마우스로 상호작용할 준비 다 된거임
}

void ASACPlayerController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FInputModeGameAndUI	InputMode;

	SetInputMode(InputMode);
}

void ASACPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASACPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASACPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void ASACPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ASACPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  


	//실시간으로 마우스와 상호작용하는 물체를 찾는다.

	FHitResult result;

	bool Collision=GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel10, false, result );

	if (Collision)
	{

		if(IsValid(mCursorPickActor)&& mCursorPickActor !=result.GetActor())
		{
			ChangePickOutLine(0);
		}

		mCursorPickActor = result.GetActor();

		ChangePickOutLine(15);

	}

	else if(IsValid(mCursorPickActor))
	{
		ChangePickOutLine(0);
		mCursorPickActor = nullptr;

	}


}

void ASACPlayerController::ChangePickOutLine(int32 StencilValue)
{

	UStaticMeshComponent* StaticMesh =mCursorPickActor->GetComponentByClass<UStaticMeshComponent>();

	if (IsValid(StaticMesh))
	{
		StaticMesh->SetCustomDepthStencilValue(StencilValue);
	}

	USkeletalMeshComponent* SkeletalMesh =
		mCursorPickActor->GetComponentByClass<USkeletalMeshComponent>();

	if (IsValid(SkeletalMesh))

	{
		SkeletalMesh->SetCustomDepthStencilValue(StencilValue);
	} 
}
