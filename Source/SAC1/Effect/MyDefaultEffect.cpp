// Fill out your copyright notice in the Description page of Project Settings.

//
//#include "MyDefaultEffect.h"
//
//AMyDefaultEffect::AMyDefaultEffect()
//{
//
//	PrimaryActorTick.bCanEverTick = true;
//
//	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
//
//	mNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
//
//	SetRootComponent(mRoot);
//
//	mNiagara->SetupAttachment(mRoot);
//
//	mRoot->bVisualizeComponent = true;
//}
//
//void AMyDefaultEffect::SetNiagaraAsset(const FString& Path)
//{
//
//	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(nullptr,
//		*Path);
//
//	if (IsValid(Particle))
//		mNiagara->SetAsset(Particle);
//}
//
//void AMyDefaultEffect::SetNiagaraAsset(UNiagaraSystem* Particle)
//{
//
//	if (IsValid(Particle))
//		mNiagara->SetAsset(Particle);
//}
