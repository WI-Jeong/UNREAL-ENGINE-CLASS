// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIPawn.h"
#include "AIZombi.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API AAIZombi : public AAIPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIZombi();


protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//������ ��ü�� ���ŵ� �� ȣ��ȴ�.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
