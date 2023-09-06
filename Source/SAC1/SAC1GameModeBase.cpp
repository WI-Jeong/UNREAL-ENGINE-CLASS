// Copyright Epic Games, Inc. All Rights Reserved.


#include "SAC1GameModeBase.h"
#include "Player/MagicioinCharacter.h"
#include "Player/SAC1PlayerState.h"

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

	//player state class를 지정한다.
	PlayerStateClass = ASAC1PlayerState::StaticClass();

}

void ASAC1GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ASAC1GameModeBase::InitGameState()
{
	Super::InitGameState();
}

void ASAC1GameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// auto : 대입받는 값의 타입으로 자동으로 결정된다.
	auto PlayerState=NewPlayer->GetPlayerState<ASAC1PlayerState>();

	if (IsValid(PlayerState))
		PlayerState->InitPlayerData(EPlayerJob::Magicion);
}

void ASAC1GameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASAC1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
