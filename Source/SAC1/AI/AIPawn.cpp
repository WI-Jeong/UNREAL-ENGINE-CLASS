// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "AISpawnPoint.h"
#include "DefaultAIController.h"
#include "AIState.h"
#include "DefaultAIAnimInstance.h" //이건 BS지우고 AB수정해준 이후인데...

TObjectPtr<UDataTable>	AAIPawn::mAIDataTable;
/*
TObjectPtr: 자동으로 메모리 관리를 해주는 포인터

UDataTable은 언리얼 엔진에서 데이터 테이블을 나타내는 클래스로, 
여러 행과 열로 이루어진 데이터를 저장하고 관리하는 데 사용됨.

AAIPawn::mAIDataTable에서 ::는 범위 지정 연산자.
범위 지정 연산자는 특정 범위 내에 있는 멤버나 변수에 접근할 때 사용됨.
즉, AAIPawn 클래스 내부의 mAIDataTable에 접근할 때 사용되는 범위 지정 연산자.

즉, AAIPawn::mAIDataTable
AAIPawn 클래스에 속한 정적 멤버 변수 mAIDataTable에 접근하는 것입니다.
클래스의 정적 멤버 변수는 해당 클래스의 모든 객체에서 공유되는 변수이므로, 
클래스 이름과 범위 지정 연산자를 사용하여 접근함.

*/

