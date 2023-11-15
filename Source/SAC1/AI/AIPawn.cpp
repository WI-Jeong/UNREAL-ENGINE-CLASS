// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "AISpawnPoint.h"
#include "DefaultAIController.h"
#include "AIState.h"
#include "DefaultAIAnimInstance.h" //�̰� BS����� AB�������� �����ε�...

TObjectPtr<UDataTable>	AAIPawn::mAIDataTable;

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mAttackEnd = false;
	mInteractionEnd = false;

	//Controller�� Yaw ȸ���� ��Ī�Ѵ�.
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

	mTeam = ETeam::Team2; //2���� ����. ��, �÷��̾�� ai�� �� �ٸ��� �����Ѱ��� 


	mHit = false;

	mMesh->bRenderCustomDepth = true;

	//0~255������ ���ϴ� ���� �־��ش�.
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

	// AIDataTable �ּ��� �ҷ����� �ʾ��� ��� �ּ��� �ҷ��´�.
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
		//��ũ�δ� { }�� �����ֳ���..
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
		�𸮾��� Ÿ�̸�
		�۷ι�Ÿ�̸� �Ŵ����� ������ �ְ� �Ŵ������� Ÿ�̸ӵ��� �����Ѵ�.
		FTimerManager�� SetTimer �Լ��� �̿��Ͽ� Ÿ�̸Ӹ� �����Ѵ�.
		*/
		// Ÿ�̸� �ڵ��� ���� �� Ÿ�̸Ӹ� �����Ѵ�.
		if (!mHitTimerHandle.IsValid())
		{
			// ActorŬ������ GetWorldTimerManager() �Լ��� �������ְ� ������
			// �ٸ� Ŭ���������� �������� ���� �� �ֱ� ������
			// GetWorld()->GetTimerManager() �� �����Ѵ�.
			GetWorld()->GetTimerManager().SetTimer(mHitTimerHandle, this,
				&AAIPawn::HitTimer, 0.2f);
		}

	}



	mHit = true;

	// MaterialInstance ��ü�� �ݺ��ϸ� HitColor�� ���������� �����Ѵ�.
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
	// mHit�� true�� ��� �ð��� ����Ͽ� �ð��� ������ HitColor�� 1.0, 1.0, 1.0
	// ���� �����غ���.

	//if (mDissolveEnable)
	//{
	//	mDissolveCurrentTime += DeltaTime;

	//	if (mDissolveCurrentTime >= mDissolveTime)
	//		Destroy();

	//	// ������ ���Ѵ�.
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

	// MaterialInstance ��ü�� �ݺ��ϸ� HitColor�� ���������� �����Ѵ�.
	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetVectorParameterValue(TEXT("HitColor"),
			FVector(1.0, 1.0, 1.0));
	}

	GetWorld()->GetTimerManager().ClearTimer(mHitTimerHandle);
}

void AAIPawn::DeathEnd()
{
	// Dissolve�� Ȱ��ȭ�Ѵ�.
	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"),
			1.f);
	}

	mDissolveEnable = true;
}




