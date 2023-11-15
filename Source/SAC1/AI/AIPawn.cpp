// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "AISpawnPoint.h"
#include "DefaultAIController.h"
#include "AIState.h"
#include "DefaultAIAnimInstance.h" //이건 BS지우고 AB수정해준 이후인데...

TObjectPtr<UDataTable>	AAIPawn::mAIDataTable;

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mAttackEnd = false;
	mInteractionEnd = false;

	//Controller의 Yaw 회전에 매칭한다.
	//bUseControllerRotationYaw = true;

	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	mAIState = CreateDefaultSubobject<UAIState>(TEXT("AIState"));

	SetRootComponent(mBody);
	mMesh->SetupAttachment(mBody);
	mMovement->SetUpdatedComponent(mBody);

	mBody->SetCollisionProfileName(TEXT("AI"));
	
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADefaultAIController::StaticClass();

	mTeam = ETeam::Team2; //2번팀 지정. 즉, 플레이어랑 ai랑 팀 다르게 지정한거임 


	mHit = false;

	mMesh->bRenderCustomDepth = true;

	//0~255사이의 원하는 값을 넣어준다.
	mMesh->SetCustomDepthStencilValue(0);

	//mDissolveCurrentTime = 0.f;
	//mDissolveTime = 3.f;
	//mDissolveEnable = false;


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

const FAIDataTable* AAIPawn::FindAIData(const FName& Name)
{ 
	return mAIDataTable->FindRow<FAIDataTable>(Name, TEXT(""));
}



void AAIPawn::SetSpawnPoint(AAISpawnPoint* SpawnPoint)
{
	mSpawnPoint = SpawnPoint;
}

void AAIPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// AIDataTable 애셋을 불러오지 않았을 경우 애셋을 불러온다.
	if (!IsValid(mAIDataTable))
		LoadAIData();

	if (IsValid(mAIDataTable))
	{
		LOG(TEXT("AIDataTable Valid"));

		const FAIDataTable* Data = FindAIData(mName);

		if (Data)
		{
			mAIState->SetInfo(mName.ToString(), Data);

			mMovement->MaxSpeed = Data->MoveSpeed;
		}
	}


	LOG(TEXT("OnConstruction : %s"), *mName.ToString());

	if(IsValid(GetWorld()->GetGameInstance()))
	{
		LOG(TEXT("GameInstance On"));
		//매크로는 { }로 묶어주나봄..
	}
	
	else
	{
		LOG(TEXT("GameInstance Off"));
	}

	if(IsValid(GetWorld()->GetAuthGameMode()))
	{
		LOG(TEXT("GameMode On"));
	}

	else
	{
		LOG(TEXT("GameMode Off")); 
	}

	//// Material Element Count
	//int32	ElementCount = mMesh->GetNumMaterials();

	//for (int32 i = 0; i < ElementCount; ++i)
	//{
	//	UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

	//	mMaterialArray.Add(Mtrl);
	//}


}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	mAnim = Cast<UDefaultAIAnimInstance>(mMesh->GetAnimInstance());
	
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(mSpawnPoint))
		mSpawnPoint->ClearObject();
}

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

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddMovementInput(GetActorForwardVector());
	// mHit가 true일 경우 시간을 계산하여 시간이 지나면 HitColor를 1.0, 1.0, 1.0
	// 으로 변경해보자.

	//if (mDissolveEnable)
	//{
	//	mDissolveCurrentTime += DeltaTime;

	//	if (mDissolveCurrentTime >= mDissolveTime)
	//		Destroy();

	//	// 비율을 구한다.
	//	float	Ratio = mDissolveCurrentTime / mDissolveTime;
	//	Ratio = 1.f - Ratio;
	//	Ratio = Ratio * 2.f - 1.f;

	//	for (auto& Mtrl : mMaterialArray)
	//	{
	//		Mtrl->SetScalarParameterValue(TEXT("Dissolve"), Ratio);
	//	}
	//}

}

void AAIPawn::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}

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

void AAIPawn::DeathEnd()
{
	// Dissolve를 활성화한다.
	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"),
			1.f);
	}

	mDissolveEnable = true;
}




