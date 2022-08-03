// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ApplePickerWidget.generated.h"

/**
 * 
 */
UCLASS()
class APPLEPICKERPROTOTYPE_API UApplePickerWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;

	UPROPERTY(meta = ( BindWidget ) , EditAnywhere)
		class UTextBlock* ApplesCollectedCounter;

	UPROPERTY(meta = (BindWidget), EditAnywhere)
		class UVerticalBox* LogsSpace;

	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<UUserWidget> WidgetToAdd;

public:
	void updateApplesCollected(int32 ApplesCollected);

	//void updateLogs();
};
