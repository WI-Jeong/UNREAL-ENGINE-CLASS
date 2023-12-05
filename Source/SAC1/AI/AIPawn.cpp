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
/*
LoadAIData �� �Լ��� AAIPawn Ŭ������ ��� �Լ��� ����Ǿ� �ִ�.
�Լ��� ������ �Ƹ��� � AI �����͸� �ε��ϴ� ��

mAIDataTable
�� �Լ����� ���Ǵ� mAIDataTable�� UDataTable Ÿ���� ��� ����
������ ���̺��� �𸮾� �������� ����ȭ�� �����͸� �����ϰ� �����ϴ� �� ���Ǵ� �ڷᱸ��
��, LoadAIData �Լ����� AI ���� �����͸� ���� ������ ���̺��� �ε��ϰ��� �ϴ� ��

LoadObject<UDataTable>(nullptr, TEXT(""))
UDataTable Ÿ���� ������Ʈ�� �ε��ϴ� ���� �Լ�
LoadObject �Լ��� Ư�� Ŭ���� Ÿ���� ������Ʈ�� �ε��ϴ� �� ����. ���⼭�� UDataTable Ÿ���� �ε�

ù ��° �Ű������� nullptr�� �ε��� ������Ʈ�� ���. 
nullptr�� �����ϸ� �⺻ ��ο��� �ش� Ŭ���� Ÿ���� ������Ʈ�� ã�� �ε�

�� ��° �Ű������� TEXT("")�� �ε��� ������Ʈ�� ��θ� ��Ÿ���� ���ڿ�


���������, LoadAIData �Լ��� UDataTable Ÿ���� �����͸� �ε��Ͽ� mAIDataTable�� �Ҵ��Ϸ��� ��

*/

const FAIDataTable* AAIPawn::FindAIData(const FName& Name)
{ 
	return mAIDataTable->FindRow<FAIDataTable>(Name, TEXT(""));
}
/*
�Լ��� ������ Ư�� �̸�(Name)�� �ش��ϴ� AI �����͸� ã�� ��ȯ�ϴ� ��

�Ű����� const FName& Name
FName Ÿ���� ����
� �ĺ��ڳ� �̸��� ��Ÿ��

mAIDataTable->FindRow<FAIDataTable>(Name, TEXT(""))
->mAIDataTable�̶�� UDataTable Ÿ���� ��� �������� Ư�� ���� ã�� ���� �Լ��� ȣ��

FindRow<FAIDataTable>(Name, TEXT(""))
->������ ���̺��� Ư�� ���� ã�� ��ȯ�ϴ� �Լ�

FAIDataTable�� ã���� �ϴ� ���� ����ü Ÿ������, 
�� ���� � ������ �����͸� ��� �ִ����� ��Ÿ��

Name�� ã���� �ϴ� ���� �ĺ��ڳ� �̸�

const FAIDataTable*
�Լ��� ��ȯ Ÿ���� const FAIDataTable*���� ã�� ���� �����͸� ��Ÿ���� FAIDataTable ����ü�� ���� �����͸� ��ȯ
��ȯ�� �����Ͱ� nullptr�� ��� �ش� ���� ã�� ���� ��

����, �� �Լ��� mAIDataTable���� Ư�� �̸��� �ش��ϴ� AI �����͸� ã�Ƽ� �� �����Ϳ� ���� �����͸� ��ȯ�ϴ� ��
�Լ��� ������ ������ �Լ��� ȣ��Ǵ� ���̳� �Լ��� ���� Ŭ������ �ٸ� �κп��� Ȯ���� �� ����.


*/



void AAIPawn::SetSpawnPoint(AAISpawnPoint* SpawnPoint)
{
	mSpawnPoint = SpawnPoint;
}
/*
SetSpawnPoint �Լ�: �Լ��� ������ AI ĳ������ ���� ���� ����

�Ű����� SpawnPoint
:�Լ��� AAISpawnPoint* SpawnPoint��� ������ Ÿ���� �Ű������� �޴´�.
�̴� AAISpawnPoint Ŭ���� �Ǵ� ���� �Ļ� Ŭ������ ��ü�� ����Ű�� ������

mSpawnPoint
: mSpawnPoint�� AAISpawnPoint* Ÿ���� ��� ����
�� �Լ������� �Լ��� �Ű����� SpawnPoint�� ���޵� ���� mSpawnPoint�� �Ҵ��ϰ� �ִ�

����
�� �Լ��� �ֿ� ������ �־��� ���� ���� ��ü�� mSpawnPoint�� �Ҵ��Ͽ� 
���߿� �̸� ����� �� �ֵ��� �ϴ� ��

*/


