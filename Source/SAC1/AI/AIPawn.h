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


	static const FAIDataTable* FindAIData(const FName& Name);
	->
	���� �Լ��� �����ϴ� �ڵ�.
	��ȯ Ÿ���� const FAIDataTable*
	�Լ� �̸��� FindAIData
	�Ű������� const FName& Name
	->
	�Լ��� �������� ����Ǿ��� ������ Ŭ������ �ν��Ͻ��� �������� �ʰ� ȣ�� ����
	�Լ��� ��ȯ�ϴ� ���� const FAIDataTable* Ÿ���� �������̸�, �̰��� FAIDataTableŸ���� ��ü�� ����Ű�� ������
	�� �����͸� ���� ������ ���̺� ����ų �� �ִ�.

	->
	�Լ��� �̸��� FindAIData������ ������ ���̺��� ã�� ������ ������ ������ ����˴ϴ�. 
	��ȯ�� �����Ͱ� const�� ����Ǿ� �ֱ� ������ ��ȯ�� ������ ���̺��� �������� �ʴ� ���� ��Ÿ���ϴ�.
	��, �� �ڵ�� ���� �Լ���, const FAIDataTable* Ÿ���� �����͸� ��ȯ�ϴ� �Լ��� �����ϴ� ������ ���Դϴ�.

	*/

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent>	mBody;
	/*
	�� ������ mBody�� TObjectPtr<UCapsuleComponent> Ÿ���� ����Ʈ �����ͷ� ����Ǿ��ٴ� ���� ��Ÿ���ϴ�.
	
	����Ʈ������
	����Ʈ�����Ͷ� ������ó�� ���������� �ڵ� �޸� ������ ���� �߰� ����� �����ϴ� C++ ��ü �����Դϴ�.
	TObjectPtr�� ǥ�� C++ ����Ʈ �����Ͱ� �ƴϹǷ� �ڵ庣�̽��� ���ƿ� ���� ������ �޶��� �� �ֽ��ϴ�. 
	�̰��� ������Ʈ���� ���Ǵ� ����� ���� ����Ʈ ������ ������ �� �ֽ��ϴ�.
	�� ���, � Ŭ������ ����ü���� ��� ����(mBody)�� �����ϰ� �ִµ�, 
	�� ������ UCapsuleComponent Ÿ���� ��ü�� ����Ű���� ����˴ϴ�.
		
	*/

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent>	mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement>	mMovement; 

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIState>	mAIState;
	//UAIStateŬ���� Ÿ���� ��ü����mAIState�� ������ �ڵ�

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	TObjectPtr<class UDefaultAIAnimInstance>	mAnim;

	// ������ ��������Ʈ�� �˰� �ְ� ���ش�.
	// ��������Ʈ�� �̿��ؼ� ������ ��ü�� �ƴ� ��� None�� ���ִ�.
	TObjectPtr<class AAISpawnPoint>	mSpawnPoint;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;
	/*
	TArray: �𸮾������� �����ϴ� �����迭(dynamic array)�� ��Ÿ���� ���ø� Ŭ����
	���� �迭�� ũ�⸦ �������� ������ �� �ִ� �迭�� �ʿ信 ���� ��Ҹ� �߰��ϰų� ������ �� �ִ�.

	��, ������ ���ϸ� TArray�� �������� ũ�Ⱑ �����Ǵ� �迭�� �����ϸ�, ���� ���� ��ɰ� �Բ� ������

	�� �ڵ�� TArray�� ����Ͽ� TObjectPtr<UMaterialInstanceDynamic> Ÿ���� ��ü�� �����ϴ� �迭�� mMaterialArray�� ������ ��
	�� ��Ҵ� UMaterialInstanceDynamic Ŭ������ ��ü�� ����Ű�� ����Ʈ ������
	���� mMaterialArray�� UMaterialInstanceDynamic Ÿ���� ��ü���� �����ϴ� �迭
	*/

	bool	mAttackEnd;
	bool	mInteractionEnd;	

	ETeam	mTeam;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class APatrolPoint>>	mPatrolPointArray;

	TArray<FVector>		mPatrolPoint;
	/*
	TArray<FVector>�� �𸮾������� FVector��� 3D ���͸� ��Ÿ���� Ŭ������ ���� �迭.
	���⼭ TArray�� ���� �迭 �ǹ�
	<FVector>�� �迭�� �����ϴ� ����� ������ Ÿ���� ��Ÿ��

	���� TArray<FVector>�� FVectorŸ���� ��Ҹ� �����ϴ� �����迭�� �ǹ�.
	�� �迭�� FVector�� �ν��Ͻ����� �����ϰ�, ���α׷� ���� �߿� �迭�� ũ�⸦ �������� ������ �� �ִ�.
	
	*/
	int32				mPatrolIndex;

	bool				mHit;
	FTimerHandle		mHitTimerHandle;
	//FTimerHandle: �ð� ��� �̺�Ʈ ó���� ���� ���Ǵ� ����ü
	//����ü: ���� ���� ������ ��� ���ο� ������ Ÿ���� ���� �� �ִ� C++��� �� �ϳ�.
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
	/*
	�� �ڵ�� C++���� Ŭ������ ��� �Լ��� GetAIState�� ����.

	const TObjectPtr<class UAIState>&
	-> TObjectPtr<class UAIState>Ÿ���� ����(reference) ��ȯ
	TObjectPtr�� �𸮾� �������� ���Ǵ� ����Ʈ �����ͷ�, 
	���⼭�� UAIStateŬ������ ��ü�� ����Ű�� �����ͷ� ����.

	GetAIState() const
	->�Լ� �̸��� GetAIState�̰�, �ڿ� const�� �پ� �� �Լ��� ��ü�� ���¸� �������� ������ �ǹ�
	��, �� �Լ��� Ŭ������ ��� ������ �б⸸ �ϰ� �������� ����.

	return mAIState;
	->�Լ��� mAIState��� Ŭ������ ��� ������ ��ȯ
	mAIState�� TObjectPtr<class UAIState> Ÿ���� ����.
	��, �� ������ ����Ű�� UAIState ��ü�� ���� ������ ��ȯ

	���� �� �Լ��� Ŭ������ mAIState ��� ������ �б� ���� ������(accessor) ����.

	�Լ��� ȣ���ϸ� �ش� ��ü�� mAIState ������ ���� ������ ��ȯ�Ǹ�, 
	��ȯ�� ������ ���� ��ü�� UAIState�� ���� �� �ֽ��ϴ�.

	*/

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
	/*
	GetHalfHeight �Լ��� ����. 
	�� �Լ��� float���� ��ȯ�ϸ� 
	��ȯ���� mBody��� ��� ������ ����Ű�� ��ü�� GetScaledCapsuleHalfHeight �Լ��� ��ȯ��
	 
	
	return mBody->GetScaledCapsuleHalfHeight();
	mBody�� ����Ű�� UCapsuleComponent ��ü�� GetScaledCapsuleHalfHeight�Լ��� ȣ���ϰ� (�̰� ������ ���� �����Ѱ� ���� ��)
	�� ����� ��ȯ�ϴ� ��.

	�� �Լ��� ĸ�������� ������Ʈ�� �� ���̸� �����ɴϴ�. 
	��ȯ�Ǵ� ���� floatŸ��. 

	��, GetHalfHeight �Լ��� �ش� Ŭ������ mBody�� ����Ű�� UCapsuleComponent ��ü�� �� ���̸� ��ȯ�ϴ� �Լ�.

	*/

	float GetCapsuleRadius()	const
	{
		return mBody->GetScaledCapsuleRadius();
	}
	// �ش� Ŭ������ mBody�� ����Ű�� UCapsuleComponent ��ü�� �������� ��ȯ�ϴ� �ڵ�

	void SetSpawnPoint(class AAISpawnPoint* SpawnPoint);
	/*
	(class AAISpawnPoint* SpawnPoint)
	���⼭
	class AAISpawnPoint*�� �Ű������� Ÿ��
	SpawnPoint�� �Ű������� �̸�	: 
	
	*/

	void SetAttackEnd(bool AttackEnd)
	{
		mAttackEnd = AttackEnd;
	}
	/*
	mAttackEnd = AttackEnd;
	�� �ڵ�� Ŭ������ ��� ������ mAttackEnd�� �Լ��� �Ű����� AttackEnd ���� �����ϴ� ����
	��, �Լ��� ȣ���ϸ� AttackEnd�� ���� mAttackEnd�� ����˴ϴ�.

	����, �� �Լ��� �Ҹ��� ���� �޾Ƽ� Ŭ������ mAttackEnd ��� ������ �Ҵ��ϴ� ������ ����(setter) ����
	�̷� ������ �Լ��� Ŭ������ ��� ������ ���� �����ϴ� �뵵�� ���� ���˴ϴ�.
	
	*/

	void SetInteractionEnd(bool InteractionEnd)
	{
		mInteractionEnd = InteractionEnd;
	}

