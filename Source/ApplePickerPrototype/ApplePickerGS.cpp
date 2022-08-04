// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplePickerGS.h"
#include <ApplePickerPrototype/ApplePickerGM.h>

int32 LogRecord::id = 0;

void AApplePickerGS::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(LogsTimerManager, this, &AApplePickerGS::UpdateLogs, SecondsBetweenLogsUpdate, true, 0.5f);
}


void AApplePickerGS::UpdateLogs()
{	
	TArray<FString> res;

	for (auto& it : LogsContainer) {		//	
		if (ShouldLogBeDeleted(it.Value)) {					//delete logs which might expire
			LogsContainer.Remove(it.Key, it.Value);	//
		}
	}

	LogsContainer.ValueSort([](const LogRecord& A, const LogRecord& B) {
		return A.log_message.Compare(B.log_message, ESearchCase::IgnoreCase) < 0;
		});

	for (auto& it : LogsContainer) {
		res.Add(it.Value.log_message);
		it.Value.time_remain-=SecondsBetweenLogsUpdate;
	}

	RefreshLogs(res);

}

void AApplePickerGS::AddLogRecord(LogTypes type, const LogRecord& log)
{
	LogsContainer.AddUnique(type, log);
}

bool AApplePickerGS::ShouldLogBeDeleted(const LogRecord& log)
{
	return log.time_remain <= 0;
}
