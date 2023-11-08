// Fill out your copyright notice in the Description page of Project Settings.


#include "AIZombi.h"

AAIZombi::AAIZombi()
{
	PrimaryActorTick.bCanEverTick = true;

	mName = TEXT("Zombi");

	mBody->SetCapsuleHalfHeight(92.f);
	mBody->SetCapsuleRadius(32.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ZombiTest/Zombiegirl_W_Kurniawan.Zombiegirl_W_Kurniawan'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/ZombiTest/AB_Test.AB_Test_C'"));

	//if (AnimAsset.Succeeded())
	//	mMesh->SetAnimInstanceClass(AnimAsset.Class);


}

void AAIZombi::BeginPlay()
{
	Super::BeginPlay();
}

void AAIZombi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAIZombi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