protected:
	virtual void OnConstruction(const FTransform& Transform);
	/*
	virtual
	: �����Լ�.
	�� Ű����� �Լ��� �Ļ� Ŭ�������� ������(override)�� �� �ִٴ� ���� �ǹ�.
	���� �Լ��� ��� ���� �������� ���Ǹ�, 
	�Ļ� Ŭ�������� ������ �̸��� �Լ��� �������� �� �ִ�.

	OnConstruction
	: �Ϲ������� OnConstruction �Լ��� �ش� ���ͳ� ������Ʈ�� �ʱ�ȭ �ܰ迡�� ����
	�����Ϳ��� �ش� ���ͳ� ������Ʈ�� �Ӽ��� ����ǰų� ���Ͱ� ������ �� ȣ��ǰ� �׿� ���� �۾� ó��

	�� �Լ� ��� ����
	: �ʱ�ȭ �۾�, ���� �����ο����� ������ ����, �����Ϳ��� �Ӽ� ������ �� �ش��ϴ� �۾� ����
	  �𸮾� ���������� �� �Լ��� ����Ͽ� �����Ϳ� ���� ���� ��� ���� �ٸ��� �����ؾ� �ϴ� �ڵ� ó���ϱ⵵��.
	
	*/



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*
	������ ����������Ŭ �� �ʱ�ȭ �ܰ迡�� ȣ��Ǵ� �Լ��Դϴ�. 
	BeginPlay �Լ��� ���Ͱ� ���� ���迡�� ������ �� ȣ��Ǹ�, �ش� ���Ͱ� ���� ���� �߿� ó������ �÷��̵Ǳ� ������ �� �ʿ��� �ʱ�ȭ �� ���� �۾��� ������ �� �ִ� ��ȸ�� ����
	�� �Լ��� �ַ� ���� �÷��� ���� �� �� ���� ȣ��Ǵ� �ʱ�ȭ ������ ���ȴ�.
	
	*/



	// ������ ��ü�� ���ŵɶ� ȣ��ȴ�.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	/*
	������ ����������Ŭ �� ���� �ܰ迡�� ȣ��Ǵ� �Լ�. 
	EndPlay �Լ��� ���Ͱ� ���� ���迡�� ���ŵ� �� ȣ��Ǹ�, �ش� ���Ͱ� ���ӿ��� �� �̻� �÷��̵��� ���� �� �ʿ��� ���� �۾��� ������ �� �ִ� ��ȸ�� ����
	EndPlayReason �Ű������� ���Ͱ� ����� ������ ��Ÿ��
	
	*/

