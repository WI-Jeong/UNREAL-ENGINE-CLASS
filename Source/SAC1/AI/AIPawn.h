// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class SAC1_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> mBody;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> mMovement;
	
	//생성된 스폰포인트를 알고 있게 해준다.
	//스폰포인트를 이용해서 생성한 객체가 아닐경우 None이 들어가있다.
	TObjectPtr<class AAISpawnPoint> mSpawnPoint;

public:
	float GetHalfHeight() const
	{
		return mBody->GetScaledCapsuleHalfHeight(); 
	}
	
	void SetSpawnPoint(class AAISpawnPoint* SpawnPoint);
	
protected:
	 //Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//생성한 객체가 제거될 때 호출된다.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetCollisionProfile(const FName& Name);

};
 