// Sets default values
AAIPawn::AAIPawn()
//생성자: 해당 클래스의 객체가 생성될 때 호출되는 함수. & 초기화 작업 수행
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	PrimaryActorTick.bCanEverTick = true;
	해당 액터가 틱(tick) 기능을 사용할 것인지를 설정하는 부분
	틱(thik)은 게임의 각 프레임에서 호출되는 함수로, 게임 로직을 주기적으로 업데이트하는 데 사용.

	PrimaryActorTick은 언리얼 엔진의 AActor 클래스에 정의된 구조체
	이 구조체는 액터의 틱에 관련된 속성을 나타냄.

	bCanEverTick은 틱 기능을 활성화할지 여부를 나타내는 부울(boolean) 값

	즉, 해당 코드는 액터가 틱을 사용할 수 있도록 설정하는 역할
	틱은 게임의 각 프레임에서 호출되는 함수를 의미하며 게임 로직을 주기적으로 업데이트하고 처리하는 데 사용됨.
	true; 이므로 해당 액터가 게임 프레임마다 업데이트를 수행하도록 허용한다는 의미

	이 코드가 없으면 액터는 틱 함수를 호출받지 않고, 
	특정 상황에서는 게임의 로직이나 상태 업데이트가 이루어지지 않을 수 있음.	
	
	*/

	mAttackEnd = false;
	mInteractionEnd = false;
	/*
	멤버변수 mAttackEnd와 mInteractionEnd를 초기화
	이들 변수는 액터의 공격이 종료되었는지, 상호 작용이 종료되었는지 여부를 나타내는 불리언 값

	false면 공격이 종료되지 않았고 상호작용도 종료되지 않았다..? 생성자부터 만들었는데..?
	아직 공격이랑 상호작용 관련 코드도 없는데..?
	->초기화는 단순히 변수를 특정 값으로 설정하는 것. 실제로 어떤 동작을 수행하지 않음.
	따라서 생성자에서 이 두 변수를 false로 초기화한 상태에서는 특정 로직이나 이벤트가 발생하지 않는 이상 
	공격이나 상호작용이 종료된 것은 아님.
	이 변수들은 초기화된 상태에서 다른 부분에서 특정 조건이나 이벤트에 따라 변경될 것.
	초기화는 해당 변수들을 어떤 상태로 시작할 지 정의하는 것이며, 실제 동작은 이후의 로직에 따라 결정됨.
	따라서, 해당 코드에서는 아직 공격종료되지않음과 아직 상호작용 종료되지 않음을 초기 상태로 설정하고, 
	나중에 특정 조건에서 이 값들이 변경되도록 다른 로직이 추가될 것임.
	->
	나중에 특정 이벤트나 조건에 따라 값을 변경해야 한다면, 
	생성자 이외의 메서드나 함수에서 해당 변수들을 사용하고 변경해도 됨.
	
	챗지피티에 
	"생성자에 mAttackEnd변수를 아예 쓰지않고 AttackEnd함수 따로 만들어서 if() {} 이건 ()안의 조건이 true일 때 {}안의 코드 실행하니까
    AttackEnd함수에서 if (mAttackEnd)하고 {}안에 idle애니메이션으로 바꾸는 코드 넣으면 안되?"
    라고 질문함.
    ->가능하다고 답함.

	예시코드
					void AAIPawn::AttackEnd()
				{
					if (mAttackEnd)
					{
						// 이미 공격이 종료된 상태일 때의 동작
						// 예를 들어, idle 애니메이션으로 전환하는 코드
					}
					else
					{
						// 공격이 종료되지 않은 상태일 때의 동작
						// 예를 들어, 현재 공격 애니메이션을 idle 애니메이션으로 변경하는 코드

						// ...

						// 공격이 종료되었음을 표시
						mAttackEnd = true;
					}
				}

		->
		이렇게 하면 AttackEnd 함수 내에서 현재 공격이 종료되었는지 확인하고, 
		종료되지 않았다면 공격 애니메이션을 idle 애니메이션으로 변경하고 
		mAttackEnd 값을 true로 설정합니다. 
		이렇게 하면 생성자에서 mAttackEnd를 초기화해도 되고, 
		나중에 특정 조건에서 변경하는 것도 가능합니다.

	*/


	//Controller의 Yaw 회전에 매칭한다.
	//bUseControllerRotationYaw = true;
	//->액터가 Yaw 회전을 컨트롤러의 회전에 사용할지 여부를 설정
	//Roll X축 , Pitch Y축, Yaw Z축
	//https://m.blog.naver.com/milkysc/221754450137 gif로 이해하기.


	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	//UCapsuleComponent 타입의 mBody 멤버 변수를 생성 
	//이는 액터의 몸체를 나타내는 캡슐 컴포넌트

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//USkeletalMeshComponent 타입의 mMesh 멤버 변수를 생성
	//이는 액터의 스켈레톤 메쉬를 나타내는 스켈레톤 메쉬 컴포넌트


	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	//UFloatingPawnMovement 타입의 mMovement 멤버 변수를 생성
	//이는 액터의 움직임을 관리하는 컴포넌트

	mAIState = CreateDefaultSubobject<UAIState>(TEXT("AIState"));
	//UAIState 타입의 mAIState 멤버 변수를 생성
	//이는 액터의 AI 상태를 나타내는 컴포넌트

	SetRootComponent(mBody);
	mMesh->SetupAttachment(mBody);
	mMovement->SetUpdatedComponent(mBody);
	/*
	SetupAttachment 함수는 부모-자식 관계 설정 시 사용됨.
	특히, 어떤 컴포넌트를 다른 컴포넌트에 부착할 때 사용.
	부착된 컴포넌트는 부모 컴포넌트에 상대적으로 위치가 결정되며,
	부모컴포넌트가 이동하면 자식 컴포넌트도 함께 이동
	따라서, mMesh->SetupAttachment(mBody); 이 코드는 mMesh를 mBody에 부착하겠다는 의미.
	즉, mMesh는 mBody의 자식으로 설정되어 mBody의 움직임에 영향을 받는다.


	SetUpdatedComponent 함수는 특정 컴포넌트를 업데이트 대상으로 설정하는 데 사용됨.
	이 함수를 사용하면 해당 컴포넌트의 물리적인 이동 및 충돌 검사 등이 엔진에 의해 관리되게 됨.
	mMovement->SetUpdatedComponent(mBody); 이 코드는 mMovement를 mBody의 업데이트 대상으로 설정하겠다는 의미
	따라서 mBody의 이동은 mMovement에 의해 관리됨.
		
	*/

	mBody->SetCollisionProfileName(TEXT("AI"));
	//mBody 캡슐 컴포넌트의 충돌 프로파일을 "AI"로 설정
	
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//mMesh 스켈레톤 메쉬 컴포넌트의 충돌을 비활성화


	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	/*
	EAutoPossessAI 열거형은 언리얼 엔진에서 AI를 자동으로 소유할지를 설정하는 데 사용

	None: AI를 자동으로 소유하지 않음. 수동으로 AI를 설정해야 합니다.
	Player: 플레이어 컨트롤러에 의해 소유되는 AI로 설정됨.->주로 플레이어가 조작하는 캐릭터나 유닛 등에 사용됨.
	AI: 게임 시작 시 AI 컨트롤러에 의해 소유되는 AI로 설정됨.->특별한 조건 없이 게임 시작과 동시에 AI 컨트롤러가 소유
	PlacedInWorld: 액터가 월드에 배치되면 AI 컨트롤러에 의해 소유됨.
	
	PlacedInWorldOrSpawned: 액터가 월드에 배치되거나 스폰될 때 AI 컨트롤러에 의해 소유됨. 
	게임 실행 중에도 스폰된 경우 AI가 자동으로 활성화됨. 
	즉, 이 옵션을 선택하면 해당 액터가 게임 월드에 나타날 때마다 AI가 자동으로 활성화됩니다.	
	*/

	AIControllerClass = ADefaultAIController::StaticClass();
	/*
	
	ADefaultAIController::StaticClass()는 ADefaultAIController 클래스의 타입을 나타내는 언리얼 엔진의 메타클래스를 반환하는 함수
	이 클래스는 기본적인 AI 컨트롤러로 사용됨.

	좀 더 설명을 하자면,
	AI 컨트롤러란 AI 캐릭터나 유닛 등을 제어하는 데 사용되는 클래스
	이 컨트롤러는 AI의 행동 및 의사 결정을 관리하고 해당 AI를 조작


	ADefaultAIController::StaticClass()
	ADefaultAIController는 언리얼 엔진에서 제공하는 기본 AI 컨트롤러 클래스
	StaticClass() 함수는 해당 클래스의 메타클래스를 반환
	메타클래스는 클래스 자체를 나타내는 런타임 정보를 제공


	AIControllerClass는 액터가 어떤 AI 컨트롤러 클래스를 사용할지를 결정하는 속성
	특정 AI 컨트롤러를 사용하려면 해당 클래스의 메타클래스를 AIControllerClass에 설정해야 함.

	예를 들어, ADefaultAIController 클래스를 사용하지 않고 사용자 정의한 AI 컨트롤러 클래스를 사용하려면
	AIControllerClass = UMyCustomAIController::StaticClass();
	여기서 UMyCustomAIController는 사용자가 만든 AI 컨트롤러 클래스
	이렇게 함으로써 액터는 UMyCustomAIController를 사용하여 AI를 제어하게 됨.


	대부분의 경우에는 StaticClass()를 사용하며, 
	특별한 상황이나 사용자 정의된 클래스 메타클래스 처리가 필요한 경우에는 다른 함수를 사용할 수 있다.
	하지만 이는 특정 상황과 사용자 코드에 따라 달라진다.

	*/

	mTeam = ETeam::Team2; //2번팀 지정. 즉, 플레이어랑 ai랑 팀 다르게 지정한거임 


	mHit = false;
	/*
	어떤 충돌이나 히트 여부를 나타낼 수 있다.
	초기값을 false로 설정하면 처음에는 어떤 충돌도 발생하지 않은 상태로 시작한다는 의미
	
	*/

	mMesh->bRenderCustomDepth = true;
	/*
	bRenderCustomDepth는 언리얼 엔진에서 제공하는 커스텀 깊이 렌더링을 사용할지 여부를 나타내는 부울(boolean) 속성
	깊이 렌더링은 일반적으로 화면에 표시되는 물체들의 깊이를 계산하여 화면에 어떻게 그려질지를 결정하는 렌더링 기술

	bRenderCustomDepth를 true로 설정하면 해당 메쉬는 기본적인 깊이 렌더링 대신에 사용자가 정의한 커스텀 깊이 값을 사용.
	이는 시각적 효과를 부여하거나 특정 렌더링 기술을 적용하는 데 사용될 수 있다.
		
	*/

	//0~255사이의 원하는 값을 넣어준다.
	mMesh->SetCustomDepthStencilValue(0);
	/*
	SetCustomDepthStencilValue 함수는 커스텀 깊이 스텐실 값을 설정하는 함수
	깊이 스텐실은 일반적으로 깊이 버퍼와 함께 사용되어 렌더링 파이프라인에서 특정 오브젝트에 대한 추가적인 제어를 제공
	커스텀 깊이 스텐실 값은 주로 시각적 효과를 부여하거나 렌더링에 특정 효과를 추가하는 데 사용된다.

	SetCustomDepthStencilValue()
	커스텀 깊이 스텐실 값을 설정할 때는 주로 0에서 255 사이의 값을 사용

	SetCustomDepthStencilValue(0)과 SetCustomDepthStencilValue(255)

	SetCustomDepthStencilValue(0)
	->커스텀 깊이 스텐실에서 가장 앞쪽에 위치
	일반적으로 오브젝트를 나타내는데 사용
	즉, 이 값이 설정된 오브젝트는 일반적인 렌더링에 참여
	

	SetCustomDepthStencilValue(255)
	-> 커스텀 깊이 스텐실에서 가장 뒤쪽에 위치
	일반적으로 렌더링에 참여하지 않는 오브젝트, 예를 들어 화면 뒤의 배경 등에 사용될 수 있다.

	즉,
	값이 클수록 해당 오브젝트는 뒤로, 작을수록 앞으로 위치
	이를 통해 사용자는 커스텀 깊이 스텐실을 활용하여 시각적인 효과를 달리할 수 있다.
	
	*/

	/*
	mDissolveCurrentTime = 0.f;
	->어떤 물체가 해체되는(dissolve) 효과를 구현할 때 사용
	해당 효과의 현재 경과 시간

	mDissolveTime = 3.f;
	->해체 효과를 완료하는 데 걸리는 전체 시간
	즉, mDissolveCurrentTime이 mDissolveTime에 도달하면 해당 효과가 완전히 적용

	mDissolveEnable = false;
	->해당 물체에 해체 효과를 활성화할지 여부를 나타내는 것
	false로 초기화되어 있으므로, 초기에는 해당 효과가 비활성화
	즉, 어떤 해체 효과나 행동이 활성화되어 있지 않다
	
	*/


}


