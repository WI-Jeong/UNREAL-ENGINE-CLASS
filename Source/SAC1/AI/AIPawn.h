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


	static const FAIDataTable* FindAIData(const FName& Name);
	->
	정적 함수를 선언하는 코드.
	반환 타입은 const FAIDataTable*
	함수 이름은 FindAIData
	매개변수는 const FName& Name
	->
	함수가 정적으로 선언되었기 때문에 클래스의 인스턴스를 생성하지 않고도 호출 가능
	함수가 반환하는 값은 const FAIDataTable* 타입의 포인터이며, 이것은 FAIDataTable타입의 객체를 가리키는 포인터
	이 포인터를 통해 데이터 테이블 가리킬 수 있다.

	->
	함수의 이름인 FindAIData에서는 데이터 테이블을 찾는 역할을 수행할 것으로 예상됩니다. 
	반환된 포인터가 const로 선언되어 있기 때문에 반환된 데이터 테이블을 수정하지 않는 것을 나타냅니다.
	즉, 이 코드는 정적 함수로, const FAIDataTable* 타입의 포인터를 반환하는 함수를 선언하는 것으로 보입니다.

	*/

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent>	mBody;
	/*
	이 구문은 mBody가 TObjectPtr<UCapsuleComponent> 타입의 스마트 포인터로 선언되었다는 것을 나타냅니다.
	
	스마트포인터
	스마트포인터란 포인터처럼 동작하지만 자동 메모리 관리와 같은 추가 기능을 제공하는 C++ 객체 유형입니다.
	TObjectPtr는 표준 C++ 스마트 포인터가 아니므로 코드베이스의 문맥에 따라 동작이 달라질 수 있습니다. 
	이것은 프로젝트에서 사용되는 사용자 정의 스마트 포인터 구현일 수 있습니다.
	이 경우, 어떤 클래스나 구조체에서 멤버 변수(mBody)를 선언하고 있는데, 
	이 변수가 UCapsuleComponent 타입의 객체를 가리키도록 예상됩니다.
		
	*/

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent>	mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement>	mMovement; 

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIState>	mAIState;
	//UAIState클래스 타입의 객체변수mAIState를 선언한 코드

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	TObjectPtr<class UDefaultAIAnimInstance>	mAnim;

	// 생성된 스폰포인트를 알고 있게 해준다.
	// 스폰포인트를 이용해서 생성한 객체가 아닐 경우 None이 들어가있다.
	TObjectPtr<class AAISpawnPoint>	mSpawnPoint;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterialArray;
	/*
	TArray: 언리얼엔진에서 제공하는 동적배열(dynamic array)을 나타내는 템플릿 클래스
	동적 배열은 크기를 동적으로 조절할 수 있는 배열로 필요에 따라 요소를 추가하거나 제거할 수 있다.

	즉, 간단히 말하면 TArray는 동적으로 크기가 조절되는 배열을 구현하며, 여러 가지 기능과 함께 제공됨

	이 코드는 TArray를 사용하여 TObjectPtr<UMaterialInstanceDynamic> 타입의 객체를 저장하는 배열인 mMaterialArray를 선언한 것
	각 요소는 UMaterialInstanceDynamic 클래스의 객체를 가리키는 스마트 포인터
	따라서 mMaterialArray는 UMaterialInstanceDynamic 타입의 객체들을 저장하는 배열
	*/

	bool	mAttackEnd;
	bool	mInteractionEnd;	

	ETeam	mTeam;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class APatrolPoint>>	mPatrolPointArray;

	TArray<FVector>		mPatrolPoint;
	/*
	TArray<FVector>는 언리얼엔진에서 FVector라는 3D 벡터를 나타내는 클래스의 동적 배열.
	여기서 TArray는 동적 배열 의미
	<FVector>는 배열이 저장하는 요소의 데이터 타입을 나타냄

	따라서 TArray<FVector>는 FVector타입의 요소를 저장하는 동적배열을 의미.
	이 배열은 FVector의 인스턴스들을 저장하고, 프로그램 실행 중에 배열의 크기를 동적으로 조절할 수 있다.
	
	*/
	int32				mPatrolIndex;

	bool				mHit;
	FTimerHandle		mHitTimerHandle;
	//FTimerHandle: 시간 기반 이벤트 처리를 위해 사용되는 구조체
	//구조체: 여러 개의 변수를 묶어서 새로운 데이터 타입을 만들 수 있는 C++기능 중 하나.
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
	/*
	이 코드는 C++에서 클래스의 멤버 함수인 GetAIState를 정의.

	const TObjectPtr<class UAIState>&
	-> TObjectPtr<class UAIState>타입의 참조(reference) 반환
	TObjectPtr는 언리얼 엔진에서 사용되는 스마트 포인터로, 
	여기서는 UAIState클래스의 객체를 가리키는 포인터로 사용됨.

	GetAIState() const
	->함수 이름은 GetAIState이고, 뒤에 const가 붙어 이 함수가 객체의 상태를 변경하지 않음을 의미
	즉, 이 함수는 클래스의 멤버 변수를 읽기만 하고 수정하지 않음.

	return mAIState;
	->함수가 mAIState라는 클래스의 멤버 변수를 반환
	mAIState는 TObjectPtr<class UAIState> 타입의 변수.
	즉, 이 변수가 가리키는 UAIState 객체에 대한 참조를 반환

	따라서 이 함수는 클래스의 mAIState 멤버 변수를 읽기 위한 접근자(accessor) 역할.

	함수를 호출하면 해당 객체의 mAIState 변수에 대한 참조가 반환되며, 
	반환된 참조를 통해 객체의 UAIState를 읽을 수 있습니다.

	*/

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
	/*
	GetHalfHeight 함수를 정의. 
	이 함수는 float값을 반환하며 
	반환값은 mBody라는 멤버 변수가 가리키는 객체의 GetScaledCapsuleHalfHeight 함수의 반환값
	 
	
	return mBody->GetScaledCapsuleHalfHeight();
	mBody가 가리키는 UCapsuleComponent 객체의 GetScaledCapsuleHalfHeight함수를 호출하고 (이건 위에서 변수 선언한거 보면 됨)
	그 결과를 반환하는 것.

	이 함수는 캡슐형태의 컴포넌트의 반 높이를 가져옵니다. 
	반환되는 값은 float타입. 

	즉, GetHalfHeight 함수는 해당 클래스의 mBody가 가리키는 UCapsuleComponent 객체의 반 높이를 반환하는 함수.

	*/

	float GetCapsuleRadius()	const
	{
		return mBody->GetScaledCapsuleRadius();
	}
	// 해당 클래스의 mBody가 가리키는 UCapsuleComponent 객체의 반지름을 반환하는 코드

	void SetSpawnPoint(class AAISpawnPoint* SpawnPoint);
	/*
	(class AAISpawnPoint* SpawnPoint)
	여기서
	class AAISpawnPoint*는 매개변수의 타입
	SpawnPoint는 매개변수의 이름	: 
	
	*/

	void SetAttackEnd(bool AttackEnd)
	{
		mAttackEnd = AttackEnd;
	}
	/*
	mAttackEnd = AttackEnd;
	이 코드는 클래스의 멤버 변수인 mAttackEnd에 함수의 매개변수 AttackEnd 값을 대입하는 역할
	즉, 함수를 호출하면 AttackEnd의 값이 mAttackEnd에 복사됩니다.

	따라서, 이 함수는 불리언 값을 받아서 클래스의 mAttackEnd 멤버 변수에 할당하는 간단한 세터(setter) 역할
	이런 형태의 함수는 클래스의 멤버 변수에 값을 설정하는 용도로 자주 사용됩니다.
	
	*/

	void SetInteractionEnd(bool InteractionEnd)
	{
		mInteractionEnd = InteractionEnd;
	}

