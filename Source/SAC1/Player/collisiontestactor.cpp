// Fill out your copyright notice in the Description page of Project Settings.


#include "collisiontestactor.h"


// Sets default values
Acollisiontestactor::Acollisiontestactor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule02 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule02"));
	mStaticMesh02 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh02"));

	SetRootComponent(mCapsule02);
	mStaticMesh02->SetupAttachment(mCapsule02);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/NaturePackage/Meshes/flora/Tree03.Tree03'"));

	if (MeshAsset.Succeeded())
	{
		mStaticMesh02->SetStaticMesh(MeshAsset.Object);
	}


	mCapsule02->SetCollisionProfileName(TEXT("Hit"));
	mStaticMesh02->SetCollisionProfileName(TEXT("NoCollision"));

	mCapsule02->SetNotifyRigidBodyCollision(true);
	mStaticMesh02->SetNotifyRigidBodyCollision(false); 

	// OnComponentHit : Multicast + Dynamic 조합의 Delegate이다.
	mCapsule02->OnComponentHit.AddDynamic(this, &Acollisiontestactor::BodyHit02);

}

// Called when the game starts or when spawned
void Acollisiontestactor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acollisiontestactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Acollisiontestactor::BodyHit02(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Dest : %s"), *OtherActor->GetName()));
}
