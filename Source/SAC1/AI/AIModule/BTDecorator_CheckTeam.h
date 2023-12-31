// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckTeam.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API UBTDecorator_CheckTeam : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckTeam();

 protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const;
	
};
