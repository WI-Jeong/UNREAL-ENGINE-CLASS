// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

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

	bool mCameraRotationEnable;

	TObjectPtr< UPlayerAnimInstance> mPlayerAnim;

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