//void AAIPawn::LoadAIData()
//{
//	mAIDataTable = LoadObject< UDataTable>(nullptr,TEXT("/Script/Engine.DataTable'/Game/Data/DT_AIData.DT_AIData'"));
//
//}

void AAIPawn::LoadAIData()
{
	mAIDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Script/Engine.DataTable'/Game/Data/DT_AIData.DT_AIData'"));
}
/*
LoadAIData 이 함수는 AAIPawn 클래스의 멤버 함수로 선언되어 있다.
함수의 목적은 아마도 어떤 AI 데이터를 로드하는 것

mAIDataTable
이 함수에서 사용되는 mAIDataTable은 UDataTable 타입의 멤버 변수
데이터 테이블은 언리얼 엔진에서 구조화된 데이터를 저장하고 관리하는 데 사용되는 자료구조
즉, LoadAIData 함수에서 AI 관련 데이터를 담은 데이터 테이블을 로드하고자 하는 것

LoadObject<UDataTable>(nullptr, TEXT(""))
UDataTable 타입의 오브젝트를 로드하는 엔진 함수
LoadObject 함수는 특정 클래스 타입의 오브젝트를 로드하는 데 사용됨. 여기서는 UDataTable 타입을 로드

첫 번째 매개변수인 nullptr는 로드할 오브젝트의 경로. 
nullptr로 지정하면 기본 경로에서 해당 클래스 타입의 오브젝트를 찾아 로드

두 번째 매개변수인 TEXT("")는 로드할 오브젝트의 경로를 나타내는 문자열


결과적으로, LoadAIData 함수는 UDataTable 타입의 데이터를 로드하여 mAIDataTable에 할당하려는 것

*/

const FAIDataTable* AAIPawn::FindAIData(const FName& Name)
{ 
	return mAIDataTable->FindRow<FAIDataTable>(Name, TEXT(""));
}
/*
함수의 목적은 특정 이름(Name)에 해당하는 AI 데이터를 찾아 반환하는 것

매개변수 const FName& Name
FName 타입의 변수
어떤 식별자나 이름을 나타냄

mAIDataTable->FindRow<FAIDataTable>(Name, TEXT(""))
->mAIDataTable이라는 UDataTable 타입의 멤버 변수에서 특정 행을 찾는 엔진 함수를 호출

FindRow<FAIDataTable>(Name, TEXT(""))
->데이터 테이블에서 특정 행을 찾아 반환하는 함수

FAIDataTable은 찾고자 하는 행의 구조체 타입으로, 
이 행이 어떤 형식의 데이터를 담고 있는지를 나타냄

Name은 찾고자 하는 행의 식별자나 이름

const FAIDataTable*
함수의 반환 타입은 const FAIDataTable*으로 찾은 행의 데이터를 나타내는 FAIDataTable 구조체에 대한 포인터를 반환
반환된 포인터가 nullptr일 경우 해당 행을 찾지 못한 것

따라서, 이 함수는 mAIDataTable에서 특정 이름에 해당하는 AI 데이터를 찾아서 그 데이터에 대한 포인터를 반환하는 것
함수의 완전한 동작은 함수가 호출되는 곳이나 함수가 속한 클래스의 다른 부분에서 확인할 수 있음.


*/



void AAIPawn::SetSpawnPoint(AAISpawnPoint* SpawnPoint)
{
	mSpawnPoint = SpawnPoint;
}
/*
SetSpawnPoint 함수: 함수의 목적은 AI 캐릭터의 스폰 지점 설정

매개변수 SpawnPoint
:함수는 AAISpawnPoint* SpawnPoint라는 포인터 타입의 매개변수를 받는다.
이는 AAISpawnPoint 클래스 또는 그의 파생 클래스의 객체를 가리키는 포인터

mSpawnPoint
: mSpawnPoint는 AAISpawnPoint* 타입의 멤버 변수
이 함수에서는 함수의 매개변수 SpawnPoint로 전달된 값을 mSpawnPoint에 할당하고 있다

따라서
이 함수의 주요 역할은 주어진 스폰 지점 객체를 mSpawnPoint에 할당하여 
나중에 이를 사용할 수 있도록 하는 것

*/