/*
Patrol�κ� ������. 

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
SetPatrolPointArray �Լ��� ������ AI ĳ������ ���� ���� ����


�Ű����� Array
->
�Լ��� const TArray<TObjectPtr<class APatrolPoint>>& Array��� �Ű������� �޴µ� �̴�
 APatrolPoint Ŭ������ ���� �Ļ� Ŭ������ ��ü�� ����Ű�� �����ͷ� �̷���� �迭(TArray)


 mPatrolPointArray
 ->mPatrolPointArray�� TArray<TObjectPtr<class APatrolPoint>> Ÿ���� ��� ����
 �� �Լ������� �Լ��� �Ű����� Array�� ���޵� ���� mPatrolPointArray�� �Ҵ��ϰ� �ִ�.

 mPatrolPoint
 ->mPatrolPoint�� TArray<FVector> Ÿ���� ��� ����
 �� �Լ������� ���� ������ ��ġ ������ �����ϴ� mPatrolPoint �迭�� �ʱ�ȭ�ϰ� �ִ�.

 mSpawnPoint->GetActorLocation()
 AI ĳ������ ���� ������ ��ġ�� �����ͼ� mPatrolPoint �迭�� �߰��ϰ� �ִ�.


 for (auto& Point : mPatrolPointArray)
 ->�� ������ mPatrolPointArray �迭�� �� ���� ������ ���� �ش� ������ ��ġ�� �����ͼ� mPatrolPoint �迭�� �߰��ϰ� �ִ�.

 ����
 �� �Լ��� AI ĳ������ ���� ������ �����ϰ�, 
 �ش� �������� ��ġ�� mPatrolPoint �迭�� �����ϴ� ������ ����
 ���Ŀ� �� �迭�� ����Ͽ� AI�� ���� �����̳� Ư�� ���ۿ� Ȱ���� �� �ִ�.





void AAIPawn::NextPatrol()
{
	mPatrolIndex = (mPatrolIndex + 1) % mPatrolPoint.Num();
}

NextPatrol �Լ��� ������ AI ĳ���Ͱ� ���� ���� �������� �̵��ϴ� ��

mPatrolIndex
->int32����. �� ������ ���� AI ĳ���Ͱ� � ���� ������ �ִ����� ��Ÿ���� �ε����� ����.

(mPatrolIndex + 1) % mPatrolPoint.Num()
->���� ���� ������ �ε����� ����ϴ� ����
���� �ε������� 1�� ���ϰ� ���� ���� �迭�� ũ��� ���� �������� ���
�̷��� �����ν� �迭�� ������ ����� �ʵ��� �ε����� ����


����, �� �Լ��� ���� �ε����� ���� ���� ������ �ε����� ������Ʈ�Ѵ�.

*/

