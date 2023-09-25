// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "SAC1PhysicalMaterial.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API USAC1PhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivatedAccess="true"))
	TObjectPtr<USoundBase> mSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivatedAccess = "true"))
	TObjectPtr<UParticleSystem> mParticle;

public:
	USoundBase* GetSound()	const 
	{
		return mSound;
	}

	UParticleSystem* GetParticle()	const
	{
		return mParticle;
	}
	
};