/*
Patrol부분 빠진거. 

void AAIPawn::SetPatrolPointArray(
	const TArray<TObjectPtr<class APatrolPoint>>& Array)
{
	mPatrolPointArray = Array;

	mPatrolPoint.Add(mSpawnPoint->GetActorLocation());

	for (auto& Point : mPatrolPointArray)
	{
		mPatrolPoint.Add(Point->GetActorLocation());
	}
}

-->>
SetPatrolPointArray 함수의 목적은 AI 캐릭터의 순찰 지점 설정


매개변수 Array
->
함수는 const TArray<TObjectPtr<class APatrolPoint>>& Array라는 매개변수를 받는데 이는
 APatrolPoint 클래스나 그의 파생 클래스의 객체를 가리키는 포인터로 이루어진 배열(TArray)


 mPatrolPointArray
 ->mPatrolPointArray는 TArray<TObjectPtr<class APatrolPoint>> 타입의 멤버 변수
 이 함수에서는 함수의 매개변수 Array로 전달된 값을 mPatrolPointArray에 할당하고 있다.

 mPatrolPoint
 ->mPatrolPoint는 TArray<FVector> 타입의 멤버 변수
 이 함수에서는 순찰 지점의 위치 정보를 저장하는 mPatrolPoint 배열을 초기화하고 있다.

 mSpawnPoint->GetActorLocation()
 AI 캐릭터의 스폰 지점의 위치를 가져와서 mPatrolPoint 배열에 추가하고 있다.


 for (auto& Point : mPatrolPointArray)
 ->이 루프는 mPatrolPointArray 배열의 각 순찰 지점에 대해 해당 지점의 위치를 가져와서 mPatrolPoint 배열에 추가하고 있다.

 따라서
 이 함수는 AI 캐릭터의 순찰 지점을 설정하고, 
 해당 지점들의 위치를 mPatrolPoint 배열에 저장하는 역할을 수행
 이후에 이 배열을 사용하여 AI의 순찰 동작이나 특정 동작에 활용할 수 있다.





void AAIPawn::NextPatrol()
{
	mPatrolIndex = (mPatrolIndex + 1) % mPatrolPoint.Num();
}

NextPatrol 함수의 목적은 AI 캐릭터가 다음 순찰 지점으로 이동하는 것

mPatrolIndex
->int32변수. 이 변수는 현재 AI 캐릭터가 어떤 순찰 지점에 있는지를 나타내는 인덱스로 사용됨.

(mPatrolIndex + 1) % mPatrolPoint.Num()
->다음 순찰 지점의 인덱스를 계산하는 수식
현재 인덱스에서 1을 더하고 순찰 지점 배열의 크기로 나눈 나머지를 계산
이렇게 함으로써 배열의 범위를 벗어나지 않도록 인덱스를 조절


따라서, 이 함수는 현재 인덱스를 다음 순찰 지점의 인덱스로 업데이트한다.

*/