void AAIPawn::OnConstruction(const FTransform& Transform)
//OnConstruction�Լ��� ���Ͱ� �����ǰų� ���� ���߿� ����� �� ȣ��Ǵ� �Լ�
//�� �Լ��� ������ �ʱ�ȭ �� ������ ���õ� �۾��� ����
{
	Super::OnConstruction(Transform);
	/*
	C++���� ��� Ŭ������ ��� �Լ��� ȣ���ϴ� ����
	Super�� �ش� Ŭ������ ����� ��� Ŭ������ ��Ÿ��

	OnConstruction �Լ��� �𸮾� ������ ���� Ŭ������ ���� �Լ���, 
	���Ͱ� �����ǰų� �����Ϳ��� ��ȭ�� ���� �� ȣ��Ǵ� �Լ�

	����, Super::OnConstruction(Transform);�� ���� Ŭ������ ����� ��� Ŭ������ 
	OnConstruction �Լ��� ȣ���ϸ�, �� �Լ��� Transform �Ű������� �����ϰ� �ִ�.
	�̷��� �����ν� ��� Ŭ�������� ���ǵ� �ʱ�ȭ �ڵ� ���� ������ �� �ִ�.
	
	*/

	// AIDataTable �ּ��� �ҷ����� �ʾ��� ��� �ּ��� �ҷ��´�.
	// mAIDataTable�� ��ȿ���� ������ LoadAIData �Լ��� ȣ���Ͽ� ������ ���̺��� �ʱ�ȭ
	if (!IsValid(mAIDataTable))
		LoadAIData();

	if (IsValid(mAIDataTable))
	{
		LOG(TEXT("AIDataTable Valid"));

		const FAIDataTable* Data = FindAIData(mName);
		/*
		FindAIData �Լ��� ȣ���Ͽ� Ư�� �̸�(mName)�� �ش��ϴ� AI �����͸� ã��, 
		�� ����� FAIDataTable ����ü�� ���� �������� Data�� �Ҵ�

		const Ű����� Data ������ ����Ű�� �����͸� ������ �� ������ ��Ÿ��

		->�̷��� �ϸ� Data �������� Ư�� �̸��� �ش��ϴ� AI �����Ϳ� ���� ������ ��� �ִ� ����ü�� ���� �����Ͱ� ���� ��.
		�� ����ü���� AI ĳ������ ����, �̵� �ӵ� ��� ���� �������� ����Ǿ� ���� ����.
		*/

		if (Data)
		{
			mAIState->SetInfo(mName.ToString(), Data);

			mMovement->MaxSpeed = Data->MoveSpeed;
		}
	}
	/*
	�ռ� ������ Data ������ ����� AI �����Ͱ� ��ȿ���� Ȯ���ϰ�, 
	��ȿ�� ��쿡 �ش� �����͸� ����Ͽ� mAIState �� mMovement�� �Ӽ��� �����ϴ� ����

	if (Data)
	Data ������ ��ȿ���� Ȯ��
	FindAIData �Լ����� ��ȯ�� AI �����Ͱ� �����ϴ����� üũ
	���� Data�� ��ȿ�ϴٸ�(��, Data�� nullptr�� �ƴ϶��)

	mAIState->SetInfo(mName.ToString(), Data);
	mAIState�� UAIState Ŭ������ ��ü�� ����Ű�� ������
	SetInfo �Լ��� ȣ���Ͽ� AI ���� ������ ����
	�Լ����� AI�� �̸�(mName�� ���ڿ� ǥ��)�� AI ������(Data)�� ���޵�.
	->ToString���� ���ڿ��� ǥ���� �Ǵ±���.
	AI ���¸� �ʱ�ȭ�ϰų� �����ϴ� �� ���

	mMovement->MaxSpeed = Data->MoveSpeed;:
	Data->MoveSpeed�� ����Ͽ� AI �����Ϳ��� �̵� �ӵ��� �����ͼ� 
	mMovement�� MaxSpeed �Ӽ��� �Ҵ�

	*/


	LOG(TEXT("OnConstruction : %s"), *mName.ToString());

	if(IsValid(GetWorld()->GetGameInstance()))
	{
		/*
		GetWorld()->GetGameInstance()
		->Unreal Engine���� ���� ����(World)�� ���� �ν��Ͻ��� ��� ����� ��Ÿ���� �ڵ�

		GetWorld():
		-> ���� ���Ͱ� ���� ����(World)�� ����
		�𸮾������� ����� ���� ����(World)�� ��Ÿ����, 
		���� ������ ��� ���Ϳ� ������Ʈ���� ��ȣ �ۿ��ϴ� ����

		GetGameInstance()
		->���� ���� ������ ���� �ν��Ͻ�(Game Instance)�� ��ȯ
		���� �ν��Ͻ��� ������ ��ü ���� ���� �����Ǵ� ��ü��, 
		�ַ� ���� ��ü���� ���³� �����͸� �����ϱ� ���� ����.

		����, GetWorld()->GetGameInstance()�� ���� ���Ͱ� ���� ������ ���� �ν��Ͻ��� ��� �ڵ��,
		�̸� ���� ���� ������ �����ͳ� ������ ������ �� �ִ�.
		
		*/
		LOG(TEXT("GameInstance On"));
		//��ũ�δ� { }�� �����ֳ���..
		//��ȿ�� �˻縦 ���� ���� �ν��Ͻ��� ���� ���θ� Ȯ���ϰ� �α� ���.
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
	->���� ����(World)�� "���� �ִ�" ���� ���
	"���� �ִ�" ���� ���� �������� ���� ���� ���ӿ��� ���Ǵ� ���� ���
	
	���⼭ "���� �ִ�"�̶�� ���� ��Ʈ��ũ ��Ƽ�÷��� ���ӿ��� �߿�
	Ŭ���̾�Ʈ�� ������ ���� ��ü�� ���� ��带 ���� �Ǵµ�, 
	�������� ����Ǵ� ���� ��尡 "���� �ִ�" ���� ���.
	�� ���� ������ ��Ģ �� ���¸� �����ϰ�, Ŭ���̾�Ʈ�� �� ��Ģ�� ���� ����ȭ

	����, GetWorld()->GetAuthGameMode()�� ���� ���忡�� ������ ���� ���� "���� �ִ�" ���� ��带 ��ȯ
	*/

	else
	{
		LOG(TEXT("GameMode Off")); 
	}

	/*
	
		// Material Element Count
	int32	ElementCount = mMesh->GetNumMaterials();
	/*
	mMesh��� USkeletalMeshComponent�� ����Ű�� �����Ϳ��� ���� ��� ���� ��Ƽ������ ������ ������ �ڵ�
	
	GetNumMaterials()
	�� �޼ҵ�� �ش� �޽� ������Ʈ�� ��� ���� ��Ƽ������ ������ ��ȯ

	ElementCount���� mMesh���� ��� ���� ��Ƽ������ ������ �����.
	�� ������ �ַ� �ݺ��� ��� ����Ͽ� �� ��Ƽ���� ���� �����̳� �ʱ�ȭ ���� ������ �� Ȱ��
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
	mMesh���� ��� ���� ������ ��Ƽ���� ���� �������� ��Ƽ���� �ν��Ͻ��� �����ϰ�, 
	�̸� mMaterialArray��� �迭�� �߰��ϴ� �۾��� ����

	int32	ElementCount = mMesh->GetNumMaterials();
	Mesh���� ���� ��� ���� ��Ƽ������ ������ ������ �� ������ ElementCount ������ ����

	for (int32 i = 0; i < ElementCount; ++i):
	ElementCount��ŭ �ݺ��ϴ� ������ ����
	�� �������� i�� ���� ��ȸ ���� ��Ƽ������ �ε���

	UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);:
	mMesh���� i��° ��Ƽ���� ���� ���� ��Ƽ���� �ν��Ͻ��� ����.
	CreateDynamicMaterialInstance �Լ��� �ش� ��Ƽ������ �����Ͽ� �������� �ν��Ͻ��� �����ϴ� �Լ�
	������ �ν��Ͻ��� UMaterialInstanceDynamic* Ÿ���� �������� Mtrl�� ����

	mMesh�� Ŭ�������� ������ USkeletalMeshComponent�� ���� ������
	CreateDynamicMaterialInstance �Լ��� Ư�� ��Ƽ������ ���� ��Ƽ���� �ν��Ͻ��� ����
	UMaterialInstanceDynamic* Mtrl:
	->
	UMaterialInstanceDynamic�� �������� ���� ������ ��Ƽ���� �ν��Ͻ��� ��Ÿ���� Ŭ����
	CreateDynamicMaterialInstance �Լ��� ��ȯ�ϴ� ���� �ٷ� �� ���� ��Ƽ���� �ν��Ͻ��� ������
	Mtrl�� �� �����͸� ����Ű��, �̸� ���� ���Ŀ� ��Ƽ������ �������� ������ �� �ִ�.

	����, �� �ڵ�� mMesh���� i��° ��Ƽ���� ���� ���� ��Ƽ���� �ν��Ͻ��� �����ϰ�, 
	�̸� Mtrl�̶�� �����Ϳ� �����ϴ� ����
	������ ���� ��Ƽ���� �ν��Ͻ��� ���߿� �迭 � �����Ͽ� �ʿ��� ������ ����� �� �ִ�.


	mMaterialArray.Add(Mtrl);:
	������ ���� ��Ƽ���� �ν��Ͻ��� mMaterialArray��� TArray�� �߰�
	�� �迭�� ���߿� ��Ƽ���� ���� �߰����� �����̳� �ʱ�ȭ�� ���� ���� �� �ִ�.

	����, �� �ڵ�� �޽����� ��� ���� �� ��Ƽ���� ���� �������� ��Ƽ���� �ν��Ͻ��� �����ϰ�, 
	�̸� �迭�� �����ϴ� �Ϲ����� �۾�
	���Ŀ� �迭�� ����� ��Ƽ���� �ν��Ͻ����� Ȱ���Ͽ� ��Ƽ������ �������� �����ϰų� ������ �� ����.	
	
	*/

	/*
	�� �ڵ忡�� ���� �κ�

		mPatrolIndex = 1;

	// Material Element Count
	int32	ElementCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		mMaterialArray.Add(Mtrl);
	}
	/*
	->mMesh���� ��� ���� ��Ƽ������ ������ ������, �� ��Ƽ���� ���� ���� ��Ƽ���� �ν��Ͻ��� �����Ͽ�
	mMaterialArray�� �߰��ϴ� �Ϸ��� �۾��� ����


	mPatrolIndex = 1;:
	->mPatrolIndex ������ 1�� �Ҵ�

	int32 ElementCount = mMesh->GetNumMaterials();:
	->mMesh���� ��� ���� ��Ƽ������ ������ ���� ElementCount ������ ����
	->GetNumMaterials() �Լ��� �ش� �޽� ������Ʈ���� ��� ���� ��Ƽ������ �� ������ ��ȯ

	UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);:
	->mMesh���� i��° ��Ƽ���� ���� ���� ��Ƽ���� �ν��Ͻ��� ����
	->CreateDynamicMaterialInstance �Լ��� �ش� ��Ƽ������ �����Ͽ� �������� �ν��Ͻ��� �����ϴ� �Լ�
	->������ �ν��Ͻ��� UMaterialInstanceDynamic* Ÿ���� �������� Mtrl�� ����

	mMaterialArray.Add(Mtrl);:
	->������ ���� ��Ƽ���� �ν��Ͻ��� mMaterialArray��� TArray�� �߰�

	����, �� �ڵ�� �޽����� ��� ���� �� ��Ƽ���� ���� �������� ��Ƽ���� �ν��Ͻ��� �����ϰ�, �̸� �迭�� �����ϴ� �۾�
	�̷��� ������ ���� ��Ƽ���� �ν��Ͻ��� ���Ŀ� ���ӿ��� �������� ����� �� �ִ�.
	
	
	*/
	
}

void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	//mAnim = Cast<UDefaultAIAnimInstance>(mMesh->GetAnimInstance());

	//// SpawnPoint ���� �ٷ� ��ġ�ؼ� ����ϸ� PatrolPoint�� �־��� ���
	//// �� ������ ������ �� ���̴�.
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
->�θ� Ŭ������ AActor�� EndPlay �Լ��� ȣ��

mSpawnPoint->ClearObject();:
->mSpawnPoint�� ��ȿ�� ���, mSpawnPoint�� ���� Ư�� ������ ����


�� �ڵ�� ���Ͱ� �Ҹ�Ǵ� ������ ȣ��Ǵ� EndPlay �̺�Ʈ���� mSpawnPoint�� ��ȿ�ϴٸ� Ư�� ������ �����ϵ��� ����
ClearObject �Լ��� ��ü���� ������ AAISpawnPoint Ŭ������ ���ǿ� ���� �޶���. 
�ű⿣ mSpawnObject = nullptr;�� �Ǿ�����.
->
mSpawnObject ������ nullptr�� �����Ͽ� �ش� ���� ����Ʈ�� ���� ������ ������Ʈ�� �����ϴ� ����
���� ClearObject �Լ��� ȣ���ϸ� mSpawnObject ������ ������ ����Ű�� ������Ʈ�� �� �̻� �������� �ʰ� ��.
�̴� �ش� ���� ����Ʈ�� ���� ������ ������Ʈ�� �����ϰ� �ʱ�ȭ�ϴ� ������ ��.
�̷��� �����ν� ������ ���ο� ������Ʈ�� �� ���� ����Ʈ�� ������ �� ������ �߻����� �ʵ��� ��.

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

/*
TakeDamage ���Ͱ� �������� �޾��� �� ȣ��

float Dmg = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator,
		DamageCauser);

->�θ� Ŭ������ AActor�� TakeDamage �Լ��� ȣ���Ͽ� �������� ó���ϰ�, 
ó���� ������ ���� Dmg ������ ����

bool Death = mAIState->AddHP((int32)Dmg);
->mAIState ��ü�� AddHP �Լ��� ȣ���Ͽ� �������� �����ϰ�, 
����� �������� ���� ���� ���θ� �Ǵ�
->���� ���� ���ΰ� false�̸� ���������, true�̸� ����� ������ ����

if (Death) ���� ����
if (mAnim)
->mAnim�� ��ȿ���� Ȯ�� (nullptr�� �ƴ��� Ȯ��) 
��ȿ�� ���,

mAnim->ChangeAnim(EAIAnimType::Death);
->mAnim�� ChangeAnim �Լ��� ȣ���Ͽ� �ִϸ��̼��� ����
->EAIAnimType::Death�� �����Ͽ� ��� �ִϸ��̼����� ����

mBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);:
->mBody��� ������Ʈ�� �浹�� ��Ȱ��ȭ
->�ش� ���ʹ� �浹�� �������� �ʰ� �Ǿ�, �ٸ� ���Ϳ��� ��ȣ�ۿ��̳� �浹�� ���� �� ����.

AAIController* AI = Cast<AAIController>(GetController());
->������ ��Ʈ�ѷ��� ���ͼ�, �ش� ��Ʈ�ѷ��� AAIController �������� Ȯ��

->GetController() �Լ��� ����Ͽ� ���� ������ ��Ʈ�ѷ��� ����
->Cast<AAIController>�� ����Ͽ� �ش� ��Ʈ�ѷ��� AAIController Ÿ������ ĳ����
->AAIController Ÿ������ ĳ������ �����ϸ�, AI��� ���� ������ �ش� ��Ʈ�ѷ��� ����

if (IsValid(AI)):
->AI�� ��ȿ�� ���, �� AAIController Ÿ���� ���

AI->BrainComponent->StopLogic(TEXT("Death"));
->AI�� �극�� ������Ʈ�� ������ �ߴ�
->Death"��� ���ڿ��� ���ڷ� �����Ͽ� Ư�� ������ �ߴ�

BrainComponent�� AAIController�� ��� ���� �� �ϳ���, �극�� ������ �����ϴ� ������Ʈ
StopLogic(TEXT("Death"))�� �극�� ������Ʈ�� Ư�� ������ �ߴܽ�Ű�� �Լ�


mMesh->SetSimulatePhysics(true);
->��� �� �޽ÿ� ���� �ùķ��̼��� Ȱ��ȭ

else->�����ߴٸ�
(�Ʒ� ������ mHitTimerHandle�� ��ȿ���� ���� ������ Ÿ�̸Ӹ� �����ϴ� ����)

if (!mHitTimerHandle.IsValid())
->mHitTimerHandle�� ��ȿ���� ������ Ȯ���մϴ�. 
��, ������ ������ Ÿ�̸Ӱ� ���� ���� ������ �������� �˻�

GetWorld()->GetTimerManager().SetTimer(mHitTimerHandle, this,
				&AAIPawn::HitTimer, 0.2f);
->
GetTimerManager().SetTimer �Լ��� ����Ͽ� Ÿ�̸Ӹ� ����
mHitTimerHandle: Ÿ�̸� �ڵ��, Ÿ�̸Ӹ� ���߿� �����ϰų� ������ �� ����.
this: Ÿ�̸� �ݹ� �Լ��� ���� ��ü. ���⼭�� AAIPawn Ŭ������ �ν��Ͻ��� ���� ��ü�� �ǹ�
&AAIPawn::HitTimer: Ÿ�̸Ӱ� ����� �� ȣ��Ǵ� �Լ�
�� ��� AAIPawn Ŭ������ HitTimer �Լ��� �ݹ����� �����

0.2f: Ÿ�̸��� �ֱ��, 0.2�ʸ��� �� ���� HitTimer �Լ� ȣ��

����, �� �ڵ��mHitTimerHandle�� ��ȿ���� ���� �� 0.2�� �������� �ֱ������� 
HitTimer �Լ��� ȣ���ϴ� Ÿ�̸Ӹ� �����մϴ�. 
�̸� ���� ������ �ൿ�̳� �ݺ����� ������ ������ �� �ִ�. 

mHit = true;:
->mHit ������ true�� ����
-> ���ظ� ���� ���¸� ��Ÿ���� ���� �÷��׷� ����. 
��, ���ظ� ���� ���¸� ��Ÿ���� ���� mHit ������ true�� ����

for (auto& Mtrl : mMaterialArray):
->mMaterialArray�� �ִ� ������ ������ ���� �ݺ�

Mtrl->SetVectorParameterValue(TEXT("HitColor"), FVector(1.0, 0.0, 0.0));
->���� ����(Mtrl)�� ���� HitColor��� ���� �Ķ���� ���� ����
-> ��� FVector(1.0, 0.0, 0.0)�� RGB ������, ���� ���� ��Ÿ���ϴ�. ���� HitColor�� ���� ������ �����Ǿ� �ð����� ȿ���� ǥ��
->�� �κ��� �ַ� ���ظ� ���� �κ��� �����ϴ� �� ���� �� �ִ�.

return Dmg;:
->�Լ��� ���ط�(Dmg)�� ��ȯ

�� �ڵ��� �ֿ� ������ ���ظ� ���� ���¸� ��Ÿ���� ���� mHit�� true�� �����ϰ�, 
�ð������� ���ظ� ���� �κ��� �����ϱ� ���� ������ HitColor�� �����ϴ� ��

*/

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//�θ� Ŭ������ AActor�� Tick �Լ��� ȣ���Ͽ� �⺻���� ƽ ����� ����

	/*
	AddMovementInput(GetActorForwardVector());
	->AddMovementInput �Լ��� ����Ͽ� ���͸� ���� �������� �̵�
	�� �κ��� DeltaTime�� �������� �ʾƼ� �̵� �ӵ��� ����
	->
	AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false);
	�ȿ� ���� ���캸��
	WorldDirection: �̵��� ������ ��Ÿ���� ����
	ScaleValue: �̵� �ӵ��� �����ϴ� ������ ��. �⺻���� 1.0f
	bForce: true�� �����ϸ� �̵��� ��� �߻��ϵ��� �����մϴ�. �⺻���� false


	if (mDissolveEnable)
	{
		mDissolveCurrentTime += DeltaTime;
		->mDissolveCurrentTime ������ DeltaTime�� ���Ͽ� ����� �ð��� ����

		if (mDissolveCurrentTime >= mDissolveTime)
			Destroy();
		->Dissolve ȿ���� ���� �ð��� ������ �� �ش� ���͸� �ı�

		// ������ ���Ѵ�.
		float	Ratio = mDissolveCurrentTime / mDissolveTime;
		Ratio = 1.f - Ratio;
		Ratio = Ratio * 2.f - 1.f;

		for (auto& Mtrl : mMaterialArray)
		{
			Mtrl->SetScalarParameterValue(TEXT("Dissolve"), Ratio);
		}


		->
		float	Ratio = mDissolveCurrentTime / mDissolveTime;
		->Ratio ������ mDissolveCurrentTime�� mDissolveTime���� ���� ���� ������, 
		�̴� ���� Dissolve ȿ���� ����� ������ ��Ÿ��
		->mDissolveCurrentTime�� ���� Dissolve�� ����� �ð��̸�, 
		mDissolveTime�� ��ü Dissolve�� �ɸ��� �ð�


		Ratio = 1.f - Ratio;:
		->Ratio�� 1���� ���� ���� Dissolve ���� ������ �Ųٷ� �����
		�̷��� �ϸ� Dissolve�� ������ �� Ratio�� 0�� �ǰ�, �ð��� ������ ���� 1�� �����ϰ� ��.

		Ratio = Ratio * 2.f - 1.f;:
		->Ratio�� 2�� ���ϰ� 1�� ���� ���� ����
		�̷��� �����ν� Ratio�� ������ [-1, 1]�� ���εǰ� ��.
		�̷��� ������ Ư�� ȿ���� �ִϸ��̼ǿ��� ���Ǵ� ��찡 �����ϴ�.


		Ratio = 1.f - Ratio;:
		Ratio = Ratio * 2.f - 1.f;
		�� ��ȯ�� �����Ͽ�, Ratio ���� �ʱ� ���¿������� � ������ ��ȭ�ϴ� ������ �����ϰ� 
		�ش� ������ �߾��� 0���� ����
		�̷��� �ϸ� �ð��� ���� Ratio�� ��ȭ�� Ư�� �������� ����ǵ��� ���� �� �ִ�.


		for (auto& Mtrl : mMaterialArray):
		->mMaterialArray�� �ִ� ������ ������ ���� �ݺ�


		Mtrl->SetScalarParameterValue(TEXT("Dissolve"), Ratio);
		->���� ����(Mtrl)�� ���� Dissolve ȿ���� ��Ÿ���� ��Į�� �Ķ������ Dissolve�� Ratio ���� ����
		->�̸� ���� Dissolve ȿ���� �ð��� ���� ���ϵ��� ����.

		����,�� �ڵ�� Dissolve ȿ���� �����ϱ� ���� �ð��� ���� ���ϴ� ������ Ratio ���� ����ϰ�, 
		�̸� ������ �����Ͽ� �ð����� ȿ���� ����

	}
	
	*/

}

