// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Interaction.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API UBTTask_Interaction : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_Interaction();

protected:
    // ExecuteTask 이 Task가 동작될때 호출된다.
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory);

    // AbortTask 작업을 중단할 때 들어온다.
    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory);

    // TickTask 매 프레임마다 동작한다.
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory, float DeltaSeconds);

    // OnTaskFinished Task가 종료될때 동작한다.
    virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory, EBTNodeResult::Type TaskResult);
	
};
