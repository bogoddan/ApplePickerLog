// Fill out your copyright notice in the Description page of Project Settings.



#include "ApplePickerWidget.h"
#include "ApplePickerGM.h"



void AApplePickerGM::BeginPlay()
{
	Super::BeginPlay();

	spawnBaskets();

	//setupWidget();
}

void AApplePickerGM::spawnBaskets()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Start"));
	for (int i = 0; i < BasketsCount; ++i) {
		FVector new_loc = BasketStart + BasketShift * i;
		auto new_basket = GetWorld()->SpawnActor<ABasket>(BasketToSpawn, new_loc, FRotator(0.0f, 0.0f, 0.0f));
		BasketsContainer.Add(new_basket);
	}
}

void AApplePickerGM::setupWidget()
{
	if (IsValid(WidgetClass)) {
		WidgetObj = Cast<UApplePickerWidget>(CreateWidget(GetWorld(), WidgetClass));
		if (WidgetObj != nullptr) {
			WidgetObj->AddToViewport();
		}
	}
}

void AApplePickerGM::deleteBasket()
{
	if (BasketsContainer.Num() > 0) {
		BasketsContainer[BasketsContainer.Num() - 1]->Destroy();
		BasketsContainer.RemoveAt(BasketsContainer.Num() - 1);
	}

}