void AAIPawn::OnConstruction(const FTransform& Transform)
//OnConstruction함수는 액터가 생성되거나 편집 도중에 변경될 때 호출되는 함수
//이 함수는 액터의 초기화 및 구성과 관련된 작업을 수행
{
	Super::OnConstruction(Transform);
	/*
	C++에서 기반 클래스의 멤버 함수를 호출하는 구문
	Super는 해당 클래스가 상속한 기반 클래스를 나타냄

	OnConstruction 함수는 언리얼 엔진의 액터 클래스에 속한 함수로, 
	액터가 생성되거나 에디터에서 변화가 있을 때 호출되는 함수

	따라서, Super::OnConstruction(Transform);은 현재 클래스가 상속한 기반 클래스의 
	OnConstruction 함수를 호출하며, 이 함수에 Transform 매개변수를 전달하고 있다.
	이렇게 함으로써 기반 클래스에서 정의된 초기화 코드 등을 실행할 수 있다.
	
	*/

	// AIDataTable 애셋을 불러오지 않았을 경우 애셋을 불러온다.
	// mAIDataTable이 유효하지 않으면 LoadAIData 함수를 호출하여 데이터 테이블을 초기화
	if (!IsValid(mAIDataTable))
		LoadAIData();

	if (IsValid(mAIDataTable))
	{
		LOG(TEXT("AIDataTable Valid"));

		const FAIDataTable* Data = FindAIData(mName);
		/*
		FindAIData 함수를 호출하여 특정 이름(mName)에 해당하는 AI 데이터를 찾아, 
		그 결과를 FAIDataTable 구조체에 대한 포인터인 Data에 할당

		const 키워드는 Data 변수가 가리키는 데이터를 수정할 수 없음을 나타냄

		->이렇게 하면 Data 변수에는 특정 이름에 해당하는 AI 데이터에 대한 정보를 담고 있는 구조체에 대한 포인터가 들어가게 됨.
		이 구조체에는 AI 캐릭터의 상태, 이동 속도 등과 같은 정보들이 저장되어 있을 것임.
		*/

		if (Data)
		{
			mAIState->SetInfo(mName.ToString(), Data);

			mMovement->MaxSpeed = Data->MoveSpeed;
		}
	}
	/*
	앞서 설명한 Data 변수에 저장된 AI 데이터가 유효한지 확인하고, 
	유효한 경우에 해당 데이터를 사용하여 mAIState 및 mMovement의 속성을 설정하는 역할

	if (Data)
	Data 변수가 유효한지 확인
	FindAIData 함수에서 반환된 AI 데이터가 존재하는지를 체크
	만약 Data가 유효하다면(즉, Data가 nullptr가 아니라면)

	mAIState->SetInfo(mName.ToString(), Data);
	mAIState는 UAIState 클래스의 객체를 가리키는 포인터
	SetInfo 함수를 호출하여 AI 상태 정보를 설정
	함수에는 AI의 이름(mName의 문자열 표현)과 AI 데이터(Data)가 전달됨.
	->ToString쓰면 문자열로 표현이 되는구나.
	AI 상태를 초기화하거나 설정하는 데 사용

	mMovement->MaxSpeed = Data->MoveSpeed;:
	Data->MoveSpeed를 사용하여 AI 데이터에서 이동 속도를 가져와서 
	mMovement의 MaxSpeed 속성에 할당

	*/


	LOG(TEXT("OnConstruction : %s"), *mName.ToString());

	if(IsValid(GetWorld()->GetGameInstance()))
	{
		/*
		GetWorld()->GetGameInstance()
		->Unreal Engine에서 현재 월드(World)의 게임 인스턴스를 얻는 방법을 나타내는 코드

		GetWorld():
		-> 현재 액터가 속한 월드(World)를 얻어옴
		언리얼엔진에서 월드는 게임 세계(World)를 나타내며, 
		게임 내에서 모든 액터와 오브젝트들이 상호 작용하는 공간

		GetGameInstance()
		->얻어온 현재 월드의 게임 인스턴스(Game Instance)를 반환
		게임 인스턴스는 게임의 전체 수명 동안 유지되는 객체로, 
		주로 게임 전체적인 상태나 데이터를 관리하기 위해 사용됨.

		따라서, GetWorld()->GetGameInstance()는 현재 액터가 속한 월드의 게임 인스턴스를 얻는 코드로,
		이를 통해 게임 전역의 데이터나 설정에 접근할 수 있다.
		
		*/
		LOG(TEXT("GameInstance On"));
		//매크로는 { }로 묶어주나봄..
		//유효성 검사를 통해 게임 인스턴스의 존재 여부를 확인하고 로그 출력.
	}
	
	else
	{
		LOG(TEXT("GameInstance Off"));
	}

	if(IsValid(GetWorld()->GetAuthGameMode()))
	{
		LOG(TEXT("GameMode On"));
	}
	/*
	GetAuthGameMode()
	->현재 월드(World)의 "권한 있는" 게임 모드
	"권한 있는" 게임 모드는 서버에서 실행 중인 게임에서 사용되는 게임 모드
	
	여기서 "권한 있는"이라는 용어는 네트워크 멀티플레이 게임에서 중요
	클라이언트와 서버가 각각 자체의 게임 모드를 갖게 되는데, 
	서버에서 실행되는 게임 모드가 "권한 있는" 게임 모드.
	이 모드는 게임의 규칙 및 상태를 관리하고, 클라이언트는 이 규칙에 따라 동기화

	따라서, GetWorld()->GetAuthGameMode()는 현재 월드에서 서버가 실행 중인 "권한 있는" 게임 모드를 반환
	*/

	else
	{
		LOG(TEXT("GameMode Off")); 
	}

	/*
	
		// Material Element Count
	int32	ElementCount = mMesh->GetNumMaterials();
	/*
	mMesh라는 USkeletalMeshComponent를 가리키는 포인터에서 현재 사용 중인 머티리얼의 개수를 얻어오는 코드
	
	GetNumMaterials()
	이 메소드는 해당 메쉬 컴포넌트에 사용 중인 머티리얼의 개수를 반환

	ElementCount에는 mMesh에서 사용 중인 머티리얼의 개수가 저장됨.
	이 정보는 주로 반복문 등에서 사용하여 각 머티리얼에 대한 조작이나 초기화 등을 수행할 때 활용
	*/

	int32	ElementCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		mMaterialArray.Add(Mtrl);
	}
	/*
	
	int32	ElementCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		mMaterialArray.Add(Mtrl);
	}

	->
	mMesh에서 사용 중인 각각의 머티리얼에 대해 동적으로 머티리얼 인스턴스를 생성하고, 
	이를 mMaterialArray라는 배열에 추가하는 작업을 수행

	int32	ElementCount = mMesh->GetNumMaterials();
	Mesh에서 현재 사용 중인 머티리얼의 개수를 얻어오고 그 개수를 ElementCount 변수에 저장

	for (int32 i = 0; i < ElementCount; ++i):
	ElementCount만큼 반복하는 루프를 시작
	각 루프에서 i는 현재 순회 중인 머티리얼의 인덱스

	UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);:
	mMesh에서 i번째 머티리얼에 대한 동적 머티리얼 인스턴스를 생성.
	CreateDynamicMaterialInstance 함수는 해당 머티리얼을 복제하여 동적으로 인스턴스를 생성하는 함수
	생성된 인스턴스를 UMaterialInstanceDynamic* 타입의 포인터인 Mtrl에 저장

	mMesh는 클래스에서 정의한 USkeletalMeshComponent에 대한 포인터
	CreateDynamicMaterialInstance 함수는 특정 머티리얼의 동적 머티리얼 인스턴스를 생성
	UMaterialInstanceDynamic* Mtrl:
	->
	UMaterialInstanceDynamic은 동적으로 변경 가능한 머티리얼 인스턴스를 나타내는 클래스
	CreateDynamicMaterialInstance 함수가 반환하는 것이 바로 이 동적 머티리얼 인스턴스의 포인터
	Mtrl은 이 포인터를 가리키며, 이를 통해 이후에 머티리얼을 동적으로 변경할 수 있다.

	따라서, 이 코드는 mMesh에서 i번째 머티리얼에 대한 동적 머티리얼 인스턴스를 생성하고, 
	이를 Mtrl이라는 포인터에 저장하는 역할
	생성된 동적 머티리얼 인스턴스는 나중에 배열 등에 저장하여 필요한 시점에 사용할 수 있다.


	mMaterialArray.Add(Mtrl);:
	생성된 동적 머티리얼 인스턴스를 mMaterialArray라는 TArray에 추가
	이 배열은 나중에 머티리얼에 대한 추가적인 조작이나 초기화를 위해 사용될 수 있다.

	따라서, 이 코드는 메쉬에서 사용 중인 각 머티리얼에 대해 동적으로 머티리얼 인스턴스를 생성하고, 
	이를 배열에 저장하는 일반적인 작업
	이후에 배열에 저장된 머티리얼 인스턴스들을 활용하여 머티리얼을 동적으로 변경하거나 조작할 수 있음.	
	
	*/

	/*
	내 코드에서 빠진 부분

		mPatrolIndex = 1;

	// Material Element Count
	int32	ElementCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		mMaterialArray.Add(Mtrl);
	}
	/*
	->mMesh에서 사용 중인 머티리얼의 개수를 얻어오고, 각 머티리얼에 대한 동적 머티리얼 인스턴스를 생성하여
	mMaterialArray에 추가하는 일련의 작업을 수행


	mPatrolIndex = 1;:
	->mPatrolIndex 변수에 1을 할당

	int32 ElementCount = mMesh->GetNumMaterials();:
	->mMesh에서 사용 중인 머티리얼의 개수를 얻어와 ElementCount 변수에 저장
	->GetNumMaterials() 함수는 해당 메쉬 컴포넌트에서 사용 중인 머티리얼의 총 개수를 반환

	UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);:
	->mMesh에서 i번째 머티리얼에 대한 동적 머티리얼 인스턴스를 생성
	->CreateDynamicMaterialInstance 함수는 해당 머티리얼을 복제하여 동적으로 인스턴스를 생성하는 함수
	->생성된 인스턴스를 UMaterialInstanceDynamic* 타입의 포인터인 Mtrl에 저장

	mMaterialArray.Add(Mtrl);:
	->생성된 동적 머티리얼 인스턴스를 mMaterialArray라는 TArray에 추가

	따라서, 이 코드는 메쉬에서 사용 중인 각 머티리얼에 대해 동적으로 머티리얼 인스턴스를 생성하고, 이를 배열에 저장하는 작업
	이렇게 생성된 동적 머티리얼 인스턴스는 이후에 게임에서 동적으로 변경될 수 있다.
	
	
	*/
	
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	//mAnim = Cast<UDefaultAIAnimInstance>(mMesh->GetAnimInstance());

	//// SpawnPoint 없이 바로 배치해서 사용하며 PatrolPoint를 넣어준 경우
	//// 이 안으로 들어오게 될 것이다.
	//if (!mPatrolPoint.IsEmpty())
	//{
	//	FVector	Loc = GetActorLocation();
	//	Loc.Z -= mBody->GetScaledCapsuleHalfHeight();

	//	mPatrolPoint.Add(Loc);

	//	for (auto& Point : mPatrolPointArray)
	//	{
	//		mPatrolPoint.Add(Point->GetActorLocation());
	//	}
	//}
}




