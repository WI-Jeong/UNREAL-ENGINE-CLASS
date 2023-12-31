// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultEffect.h"

// Sets default values
ADefaultEffect::ADefaultEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	mAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	////mParticle이 root가 될거임
	//SetRootComponent(mParticle);
	////부모지정
	//mAudio->SetupAttachment(mParticle);


	SetRootComponent(mRoot);

	mAudio->SetupAttachment(mRoot);
	mParticle->SetupAttachment(mRoot);
	mNiagara->SetupAttachment(mRoot);

	mRoot->bVisualizeComponent = true;

}

// Called when the game starts or when spawned
void ADefaultEffect::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADefaultEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultEffect::SetNiagaraAsset(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(nullptr,
		*Path);

	if (IsValid(Particle))
		mNiagara->SetAsset(Particle);
}

void ADefaultEffect::SetNiagaraAsset(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mNiagara->SetAsset(Particle);
}

void ADefaultEffect::SetParticleAsset(const FString& Path)
{
	//FString은 역참조를 하면 이 문자열 클래스가 가지고 있는 문자열 포인터(TCHAR*)를 반환해준다.
	//그래서 2번째 인자에 Path의 역참조를 통헤 에셋의 경로를 넣어주면
	//해당 애셋을 불러오게 된다.
	UParticleSystem* Particle = LoadObject< UParticleSystem>(nullptr, *Path);

	//불러온 애셋의 유효성 검사를 실시한다.
	//유효할 경우 ParticleSystemComponent에 파티클 에셋을 지정한다.
	if (IsValid(Particle))
	{
		mParticle->SetTemplate(Particle);
		mParticle->OnSystemFinished.AddDynamic(this, &ADefaultEffect::ParticleFinish);
	}
}

void ADefaultEffect::SetParticleAsset(UParticleSystem* Particle)
{
	if (IsValid(Particle))
	{
		mParticle->SetTemplate(Particle);
		mParticle->OnSystemFinished.AddDynamic(this, &ADefaultEffect::ParticleFinish);
	}
}

void ADefaultEffect::SetAudioAsset(const FString& Path)
{
	USoundBase*Sound = LoadObject< USoundBase>(nullptr, *Path);

	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
		mAudio->Play();
	}
}

void ADefaultEffect::SetAudioAsset(USoundBase* Sound)
{
	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
		mAudio->Play();
	}
}

void ADefaultEffect::ParticleFinish(UParticleSystemComponent* System)
{
	//LOG(TEXT("Particle Finish"));
	Destroy();
}

