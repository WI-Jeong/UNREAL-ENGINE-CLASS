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




	mMesh->bRenderCustomDepth = true;

	//0~255사이의 원하는 값을 넣어준다.
	mMesh->SetCustomDepthStencilValue(0);


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

		mAIState->SetInfo(mName.ToString(), Data);

		mMovement->MaxSpeed = Data->MoveSpeed;
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

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AddMovementInput(GetActorForwardVector());

}

void AAIPawn::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}




