// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "NiagaraEffectTest.generated.h"

UCLASS()
class SAC1_API ANiagaraEffectTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANiagaraEffectTest();

protected:

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> mRoot;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> mNiagara;

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