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
	/*
	������
	�ش� Ŭ������ �ν��Ͻ��� ������ �� ȣ��Ǵ� Ư���� ��� �Լ�.
	�ַ� Ŭ���� ��� ������ �ʱ�ȭ�ϰų� �ٸ� �ʱ�ȭ �۾��� �����ϴ� �� ����.

	�𸮾� ���������� GENERATED_BODY() ��ũ�ΰ� Ŭ���� ���� ���Ǿ�� �ϸ�, 
	�̴� �𸮾� ������ �ڵ� ���� �ý��ۿ� �ʿ��� ������ �����մϴ�.

	* Ŭ������ �ν��Ͻ��� �����ΰ�
	Ŭ����: ��ü�� �����ϱ� ���� ���ø� �Ǵ� ���赵�� ���� ���� ex)�ؾ Ʋ
	Ŭ������ �ν��Ͻ�: �� Ŭ������ ������� ������ ������ ��ü ex)�ؾ Ʋ�� ���� ��������� ���� �ؾ 

	��)
			class FishBread
		{
		public:
			int filling;  // �ؾ ��
			FishBread()   // �ؾ ������
			{
				filling = 0; // �ؾ �� �ʱ�ȭ
			}
		};

		FishBread myFishBread;   // FishBread Ŭ������ �ν��Ͻ� ����

		->FishBread Ŭ������ �ؾ�� ����� ���� Ʋ
		myFishBread�� �� Ʋ�� ����Ͽ� ������� ���� �ؾ
		myFishBread�� FishBreadŬ������ �ν��Ͻ�.


	��, �ν��Ͻ��� Ŭ������ ������� �����Ǹ�, �� �ν��Ͻ��� �ش� Ŭ������ ��� ������ ��� �Լ��� ������ ��.
	Ŭ������ �����ڴ� �ش� Ŭ������ �ν��Ͻ��� ������ �� ȣ��Ǵ� Ư���� �Լ���, 
	�ν��Ͻ��� ������ �� �ʱ�ȭ �۾��� �����ϴµ� ����.
		
	*/

protected:
	static TObjectPtr<UDataTable>	mAIDataTable;//���α׷��� ���۵� �� static�� �ִ°� ���� ����� �׸��� �߰��� ���ٲ�
	//static�Ⱦ��� �Ʒ����� ����ϸ� ������(����������µ� �� ����°ž�!) . static�ϸ� ���� ���� ���ִϱ� ������.
	//������ ���� static ���� ���� �̰Ŷ� �迭���� �����̶� �̸��� �������� �������� �ٸ�����.

	/*
	static Ű����� ����(static)������ �Լ� ����, �׸��� Ŭ���� ����� ���� �� ����.

	��������
	static Ű����� ���� ������ ������ �� ���ȴ�.
	���� ������ ���α׷��� ����� �� �޸𸮿� �Ҵ�Ǿ� ���α׷��� ������Ÿ�ӵ��� �����ȴ�.
	�Լ� ������ ����� ���� ������ �ش� �Լ��� ȣ��� ������ �ʱ�ȭ���� �ʰ� ���� ���� �����ȴ�.

	��������
	new��� �����ڸ� ����Ͽ� heap�� �������� �Ҵ��� ��, �ش� �޸� �ּҸ� ����Ű�� "������"�� ����.
	��)
	int *dynamicVariable = new int; // ���� ����

	�� ���� �ַ� ���� �Ҵ�� �޸𸮸� ����Ű�� �����͸� ��Ÿ��.
	���� ������ ������Ÿ���� ���α׷��Ӱ� ����� ��ģ ������������ �Ÿ𸮸� ����(delete ������)�� ������.

	���� �迭
	���� �迭�� �������� �Ҵ�� �޸𸮿��� �迭�� �����ϴ� ���� �ǹ�.
	new�����ڸ� ����Ͽ� �迭�� �������� �Ҵ��ϰ�, �ش� �迭�� ����Ű�� �����͸� ���� �迭�� ���
	��)
	int *dynamicArray = new int[10]; // ���� �迭

	��, �ֿ� �������� ���� ������ ���� ������ ����Ű�� �ݸ�, ���� �迭�� ���� ������ �̷���� �迭�� ����Ų�ٴ� ��.
	�� �� new��� �����ڸ� ����Ͽ� �������� �Ҵ�� �޸𸮸� ��������� ���� �迭�� ���� ���� ��� �迭 ���·� �Ҵ��.

	*/

