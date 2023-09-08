// Copyright Epic Games, Inc. All Rights Reserved.


#include "SAC1GameModeBase.h"
#include "Player/MagicioinCharacter.h"
#include "Player/SAC1PlayerState.h"
#include "SAC1GameState.h"
#include "AI/AIPawn.h"

ASAC1GameModeBase::ASAC1GameModeBase()
{
	// Ŭ���� ���۷��� �ּ��� �ҷ������� �� ��� �ּ��� ��ο���
	// ���� �������� _C �� �ݵ�� �ٿ���� �Ѵ�.
	static ConstructorHelpers::FClassFinder<ACharacter>	BlueprintPawn(TEXT("/Script/Engine.Blueprint'/Game/TestBlueprints/TestPlayerCharacter.TestPlayerCharacter_C'"));

	if (BlueprintPawn.Succeeded())
	{
		//DefaultPawnClass = BlueprintPawn.Class;
	}

	// AMagicionCharacter::StaticClass() : AMagicionCharacter Ŭ������
	// Ŭ���� ���۷����� ���´�.
	DefaultPawnClass = AMagicioinCharacter::StaticClass();
	//MagicioinCharacter �̰� ���ʿ� �� ��Ÿ�� ���·� ���Ŷ�..��¿��������......
	//�� ��� �̰ɷ� �����

	// Player State Class�� �����Ѵ�.
	PlayerStateClass = ASAC1PlayerState::StaticClass();

	GameStateClass = ASAC1GameState::StaticClass();

}

void ASAC1GameModeBase::InitGame(const FString& MapName, const FString& Options,
	FString& ErrorMessage)
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

	// auto : ���Թ޴� ���� Ÿ������ �ڵ����� �����ȴ�.
	auto PlayerState = NewPlayer->GetPlayerState<ASAC1PlayerState>();

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

