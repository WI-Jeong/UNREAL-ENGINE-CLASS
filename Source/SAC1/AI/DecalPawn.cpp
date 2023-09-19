// Fill out your copyright notice in the Description page of Project Settings.


//#include "DecalPawn.h"
//
//// Sets default values
//ADecalPawn::ADecalPawn()
//{
// 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	mName = TEXT("Decal");
//
//	mBody->SetCapsuleHalfHeight(120.f);
//	mBody->SetCapsuleRadius(34.f);
//
//	
//	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Green/Meshes/Buff_Green.Buff_Green'"));
//
//	if (MeshAsset.Succeeded())
//		mMesh->SetSkeletalMesh(MeshAsset.Object);
//
//	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -120.0));
//	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
//
//	//애니메이션 블루프린트를 지정한다.
//	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/AB_Decal.AB_Decal_C'"));
//
//	if (AnimAsset.Succeeded())
//		mMesh->SetAnimInstanceClass(AnimAsset.Class);
//
//
//}
//
//// Called when the game starts or when spawned
//void ADecalPawn::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//void ADecalPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	Super::EndPlay(EndPlayReason);
//}
//
//
//
//// Called every frame
//void ADecalPawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//void ADecalPawn::Attack()
//{
//
//	//현재 캐릭터의 위치에서 50cm앞을 시작점으로 잡아준다.
//	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;
//
//	//끝점은 시작점으로부터 2m전방으로 잡아준다.
//	FVector End = Start + GetActorForwardVector() * 200.f;
//
//	FHitResult result;
//
//	FCollisionQueryParams  param(NAME_None, false, this);
//
//
//	bool Collision = GetWorld()->SweepSingleByChannel(result, Start, End,
//		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel5,
//		FCollisionShape::MakeSphere(50.f), param);
//
//	//디버깅용(에디터)으로 출력한다.
//#if ENABLE_DRAW_DEBUG
//
//	//Collisioin값에 따라 ture일 경우 red, false일 경우 green으로 출력한다.
//	FColor DrawColor = Collision ? FColor::Red : FColor::Green;
//
//	//FRotatioinMatrix::MakeFromZ(GetActorForwardVector()):Z축을 캐릭터
//	//의 앞쪽으로 만들어주는 회전 행렬을 구한다. (FMatrix로 결과가 나온다.)
//	//그래서 .ToQuat()을 이용해서 FQuat(회전값)으로 변환한다.
//
//	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, 100.f,
//		50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
//		DrawColor, false, 20.f);
//#endif
//	if (Collision)
//	{
//		FActorSpawnParameters ActorParam;
//		ActorParam.SpawnCollisionHandlingOverride =
//			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//		ADefaultEffect* Effect = GetWorld()->SpawnActor<ADefaultEffect>(result.ImpactPoint,
//			FRotator::ZeroRotator, ActorParam);
//
//
//		Effect->SetParticleAsset(TEXT("/Script/Engine.Material'/Game/Materials/MDefaultDecal.MDefaultDecal'"));
//
//	}
//
//}
//
//

