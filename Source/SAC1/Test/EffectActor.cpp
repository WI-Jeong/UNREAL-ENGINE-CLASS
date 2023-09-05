// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectActor.h"
#include "TestActor.h" 
#include "../Effect/DefaultEffect.h"



// Sets default values
AEffectActor::AEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBoxc = CreateDefaultSubobject<UBoxComponent>(TEXT("Boxc"));

	SetRootComponent(mBoxc);


	mBoxc->SetBoxExtent(FVector(212.5, 240.5, 323));

	mBoxc->SetGenerateOverlapEvents(true);

	mBoxc->SetCollisionProfileName(TEXT("TestOverlap"));


	mMesh01 = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh01"));

	mMesh01->SetupAttachment(mBoxc);

	mMesh01->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mMesh01->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/NaturePackage/Meshes/flora/rock2.rock2'"));

	if (MeshAsset.Succeeded())
	{
		mMesh01->SetStaticMesh(MeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

