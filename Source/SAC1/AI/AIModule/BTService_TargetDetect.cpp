// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TargetDetect.h"
#include "../AIPawn.h"
#include "AIController.h" // �̰� �߰����ִϱ� ������ �����ȳ���...



UBTService_TargetDetect::UBTService_TargetDetect()
{
	NodeName = TEXT("TargetDetect");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_TargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//BehaviorTreeComponent�� �̿��Ͽ� AIController�� ���� �� �ִ�.
	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	//AIPawn�� �ƴ� ��� ����.
	if (!IsValid(AIPawn))
		return;

	FHitResult result;

	FCollisionQueryParams  param(NAME_None, false, AIPawn);


	bool Collision = GetWorld()->SweepSingleByChannel(result, 
		AIPawn->GetActorLocation(), AIPawn->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel9,
		FCollisionShape::MakeSphere(800.f), param);

	//������(������)���� ����Ѵ�.
#if ENABLE_DRAW_DEBUG

	//Collisioin���� ���� ture�� ��� red, false�� ��� green���� ����Ѵ�.
	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	//FRotatioinMatrix::MakeFromZ(GetActorForwardVector()):Z���� ĳ����
	//�� �������� ������ִ� ȸ�� ����� ���Ѵ�. (FMatrix�� ����� ���´�.)
	//�׷��� .ToQuat()�� �̿��ؼ� FQuat(ȸ����)���� ��ȯ�Ѵ�.

	DrawDebugSphere(GetWorld(), AIPawn->GetActorLocation(), 800.f,
		20, DrawColor, false, 0.35f);
#endif


	// �浹�� �Ǿ��ٸ� Blackboard�� Target ������ �浹�� ��ü�� �����ϰ�
	// �浹�� �ƴϸ� nullptr�� �����Ѵ�.
	if (Collision)
	{
		// Controller�κ��� Blackboard�� ���ͼ� Target�� �����Ѵ�.
		// FHitResult�� GetActor() �Լ��� �浹�� ���͸� �������� �Լ��̴�.
		Controller->GetBlackboardComponent()->SetValueAsObject(
			TEXT("Target"), result.GetActor());

	}

	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(
			TEXT("Target"), nullptr);
	}




}
