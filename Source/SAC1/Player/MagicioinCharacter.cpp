// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicioinCharacter.h"
#include "../Effect/DefaultEffect.h"
#include "../Projectile/ProjectileBase.h"
#include "../Effect/DecalEffect.h"
#include "SAC1PlayerState.h"


AMagicioinCharacter::AMagicioinCharacter()
{
	//FObjectFinder : �ּ��� �ε��ؼ� ����� �� ����.
	//� �ּ��� �ҷ����� �� �� ���� ������ template���� �����Ǿ� 
	// �ְ� template�� �ε��ϰ��� �ϴ� �ּ��� Ÿ���� �������ָ� �ȴ�.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (MeshAsset.Succeeded())
	{
		//������ �ҷ��� skeletalmesh�� characterŬ������ �������ִ� 
		//skeletalmeshcomponent�� �������ش�.
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	LOG(TEXT("Log Test"));



	//Animation Blueprint Ŭ���� ���۷����� ���´�.
	static ConstructorHelpers::FClassFinder <UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/AB_Magicion.AB_Magicion_C'"));  
	
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	//ĸ���� ���ݳ��̴� �⺻ 88�� �Ǿ������� �޽��� Ű�� Ŀ�� 92�� �����Ѵ�.
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	
	//ĸ���� ���ݳ��̰� 92�� �����Ǿ��� ������ �⺻ �޽� ����� 
	//ĸ���� ����� �߷� ��� ���� �ٶ󺸰� �Ͽ� ��µǾ� �����Ƿ�
	//ĸ���� ���ݳ����� 92��ŭ �Ʒ��� �����ش�.
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));

	//�޽ð� ������ �ٶ󺸰� ȸ���Ѵ�.
	GetMesh()->SetRelativeRotation(FRotator(0.0,-90.0,0.0));

}

void AMagicioinCharacter::BeginPlay()
{

	Super::BeginPlay();

	LOG(TEXT("MagicionCharacter Begin"));

	FLinearColor	Color(1.f, 0.f, 0.f, 1.f);
	mTrail->SetNiagaraVariableLinearColor(TEXT("Color"), Color);

	mTrail->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));


}

void AMagicioinCharacter::Attack1()
{
	//��������. �÷��̾� �������� ���� �Ÿ���ŭ�� ���ݰŸ��� �ΰ� 
	//��� �浹üũ�� �����Ѵ�.
	//�������Ӱ��� �浹 �������ϰ� �ؾ��ϴ°�� �ָԿ��� �浹ü�� ���� �����
	//�������ϰ� �������..���߿� �˷��ֽŴ��� 
	//�ַ� ��Ÿ������ �� ��. ��Ư���ټ��� ���� 
	//���콺�� ���� Ŭ���ؼ� �����ϸ� ���� �浹�ʿ���ٰ� �Ͻ�.

	//sweep�� overlap2���� ������ ������.
	//���⿡�� sweep�� overlap�� single�� multi2������ ������.
	//single�� ���� ���� �浹�� �ϳ��� ��ü�� �浹�� �����ϰ�
	//multi�� �浹�� ��� ��ü�� ���� �浹�� �����Ѵ�.
	//Trace�浹ä���� �̿��ؼ� �浹�� �����Ѵ�.
	//�� �Լ��� ��ȯ������ �浹�� ���� ��� true, ���� ��� false�� ��ȯ�Ѵ�.
	/*
	1�� ����: FHitResult�� �浹�� ����� �� ���ڿ� �������ش�.
	2�� ����: Start�� �浹 ������ġ�� �ǹ��Ѵ�.
	3������: End�� �浹 �� ��ġ�� �ǹ��Ѵ�.
	4�� ����: ȸ������ �־��ش�.
	5�� ����: �浹 ä���� �־��ش�. �� ä�ΰ� �����ϴ� ���������� ������ �ִ� ��ü�� 
	�浹���� ���ܵȴ�.
	6�� ����: �浹 ������ ������ش�.
	*/

	//���� ĳ������ ��ġ���� 50cm���� ���������� ����ش�.
	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.f;

	//������ ���������κ��� 2m�������� ����ش�.
	FVector End = Start + GetActorForwardVector() * 200.f;

	FHitResult result;

	FCollisionQueryParams  param(NAME_None, false, this);

	
	bool Collision = GetWorld()->SweepSingleByChannel(result,Start,End, 
		FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(50.f), param);

	//������(������)���� ����Ѵ�.
#if ENABLE_DRAW_DEBUG

	//Collisioin���� ���� ture�� ��� red, false�� ��� green���� ����Ѵ�.
	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	//FRotatioinMatrix::MakeFromZ(GetActorForwardVector()):Z���� ĳ����
	//�� �������� ������ִ� ȸ�� ����� ���Ѵ�. (FMatrix�� ����� ���´�.)
	//�׷��� .ToQuat()�� �̿��ؼ� FQuat(ȸ����)���� ��ȯ�Ѵ�.

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


		FHitResult	LineResult;

		FCollisionQueryParams	param1(NAME_None, false, this);

		bool LineCollision = GetWorld()->LineTraceSingleByChannel(LineResult,
			result.ImpactPoint,
			result.ImpactPoint - FVector(0.0, 0.0, 200.0),
			ECollisionChannel::ECC_GameTraceChannel9, param1);

		if (LineCollision)
		{
			ADecalEffect* Decal = GetWorld()->SpawnActor<ADecalEffect>(
				LineResult.ImpactPoint,
				FRotator::ZeroRotator, ActorParam);

			Decal->SetDecalMaterial(TEXT("/Script/Engine.Material'/Game/Materials/MDefaultDecal.MDefaultDecal'"));
			// ������ �����ֱ⸦ �����Ѵ�. 5.f�� �����ϸ� �����ǰ� 5�� �ڿ� ���ŵȴ�.
			Decal->SetLifeSpan(5.f);
		}

		auto State = GetPlayerState<ASAC1PlayerState>();

		float	Dmg = 0.f;

		if (IsValid(State))
			Dmg = (float)State->GetAttackPoint();

	/*	FDamageEvent	DmgEvent;
		result.GetActor()->TakeDamage(Dmg, DmgEvent, GetController(),this);*/
	}
	
}

void AMagicioinCharacter::Attack2()
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//������ ��ġ�� ���´�. ������ ��ġ�� SkeletalMeshComponent�� �̿��ؼ�
	//���� �� �ִ�.

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


	//����Ʈ�߿� ����Ŭ���ؼ� ���� �� particle�� �մ°� ����. �װ� �ִ°͵鸸 ���ư��°� ����!!!!
	Projectile->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_WeaponThrow/P_Skill_Throw_Fire_Proj_Hammer_Heroic.P_Skill_Throw_Fire_Proj_Hammer_Heroic'"));
	Projectile->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/MainBgm.MainBgm'"));

	Projectile->SetCollisionProfile(TEXT("PlayerProjectile"));
	
}
//