void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(mSpawnPoint))
		mSpawnPoint->ClearObject();
}
/*
Super::EndPlay(EndPlayReason);
->부모 클래스인 AActor의 EndPlay 함수를 호출

mSpawnPoint->ClearObject();:
->mSpawnPoint가 유효할 경우, mSpawnPoint에 대한 특정 동작을 수행


이 코드는 액터가 소멸되는 시점에 호출되는 EndPlay 이벤트에서 mSpawnPoint가 유효하다면 특정 동작을 수행하도록 구현
ClearObject 함수의 구체적인 동작은 AAISpawnPoint 클래스의 정의에 따라 달라짐. 
거기엔 mSpawnObject = nullptr;로 되어있음.
->
mSpawnObject 변수를 nullptr로 설정하여 해당 스폰 포인트에 속한 스폰된 오브젝트를 제거하는 역할
따라서 ClearObject 함수를 호출하면 mSpawnObject 변수가 이전에 가리키던 오브젝트를 더 이상 참조하지 않게 됨.
이는 해당 스폰 포인트에 현재 스폰된 오브젝트를 제거하고 초기화하는 역할을 함.
이렇게 함으로써 다음에 새로운 오브젝트가 이 스폰 포인트에 스폰될 때 문제가 발생하지 않도록 함.

*/

float AAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Dmg = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator,
		DamageCauser);

	bool Death = mAIState->AddHP((int32)Dmg);


	if (Death)
	{
		if (mAnim)
			mAnim->ChangeAnim(EAIAnimType::Death);

		mBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		AAIController* AI = Cast<AAIController>(GetController());

		if (IsValid(AI))
			AI->BrainComponent->StopLogic(TEXT("Death"));

		//mMesh->SetSimulatePhysics(true);
	}

	else
	{
		/*
		언리얼엔진 타이머
		글로벌타이머 매니저를 가지고 있고 매니저에서 타이머들을 관리한다.
		FTimerManager의 SetTimer 함수를 이용하여 타이머를 생성한다.
		*/
		// 타이머 핸들이 없을 때 타이머를 생성한다.
		if (!mHitTimerHandle.IsValid())
		{
			// Actor클래스는 GetWorldTimerManager() 함수를 지원해주고 있지만
			// 다른 클래스에서는 지원하지 않을 수 있기 때문에
			// GetWorld()->GetTimerManager() 로 접근한다.
			GetWorld()->GetTimerManager().SetTimer(mHitTimerHandle, this,
				&AAIPawn::HitTimer, 0.2f);
		}

	}

	mHit = true;

	// MaterialInstance 전체를 반복하며 HitColor를 붉은색으로 변경한다.
	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetVectorParameterValue(TEXT("HitColor"),
			FVector(1.0, 0.0, 0.0));
	}

	return Dmg;
}

