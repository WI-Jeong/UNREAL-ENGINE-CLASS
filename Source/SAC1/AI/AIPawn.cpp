// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "AISpawnPoint.h"
#include "DefaultAIController.h"
#include "AIState.h"
#include "DefaultAIAnimInstance.h" //�̰� BS����� AB�������� �����ε�...

TObjectPtr<UDataTable>	AAIPawn::mAIDataTable;
/*
TObjectPtr: �ڵ����� �޸� ������ ���ִ� ������

UDataTable�� �𸮾� �������� ������ ���̺��� ��Ÿ���� Ŭ������, 
���� ��� ���� �̷���� �����͸� �����ϰ� �����ϴ� �� ����.

AAIPawn::mAIDataTable���� ::�� ���� ���� ������.
���� ���� �����ڴ� Ư�� ���� ���� �ִ� ����� ������ ������ �� ����.
��, AAIPawn Ŭ���� ������ mAIDataTable�� ������ �� ���Ǵ� ���� ���� ������.

��, AAIPawn::mAIDataTable
AAIPawn Ŭ������ ���� ���� ��� ���� mAIDataTable�� �����ϴ� ���Դϴ�.
Ŭ������ ���� ��� ������ �ش� Ŭ������ ��� ��ü���� �����Ǵ� �����̹Ƿ�, 
Ŭ���� �̸��� ���� ���� �����ڸ� ����Ͽ� ������.

*/

