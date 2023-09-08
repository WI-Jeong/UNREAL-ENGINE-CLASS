// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveInteraction.h"
#include "../AIPawn.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIState.h"
#include "../DefaultAIController.h" // 이거 추가해줌

UBTTask_MoveInteraction::UBTTask_MoveInteraction()
{
	NodeName = TEXT("MoveInteraction");

	// TickTask 함수를 호출한다.(true로 해야 호출됨)
	bNotifyTick = true;

	// OnTaskFinished 함수를 호출한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveInteraction::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	// AIPawn이 아닐 경우 정지.
	if (!IsValid(AIPawn))
		return EBTNodeResult::Failed;

	// AIController가 가지고 있는 BlackboardComponent를 이용하여 Target을
	// 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		Controller->StopMovement(); //강제로 이동 멈추기

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	// 타겟의 위치로 NavMesh를 활용하여 길을 찾아 이동시킨다.
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


//헤더파일에 함수만 만들었더니 에러남. 함수 선언/정의 해주고 내용ㅇ쓰고 
//컴파일했더니 에러 안남. Super이거 안쓰고 생성만 해도 되는지는 몰루.