/*
TakeDamage 액터가 데미지를 받았을 때 호출

float Dmg = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator,
		DamageCauser);

->부모 클래스인 AActor의 TakeDamage 함수를 호출하여 데미지를 처리하고, 
처리된 데미지 양을 Dmg 변수에 저장

bool Death = mAIState->AddHP((int32)Dmg);
->mAIState 객체의 AddHP 함수를 호출하여 데미지를 적용하고, 
적용된 데미지로 인해 생존 여부를 판단
->만약 생존 여부가 false이면 살아있으며, true이면 사망한 것으로 간주

if (Death) 안의 구문
if (mAnim)
->mAnim이 유효한지 확인 (nullptr이 아닌지 확인) 
유효한 경우,

mAnim->ChangeAnim(EAIAnimType::Death);
->mAnim의 ChangeAnim 함수를 호출하여 애니메이션을 변경
->EAIAnimType::Death를 전달하여 사망 애니메이션으로 변경

mBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);:
->mBody라는 컴포넌트의 충돌을 비활성화
->해당 액터는 충돌을 감지하지 않게 되어, 다른 액터와의 상호작용이나 충돌을 막을 수 있자.

AAIController* AI = Cast<AAIController>(GetController());
->액터의 컨트롤러를 얻어와서, 해당 컨트롤러가 AAIController 형식인지 확인

->GetController() 함수를 사용하여 현재 액터의 컨트롤러를 얻어옴
->Cast<AAIController>를 사용하여 해당 컨트롤러를 AAIController 타입으로 캐스팅
->AAIController 타입으로 캐스팅이 성공하면, AI라는 지역 변수에 해당 컨트롤러를 저장

if (IsValid(AI)):
->AI가 유효한 경우, 즉 AAIController 타입인 경우

AI->BrainComponent->StopLogic(TEXT("Death"));
->AI의 브레인 컴포넌트의 로직을 중단
->Death"라는 문자열을 인자로 전달하여 특정 로직을 중단

BrainComponent는 AAIController의 멤버 변수 중 하나로, 브레인 로직을 관리하는 컴포넌트
StopLogic(TEXT("Death"))는 브레인 컴포넌트의 특정 로직을 중단시키는 함수


mMesh->SetSimulatePhysics(true);
->사망 시 메시에 물리 시뮬레이션을 활성화

else->생존했다면
(아래 내용은 mHitTimerHandle이 유효하지 않을 때에만 타이머를 설정하는 구문)

if (!mHitTimerHandle.IsValid())
->mHitTimerHandle이 유효하지 않은지 확인합니다. 
즉, 이전에 설정한 타이머가 현재 실행 중이지 않은지를 검사

GetWorld()->GetTimerManager().SetTimer(mHitTimerHandle, this,
				&AAIPawn::HitTimer, 0.2f);
->
GetTimerManager().SetTimer 함수를 사용하여 타이머를 설정
mHitTimerHandle: 타이머 핸들로, 타이머를 나중에 제거하거나 조작할 때 사용됨.
this: 타이머 콜백 함수가 속한 객체. 여기서는 AAIPawn 클래스의 인스턴스인 현재 객체를 의미
&AAIPawn::HitTimer: 타이머가 만료될 때 호출되는 함수
이 경우 AAIPawn 클래스의 HitTimer 함수를 콜백으로 사용함

0.2f: 타이머의 주기로, 0.2초마다 한 번씩 HitTimer 함수 호출

따라서, 이 코드는mHitTimerHandle이 유효하지 않을 때 0.2초 간격으로 주기적으로 
HitTimer 함수를 호출하는 타이머를 설정합니다. 
이를 통해 지연된 행동이나 반복적인 동작을 구현할 수 있다. 

mHit = true;:
->mHit 변수를 true로 설정
-> 피해를 입은 상태를 나타내기 위한 플래그로 사용됨. 
즉, 피해를 입은 상태를 나타내기 위해 mHit 변수를 true로 설정

for (auto& Mtrl : mMaterialArray):
->mMaterialArray에 있는 각각의 재질에 대해 반복

Mtrl->SetVectorParameterValue(TEXT("HitColor"), FVector(1.0, 0.0, 0.0));
->현재 재질(Mtrl)에 대해 HitColor라는 벡터 파라미터 값을 설정
-> 경우 FVector(1.0, 0.0, 0.0)은 RGB 값으로, 붉은 색을 나타냅니다. 따라서 HitColor가 붉은 색으로 설정되어 시각적인 효과를 표현
->이 부분은 주로 피해를 입은 부분을 강조하는 데 사용될 수 있다.

return Dmg;:
->함수가 피해량(Dmg)을 반환

이 코드의 주요 목적은 피해를 입은 상태를 나타내기 위해 mHit을 true로 설정하고, 
시각적으로 피해를 입은 부분을 강조하기 위해 재질의 HitColor를 설정하는 것

*/

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//부모 클래스인 AActor의 Tick 함수를 호출하여 기본적인 틱 기능을 수행

	/*
	AddMovementInput(GetActorForwardVector());
	->AddMovementInput 함수를 사용하여 액터를 현재 전방으로 이동
	이 부분은 DeltaTime을 적용하지 않아서 이동 속도는 고정
	->
	AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false);
	안에 변수 살펴보면
	WorldDirection: 이동할 방향을 나타내는 벡터
	ScaleValue: 이동 속도를 제어하는 스케일 값. 기본값은 1.0f
	bForce: true로 설정하면 이동이 즉시 발생하도록 강제합니다. 기본값은 false


	if (mDissolveEnable)
	{
		mDissolveCurrentTime += DeltaTime;
		->mDissolveCurrentTime 변수에 DeltaTime를 더하여 경과한 시간을 누적

		if (mDissolveCurrentTime >= mDissolveTime)
			Destroy();
		->Dissolve 효과를 위한 시간이 지났을 때 해당 액터를 파괴

		// 비율을 구한다.
		float	Ratio = mDissolveCurrentTime / mDissolveTime;
		Ratio = 1.f - Ratio;
		Ratio = Ratio * 2.f - 1.f;

		for (auto& Mtrl : mMaterialArray)
		{
			Mtrl->SetScalarParameterValue(TEXT("Dissolve"), Ratio);
		}


		->
		float	Ratio = mDissolveCurrentTime / mDissolveTime;
		->Ratio 변수는 mDissolveCurrentTime을 mDissolveTime으로 나눈 값을 가지며, 
		이는 현재 Dissolve 효과가 진행된 비율을 나타냄
		->mDissolveCurrentTime은 현재 Dissolve가 진행된 시간이며, 
		mDissolveTime은 전체 Dissolve에 걸리는 시간


		Ratio = 1.f - Ratio;:
		->Ratio를 1에서 빼서 현재 Dissolve 진행 비율을 거꾸로 만들기
		이렇게 하면 Dissolve가 시작할 때 Ratio가 0이 되고, 시간이 지남에 따라 1에 수렴하게 됨.

		Ratio = Ratio * 2.f - 1.f;:
		->Ratio에 2를 곱하고 1을 빼서 값을 조절
		이렇게 함으로써 Ratio의 범위가 [-1, 1]로 매핑되게 됨.
		이러한 조절은 특정 효과나 애니메이션에서 사용되는 경우가 많습니다.


		Ratio = 1.f - Ratio;:
		Ratio = Ratio * 2.f - 1.f;
		두 변환을 조합하여, Ratio 값을 초기 상태에서부터 어떤 값까지 변화하는 범위로 매핑하고 
		해당 범위의 중앙을 0으로 설정
		이렇게 하면 시간에 따른 Ratio의 변화가 특정 범위에서 진행되도록 만들 수 있다.


		for (auto& Mtrl : mMaterialArray):
		->mMaterialArray에 있는 각각의 재질에 대해 반복


		Mtrl->SetScalarParameterValue(TEXT("Dissolve"), Ratio);
		->현재 재질(Mtrl)에 대해 Dissolve 효과를 나타내는 스칼라 파라미터인 Dissolve에 Ratio 값을 설정
		->이를 통해 Dissolve 효과가 시간에 따라 변하도록 만듬.

		따라서,이 코드는 Dissolve 효과를 구현하기 위해 시간에 따라 변하는 비율인 Ratio 값을 계산하고, 
		이를 재질에 적용하여 시각적인 효과를 생성

	}
	
	*/

}

