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
	생성자
	해당 클래스의 인스턴스가 생성될 때 호출되는 특별한 멤버 함수.
	주로 클래스 멤버 변수를 초기화하거나 다른 초기화 작업을 수행하는 데 사용됨.

	언리얼 엔진에서는 GENERATED_BODY() 매크로가 클래스 선언에 사용되어야 하며, 
	이는 언리얼 엔진의 코드 생성 시스템에 필요한 정보를 제공합니다.

	* 클래스의 인스턴스가 무엇인가
	클래스: 객체를 생성하기 위한 템플릿 또는 설계도와 같은 열할 ex)붕어빵 틀
	클래스의 인스턴스: 이 클래스를 기반으로 실제로 생성된 실체 ex)붕어빵 틀에 의해 만들어지는 실제 붕어빵 

	예)
			class FishBread
		{
		public:
			int filling;  // 붕어빵 속
			FishBread()   // 붕어빵 생성자
			{
				filling = 0; // 붕어빵 속 초기화
			}
		};

		FishBread myFishBread;   // FishBread 클래스의 인스턴스 생성

		->FishBread 클래스는 붕어빵을 만들기 위한 틀
		myFishBread는 이 틀을 사용하여 만들어진 실제 붕어빵
		myFishBread는 FishBread클래스의 인스턴스.


	즉, 인스턴스는 클래스를 기반으로 생성되며, 각 인스턴스는 해당 클래스의 멤버 변수와 멤버 함수를 가지게 됨.
	클래스의 생성자는 해당 클래스의 인스턴스가 생성될 때 호출되는 특별한 함수로, 
	인스턴스가 생성될 때 초기화 작업을 수행하는데 사용됨.
		
	*/

protected:
	static TObjectPtr<UDataTable>	mAIDataTable;//프로그램이 시작될 때 static이 있는게 먼저 실행됨 그리고 중간에 못바꿈
	//static안쓰고 아래에서 사용하면 에러남(지정안해줬는데 뭘 쓰라는거야!) . static하면 가장 먼저 해주니까 가능함.
	//변수에 붙은 static 정적 동적 이거랑 배열에서 동적이랑 이름만 동적으로 같은거지 다른거임.

	/*
	static 키워드는 정적(static)변수와 함수 선언, 그리고 클래스 멤버에 사용될 수 있음.

	정적변수
	static 키워드는 정적 변수를 선언할 때 사용된다.
	정적 변수는 프로그램이 실행될 때 메모리에 할당되어 프로그램의 라이프타임동안 유지된다.
	함수 내에서 선언된 정적 변수는 해당 함수가 호출될 때마다 초기화되지 않고 이전 값이 유지된다.

	동적변수
	new라는 연산자를 사용하여 heap에 동적으로 할당한 후, 해당 메모리 주소를 가리키는 "포인터"로 사용됨.
	예)
	int *dynamicVariable = new int; // 동적 변수

	이 용어는 주로 동적 할당된 메모리를 가리키는 포인터를 나타냄.
	동적 변수의 라이프타임은 프로그래머가 사용을 마친 시점에서부터 매모리를 해제(delete 연산자)할 때까지.

	동적 배열
	동적 배열은 동적으로 할당된 메모리에서 배열을 생성하는 것을 의미.
	new연산자를 사용하여 배열을 동적으로 할당하고, 해당 배열을 가리키는 포인터를 동적 배열로 사용
	예)
	int *dynamicArray = new int[10]; // 동적 배열

	즉, 주요 차이점은 동적 변수가 단일 변수를 가리키는 반면, 동적 배열은 여러 변수로 이루어진 배열을 가리킨다는 것.
	둘 다 new라는 연산자를 사용하여 동적으로 할당된 메모리를 사용하지만 동적 배열은 여러 값을 담는 배열 형태로 할당됨.

	*/

public:
	static void LoadAIData();
	//void: 함수가 어떠한 값을 반환하지 않음을 의미.
	//즉, LoadAIData라는 함수가 아무런 값을 반환하지 않는다는 것을 의미.
	//이 함수는 작업을 수행하고 그 결과를 반환하지 않는다는 의미.

protected:
	static const FAIDataTable* FindAIData(const FName& Name);
	/*
	static: 이 키워드는 함수가 클래스의 인스턴스에 속하지 않고 클래스와 직접 연결되어 있다는 것을 의미.
	클래스의 인스턴스를 만들지 않고도 호출할 수 있는 정적(static)함수임을 나타냄.

	const: 이 키워드는 함수가 호출될 때 객체의 상태를 변경하지 않음을 나타냄.
	즉, 이 함수는 객체의 멤버 변수를 수정하지 않을 것.

	FAIDataTable*: 이 부분은 함수가 반환하는 값의 타입을 나타냅니다. 
	이 함수는 FAIDataTable 형식의 포인터를 반환합니다. 
	이것은 주로 메모리의 특정 위치를 가리키는 포인터로 생각할 수 있습니다.

	FindAIData: 함수의 이름입니다.

	(const FName& Name): 이 부분은 함수의 매개변수입니다. 
	함수를 호출할 때 필요한 값을 함수에 전달할 때 사용됩니다. 
	여기서 const FName& Name은 Name이라는 매개변수가 FName 형식의 상수 참조로 선언되어 있습니다. 
	즉, 함수 내에서 Name을 변경하지 않을 것이며, 
	FName은 어떤 이름을 나타내는 언리얼 엔진의 데이터 타입입니다.

	따라서, 이 함수는 어떤 이름(Name)에 해당하는 FAIDataTable을 찾아서 
	해당 데이터 테이블의 포인터를 반환하는 정적 함수입니다.	
	
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

	// 생성된 스폰포인트를 알고 있게 해준다.
	// 스폰포인트를 이용해서 생성한 객체가 아닐 경우 None이 들어가있다.
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
	//FTimerHandle: 시간 기반 이벤트 처리를 위해 사용되는 구조체
	//특정 시간 간격 또는 딜레이 이후에 어떤 함수를 호출하도록 예약하는데 사용

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float				mDissolveTime; 

	float				mDissolveCurrentTime;
	bool				mDissolveEnable;

public:
	ETeam GetTeam() // 객체의 팀을 현재 상태에서 가져오는 데 사용됨.
	{
		return mTeam; //반환: ETeam형식을 반환
	}

	void SetTeam(ETeam Team) //객체의 팀을 특정 값으로 설정하는 데 사용됨.
	{
		mTeam = Team; // 배개변수: ETeam 형식의 값을 받아서 이를 mTeam에 설정.
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

	//이것도 BS지우고 AB수정해준 이후에 해준건데....

	

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
	// 생성한 객체가 제거될때 호출된다.
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
