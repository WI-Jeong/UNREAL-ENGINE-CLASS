// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h" 
#include "../Player/PlayerCharacter.h" 

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	CreateDefaultSubobject:생성자 전용함수이다. 생성자에서 컴포넌트를 생성하기 
	위한 함수이다. 이 함수는 템플릿으로 만들어져 있다. 왜냐하면
	다양한 컴포넌트를 생성하기 위함인데 만약 템플릿이 아니라면 컴포넌트 종류별로 
	생성할 함수를 다 만들어 주어야 한다. 컴포넌트가 100종류라면 100개의 함수를 만들어야
	하기 때문에 템플릿을 이용하여 생성할 컴포넌트의 타입을 지정하면 해당 타입의 컴포넌트
	를 생성하고 그 객체의 주소를 반환해주는 방식이다.
	*/
	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	//위에서 생성한 body가 루트 컴포넌트가 되어야한다. 루트컴포넌트=부모
	SetRootComponent(mBody);

	//상자의 크기를 설정한다.
	mBody->SetBoxExtent(FVector(84.0, 80.5, 77)); //더블 타입이라 f안씀

	// Overlap이 가능하게 설정한다.(메쉬는 충돌하면 안되고 박스만 충돌해야함)
	mBody->SetGenerateOverlapEvents(true);

	//프로파일 지정
	mBody->SetCollisionProfileName(TEXT("TestOverlap"));



	/*
	엔진은 어떤 충돌체들끼리 충돌 여부를 판만단 해준다.
	충돌 이후의 상황은 엔진을 이용하는 프로그래머가 직접 구현을 해야한다.
	그런데 엔진 입장에서 보면 우리가 기능을 동작시키기 위해서 구현한
	함수를 모른다. 그러므로 충돌이 되어도 해당 기능을 구현한 함수를 호출할 수 없기 
	때문에 기능을 동작시킬 수가 없다. 그래서 지원하는 기능이 델리게이트이다. 델리게이트를
	통해서 충돌 이후에 동작할 함수의 주소를 델리겡트에 넘겨준다면 델리게이트는 그 함수의
	주소를 가지고 있다가 엔진에서 충돌이 일어나면 가지고 있는 함수를 호출하여
	충돌 시 동작할 내용을 동작시켜줄 수 있게 된다.
	이런 방식을 call back이라고 함
	*/



	//OnComponentBeginOverlap: 겹치기 시작할 때 호출할 함수를 등록하는 델리게이트
	mBody->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::OverlapBegin);

	//메쉬 컴포넌트를 생성한다.
	//화면에 출력하는 컴포넌트들은 모두 UPrimitiveComponent를 상속받아
	//만들어져 있다.
	mMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//위에서 생성한 MeshComponent의 부모 컴포넌트로 박스르 지정한다. 
	mMesh->SetupAttachment(mBody);

	//Mesh의 충돌을 끈다.
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//
	mMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	//출력할 StaticMesh Asset을 얻어온다.
	//매번 생성되는 객체마다 애셋을 로드할 필요 없이 한번만 로드될 수 잇도록
	//Static으로 로드한다.

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/NaturePackage/Meshes/flora/rock6.rock6'"));

	//Mesh를 얻어오는것이 성공했다면
	if (MeshAsset.Succeeded())
	{
		//StaticMeshComponent에 출력할 에셋으로 지정한다.
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	/*
#pragma region 원하는이름
	여기에 있는 코드를 접었다 폈다 할 수 있게 된다.
#pragma endregion 원하는이름
	*/

#pragma endregion CollisionActor
	//플레이어의 뒤를 향하는 방향벡터를 구한다.
	FVector Back = OtherActor->GetActorForwardVector() * -1.f;

	//최종위치구하기
	//GetActorLocation: 이 액터의 현재 위치
	//BAck: 이 액터의 뒤를 향하는 벡터
	//현재위치+뒤*300cm
	FVector Loc = OtherActor->GetActorLocation() + Back * 300.f;

	//강제로 이 위치로 이동시킨다.
	//	OtherActor->SetActorLocation(Loc);

	//TeleportTo: 지정한 위치와 회전을 이용해서 해당 위치 이동시키고 
	// 해당 회전을 적용시킨다.
	//1번인자: 이동시킬 위치
	//2번인자: 이동 후의 회전값
	//3번인자: 알림을 동작시키는 테스트의 경우 true
	//4번인자: 이동시킨 위치에 겹치는 물체가 있는지 체크를 하기 위한 기능이다.

	OtherActor->TeleportTo(Loc, OtherActor->GetActorRotation(), false, true);

	//Cast함수는 형변환하는 타입이 아닐 경우 nullptr을 반환한다.
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

		if (Player != nullptr)
		{
			Player->ChangeAnimation(EPlayerAnimType::Teleport);

			//이동 속도를 0으로 만들어준다.
			Player->GetCharacterMovement()->MaxWalkSpeed = 0.f;

		}
#pragma endregion CollisionActor


	
#pragma endregion CurrentActor 
		/*
	//플레이어의 뒤를 향하는 방향벡터를 구한다.
	FVector Back = GetActorForwardVector() * -1.f;

	//최종위치구하기
	//GetActorLocation: 이 액터의 현재 위치
	//BAck: 이 액터의 뒤를 향하는 벡터
	//현재위치+뒤*300cm
	FVector Loc = GetActorLocation() + Back * 300.f;

	//강제로 이 위치로 이동시킨다.
	//OtherActor->SetActorLocation(Loc);

	//TeleportTo: 지정한 위치와 회전을 이용해서 해당 위치 이동시키고 
	// 해당 회전을 적용시킨다.
	//1번인자: 이동시킬 위치
	//2번인자: 이동 후의 회전값
	//3번인자: 알림을 동작시키는 테스트의 경우 true
	//4번인자: 이동시킨 위치에 겹치는 물체가 있는지 체크를 하기 위한 기능이다.

	TeleportTo(Loc,GetActorRotation(), false, true);
	*/
#pragma endregion CurrentActor 


}