public:
		virtual float TakeDamage(float DamageAmount,
			struct FDamageEvent const& DamageEvent,
			class AController* EventInstigator, AActor* DamageCauser);
		/*
		�Ű�����
		float DamageAmount: 
		���Ͱ� ���� ������ ��.
		floatŸ���̱� ������ �Ǽ����� ���� �� �ִ�.

		struct FDamageEvent const& DamageEvent:
		� ������ ������ �̺�Ʈ�� �߻��ߴ����� ��Ÿ���� ����ü(FDamageEvent)�� ���� ����


		class AController* EventInstigator:
		������ �̺�Ʈ�� ����Ų AController Ÿ���� ��Ʈ�ѷ�

		AActor* DamageCauser: 
		�������� ����Ų ���� ��ü
		���� ���, � ���⿡ ���� �߻��� �������� ���, �� �Ű������� �ش� ����


		->
		�� �Լ��� ���Ͱ� �������� ���� �� ȣ��Ǿ� ������ ó���� �����ϰ�, 
		ó���� �������� ���� ��ȯ�ϴ� ������ �մϴ�. 
		�̸� ���� ���ʹ� �������� �޾��� �� Ư���� ������ �����ϰų� ���� ���¸� ������ �� �ֽ��ϴ�.	
		
		
		*/

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetCollisionProfile(const FName& Name);

	UFUNCTION()
	void HitTimer();

	void DeathEnd();
};


