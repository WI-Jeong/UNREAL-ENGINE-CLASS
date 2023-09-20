// Fill out your copyright notice in the Description page of Project Settings.


#include "SACPlayerController.h"

ASACPlayerController::ASACPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;



	//������� ���� ���콺�� ��ȣ�ۿ��� �غ� �� �Ȱ���
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


	//�ǽð����� ���콺�� ��ȣ�ۿ��ϴ� ��ü�� ã�´�.

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
