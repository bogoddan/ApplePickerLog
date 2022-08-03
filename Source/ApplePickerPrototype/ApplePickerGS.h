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


class LogRecord {

public:
	LogRecord() = default;
	LogRecord(LogRecord&&) = default;
	LogRecord(const LogRecord&) = default;
	LogRecord& operator=(LogRecord&&) = default;
	LogRecord& operator=(const LogRecord&) = default;

	LogRecord(FString message, int32 time) : log_message(message), timeRemain(time) {
		log_id = id++;
	}

	bool operator==(const LogRecord& other) {
		return log_id == other.log_id;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "From ==");
	}

	//bool operator< (const Log& other) const
	//{
	//	return other.log_message.Compare(log_message, ESearchCase::IgnoreCase) < 0;
	//}

	static int32 id;

	UPROPERTY(EditAnywhere)
	FString log_message;

	int32 timeRemain;
	int32 log_id;

};

struct LogCompare
{
	bool operator() (const LogRecord& lhs, const LogRecord& rhs) const
	{
		return lhs.log_message.Compare(rhs.log_message, ESearchCase::IgnoreCase) < 0;
	}
};

UCLASS()
class APPLEPICKERPROTOTYPE_API AApplePickerGS : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BPNativeEventF")
	void updateLogs();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ApplesCollected")
	int32 ApplesCollected_cpp = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BPNativeEventF")
	void UpdateApplesCollected();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BPNativeEventF")
		void RefreshLogs(const TArray<FString>& LogRecords);

	void addLog(LogTypes type, const LogRecord& log);

	bool shouldLogBeDeleted(const LogRecord& log);

	//TSortedMap<Log, int32, FDefaultAllocator, LogCompare> logs_new;

	//UPROPERTY(EditAnywhere, Category = "logs")
	TMultiMap<LogTypes, LogRecord> logs;

	int32 HighScore = 0;
	FName SaveHSSlotName = "High Score";

	FTimerHandle LogsTimerManager;

	float secondsBetweenLogsUpdate = 1;

};
