// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicioinCharacter.h"
#include "../Effect/DefaultEffect.h"
#include "../Projectile/ProjectileBase.h"


AMagicioinCharacter::AMagicioinCharacter()
{
	//FObjectFinder : 애셋을 로딩해서 사용할 때 쓴다.
	//어떤 애셋을 불러올지 알 수 없기 때문에 template으로 구현되어 
	// 있고 template에 로딩하고자 하는 애셋의 타입을 지정해주면 된다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (MeshAsset.Succeeded())
	{
		//위에서 불러온 skeletalmesh를 character클래스가 가지고있는 
		//skeletalmeshcomponent에 지정해준다.
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	LOG(TEXT("Log Test"));



	//Animation Blueprint 클래스 레퍼런스를 얻어온다.
	static ConstructorHelpers::FClassFinder <UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/AB_Magicion.AB_Magicion_C'"));  
	
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	//캡슐의 절반높이는 기본 88로 되어있지만 메쉬의 키가 커서 92로 설정한다.
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	
	//캡슐의 절반높이가 92로 설정되었기 때문에 기본 메시 출력은 
	//캡슐의 가운데를 발로 밟고 옆을 바라보게 하여 출력되어 있으므로
	//캡슐의 절반높이인 92만큼 아래로 내려준다.
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));

	//메시가 전방을 바라보게 회전한다.
	GetMesh()->SetRelativeRotation(FRotator(0.0,-90.0,0.0));

}

void AMagicioinCharacter::Attack1()
{
	//근접공격. 플레이어 전방으로 일정 거리만큼을 공격거리로 두고 
	//곡격 충돌체크를 진행한다.
	//격투게임같이 충돌 디테일하게 해야하는경우 주먹에도 충돌체를 따로 씌우고
	//디테일하게 해줘야함..나중에 알려주신다함 
	//주로 논타겟팅할 때 씀. 불특정다수에 공격 
	//마우스로 몬스터 클릭해서 공격하면 굳이 충돌필요없다고 하심.

	//sweep과 overlap2가지 종류로 나뉜다.
	//여기에서 sweep과 overlap은 single과 multi2가지로 나뉜다.
	//single은 가장 먼저 충돌된 하나의 객체에 충돌을 진행하고
	//multi는 충돌된 모든 물체에 대해 충돌을 진행한다.
	//Trace충돌채널을 이용해서 충돌을 진행한다.
	//이 함수는 반환값으로 충돌이 있을 경우 true, 없을 경우 false를 반환한다.
	/*
	1번 인자: FHitResult로 충돌된 결과를 이 인자에 저장해준다.
	2번 인자: Start는 충돌 시작위치를 의미한다.
	3번인자: End는 충돌 끝 위치를 의미한다.
	4번 인자: 회전값을 넣어준다.
	5번 인자: 충돌 채널을 넣어준다. 이 채널과 무시하는 프로파일을 가지고 있는 물체는 
	충돌에서 제외된다.
	6번 인자: 충돌 도형을 만들어준다.
	*/

	//현재 캐릭터의 위치에서 50cm앞을 시작점으로 잡아준다.
	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;

	//끝점은 시작점으로부터 2m전방으로 잡아준다.
	FVector End = Start + GetActorForwardVector() * 200.f;

	FHitResult result;

	FCollisionQueryParams  param(NAME_None, false, this);

	
	bool Collision = GetWorld()->SweepSingleByChannel(result,Start,End, 
		FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(50.f), param);

	//디버깅용(에디터)으로 출력한다.
#if ENABLE_DRAW_DEBUG

	//Collisioin값에 따라 ture일 경우 red, false일 경우 green으로 출력한다.
	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	//FRotatioinMatrix::MakeFromZ(GetActorForwardVector()):Z축을 캐릭터
	//의 앞쪽으로 만들어주는 회전 행렬을 구한다. (FMatrix로 결과가 나온다.)
	//그래서 .ToQuat()을 이용해서 FQuat(회전값)으로 변환한다.

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, 100.f,
		50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 20.f);
#endif
	if (Collision)
	{
		FActorSpawnParameters ActorParam;
		ActorParam.SpawnCollisionHandlingOverride = 
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ADefaultEffect* Effect = GetWorld()->SpawnActor<ADefaultEffect>(result.ImpactPoint,
			FRotator::ZeroRotator, ActorParam);

		
		Effect->SetParticleAsset(TEXT("/Script/Engine.StaticMesh'/Game/BlueprintTest/Sphere1.Sphere1'"));

		Effect->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));


	}
}

void AMagicioinCharacter::Attack2()
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//소켓의 위치를 얻어온다. 소켓의 위치는 SkeletalMeshComponent를 이용해서
	//얻어올 수 있다.

	FVector SocketLoc = GetMesh()->GetSocketLocation(TEXT("hand_l_Projectile"));


	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(SocketLoc,
		GetActorRotation(), ActorParam);

	Projectile->SetMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/BlueprintTest/Sphere1.Sphere1'"));
	Projectile->SetCollisionProfile(TEXT("PlayerProjectile"));
}
//
void AMagicioinCharacter::Attack3()
{

	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SocketLoc = GetMesh()->GetSocketLocation(TEXT("hand_r_Projectile"));

	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(SocketLoc,
		GetActorRotation(), ActorParam);


	//이펙트중에 더블클릭해서 봤을 때 particle이 잇는게 있음. 그게 있는것들만 날아가는거 보임!!!!
	Projectile->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_WeaponThrow/P_Skill_Throw_Fire_Proj_Hammer_Heroic.P_Skill_Throw_Fire_Proj_Hammer_Heroic'"));
	Projectile->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/MainBgm.MainBgm'"));

	Projectile->SetCollisionProfile(TEXT("PlayerProjectile"));
	
}
//