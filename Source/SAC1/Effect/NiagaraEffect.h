// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "DefaultEffect.h"
//#include "GameFramework/Actor.h"
#include "NiagaraEffect.generated.h"

UCLASS()
class SAC1_API ANiagaraEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANiagaraEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetNiagaraAsset(const FString& Path);
	void SetNiagaraAsset(UNiagaraSystem* Particle);

};
