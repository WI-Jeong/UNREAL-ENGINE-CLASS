// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPointFromParticle.h"

// Sets default values
AAISpawnPointFromParticle::AAISpawnPointFromParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAISpawnPointFromParticle::SpawnObject()
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Template ������ Ư�� ���͸� �־��ָ� �ش� ���͸� ������ ���͸�
	// �������ش�.
	//ActorParam.Template=mSpawnClass->GetDefaultObject();

	// UClass�� ������ �ִ� �� Ÿ���� �⺻ ������Ʈ�� ���´�.
	TObjectPtr<AAIPawn> DefaultObj = Cast<AAIPawn>(mSpawnClass->GetDefaultObject());

	float HalfHeight = 0.f;

	// �⺻ ������Ʈ�� ��ȿ�� ��� ĸ���� ���� ���̸� ���´�.
	if (IsValid(DefaultObj))
		HalfHeight = DefaultObj->GetHalfHeight();

	LOG(TEXT("HalfHeight : %.5f"), HalfHeight);

	GetWorld()->SpawnActor<AAIPawn>(mSpawnClass,
		GetActorLocation() + FVector(0.0, 0.0, (double)HalfHeight),
		GetActorRotation(), ActorParam);

	mSpawnObject->SetSpawnPoint(this);

}

// Called when the game starts or when spawned
void AAISpawnPointFromParticle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAISpawnPointFromParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