protected:
	virtual void OnConstruction(const FTransform& Transform);
	/*
	virtual
	: 가상함수.
	이 키워드는 함수가 파생 클래스에서 재정의(override)될 수 있다는 것을 의미.
	가상 함수는 상속 계층 구조에서 사용되며, 
	파생 클래스에서 동일한 이름의 함수를 재정의할 수 있다.

	OnConstruction
	: 일반적으로 OnConstruction 함수는 해당 액터나 컴포넌트의 초기화 단계에서 사용됨
	에디터에서 해당 액터나 컴포넌트의 속성이 변경되거나 액터가 생성될 때 호출되고 그에 따른 작업 처리

	이 함수 사용 예시
	: 초기화 작업, 레벨 디자인에서의 렌더링 설정, 에디터에서 속성 조절할 때 해당하는 작업 수행
	  언리얼 엔진에서는 이 함수를 사용하여 에디터와 게임 실행 모드 간에 다르게 동작해야 하는 코드 처리하기도함.
	
	*/



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*
	액터의 라이프사이클 중 초기화 단계에서 호출되는 함수입니다. 
	BeginPlay 함수는 액터가 게임 세계에서 생성될 때 호출되며, 해당 액터가 게임 실행 중에 처음으로 플레이되기 시작할 때 필요한 초기화 및 시작 작업을 수행할 수 있는 기회를 제공
	이 함수는 주로 게임 플레이 시작 시 한 번만 호출되는 초기화 로직에 사용된다.
	
	*/



	// 생성한 객체가 제거될때 호출된다.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	/*
	액터의 라이프사이클 중 종료 단계에서 호출되는 함수. 
	EndPlay 함수는 액터가 게임 세계에서 제거될 때 호출되며, 해당 액터가 게임에서 더 이상 플레이되지 않을 때 필요한 정리 작업을 수행할 수 있는 기회를 제공
	EndPlayReason 매개변수는 액터가 종료된 이유를 나타냄
	
	*/