/*

���⼭ ���� �Լ���

OnConstruction()
��� ����: �ش� ���Ͱ� ������ ��ġ�ǰų� �����Ϳ��� �Ӽ��� ����� �� ȣ��
����: ������ �ʱ�ȭ�� �Ӽ� ���濡 ���� �� �ִ�.
���� ���, �ʱ�ȭ �����̳� �����Ϳ��� ����� ���� �ݿ��ϴ� �뵵�� ����.


BeginPlay()
��� ����: ���Ͱ� ���� ���迡 ó������ �����Ͽ� �÷��̵Ǳ� ������ �� ȣ��
����: ���Ͱ� ���ӿ� �����ϸ鼭 �ʿ��� �ʱ�ȭ �۾��̳� ���� �÷��̿� �ʿ��� ������ ����


EndPlay()
��� ����: ���Ͱ� ���� ���迡�� ���ŵǾ� ����� �� ȣ��
����: ���Ͱ� ���ӿ��� ���ŵ� �� �ʿ��� ���� �۾��̳� ���� ���� ������ ����


TakeDamage()
��� ����: ���Ͱ� �������� �޾��� �� ȣ��
����: ���Ͱ� �������� �޾��� �� ��� ���������� ó���ϴ� ������ ����.
���� ���, �������� ������ ü���� ���ҽ�Ű��, ü���� �� �����Ǹ� ��� ó���� ������ �� �ִ�.


Tick()
��� ����: ������ �� �����Ӹ��� ȣ��
����: �� �����Ӹ��� ����Ǵ� ������ ����.
���� ���, ������ �̵�, ���� ����, �ִϸ��̼� ������Ʈ ���� �� �����Ӹ��� ������ �� �ִ�.


SetCollisionProfile()
��� ����: �浹 ���������� ������ �� ����.
����: ������ �浹 ������ ������ ��, �浹 ���������� �����Ͽ� � ������ �浹 ������ ���� ������ �� �ִ�.

.
HitTimer()
��� ����: Ư�� �ð� ���� ������ �������� ȣ���.
����: Ÿ�̸� �̺�Ʈ��, Ư�� �ð� ���ݸ��� � ������ ������ �� ����.


DeathEnd()
��� ����: ���Ͱ� ������� �� ȣ��
����: ���Ͱ� ������� ���� ó���� ����
���� ���, �ִϸ��̼� ��� ����, ��� ����Ʈ ǥ��, ������ ���� ���� ������ �� �ִ�.

*/