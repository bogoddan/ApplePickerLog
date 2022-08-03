// Fill out your copyright notice in the Description page of Project Settings.

#include "AppleTree.h"
#include <random>
#include "TimerManager.h"

// Sets default values
AAppleTree::AAppleTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAppleTree::BeginPlay()
{
	Super::BeginPlay();
	initializeEdges();
	GetWorldTimerManager().SetTimer(DropAppleTimerManager, this, &AAppleTree::dropApple, secondsBetweenAppleDrop, true, 0.5f);
	
}

void AAppleTree::initializeEdges()
{
	rightEdge = GetActorLocation().Y + gameFieldSize;
	leftEdge = GetActorLocation().Y - gameFieldSize;
}

bool AAppleTree::isTimeToChangeDirection(float currentY, float deltaSeconds)
{
	if (currentY > rightEdge || currentY < leftEdge || isTimeForRandomChangeDir(deltaSeconds)) {
		return true;
	}
	return false;
}

float AAppleTree::moveTree(float deltaSeconds)
{
	auto new_y = GetActorLocation().Y + speed * deltaSeconds;
	FVector new_loc(GetActorLocation().X, new_y, GetActorLocation().Z);
	SetActorLocation(new_loc);
	return new_y;
}

bool AAppleTree::isTimeForRandomChangeDir(float deltaSeconds)
{
	int chance = std::rand() % 100;
	if (chance <= chanceToChangeDirection*100*deltaSeconds) {
		return true;
	}
	return false;
}

void AAppleTree::changeDirection()
{
	speed *= -1;
}

void AAppleTree::dropApple()
{
	FVector new_loc(GetActorLocation().X + 100, GetActorLocation().Y, GetActorLocation().Z);
	GetWorld()->SpawnActor<AApple>(AppleThatDrops, new_loc, FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void AAppleTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float new_y_of_tree = moveTree(DeltaTime);
	if (isTimeToChangeDirection(new_y_of_tree, DeltaTime)) {
		changeDirection();
	}
}

