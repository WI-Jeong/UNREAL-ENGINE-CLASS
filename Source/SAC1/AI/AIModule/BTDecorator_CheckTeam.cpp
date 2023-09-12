// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckTeam.h"
#include "../AIPawn.h"
#include "../AIState.h"
#include "../../Player/PlayerCharacter.h"
#include "../DefaultAIController.h" ///!!이거 추가해줬더니 오류 안남!!

UBTDecorator_CheckTeam::UBTDecorator_CheckTeam()
{
}

bool UBTDecorator_CheckTeam::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// BehaviorTreeComponent를 이용하여 AIController를 얻어올 수 있다.
	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	// AIPawn이 아닐 경우 정지.
	if (!IsValid(AIPawn))
		return false;

	//float	TypeDistance = 0.f;

	//switch (mCheckType)
	//{
	//case ECheckDistanceType::Attack:
	//	TypeDistance = AIPawn->GetAIState()->GetAttackDistance();
	//	break;
	//case ECheckDistanceType::Interaction:
	//	TypeDistance = AIPawn->GetAIState()->GetInteractionDistance();
	//	break;
	//}

	// AIController가 가지고 있는 BlackboardComponent를 이용하여 Target을
	// 얻어온다.
	AActor* CheckTarget = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(CheckTarget))
		return false;


	FVector	AILoc = AIPawn->GetActorLocation(); 
	FVector	TargetLoc = CheckTarget->GetActorLocation();

	AILoc.Z -= AIPawn->GetHalfHeight();
	TargetLoc.Z -= AIPawn->GetHalfHeight();

	float Distance = FVector::Distance(AILoc, TargetLoc);

	// 거리에서 각 물체들의 캡슐 반경을 빼준다.
	Distance -= AIPawn->GetCapsuleRadius();

	// Target의 RootComponent를 얻어와서 Capsule인지 확인한다.
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(CheckTarget->GetRootComponent());

	if (IsValid(Capsule))
	{
		Distance -= Capsule->GetScaledCapsuleRadius();
	}

	if (Distance > AIPawn->GetAIState()->GetAttackDistance())
		return false;

	APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	//LOG(TEXT("CheckDist : %.5f Dist : %.5f"), TypeDistance, Distance);

	if (IsValid(Target))
	{
		LOG(TEXT("AI Team : %d TargetTeam : %d"), (int32)AIPawn->GetTeam(),
			(int32)Target->GetTeam());
		return AIPawn->GetTeam() == Target->GetTeam();
	}

	AAIPawn* TargetPawn = Cast<AAIPawn>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (IsValid(TargetPawn))
		return AIPawn->GetTeam() == TargetPawn->GetTeam();

	return false;
}