void AAIPawn::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}
/*
�浹 �������� �����ϴ� ���� ����
�� �Լ��� ��ȯ���� void��, ��� ���� ��ȯ���� ����.
�Ű����� const FName& Name�� �����Ϸ��� �浹 �������� �̸��� ��Ÿ��

mBody->SetCollisionProfileName(Name);:
SetCollisionProfileName(Name)�� UCapsuleComponent�� ��� �Լ���, 
�ش� �浹 ��ü�� �浹 �������� ������ �̸�(Name)���� ����


����, �� �Լ��� AAIPawn Ŭ������ mBody��� �浹 ��ü�� �浹 �������� ������ �̸����� �����ϴ� ����
�浹 �������� �Ϲ������� �浹 �� ���� Ư���� �����ϴ� �� ���Ǹ�, ���� ��� "BlockAllDynamic"�� ���� �̸� ���ǵ� �������� ���� �� �ִ�.
*/

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
/*

HitTimer()
->Ÿ�̸� �̺�Ʈ��, Ư�� �ð� ���ݸ��� � ������ ������ �� ����

mHit = false;
-> ���� ������ ���� ���� ���·� ����

for (auto& Mtrl : mMaterialArray)
->mMaterialArray�� �ִ� ��� ���� �ν��Ͻ��� ���� �ݺ�

Mtrl->SetVectorParameterValue(TEXT("HitColor"),
			FVector(1.0, 1.0, 1.0));
->
Mtrl�� ���� �ݺ��Ǵ� ���� ���� �ν��Ͻ�
SetVectorParameterValue�Լ��� ����Ͽ� HitColor��� �̸��� ���� �Ķ���Ϳ� Ư�� RGB�� ����.
�� ��쿣 ������� �����Ͽ��� ��� ������ ���� ���·� ���ư����� ��.

SetVectorParameterValue()
->���� ���� �߿� ��Ÿ�ӿ��� ������ �Ӽ��� �����ϰų� �ִϸ��̼� ȿ���� �ִ� �� ���

GetWorld()->GetTimerManager().ClearTimer(mHitTimerHandle);
->mHitTimerHandle�̶�� Ÿ�̸� �ڵ� Ŭ����. 
�̷ν� ���� ���� ���� Ÿ�̸Ӱ� �����ǰ� ���̻� HitTimer�Լ� ȣ����� X
: 
�����ϸ�, Ư�� �ð� ���� Ȱ��ȭ�� HitColor�� ���� ���·� �����ϰ�, 
mHit������ false�� �����Ͽ� Ư�� ������ �������� �ʰ� ��.

*/




