// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
//
//void UCharacterSelectWidget::NativeOnInitialized()
//{
//
//	Super::NativeOnInitialized();
//}
//
//void UCharacterSelectWidget::NativePreConstruct()
//{
//	Super::NativePreConstruct();
//}
//
//void UCharacterSelectWidget::NativeConstruct()
//{
//		Super::NativeConstruct();
//
//
		//mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
		//mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));

		//mStartButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::StartButtonClick);
		//mStartButton->OnHovered.AddDynamic(this, &UCharacterSelectWidget::StartButtonHovered);
		//mStartButton->OnUnhovered.AddDynamic(this, &UCharacterSelectWidget::StartButtonUnHovered);

		//mExitButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::ExitButtonClick);
		//mExitButton->OnHovered.AddDynamic(this, &UCharacterSelectWidget::ExitButtonHovered);
		//mExitButton->OnUnhovered.AddDynamic(this, &UCharacterSelectWidget::ExitButtonUnHovered);

		//// UserWidget이 가지고 있는 모든 Animation을 반복하며 찾는다.
		//UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

		//for (int32 i = 0; i < WidgetClass->Animations.Num(); ++i)
		//{
		//	FString Name = WidgetClass->Animations[i]->GetName();
		//	LOG(TEXT("Name : %s"), *Name);
		//}
//}
//
//void UCharacterSelectWidget::NativeDestruct()
//{
//	Super::NativeDestruct();
//}
//
//void UCharacterSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//	Super::NativeTick(MyGeometry, InDeltaTime);
//}
//
//FReply UCharacterSelectWidget::NativeOnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharEvent)
//{
//	FReply Reply = Super::NativeOnKeyChar(InGeometry, InCharEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
//{
//	FReply Reply = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
//{
//
//	FReply Reply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
//{
//	FReply Reply = Super::NativeOnKeyUp(InGeometry, InKeyEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//
//	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//
//	FReply Reply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//
//	FReply Reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	FReply Reply = Super::NativeOnMouseMove(InGeometry, InMouseEvent);
//
//	return Reply;
//}
//
//void UCharacterSelectWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
//
//}
//
//void UCharacterSelectWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
//{
//	Super::NativeOnMouseLeave(InMouseEvent);
//}
//
//FReply UCharacterSelectWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	FReply Reply = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//
//	FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
//
//	return Reply;
//}
//
//void UCharacterSelectWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
//{
//	Super::NativeOnDragDetected(InGeometry, InMouseEvent,
//		OutOperation);
//
//}
//
//void UCharacterSelectWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	Super::NativeOnDragEnter(InGeometry, InDragDropEvent,
//		InOperation);
//
//}
//
//void UCharacterSelectWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	Super::NativeOnDragLeave(InDragDropEvent,
//		InOperation);
//}
//
//bool UCharacterSelectWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	bool Reply = Super::NativeOnDragOver(InGeometry, InDragDropEvent,
//		InOperation);
//
//	return Reply;
//}
//
//bool UCharacterSelectWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	bool Reply = Super::NativeOnDrop(InGeometry, InDragDropEvent,
//		InOperation);
//
//	return Reply;
//}
//
//void UCharacterSelectWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	Super::NativeOnDragCancelled(InDragDropEvent,
//		InOperation);
//}
//
//FReply UCharacterSelectWidget::NativeOnTouchGesture(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
//{
//	FReply Reply = Super::NativeOnTouchGesture(InGeometry,
//		InGestureEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
//{
//	FReply Reply = Super::NativeOnTouchStarted(InGeometry,
//		InGestureEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
//{
//	FReply Reply = Super::NativeOnTouchMoved(InGeometry,
//		InGestureEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
//{
//	FReply Reply = Super::NativeOnTouchEnded(InGeometry,
//		InGestureEvent);
//
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnMotionDetected(const FGeometry& InGeometry, const FMotionEvent& InMotionEvent)
//{
//
//	FReply Reply = Super::NativeOnMotionDetected(InGeometry,
//		InMotionEvent);
//
//	return Reply;
//}
//
//FReply UCharacterSelectWidget::NativeOnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
//{
//
//	FReply Reply = Super::NativeOnTouchForceChanged(MyGeometry,
//		TouchEvent);
//
//	return Reply;
//}
//
//void UCharacterSelectWidget::StartButtonClick()
//{
//	UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharaterSelect"));
//}
//
//void UCharacterSelectWidget::StartButtonHovered()
//{
//	PlayAnimation(StartButtonScaleAnim);
//}
//
//void UCharacterSelectWidget::StartButtonUnHovered()
//{
//	PlayAnimation(StartButtonScaleAnim, 0.f, 1, EUMGSequencePlayMode::Reverse);
//}
//
//void UCharacterSelectWidget::ExitButtonClick()
//{
//	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
//		EQuitPreference::Quit, true);
//}
//
//void UCharacterSelectWidget::ExitButtonHovered()
//{
//	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
//
	//for (int32 i = 0; i < WidgetClass->Animations.Num(); ++i)
	//{
	//	FString Name = WidgetClass->Animations[i]->GetName();

	//	if (Name == TEXT("ExitButtonScaleAnim_INST"))
	//	{
	//		PlayAnimation(WidgetClass->Animations[i]);
	//		break;
	//	}
	//}
//}
//
//void UCharacterSelectWidget::ExitButtonUnHovered()
//{
//	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
//
	//for (int32 i = 0; i < WidgetClass->Animations.Num(); ++i)
	//{
	//	FString Name = WidgetClass->Animations[i]->GetName();

	//	if (Name == TEXT("ExitButtonScaleAnim_INST"))
	//	{
	//		PlayAnimation(WidgetClass->Animations[i], 0.f, 1, EUMGSequencePlayMode::Reverse);
	//		break;
	//	}
	//}
//}
