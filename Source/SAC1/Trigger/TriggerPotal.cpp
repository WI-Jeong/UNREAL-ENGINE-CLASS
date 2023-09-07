// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPotal.h"

ATriggerPotal::ATriggerPotal()
{
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	mParticle->SetupAttachment(RootComponent);

}

void ATriggerPotal::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	// ��ȯ�� ������ �̸��� ��ȿ�� ���
	if (mTransitionName.IsValid())
	{
		UGameplayStatics::OpenLevel(GetWorld(), mTransitionName);
	}
}
