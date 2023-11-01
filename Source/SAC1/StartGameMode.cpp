// Fill out your copyright notice in the Description page of Project Settings.

#include "StartGameMode.h"
#include "UI/StartWidget.h"

AStartGameMode::AStartGameMode()
{
	DefaultPawnClass = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget>	StartUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Start.UI_Start_C'"));

	if (StartUIClass.Succeeded())
		mStartUIClass = StartUIClass.Class;
}

void AStartGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AStartGameMode::InitGameState()
{
	Super::InitGameState( );
}

void AStartGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NewPlayer->SetShowMouseCursor(true);

	FInputModeUIOnly	input;
	NewPlayer->SetInputMode(input);
}

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	//if (IsValid(mStartUIClass))
	//{
	//	mStartWidget = CreateWidget<UStartWidget>(GetWorld(), mStartUIClass);

	//	if (IsValid(mStartWidget))
	//		mStartWidget->AddToViewport();
	//}
}

void AStartGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
