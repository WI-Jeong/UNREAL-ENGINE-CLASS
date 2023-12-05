// Fill out your copyright notice in the Description page of Project Settings.


#include "CodePractice.h"

// Sets default values
ACodePractice::ACodePractice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TObjectPtr<UDataTable> AIPawn::

}

// Called when the game starts or when spawned
void ACodePractice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACodePractice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

