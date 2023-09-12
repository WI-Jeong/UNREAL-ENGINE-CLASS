// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "../AIPawn.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIState.h"
#include "../DefaultAIController.h" 

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");

	// TickTask 함수를 호출한다.(true로 해야 호출됨)
	bNotifyTick = true;

	// OnTaskFinished 함수를 호출한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	Super::ExecuteTask(OwnerComp, NodeMemory);

	// BehaviorTreeComponent를 이용하여 AIController를 얻어올 수 있다.
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
		Controller->StopMovement(); //이제는 이동이 아니라 어택이기 때문에 꼭 StopMovement

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle); //타겟 없으면 idle로

		return EBTNodeResult::Failed;
	}

	//이제는 이동시킬 이유가 없음. 이동이 아니라 공격을 해야하기 때문에 아래 SimpleMoveToActor 코드 지워주기
	// SimpleMoveToActor: 길을 찾아서 이동하는 코드
	// 타겟의 위치로 NavMesh를 활용하여 길을 찾아 이동시킨다.
	//UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	//애니메이션 run이 아니라 attack으로 바궈주기
	//AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Run);
	AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Attack);


	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);



	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	// AIPawn이 아닐 경우 정지.
	if (!IsValid(AIPawn))
	{
		//Task를 종료시킨다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement(); //강제로 이동 멈추기

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return;
	}

	// AIController가 가지고 있는 BlackboardComponent를 이용하여 Target을
	// 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement(); //강제로 이동 멈추기

		AIPawn->GetAIAnimInstance()->ChangeAnim(EAIAnimType::Idle);

		return;
	}

	//현재 이동 방향을 향하도록 AI를 회전시킨다.
	FVector Dir = AIPawn->GetMovementComponent()->Velocity;
	Dir.Z = 0.f;

	//Dir은 현재 크기까지 가지고 있다. 그러므로 방향만을 남기기 위해서 벡터를
	//정규화 시켜준다.
	Dir.Normalize();

	AIPawn->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));


	// 타겟과 AIPawn과의 거리를 구한다.
	FVector	AILoc = AIPawn->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z -= AIPawn->GetHalfHeight();
	TargetLoc.Z -= AIPawn->GetHalfHeight();

	float Distance = FVector::Distance(AILoc, TargetLoc);

	// 거리에서 각 물체들의 캡슐 반경을 빼준다.
	Distance -= AIPawn->GetCapsuleRadius();

	// Target의 RootComponent를 얻어와서 Capsule인지 확인한다.
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(Capsule))
	{
		Distance -= Capsule->GetScaledCapsuleRadius();
	}

	if (Distance <= AIPawn->GetAIState()->GetAttackDistance())
	{
		// Task를 종료시킨다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		Controller->StopMovement();
	}


}

void UBTTask_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
