// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TargetDetect.h"
#include "../AIPawn.h"
#include "AIController.h" // 이거 추가해주니까 컴파일 오류안나네...



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

	//BehaviorTreeComponent를 이용하여 AIController를 얻어올 수 있다.
	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* AIPawn = Cast<AAIPawn>(Controller->GetPawn());

	//AIPawn이 아닐 경우 정지.
	if (!IsValid(AIPawn))
		return;

	FHitResult result;

	FCollisionQueryParams  param(NAME_None, false, AIPawn);


	bool Collision = GetWorld()->SweepSingleByChannel(result, 
		AIPawn->GetActorLocation(), AIPawn->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel9,
		FCollisionShape::MakeSphere(800.f), param);

	//디버깅용(에디터)으로 출력한다.
#if ENABLE_DRAW_DEBUG

	//Collisioin값에 따라 ture일 경우 red, false일 경우 green으로 출력한다.
	FColor DrawColor = Collision ? FColor::Red : FColor::Green;

	//FRotatioinMatrix::MakeFromZ(GetActorForwardVector()):Z축을 캐릭터
	//의 앞쪽으로 만들어주는 회전 행렬을 구한다. (FMatrix로 결과가 나온다.)
	//그래서 .ToQuat()을 이용해서 FQuat(회전값)으로 변환한다.

	DrawDebugSphere(GetWorld(), AIPawn->GetActorLocation(), 800.f,
		20, DrawColor, false, 0.35f);
#endif


	// 충돌이 되었다면 Blackboard의 Target 변수에 충돌된 물체를 지정하고
	// 충돌이 아니면 nullptr을 지정한다.
	if (Collision)
	{
		// Controller로부터 Blackboard를 얻어와서 Target을 지정한다.
		// FHitResult의 GetActor() 함수는 충돌된 액터를 가져오는 함수이다.
		Controller->GetBlackboardComponent()->SetValueAsObject(
			TEXT("Target"), result.GetActor());

	}

	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(
			TEXT("Target"), nullptr);
	}




}
