// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckTargetDistance.h"
#include "../AIPawn.h"
#include "../AIState.h"
#include "../DefaultAIController.h" ///!!�̰� �߰�������� ���� �ȳ�!!

UBTDecorator_CheckTargetDistance::UBTDecorator_CheckTargetDistance()
{
	mCheckType = ECheckDistanceType::Interaction;
}

bool UBTDecorator_CheckTargetDistance::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// BehaviorTreeComponent�� �̿��Ͽ� AIController�� ���� �� �ִ�.
	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	// AIPawn�� �ƴ� ��� ����.
	if (!IsValid(AIPawn))
		return false;

	float	TypeDistance = 0.f;

	switch (mCheckType)
	{
	case ECheckDistanceType::Attack:
		TypeDistance = AIPawn->GetAIState()->GetAttackDistance();
		break;
	case ECheckDistanceType::Interaction:
		TypeDistance = AIPawn->GetAIState()->GetInteractionDistance();
		break;
	}

	// AIController�� ������ �ִ� BlackboardComponent�� �̿��Ͽ� Target��
	// ���´�.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	FVector	AILoc = AIPawn->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	AILoc.Z -= AIPawn->GetHalfHeight();
	TargetLoc.Z -= AIPawn->GetHalfHeight();

	float Distance = FVector::Distance(AILoc, TargetLoc);

	// �Ÿ����� �� ��ü���� ĸ�� �ݰ��� ���ش�.
	Distance -= AIPawn->GetCapsuleRadius();

	// Target�� RootComponent�� ���ͼ� Capsule���� Ȯ���Ѵ�.
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(Capsule))
	{
		Distance -= Capsule->GetScaledCapsuleRadius();
	}

	LOG(TEXT("CheckDist : %.5f Dist : %.5f"), TypeDistance, Distance);

	return Distance <= TypeDistance;
}
