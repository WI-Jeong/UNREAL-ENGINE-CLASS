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
	static TObjectPtr<UDataTable>	mAIDataTable;

public:
	static void LoadAIData();

protected:
	static const FAIDataTable* FindAIData(const FName& Name);

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent>	mBody;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent>	mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement>	mMovement; 

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIState>	mAIState;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	TObjectPtr<class UDefaultAIAnimInstance>	mAnim;

	// ������ ��������Ʈ�� �˰� �ְ� ���ش�.
	// ��������Ʈ�� �̿��ؼ� ������ ��ü�� �ƴ� ��� None�� ���ִ�.
	TObjectPtr<class AAISpawnPoint>	mSpawnPoint;

	bool	mAttackEnd;
	bool	mInteractionEnd;	

	ETeam	mTeam;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class APatrolPoint>>	mPatrolPointArray;

public:
	ETeam GetTeam()
	{
		return mTeam;
	}

	void SetTeam(ETeam Team) //�� �����ϴ� �Լ�
	{
		mTeam = Team;
	}

public:
	bool GetAttackEnd()	const
	{
		return mAttackEnd;
	}

	bool GetInteractionEnd()	const
	{
		return mInteractionEnd;
	}

	const TObjectPtr<class UAIState>& GetAIState() const
	{
		return mAIState;
	}


	const TObjectPtr<class UDefaultAIAnimInstance>& GetAIAnimInstance()	const
	{
		return mAnim;
	}

	//�̰͵� BS����� AB�������� ���Ŀ� ���ذǵ�....

	

public:
	float GetHalfHeight()	const
	{
		return mBody->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius()	const
	{
		return mBody->GetScaledCapsuleRadius();
	}

	void SetSpawnPoint(class AAISpawnPoint* SpawnPoint);

	void SetAttackEnd(bool AttackEnd)
	{
		mAttackEnd = AttackEnd;
	}

	void SetInteractionEnd(bool InteractionEnd)
	{
		mInteractionEnd = InteractionEnd;
	}

protected:
	virtual void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// ������ ��ü�� ���ŵɶ� ȣ��ȴ�.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetCollisionProfile(const FName& Name);
};