void AAIPawn::DeathEnd()
{
	// Dissolve�� Ȱ��ȭ�Ѵ�.
	for (auto& Mtrl : mMaterialArray)
	{
		Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"),
			1.f);
		/*
		SetScalarParameterValue �Լ��� ����Ͽ� UMaterialInstanceDynamic�� ��Į�� �Ű������� ����
		"DissolveEnable"�� �����Ϸ��� ��Į�� �Ű������� �̸��̸�, 
		1.f�� �ش� ��Į�� �Ű������� ���� ��. ���⼭ 1.f�� Ȱ��ȭ�� ��Ÿ��

		��Į�� �Ű������� ����Ͽ� UMaterialInstanceDynamic�� �Ӽ��� �����ϴ� ���� 
		������ Ư�� ȿ���� �Ӽ��� �����ϴ� �� ����.
		��Į�� �Ű������� ���� ���� ��Ÿ���Ƿ� �ַ� � Ư���̳� ȿ���� ������ ������ �� ����.
		
		*/

	}

	mDissolveEnable = true;
}

/*
	AI ��Ʈ�ѷ� Ŭ�������� ���Ǵ� �� ���� ���� �Լ�
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	OnPossess(APawn* aPawn)
	->AI ��Ʈ�ѷ��� AI ĳ���͸� ������ �� ȣ���.
	APawn* aPawn �Ű������� ������ AI ĳ���Ϳ� ���� �����Ͱ� ���޵�.
	�Ϲ������� �� �Լ������� AI ĳ���͸� �ʱ�ȭ�ϰų� �����̳� Ư�� ������ �����ϴ� ���� �ʱ� ������ ����


	OnUnPossess()
	->AI ��Ʈ�ѷ��� AI ĳ������ ������ ������ �� ȣ���.
	������ �����ϴ� ������ �ַ� AI ĳ���Ͱ� ����ϰų� Ư�� ��Ȳ���� ������ ������ ��
	�� �Լ������� ������ ������ AI ĳ���Ϳ� ���� ���� �۾��̳� �߰����� ������ ������ �� �ִ�.

*/


