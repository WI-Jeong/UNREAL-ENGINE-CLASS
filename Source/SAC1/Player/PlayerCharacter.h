// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

/*
Player�� Pawn�� ���尡 ������ �Ǹ� �޸𸮿��� ���Ű� �ȴ�.
�޸𸮿��� �����ϸ� ������ �ִ� ��� �����Ͱ� ���ŵȴ�.
�׷��� playerState�� �޸𸮿� �״�� �����ְ� �ȴ�.
��, �����͸� ���� ���忡���� �����ؾ� �Ѵٸ� Playerstate�� Ȱ���Ͽ� 
�����͸� �����ؾ��Ѵ�.
*/

UCLASS()
class SAC1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) 
	TObjectPtr< USpringArmComponent> mSpringArm;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) 
	TObjectPtr<UCameraComponent> mCamera;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraComponent> mTrail;

	bool mCameraRotationEnable;

	TObjectPtr< UPlayerAnimInstance> mPlayerAnim;

	ETeam	mTeam;

public:
	ETeam GetTeam() 
	//GetTeam()�� ETeam Ÿ���� ��ü�� ��ȯ�ϴ� ���� �Լ�
	{
		return mTeam;
		//mTeam�̶�� ��� ������ ���� �������� ��
	}

	void SetTeam(ETeam Team)
	//SetTeam(ETeam Team)�� mTeam ��� ������ ���� �����ϴ� ���� �Լ�
	{
		mTeam = Team;
	}

public:
	void ChangeAnimation(EPlayerAnimType Type)
//�� ���� �Լ��� EPlayerAnimType Ÿ���� Type ���ڸ� �޾� �÷��̾��� �ִϸ��̼��� ����
	{
		mPlayerAnim->ChangeAnim(Type);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//�÷��̾� �Է��� �ٷ� �� �ʿ��� �Լ�
	//�÷��̾� �Է¿� ����� ���ε��ϴ� �� ����
	//UInputComponent�� �Ű������� �޴´�.

	virtual float TakeDamage(float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser);



private:
	void MoveFront(float Scale);
	void MoveSide(float Scale);
	void RotationCharacterYaw(float Scale);
	void UpDownPitch(float Scale);
	void CameraZoom(float Scale);

	void RotationCamera();
	void RotationCameraReleased();
	void Jumpkey();
	void Attack();

private:
	UFUNCTION()
	void BodyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/*
	�Ű�����
	BodyHit
	->
	HitComponent: �浹�� �߻��� ����(Primitive) ������Ʈ�� ��Ÿ���� ������.
	�浹�� �߻��� ��ü�� ������Ʈ

	OtherActor: ������� �浹�� �߻��� �ٸ� ���Ϳ� ���� ������.
	��������� �浹�� �ٸ� ��ü

	OtherComp: �ٸ� ������ �浹 ������Ʈ�� ��Ÿ���� ������.
	NormalImpulse: �浹������ �������� ����� ǥ���ϴ� FVector.
	Hit: �浹�� ���� ������ �����ϴ� FHitResult ����ü
	�浹�� ���� ���� ������ ����.

	OverlapBegin
	->�� �Լ��� �� ��ü�� ��ĥ �� ȣ��
	��ħ�� ���� ���������� �������� �浹�� �߻����� �ʴ� ��Ȳ
	���� ���, �÷��̾ ������ ������ �����ϸ� �� �Լ��� ȣ���

	OverlappedComponent: ��ħ�� ������ ����/��ü ������Ʈ�� ��Ÿ���� ������.
	OtherActor: ��ģ �ٸ� ���Ϳ� ���� ������.
	OtherComp: ��ģ �ٸ� ������ ������Ʈ�� ��Ÿ���� ������.
	OtherBodyIndex: �ٸ� ������ ��ü(�ٵ�) �ε���.
	bFromSweep: ��ġ�Ⱑ ������ �������κ��� �߻��ߴ��� ���θ� ��Ÿ���� �ο� ��.
	SweepResult: ��ġ���� ����� �����ϴ� FHitResult ����ü.
	��ħ�� ���� ������ Ȯ���� �� �ִ�. 


	OverlapEnd
	->��ħ�� ������ �� ȣ��
	OverlappedComponent: ��ġ�Ⱑ ���� ���� ������Ʈ�� ��Ÿ���� ������.
	OtherActor: ��ģ �ٸ� ���Ϳ� ���� ������.
	OtherComp: ��ģ �ٸ� ������ ������Ʈ�� ��Ÿ���� ������.
	OtherBodyIndex: �ٸ� ������ ��ü(�ٵ�) �ε���.
		
	*/

public:
	virtual void Attack1();
	virtual void Attack2();
	/// 
	virtual void Attack3();
	
	//	void FootInteraction(bool Left);

};
