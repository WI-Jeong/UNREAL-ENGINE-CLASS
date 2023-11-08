// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

/*
Player용 Pawn은 월드가 변경이 되면 메모리에서 제거가 된다.
메모리에서 제거하면 가지고 있던 모든 데이터가 제거된다.
그러나 playerState는 메모리에 그대로 남아있게 된다.
즉, 데이터를 다음 월드에서도 유지해야 한다면 Playerstate를 활용하여 
데이터를 저장해야한다.
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
	{
		return mTeam;
	}

	void SetTeam(ETeam Team)
	{
		mTeam = Team;
	}

public:
	void ChangeAnimation(EPlayerAnimType Type)
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

public:
	virtual void Attack1();
	virtual void Attack2();
	/// 
	virtual void Attack3();
	////
};
