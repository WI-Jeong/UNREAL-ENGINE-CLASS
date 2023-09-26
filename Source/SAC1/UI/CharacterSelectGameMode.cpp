// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectGameMode.h"
#include "CharacterSelectWidget.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{
	DefaultPawnClass = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget>	CharacterUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_CharacterSelecet.UI_CharacterSelecet_C'"));

	if (CharacterUIClass.Succeeded())
		mCharacterUIClass = CharacterUIClass.Class;
}

void ACharacterSelectGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ACharacterSelectGameMode::InitGameState()
{
	Super::InitGameState();
}

void ACharacterSelectGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NewPlayer->SetShowMouseCursor(true);

	FInputModeUIOnly	input;
	NewPlayer->SetInputMode(input);
}

void ACharacterSelectGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mCharacterUIClass))
	{
		mCharacterWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), mCharacterUIClass);

		if (IsValid(mCharacterWidget))
		mCharacterWidget->AddToViewport();
	}

}

void ACharacterSelectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
