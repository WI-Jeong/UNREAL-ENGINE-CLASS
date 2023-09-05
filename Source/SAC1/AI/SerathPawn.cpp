// Fill out your copyright notice in the Description page of Project Settings.

#include "SerathPawn.h"
#include "DefaultAIAnimInstance.h"

ASerathPawn::ASerathPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody->SetCapsuleHalfHeight(92.f);
	mBody->SetCapsuleRadius(32.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSerath/Characters/Heroes/Serath/Meshes/Serath.Serath'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//애니메이션 블루프린트를 지정한다.
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/AB_AISerath.AB_AISerath_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);


}

void ASerathPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASerathPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASerathPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