// Sets default values
AAIPawn::AAIPawn()
//������: �ش� Ŭ������ ��ü�� ������ �� ȣ��Ǵ� �Լ�. & �ʱ�ȭ �۾� ����
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	PrimaryActorTick.bCanEverTick = true;
	�ش� ���Ͱ� ƽ(tick) ����� ����� �������� �����ϴ� �κ�
	ƽ(thik)�� ������ �� �����ӿ��� ȣ��Ǵ� �Լ���, ���� ������ �ֱ������� ������Ʈ�ϴ� �� ���.

	PrimaryActorTick�� �𸮾� ������ AActor Ŭ������ ���ǵ� ����ü
	�� ����ü�� ������ ƽ�� ���õ� �Ӽ��� ��Ÿ��.

	bCanEverTick�� ƽ ����� Ȱ��ȭ���� ���θ� ��Ÿ���� �ο�(boolean) ��

	��, �ش� �ڵ�� ���Ͱ� ƽ�� ����� �� �ֵ��� �����ϴ� ����
	ƽ�� ������ �� �����ӿ��� ȣ��Ǵ� �Լ��� �ǹ��ϸ� ���� ������ �ֱ������� ������Ʈ�ϰ� ó���ϴ� �� ����.
	true; �̹Ƿ� �ش� ���Ͱ� ���� �����Ӹ��� ������Ʈ�� �����ϵ��� ����Ѵٴ� �ǹ�

	�� �ڵ尡 ������ ���ʹ� ƽ �Լ��� ȣ����� �ʰ�, 
	Ư�� ��Ȳ������ ������ �����̳� ���� ������Ʈ�� �̷������ ���� �� ����.	
	
	*/

	mAttackEnd = false;
	mInteractionEnd = false;
	/*
	������� mAttackEnd�� mInteractionEnd�� �ʱ�ȭ
	�̵� ������ ������ ������ ����Ǿ�����, ��ȣ �ۿ��� ����Ǿ����� ���θ� ��Ÿ���� �Ҹ��� ��

	false�� ������ ������� �ʾҰ� ��ȣ�ۿ뵵 ������� �ʾҴ�..? �����ں��� ������µ�..?
	���� �����̶� ��ȣ�ۿ� ���� �ڵ嵵 ���µ�..?
	->�ʱ�ȭ�� �ܼ��� ������ Ư�� ������ �����ϴ� ��. ������ � ������ �������� ����.
	���� �����ڿ��� �� �� ������ false�� �ʱ�ȭ�� ���¿����� Ư�� �����̳� �̺�Ʈ�� �߻����� �ʴ� �̻� 
	�����̳� ��ȣ�ۿ��� ����� ���� �ƴ�.
	�� �������� �ʱ�ȭ�� ���¿��� �ٸ� �κп��� Ư�� �����̳� �̺�Ʈ�� ���� ����� ��.
	�ʱ�ȭ�� �ش� �������� � ���·� ������ �� �����ϴ� ���̸�, ���� ������ ������ ������ ���� ������.
	����, �ش� �ڵ忡���� ���� ����������������� ���� ��ȣ�ۿ� ������� ������ �ʱ� ���·� �����ϰ�, 
	���߿� Ư�� ���ǿ��� �� ������ ����ǵ��� �ٸ� ������ �߰��� ����.
	->
	���߿� Ư�� �̺�Ʈ�� ���ǿ� ���� ���� �����ؾ� �Ѵٸ�, 
	������ �̿��� �޼��峪 �Լ����� �ش� �������� ����ϰ� �����ص� ��.
	
	ê����Ƽ�� 
	"�����ڿ� mAttackEnd������ �ƿ� �����ʰ� AttackEnd�Լ� ���� ���� if() {} �̰� ()���� ������ true�� �� {}���� �ڵ� �����ϴϱ�
    AttackEnd�Լ����� if (mAttackEnd)�ϰ� {}�ȿ� idle�ִϸ��̼����� �ٲٴ� �ڵ� ������ �ȵ�?"
    ��� ������.
    ->�����ϴٰ� ����.

	�����ڵ�
					void AAIPawn::AttackEnd()
				{
					if (mAttackEnd)
					{
						// �̹� ������ ����� ������ ���� ����
						// ���� ���, idle �ִϸ��̼����� ��ȯ�ϴ� �ڵ�
					}
					else
					{
						// ������ ������� ���� ������ ���� ����
						// ���� ���, ���� ���� �ִϸ��̼��� idle �ִϸ��̼����� �����ϴ� �ڵ�

						// ...

						// ������ ����Ǿ����� ǥ��
						mAttackEnd = true;
					}
				}

		->
		�̷��� �ϸ� AttackEnd �Լ� ������ ���� ������ ����Ǿ����� Ȯ���ϰ�, 
		������� �ʾҴٸ� ���� �ִϸ��̼��� idle �ִϸ��̼����� �����ϰ� 
		mAttackEnd ���� true�� �����մϴ�. 
		�̷��� �ϸ� �����ڿ��� mAttackEnd�� �ʱ�ȭ�ص� �ǰ�, 
		���߿� Ư�� ���ǿ��� �����ϴ� �͵� �����մϴ�.

	*/


	//Controller�� Yaw ȸ���� ��Ī�Ѵ�.
	//bUseControllerRotationYaw = true;
	//->���Ͱ� Yaw ȸ���� ��Ʈ�ѷ��� ȸ���� ������� ���θ� ����
	//Roll X�� , Pitch Y��, Yaw Z��
	//https://m.blog.naver.com/milkysc/221754450137 gif�� �����ϱ�.


	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	//UCapsuleComponent Ÿ���� mBody ��� ������ ���� 
	//�̴� ������ ��ü�� ��Ÿ���� ĸ�� ������Ʈ

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//USkeletalMeshComponent Ÿ���� mMesh ��� ������ ����
	//�̴� ������ ���̷��� �޽��� ��Ÿ���� ���̷��� �޽� ������Ʈ


	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	//UFloatingPawnMovement Ÿ���� mMovement ��� ������ ����
	//�̴� ������ �������� �����ϴ� ������Ʈ

	mAIState = CreateDefaultSubobject<UAIState>(TEXT("AIState"));
	//UAIState Ÿ���� mAIState ��� ������ ����
	//�̴� ������ AI ���¸� ��Ÿ���� ������Ʈ

	SetRootComponent(mBody);
	mMesh->SetupAttachment(mBody);
	mMovement->SetUpdatedComponent(mBody);
	/*
	SetupAttachment �Լ��� �θ�-�ڽ� ���� ���� �� ����.
	Ư��, � ������Ʈ�� �ٸ� ������Ʈ�� ������ �� ���.
	������ ������Ʈ�� �θ� ������Ʈ�� ��������� ��ġ�� �����Ǹ�,
	�θ�������Ʈ�� �̵��ϸ� �ڽ� ������Ʈ�� �Բ� �̵�
	����, mMesh->SetupAttachment(mBody); �� �ڵ�� mMesh�� mBody�� �����ϰڴٴ� �ǹ�.
	��, mMesh�� mBody�� �ڽ����� �����Ǿ� mBody�� �����ӿ� ������ �޴´�.


	SetUpdatedComponent �Լ��� Ư�� ������Ʈ�� ������Ʈ ������� �����ϴ� �� ����.
	�� �Լ��� ����ϸ� �ش� ������Ʈ�� �������� �̵� �� �浹 �˻� ���� ������ ���� �����ǰ� ��.
	mMovement->SetUpdatedComponent(mBody); �� �ڵ�� mMovement�� mBody�� ������Ʈ ������� �����ϰڴٴ� �ǹ�
	���� mBody�� �̵��� mMovement�� ���� ������.
		
	*/

	mBody->SetCollisionProfileName(TEXT("AI"));
	//mBody ĸ�� ������Ʈ�� �浹 ���������� "AI"�� ����
	
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//mMesh ���̷��� �޽� ������Ʈ�� �浹�� ��Ȱ��ȭ


	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	/*
	EAutoPossessAI �������� �𸮾� �������� AI�� �ڵ����� ���������� �����ϴ� �� ���

	None: AI�� �ڵ����� �������� ����. �������� AI�� �����ؾ� �մϴ�.
	Player: �÷��̾� ��Ʈ�ѷ��� ���� �����Ǵ� AI�� ������.->�ַ� �÷��̾ �����ϴ� ĳ���ͳ� ���� � ����.
	AI: ���� ���� �� AI ��Ʈ�ѷ��� ���� �����Ǵ� AI�� ������.->Ư���� ���� ���� ���� ���۰� ���ÿ� AI ��Ʈ�ѷ��� ����
	PlacedInWorld: ���Ͱ� ���忡 ��ġ�Ǹ� AI ��Ʈ�ѷ��� ���� ������.
	
	PlacedInWorldOrSpawned: ���Ͱ� ���忡 ��ġ�ǰų� ������ �� AI ��Ʈ�ѷ��� ���� ������. 
	���� ���� �߿��� ������ ��� AI�� �ڵ����� Ȱ��ȭ��. 
	��, �� �ɼ��� �����ϸ� �ش� ���Ͱ� ���� ���忡 ��Ÿ�� ������ AI�� �ڵ����� Ȱ��ȭ�˴ϴ�.	
	*/

	AIControllerClass = ADefaultAIController::StaticClass();
	/*
	
	ADefaultAIController::StaticClass()�� ADefaultAIController Ŭ������ Ÿ���� ��Ÿ���� �𸮾� ������ ��ŸŬ������ ��ȯ�ϴ� �Լ�
	�� Ŭ������ �⺻���� AI ��Ʈ�ѷ��� ����.

	�� �� ������ ���ڸ�,
	AI ��Ʈ�ѷ��� AI ĳ���ͳ� ���� ���� �����ϴ� �� ���Ǵ� Ŭ����
	�� ��Ʈ�ѷ��� AI�� �ൿ �� �ǻ� ������ �����ϰ� �ش� AI�� ����


	ADefaultAIController::StaticClass()
	ADefaultAIController�� �𸮾� �������� �����ϴ� �⺻ AI ��Ʈ�ѷ� Ŭ����
	StaticClass() �Լ��� �ش� Ŭ������ ��ŸŬ������ ��ȯ
	��ŸŬ������ Ŭ���� ��ü�� ��Ÿ���� ��Ÿ�� ������ ����


	AIControllerClass�� ���Ͱ� � AI ��Ʈ�ѷ� Ŭ������ ��������� �����ϴ� �Ӽ�
	Ư�� AI ��Ʈ�ѷ��� ����Ϸ��� �ش� Ŭ������ ��ŸŬ������ AIControllerClass�� �����ؾ� ��.

	���� ���, ADefaultAIController Ŭ������ ������� �ʰ� ����� ������ AI ��Ʈ�ѷ� Ŭ������ ����Ϸ���
	AIControllerClass = UMyCustomAIController::StaticClass();
	���⼭ UMyCustomAIController�� ����ڰ� ���� AI ��Ʈ�ѷ� Ŭ����
	�̷��� �����ν� ���ʹ� UMyCustomAIController�� ����Ͽ� AI�� �����ϰ� ��.


	��κ��� ��쿡�� StaticClass()�� ����ϸ�, 
	Ư���� ��Ȳ�̳� ����� ���ǵ� Ŭ���� ��ŸŬ���� ó���� �ʿ��� ��쿡�� �ٸ� �Լ��� ����� �� �ִ�.
	������ �̴� Ư�� ��Ȳ�� ����� �ڵ忡 ���� �޶�����.

	*/

	mTeam = ETeam::Team2; //2���� ����. ��, �÷��̾�� ai�� �� �ٸ��� �����Ѱ��� 


	mHit = false;
	/*
	� �浹�̳� ��Ʈ ���θ� ��Ÿ�� �� �ִ�.
	�ʱⰪ�� false�� �����ϸ� ó������ � �浹�� �߻����� ���� ���·� �����Ѵٴ� �ǹ�
	
	*/

	mMesh->bRenderCustomDepth = true;
	/*
	bRenderCustomDepth�� �𸮾� �������� �����ϴ� Ŀ���� ���� �������� ������� ���θ� ��Ÿ���� �ο�(boolean) �Ӽ�
	���� �������� �Ϲ������� ȭ�鿡 ǥ�õǴ� ��ü���� ���̸� ����Ͽ� ȭ�鿡 ��� �׷������� �����ϴ� ������ ���

	bRenderCustomDepth�� true�� �����ϸ� �ش� �޽��� �⺻���� ���� ������ ��ſ� ����ڰ� ������ Ŀ���� ���� ���� ���.
	�̴� �ð��� ȿ���� �ο��ϰų� Ư�� ������ ����� �����ϴ� �� ���� �� �ִ�.
		
	*/

	//0~255������ ���ϴ� ���� �־��ش�.
	mMesh->SetCustomDepthStencilValue(0);
	/*
	SetCustomDepthStencilValue �Լ��� Ŀ���� ���� ���ٽ� ���� �����ϴ� �Լ�
	���� ���ٽ��� �Ϲ������� ���� ���ۿ� �Բ� ���Ǿ� ������ ���������ο��� Ư�� ������Ʈ�� ���� �߰����� ��� ����
	Ŀ���� ���� ���ٽ� ���� �ַ� �ð��� ȿ���� �ο��ϰų� �������� Ư�� ȿ���� �߰��ϴ� �� ���ȴ�.

	SetCustomDepthStencilValue()
	Ŀ���� ���� ���ٽ� ���� ������ ���� �ַ� 0���� 255 ������ ���� ���

	SetCustomDepthStencilValue(0)�� SetCustomDepthStencilValue(255)

	SetCustomDepthStencilValue(0)
	->Ŀ���� ���� ���ٽǿ��� ���� ���ʿ� ��ġ
	�Ϲ������� ������Ʈ�� ��Ÿ���µ� ���
	��, �� ���� ������ ������Ʈ�� �Ϲ����� �������� ����
	

	SetCustomDepthStencilValue(255)
	-> Ŀ���� ���� ���ٽǿ��� ���� ���ʿ� ��ġ
	�Ϲ������� �������� �������� �ʴ� ������Ʈ, ���� ��� ȭ�� ���� ��� � ���� �� �ִ�.

	��,
	���� Ŭ���� �ش� ������Ʈ�� �ڷ�, �������� ������ ��ġ
	�̸� ���� ����ڴ� Ŀ���� ���� ���ٽ��� Ȱ���Ͽ� �ð����� ȿ���� �޸��� �� �ִ�.
	
	*/

	/*
	mDissolveCurrentTime = 0.f;
	->� ��ü�� ��ü�Ǵ�(dissolve) ȿ���� ������ �� ���
	�ش� ȿ���� ���� ��� �ð�

	mDissolveTime = 3.f;
	->��ü ȿ���� �Ϸ��ϴ� �� �ɸ��� ��ü �ð�
	��, mDissolveCurrentTime�� mDissolveTime�� �����ϸ� �ش� ȿ���� ������ ����

	mDissolveEnable = false;
	->�ش� ��ü�� ��ü ȿ���� Ȱ��ȭ���� ���θ� ��Ÿ���� ��
	false�� �ʱ�ȭ�Ǿ� �����Ƿ�, �ʱ⿡�� �ش� ȿ���� ��Ȱ��ȭ
	��, � ��ü ȿ���� �ൿ�� Ȱ��ȭ�Ǿ� ���� �ʴ�
	
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




