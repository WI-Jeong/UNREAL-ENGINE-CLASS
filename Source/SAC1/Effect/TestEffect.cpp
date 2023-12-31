// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEffect.h"

// Sets default values
ATestEffect::ATestEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara")); 
 
	mNiagara->SetupAttachment(mRoot);
	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void ATestEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestEffect::SetNiagaraAsset(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(nullptr,
		*Path);

	if (IsValid(Particle))
		mNiagara->SetAsset(Particle);
}

void ATestEffect::SetNiagaraAsset(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mNiagara->SetAsset(Particle);
}

