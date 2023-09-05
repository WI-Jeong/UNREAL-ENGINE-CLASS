// Copyright Epic Games, Inc. All Rights Reserved.


#include "SAC1GameModeBase.h"
#include "Player/MagicioinCharacter.h"

ASAC1GameModeBase::ASAC1GameModeBase()
{
	// 클래스 레퍼런스 애셋을 불러오고자 할 경우 에셋의 경로에서 
	//가장 마지막에 _C를 반드시 붙여줘야 한다.
	static ConstructorHelpers::FClassFinder<ACharacter> BlueprintPawn(TEXT("/Script/Engine.Blueprint'/Game/BlueprintTest/TestPlayerCharacter.TestPlayerCharacter_C'"));

	if (BlueprintPawn.Succeeded())
	{
		// DefaultPawnClass = BlueprintPawn.Class;
	 }


	//AMagicioinCharacter::StaticClass() : AMagicioinCharacter 클래스의 
	//클래스 레퍼런스를 얻어온다.
	DefaultPawnClass = AMagicioinCharacter::StaticClass();

}
