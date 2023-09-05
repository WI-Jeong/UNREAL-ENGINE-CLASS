// Fill out your copyright notice in the Description page of Project Settings.


#include "collisiontest.h"

// Sets default values
Acollisiontest::Acollisiontest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//////////////////////////////////////////내가한거//////////////////////////////

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	//부모로 지정
	SetRootComponent(mCapsule);
	mStaticMesh->SetupAttachment(mCapsule);

	mCapsule->SetCollisionProfileName(TEXT("Hit"));
	//mStaticMesh->SetCollisionProfileName(TEXT(""));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/NaturePackage/Meshes/flora/rock1.rock1'"));
	
	if (MeshAsset.Succeeded())
	{
		mStaticMesh->SetStaticMesh(MeshAsset.Object);
	}


	// 오버랩 이벤트 생성을 켜준다.
	mCapsule->SetGenerateOverlapEvents(true);

	// 시뮬레이션 히트 이벤트 생성을 켜준다.
	mCapsule->SetNotifyRigidBodyCollision(true);

	// OnComponentHit : Multicast + Dynamic 조합의 Delegate이다.
	mCapsule->OnComponentHit.AddDynamic(this,
		&Acollisiontest::BodyHit);


	mCapsule->OnComponentBeginOverlap.AddDynamic(this,&Acollisiontest::OverlapBegin);

	mCapsule->OnComponentEndOverlap.AddDynamic(this,&Acollisiontest::OverlapEnd);

	mCapsule->CanCharacterStepUpOn =
		ECanBeCharacterBase::ECB_No;
	//캐릭터가 캐릭터 위에 올라가지못하게 해주는거

	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	//////////////////////////////////////////////////////

}

// Called when the game starts or when spawned
void Acollisiontest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acollisiontest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Acollisiontest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

////////////////////////////////////////////////////

void Acollisiontest::BodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		FString::Printf(TEXT("Dest : %s"), *OtherActor->GetName()));
}

void Acollisiontest::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow,
		FString::Printf(TEXT("BeginOverlap Dest : %s"), *OtherActor->GetName()));
}

void Acollisiontest::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue,
		FString::Printf(TEXT("EndOverlap Dest : %s"), *OtherActor->GetName()));
}



///////////////////////////////////

