// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Basket.h"
#include "ApplePickerWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ApplePickerGM.generated.h"

/**
 * 
 */
UCLASS()
class APPLEPICKERPROTOTYPE_API AApplePickerGM : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	TArray<ABasket*> BasketsContainer;
	FVector BasketStart{630,500,60};
	FVector BasketShift{0,0,60};
	int32 BasketsCount = 5;

	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<UApplePickerWidget> WidgetClass;

	UPROPERTY(EditAnywhere, Category = "Basket")
		TSubclassOf<ABasket> BasketToSpawn;



	void spawnBaskets();

	void setupWidget();

public:

	UPROPERTY(VisibleAnywhere, Category = "Runtime")
		class UApplePickerWidget* WidgetObj;

	virtual void BeginPlay() override;

	void deleteBasket();


};
