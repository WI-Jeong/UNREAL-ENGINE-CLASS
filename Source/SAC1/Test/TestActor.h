// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h" //이전폴더의 gameinfo.h 인클루드
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class SAC1_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestActor();


protected:
	/*
	여기에 컴포넌트 변수를 선언했다고 실제 사용할 컴포넌트 생성한 것은
	아니다. 여기에 이렇게 한 것은 단순히 포인터 변수를 선언해둔 것이다.
	그렇기 때문에 실제 사용할 컴포넌트를 생성하고 이 포인터 변수에 생성한
	객체의 주소를 넘겨주어야 한다.
	*/

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> mMesh;

	//도형을 이용한 충돌 컴포넌트는 다양한 컴포넌트가 지원된다.
	//대표적으로 많이 활용되는 컴포넌트는 박스, 구, 캡슐이다.
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> mBody;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	/*
	1번인자: 부딪힌 충돌체가 들어온다.
	2번인자: 부딪힌 상대방 액터가 들어온다.
	3번인자: 부딪힌 상대방 액터의 충돌체중 어떤 충돌체인지가 들어온다.
	4번인자: 상대방 바디 인덱스가 들어온다.
	5번인자: 충돌 시 모양을 추적한다. (이건 걍 무시하라하심)
	6번인자: 충돌 결과가 들어온다. 충돌 위치, 충돌 대상, 충돌방향 등 다양한 정보가 
	들어온다!!! 6번 인자가 중요하다고 하셨음!!!

	UPROPERTY()
	int32 FaceIndex;

	UPROPERTY()
	float Time;

	UPROPERTY()  충돌 거리
	float Distance;

	UPROPERTY()
	FVector_NetQuantize Location;

	UPROPERTY()  부딪힌 위치
	FVector_NetQuantize ImpactPoint;

	UPROPERTY()
	FVector_NetQuantizeNormal Normal;

	UPROPERTY()  부딪힌 방향
	FVector_NetQuantizeNormal ImpactNormal;

	UPROPERTY()
	FVector_NetQuantize TraceStart;

	UPROPERTY()
	FVector_NetQuantize TraceEnd;

	UPROPERTY()
	float PenetrationDepth;

	UPROPERTY()
	int32 MyItem;

	UPROPERTY()
	int32 Item;

	UPROPERTY()
	uint8 ElementIndex;

	UPROPERTY()
	uint8 bBlockingHit : 1;

	UPROPERTY()
	uint8 bStartPenetrating : 1;

	UPROPERTY()
	TWeakObjectPtr<UPhysicalMaterial> PhysMaterial;

	UPROPERTY()
	FActorInstanceHandle HitObjectHandle;

	UPROPERTY()
	TWeakObjectPtr<UPrimitiveComponent> Component;

	UPROPERTY()
	FName BoneName;

	UPROPERTY()
	FName MyBoneName;
	*/
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
