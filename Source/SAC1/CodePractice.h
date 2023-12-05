// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Gameinfo.h"
#include "GameFramework/Actor.h"
#include "CodePractice.generated.h"

UCLASS()
class SAC1_API ACodePractice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodePractice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
