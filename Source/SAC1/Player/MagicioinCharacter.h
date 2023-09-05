// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "MagicioinCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API AMagicioinCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AMagicioinCharacter();

public:
	virtual void Attack1();
	virtual void Attack2();
	//
	virtual void Attack3();
	//
};
