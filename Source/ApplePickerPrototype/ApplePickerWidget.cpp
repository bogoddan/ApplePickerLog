// Fill out your copyright notice in the Description page of Project Settings.

#include "ApplePickerWidget.h"

void UApplePickerWidget::NativeConstruct()
{
	//UTextBlock Text;
	//FText ftext;
	//ftext.FromString(FString("Hi text"));
	//Text.SetText(ftext);
	//UWidget* widget_ptr = &Text;
	UWidget* widget_ptr = (CreateWidget(GetWorld(), UTextBlock::StaticClass()));
	Cast<UTextBlock>(widget_ptr)->SetText(FText::FromString("123"));
	LogsSpace->AddChild(widget_ptr);
}

void UApplePickerWidget::updateApplesCollected(int32 ApplesCollected)
{
	ApplesCollectedCounter->SetText(FText::AsNumber(ApplesCollected));
}


