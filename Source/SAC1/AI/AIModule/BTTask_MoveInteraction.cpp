// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveInteraction.h"
#include "../AIPawn.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIState.h"
#include "../DefaultAIController.h" // �̰� �߰�����

UBTTask_MoveInteraction::UBTTask_MoveInteraction()
{
	NodeName = TEXT("MoveInteraction");

	// TickTask �Լ��� ȣ���Ѵ�.(true�� �ؾ� ȣ���)
	bNotifyTick = true;

	// OnTaskFinished �Լ��� ȣ���Ѵ�.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveInteraction::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	// AIPawn�� �ƴ� ��� ����.
	if (!IsValid(AIPawn))
		return EBTNodeResult::Failed;

	// AIController�� ������ �ִ� BlackboardComponent�� �̿��Ͽ� Target��
	// ���´�.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		Controller->StopMovement(); //������ �̵� ���߱�

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	// Ÿ���� ��ġ�� NavMesh�� Ȱ���Ͽ� ���� ã�� �̵���Ų��.
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Run);


	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_MoveInteraction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_MoveInteraction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_MoveInteraction::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}


//������Ͽ� �Լ��� ��������� ������. �Լ� ����/���� ���ְ� ���뤷���� 
//�������ߴ��� ���� �ȳ�. Super�̰� �Ⱦ��� ������ �ص� �Ǵ����� ����.