void AAIPawn::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}
/*
충돌 프로필을 설정하는 역할 수행
이 함수는 반환값이 void로, 어떠한 값도 반환하지 않음.
매개변수 const FName& Name는 설정하려는 충돌 프로필의 이름을 나타냄

mBody->SetCollisionProfileName(Name);:
SetCollisionProfileName(Name)은 UCapsuleComponent의 멤버 함수로, 
해당 충돌 본체의 충돌 프로필을 지정된 이름(Name)으로 설정


따라서, 이 함수는 AAIPawn 클래스의 mBody라는 충돌 본체의 충돌 프로필을 지정된 이름으로 설정하는 역할
충돌 프로필은 일반적으로 충돌 및 물리 특성을 정의하는 데 사용되며, 예를 들어 "BlockAllDynamic"과 같은 미리 정의된 프로필이 있을 수 있다.
*/

void AAIPawn::HitTimer()
{
	mHit = false;

	// MaterialInstance 전체를 반복하며 HitColor를 붉은색으로 변경한다.
	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetVectorParameterValue(TEXT("HitColor"),
			FVector(1.0, 1.0, 1.0));
	}

	GetWorld()->GetTimerManager().ClearTimer(mHitTimerHandle);
}
/*

HitTimer()
->타이머 이벤트로, 특정 시간 간격마다 어떤 동작을 수행할 때 사용됨

mHit = false;
-> 현재 공격을 받지 않은 상태로 설정

for (auto& Mtrl : mMaterialArray)
->mMaterialArray에 있는 모든 재질 인스턴스에 대해 반복

Mtrl->SetVectorParameterValue(TEXT("HitColor"),
			FVector(1.0, 1.0, 1.0));
->
Mtrl은 현재 반복되는 동적 재질 인스턴스
SetVectorParameterValue함수를 사용하여 HitColor라는 이름의 백터 파라미터에 특정 RGB값 설정.
이 경우엔 흰색으로 설정하여ㅏ 모든 재질이 원래 상태로 돌아가도록 함.

SetVectorParameterValue()
->게임 실행 중에 런타임에서 재질의 속성을 변경하거나 애니메이션 효과를 주는 데 사용

GetWorld()->GetTimerManager().ClearTimer(mHitTimerHandle);
->mHitTimerHandle이라는 타이머 핸들 클리어. 
이로써 현재 진행 중인 타이머가 중지되고 더이상 HitTimer함수 호출되지 X
: 
종합하면, 특정 시간 동안 활성화된 HitColor를 원래 상태로 복원하고, 
mHit변수를 false로 설정하여 특정 동작을 유지하지 않게 함.

*/




void AAIPawn::DeathEnd()
{
	// Dissolve를 활성화한다.
	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"),
			1.f);
		/*
		SetScalarParameterValue 함수를 사용하여 UMaterialInstanceDynamic의 스칼라 매개변수를 설정
		"DissolveEnable"는 설정하려는 스칼라 매개변수의 이름이며, 
		1.f는 해당 스칼라 매개변수에 대한 값. 여기서 1.f는 활성화를 나타냄

		스칼라 매개변수를 사용하여 UMaterialInstanceDynamic의 속성을 설정하는 것은 
		재질의 특정 효과나 속성을 조절하는 데 사용됨.
		스칼라 매개변수는 단일 값을 나타내므로 주로 어떤 특성이나 효과의 강도를 조절할 때 유용.
		
		*/

	}

	mDissolveEnable = true;
}

/*
	AI 컨트롤러 클래스에서 사용되는 두 개의 가상 함수
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	OnPossess(APawn* aPawn)
	->AI 컨트롤러가 AI 캐릭터를 소유할 때 호출됨.
	APawn* aPawn 매개변수로 소유된 AI 캐릭터에 대한 포인터가 전달됨.
	일반적으로 이 함수에서는 AI 캐릭터를 초기화하거나 순찰이나 특정 동작을 시작하는 등의 초기 설정을 수행


	OnUnPossess()
	->AI 컨트롤러가 AI 캐릭터의 소유를 해제할 때 호출됨.
	소유를 해제하는 시점은 주로 AI 캐릭터가 사망하거나 특정 상황에서 소유를 해제할 때
	이 함수에서는 소유를 해제한 AI 캐릭터에 대한 정리 작업이나 추가적인 동작을 수행할 수 있다.

*/


