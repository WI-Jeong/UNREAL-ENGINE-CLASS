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
	//GetTeam()는 ETeam 타입의 객체를 반환하는 공개 함수
	{
		return mTeam;
		//mTeam이라는 멤버 변수의 값을 가져오는 것
	}

	void SetTeam(ETeam Team)
	//SetTeam(ETeam Team)은 mTeam 멤버 변수의 값을 설정하는 공개 함수
	{
		mTeam = Team;
	}

public:
	void ChangeAnimation(EPlayerAnimType Type)
//이 공개 함수는 EPlayerAnimType 타입의 Type 인자를 받아 플레이어의 애니메이션을 변경
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
	//플레이어 입력을 다룰 때 필요한 함수
	//플레이어 입력에 기능을 바인딩하는 데 사용됨
	//UInputComponent를 매개변수로 받는다.

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
	매개변수
	BodyHit
	->
	HitComponent: 충돌이 발생한 원시(Primitive) 컴포넌트를 나타내는 포인터.
	충돌이 발생한 객체의 컴포넌트

	OtherActor: 상대적인 충돌이 발생한 다른 액터에 대한 포인터.
	상대적으로 충돌한 다른 객체

	OtherComp: 다른 액터의 충돌 컴포넌트를 나타내는 포인터.
	NormalImpulse: 충돌에서의 정상적인 충격을 표현하는 FVector.
	Hit: 충돌에 대한 정보를 포함하는 FHitResult 구조체
	충돌에 대한 상세한 정보를 제공.

	OverlapBegin
	->이 함수는 두 객체가 겹칠 때 호출
	겹침은 서로 교차하지만 물리적인 충돌은 발생하지 않는 상황
	예를 들어, 플레이어가 아이템 영역에 진입하면 이 함수가 호출됨

	OverlappedComponent: 겹침이 시작한 원시/객체 컴포넌트를 나타내는 포인터.
	OtherActor: 겹친 다른 액터에 대한 포인터.
	OtherComp: 겹친 다른 액터의 컴포넌트를 나타내는 포인터.
	OtherBodyIndex: 다른 액터의 몸체(바디) 인덱스.
	bFromSweep: 겹치기가 스위핑 동작으로부터 발생했는지 여부를 나타내는 부울 값.
	SweepResult: 겹치기의 결과를 포함하는 FHitResult 구조체.
	겹침의 상세한 정보를 확인할 수 있다. 


	OverlapEnd
	->겹침이 해제될 때 호출
	OverlappedComponent: 겹치기가 끝난 원시 컴포넌트를 나타내는 포인터.
	OtherActor: 겹친 다른 액터에 대한 포인터.
	OtherComp: 겹친 다른 액터의 컴포넌트를 나타내는 포인터.
	OtherBodyIndex: 다른 액터의 몸체(바디) 인덱스.
		
	*/

public:
	virtual void Attack1();
	virtual void Attack2();
	/// 
	virtual void Attack3();
	
	//	void FootInteraction(bool Left);

};
