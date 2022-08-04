// Fill out your copyright notice in the Description page of Project Settings.

#include "Apple.h"
#include "Floor.h"
#include "Kismet/GameplayStatics.h"
#include "ApplePickerGS.h"
#include "Basket.h"
#include "ApplePickerGM.h"

enum class LogTypes;
class Log;

// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AApple::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();
	GameStateRef = Cast<AApplePickerGS>(UGameplayStatics::GetGameState(this));

}

void AApple::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AFloor>(OtherActor) != nullptr) {
		processOverlapByFloor();
	}
	else if (Cast<ABasket>(OtherActor) != nullptr) {
		processOverlapByBasket();
	}
	Destroy();
}

void AApple::processOverlapByBasket()
{
	GameStateRef->LogsContainer.AddUnique(LogTypes::OverlapByBasket, LogRecord("Basket", 5));
	Destroy();
	GameStateRef->UpdateApplesCollected();
}

void AApple::processOverlapByFloor()
{
	GameStateRef->LogsContainer.AddUnique(LogTypes::OverlapByFloor, LogRecord("Apple", 15));
	Cast<AApplePickerGM>(GetWorld()->GetAuthGameMode())->deleteBasket();
	Destroy();
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

