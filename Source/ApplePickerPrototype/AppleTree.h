// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Apple.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleTree.generated.h"

UCLASS()
class APPLEPICKERPROTOTYPE_API AAppleTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppleTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Init")
	void initializeEdges();

	UFUNCTION(BlueprintCallable, Category = "MoveRules")
	bool isTimeToChangeDirection(float currentY, float deltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "MoveRules")
	float moveTree(float deltaSeconds);

	bool isTimeForRandomChangeDir(float deltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "MoveRules")
	void changeDirection();

	UFUNCTION(BlueprintCallable, Category = "Apple")
		void dropApple();

	UPROPERTY(EditDefaultsOnly, Category = "StartStats")
	float speed = 800;

	float leftEdge=0;
	float rightEdge=1000;
	float chanceToChangeDirection = 0.1;
	float secondsBetweenAppleDrop = 0.5;
	float gameFieldSize = 500;

	UPROPERTY(EditAnywhere, Category = "Apple")
	TSubclassOf<AApple> AppleThatDrops;

	FTimerHandle DropAppleTimerManager;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
