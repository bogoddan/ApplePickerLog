// Fill out your copyright notice in the Description page of Project Settings.

#include "Basket.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasket::ABasket()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	//RootComponent = Mesh; 

	Mesh->SetupAttachment(RootComponent); //  кріплю меш до рута?


}

// Called when the game starts or when spawned
void ABasket::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABasket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	moveBasketByMouse();
}

// Called to bind functionality to input
void ABasket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasket::moveBasketByMouse()
{
	float mouseX;
	float mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);

	FVector new_loc(GetActorLocation().X, mouseX, GetActorLocation().Z);
	SetActorLocation(new_loc);
}

