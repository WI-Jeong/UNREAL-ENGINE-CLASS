// Fill out your copyright notice in the Description page of Project Settings.

//
//#include "TestEffect.h"
//
//ATestEffect::ATestEffect()
//{
//	PrimaryActorTick.bCanEverTick = true;
//
//	SetRootComponent(mRoot);
//	mNiagara->SetupAttachment(mRoot);
//
//	mRoot->bVisualizeComponent = true;
//}
//
//void ATestEffect::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//void ATestEffect::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}
//
//void ATestEffect::SetNiagaraAsset(const FString& Path)
//{
//	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(nullptr,
//		*Path);
//
//	if (IsValid(Particle))
//		mNiagara->SetAsset(Particle);
//}
//
//void ATestEffect::SetNiagaraAsset(UNiagaraSystem* Particle)
//{
//	if (IsValid(Particle))
//		mNiagara->SetAsset(Particle);
//}
//
//void ATestEffect::ParticleFinish(UParticleSystemComponent* System)
//{
//	Destroy();
//}