public:
	static void LoadAIData();
	//void: �Լ��� ��� ���� ��ȯ���� ������ �ǹ�.
	//��, LoadAIData��� �Լ��� �ƹ��� ���� ��ȯ���� �ʴ´ٴ� ���� �ǹ�.
	//�� �Լ��� �۾��� �����ϰ� �� ����� ��ȯ���� �ʴ´ٴ� �ǹ�.

protected:
	static const FAIDataTable* FindAIData(const FName& Name);
	/*
	static: �� Ű����� �Լ��� Ŭ������ �ν��Ͻ��� ������ �ʰ� Ŭ������ ���� ����Ǿ� �ִٴ� ���� �ǹ�.
	Ŭ������ �ν��Ͻ��� ������ �ʰ� ȣ���� �� �ִ� ����(static)�Լ����� ��Ÿ��.

	const: �� Ű����� �Լ��� ȣ��� �� ��ü�� ���¸� �������� ������ ��Ÿ��.
	��, �� �Լ��� ��ü�� ��� ������ �������� ���� ��.

	FAIDataTable*: �� �κ��� �Լ��� ��ȯ�ϴ� ���� Ÿ���� ��Ÿ���ϴ�. 
	�� �Լ��� FAIDataTable ������ �����͸� ��ȯ�մϴ�. 
	�̰��� �ַ� �޸��� Ư�� ��ġ�� ����Ű�� �����ͷ� ������ �� �ֽ��ϴ�.

	FindAIData: �Լ��� �̸��Դϴ�.

	(const FName& Name): �� �κ��� �Լ��� �Ű������Դϴ�. 
	�Լ��� ȣ���� �� �ʿ��� ���� �Լ��� ������ �� ���˴ϴ�. 
	���⼭ const FName& Name�� Name�̶�� �Ű������� FName ������ ��� ������ ����Ǿ� �ֽ��ϴ�. 
	��, �Լ� ������ Name�� �������� ���� ���̸�, 
	FName�� � �̸��� ��Ÿ���� �𸮾� ������ ������ Ÿ���Դϴ�.

	����, �� �Լ��� � �̸�(Name)�� �ش��ϴ� FAIDataTable�� ã�Ƽ� 
	�ش� ������ ���̺��� �����͸� ��ȯ�ϴ� ���� �Լ��Դϴ�.	
	
	*/

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent>	mBody;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent>	mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement>	mMovement; 

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIState>	mAIState;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	TObjectPtr<class UDefaultAIAnimInstance>	mAnim;

	// ������ ��������Ʈ�� �˰� �ְ� ���ش�.
	// ��������Ʈ�� �̿��ؼ� ������ ��ü�� �ƴ� ��� None�� ���ִ�.
	TObjectPtr<class AAISpawnPoint>	mSpawnPoint;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;

	bool	mAttackEnd;
	bool	mInteractionEnd;	

	ETeam	mTeam;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class APatrolPoint>>	mPatrolPointArray;

	TArray<FVector>		mPatrolPoint;
	int32				mPatrolIndex;

	bool				mHit;
	FTimerHandle		mHitTimerHandle;
	//FTimerHandle: �ð� ��� �̺�Ʈ ó���� ���� ���Ǵ� ����ü
	//Ư�� �ð� ���� �Ǵ� ������ ���Ŀ� � �Լ��� ȣ���ϵ��� �����ϴµ� ���

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float				mDissolveTime; 

	float				mDissolveCurrentTime;
	bool				mDissolveEnable;

public:
	ETeam GetTeam() // ��ü�� ���� ���� ���¿��� �������� �� ����.
	{
		return mTeam; //��ȯ: ETeam������ ��ȯ
	}

	void SetTeam(ETeam Team) //��ü�� ���� Ư�� ������ �����ϴ� �� ����.
	{
		mTeam = Team; // �谳����: ETeam ������ ���� �޾Ƽ� �̸� mTeam�� ����.
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
		virtual float TakeDamage(float DamageAmount,
			struct FDamageEvent const& DamageEvent,
			class AController* EventInstigator, AActor* DamageCauser);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetCollisionProfile(const FName& Name);

	UFUNCTION()
	void HitTimer();

	void DeathEnd();
};
