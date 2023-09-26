// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

void UStartWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    LOG(TEXT("NativeOnInitialized()"));
}

void UStartWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    LOG(TEXT("NativePreConstruct()"));
}

void UStartWidget::NativeConstruct()
{
    Super::NativeConstruct();

    LOG(TEXT("NativeConstruct()"));

    mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
    mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));

    mStartButton->OnClicked.AddDynamic(this, &UStartWidget::StartButtonClick);
    mStartButton->OnHovered.AddDynamic(this, &UStartWidget::StartButtonHovered);
    mStartButton->OnUnhovered.AddDynamic(this, &UStartWidget::StartButtonUnHovered);

    mExitButton->OnClicked.AddDynamic(this, &UStartWidget::ExitButtonClick);
    mExitButton->OnHovered.AddDynamic(this, &UStartWidget::ExitButtonHovered);
    mExitButton->OnUnhovered.AddDynamic(this, &UStartWidget::ExitButtonUnHovered);

    // UserWidget이 가지고 있는 모든 Animation을 반복하며 찾는다.
    UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

    for (int32 i = 0; i < WidgetClass->Animations.Num(); ++i)
    {
        FString Name = WidgetClass->Animations[i]->GetName();
        LOG(TEXT("Name : %s"), *Name);
    }
}

void UStartWidget::NativeDestruct()
{
    Super::NativeDestruct();

    LOG(TEXT("NativeDestruct()"));
}

void UStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

FReply UStartWidget::NativeOnKeyChar(const FGeometry& InGeometry,
    const FCharacterEvent& InCharEvent)
{
    FReply Reply = Super::NativeOnKeyChar(InGeometry, InCharEvent);

    return Reply;
}

FReply UStartWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry,
    const FKeyEvent& InKeyEvent)
{
    FReply Reply = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);

    return Reply;
}

FReply UStartWidget::NativeOnKeyDown(const FGeometry& InGeometry,
    const FKeyEvent& InKeyEvent)
{
    FReply Reply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

    return Reply;
}

FReply UStartWidget::NativeOnKeyUp(const FGeometry& InGeometry,
    const FKeyEvent& InKeyEvent)
{
    FReply Reply = Super::NativeOnKeyUp(InGeometry, InKeyEvent);

    return Reply;
}

FReply UStartWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    return Reply;
}

FReply UStartWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

    return Reply;
}

FReply UStartWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

    return Reply;
}

FReply UStartWidget::NativeOnMouseMove(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

    return Reply;
}

void UStartWidget::NativeOnMouseEnter(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UStartWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UStartWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

    return Reply;
}

FReply UStartWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

    return Reply;
}

void UStartWidget::NativeOnDragDetected(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent,
        OutOperation);
}

void UStartWidget::NativeOnDragEnter(const FGeometry& InGeometry,
    const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDragEnter(InGeometry, InDragDropEvent,
        InOperation);
}

void UStartWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    Super::NativeOnDragLeave(InDragDropEvent,
        InOperation);
}

bool UStartWidget::NativeOnDragOver(const FGeometry& InGeometry,
    const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    bool Reply = Super::NativeOnDragOver(InGeometry, InDragDropEvent,
        InOperation);

    return Reply;
}

bool UStartWidget::NativeOnDrop(const FGeometry& InGeometry,
    const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    bool Reply = Super::NativeOnDrop(InGeometry, InDragDropEvent,
        InOperation);

    return Reply;
}

void UStartWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    Super::NativeOnDragCancelled(InDragDropEvent,
        InOperation);
}

FReply UStartWidget::NativeOnTouchGesture(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply Reply = Super::NativeOnTouchGesture(InGeometry,
        InGestureEvent);

    return Reply;
}

FReply UStartWidget::NativeOnTouchStarted(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply Reply = Super::NativeOnTouchStarted(InGeometry,
        InGestureEvent);

    return Reply;
}

FReply UStartWidget::NativeOnTouchMoved(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply Reply = Super::NativeOnTouchMoved(InGeometry,
        InGestureEvent);

    return Reply;
}

FReply UStartWidget::NativeOnTouchEnded(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply Reply = Super::NativeOnTouchEnded(InGeometry,
        InGestureEvent);

    return Reply;
}

FReply UStartWidget::NativeOnMotionDetected(const FGeometry& InGeometry,
    const FMotionEvent& InMotionEvent)
{
    FReply Reply = Super::NativeOnMotionDetected(InGeometry,
        InMotionEvent);

    return Reply;
}

FReply UStartWidget::NativeOnTouchForceChanged(const FGeometry& MyGeometry,
    const FPointerEvent& TouchEvent)
{
    FReply Reply = Super::NativeOnTouchForceChanged(MyGeometry,
        TouchEvent);

    return Reply;
}

void UStartWidget::StartButtonClick()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharaterSelect"));
}

void UStartWidget::StartButtonHovered()
{
    PlayAnimation(StartButtonScaleAnim);
}

void UStartWidget::StartButtonUnHovered()
{
    PlayAnimation(StartButtonScaleAnim, 0.f, 1, EUMGSequencePlayMode::Reverse);
}

void UStartWidget::ExitButtonClick()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
        EQuitPreference::Quit, true);
}

void UStartWidget::ExitButtonHovered()
{
    UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

    for (int32 i = 0; i < WidgetClass->Animations.Num(); ++i)
    {
        FString Name = WidgetClass->Animations[i]->GetName();

        if (Name == TEXT("ExitButtonScaleAnim_INST"))
        {
            PlayAnimation(WidgetClass->Animations[i]);
            break;
        }
    }
}

void UStartWidget::ExitButtonUnHovered()
{
    UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

    for (int32 i = 0; i < WidgetClass->Animations.Num(); ++i)
    {
        FString Name = WidgetClass->Animations[i]->GetName();

        if (Name == TEXT("ExitButtonScaleAnim_INST"))
        {
            PlayAnimation(WidgetClass->Animations[i], 0.f, 1, EUMGSequencePlayMode::Reverse);
            break;
        }
    }
}