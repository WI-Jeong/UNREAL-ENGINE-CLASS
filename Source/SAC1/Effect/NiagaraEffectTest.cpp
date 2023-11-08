// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraEffectTest.h"
//#include "NiagaraEffectTest.h"

// Sets default values
ANiagaraEffectTest::ANiagaraEffectTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));


	SetRootComponent(mRoot);

	mNiagara->SetupAttachment(mRoot);

	mRoot->bVisualizeComponent = true;

}

// Called when the game starts or when spawned
void ANiagaraEffectTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANiagaraEffectTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANiagaraEffectTest::SetNiagaraAsset(const FString& Path)
{

	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(nullptr,
		*Path);

	if (IsValid(Particle))
		mNiagara->SetAsset(Particle);
}

void ANiagaraEffectTest::SetNiagaraAsset(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mNiagara->SetAsset(Particle);
}

