// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ApplePickerGS.generated.h"

/**
 * 
 */

enum class LogTypes : int32 {
	OverlapByFloor,
	OverlapByBasket
};


struct LogRecord {

public:

	LogRecord(FString message, int32 time) : log_message(message), time_remain(time) {
		log_id = id++;
	}

	bool operator==(const LogRecord& other) {
		return log_id == other.log_id;
	}

	static int32 id;

	UPROPERTY(EditAnywhere)
	FString log_message;

	int32 time_remain;
	int32 log_id;

};

UCLASS()
class APPLEPICKERPROTOTYPE_API AApplePickerGS : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ApplesCollected")
	int32 ApplesCollected_cpp = 0;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UpdateHUD")
	void UpdateApplesCollected();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UpdateHUD")
	void RefreshLogs(const TArray<FString>& LogRecords);

	void AddLogRecord(LogTypes type, const LogRecord& log);

	bool ShouldLogBeDeleted(const LogRecord& log);

	void UpdateLogs();

	TMultiMap<LogTypes, LogRecord> LogsContainer;

	int32 HighScore = 0;
	FName SaveHSSlotName = "High Score";

	FTimerHandle LogsTimerManager;

	float SecondsBetweenLogsUpdate = 0.3;

};
