//// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADefaultAIController();

private:
	//에셋 지정할 수 잇게 만들꺼임.
	UPROPERTY(Category = AI, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> mAITree;

	UPROPERTY(Category = AI, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardData> mAIBlackboard;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