public:
		virtual float TakeDamage(float DamageAmount,
			struct FDamageEvent const& DamageEvent,
			class AController* EventInstigator, AActor* DamageCauser);
		/*
		매개변수
		float DamageAmount: 
		액터가 받을 데미지 양.
		float타입이기 때문에 실수값을 받을 수 있다.

		struct FDamageEvent const& DamageEvent:
		어떤 종류의 데미지 이벤트가 발생했는지를 나타내는 구조체(FDamageEvent)에 대한 참조


		class AController* EventInstigator:
		데미지 이벤트를 일으킨 AController 타입의 컨트롤러

		AActor* DamageCauser: 
		데미지를 일으킨 액터 자체
		예를 들어, 어떤 무기에 의해 발생한 데미지의 경우, 이 매개변수는 해당 무기


		->
		이 함수는 액터가 데미지를 받을 때 호출되어 데미지 처리를 수행하고, 
		처리된 데미지의 양을 반환하는 역할을 합니다. 
		이를 통해 액터는 데미지를 받았을 때 특별한 동작을 수행하거나 게임 상태를 변경할 수 있습니다.	
		
		
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

여기서 사용된 함수들

OnConstruction()
사용 시점: 해당 액터가 레벨에 배치되거나 에디터에서 속성이 변경될 때 호출
예시: 액터의 초기화나 속성 변경에 사용될 수 있다.
예를 들어, 초기화 로직이나 에디터에서 변경된 값을 반영하는 용도로 사용됨.


BeginPlay()
사용 시점: 액터가 게임 세계에 처음으로 등장하여 플레이되기 시작할 때 호출
예시: 액터가 게임에 등장하면서 필요한 초기화 작업이나 게임 플레이에 필요한 설정을 수행


EndPlay()
사용 시점: 액터가 게임 세계에서 제거되어 종료될 때 호출
예시: 액터가 게임에서 제거될 때 필요한 정리 작업이나 종료 관련 동작을 수행


TakeDamage()
사용 시점: 액터가 데미지를 받았을 때 호출
예시: 액터가 데미지를 받았을 때 어떻게 반응할지를 처리하는 로직에 사용됨.
예를 들어, 데미지를 받으면 체력을 감소시키고, 체력이 다 소진되면 사망 처리를 수행할 수 있다.


Tick()
사용 시점: 게임의 각 프레임마다 호출
예시: 매 프레임마다 실행되는 로직에 사용됨.
예를 들어, 액터의 이동, 상태 감지, 애니메이션 업데이트 등을 매 프레임마다 수행할 수 있다.


SetCollisionProfile()
사용 시점: 충돌 프로파일을 설정할 때 사용됨.
예시: 액터의 충돌 동작을 정의할 때, 충돌 프로파일을 설정하여 어떤 종류의 충돌 동작을 할지 결정할 수 있다.

.
HitTimer()
사용 시점: 특정 시간 동안 일정한 간격으로 호출됨.
예시: 타이머 이벤트로, 특정 시간 간격마다 어떤 동작을 수행할 때 사용됨.


DeathEnd()
사용 시점: 액터가 사망했을 때 호출
예시: 액터가 사망했을 때의 처리를 정의
예를 들어, 애니메이션 재생 종료, 사망 이펙트 표시, 리스폰 로직 등을 수행할 수 있다.

*/