// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplePickerGS.h"
#include <ApplePickerPrototype/ApplePickerGM.h>

void AApplePickerGS::UpdateApplesCollected_Implementation()
{
}

int32 LogRecord::id = 0;

void AApplePickerGS::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(LogsTimerManager, this, &AApplePickerGS::updateLogs, secondsBetweenLogsUpdate, true, 0.5f);
}

//void AApplePickerGS::updateLogs()
//{
//	GEngine->ClearOnScreenDebugMessages();
//	FString a("");
//	a.AppendInt(logs_new.Num());
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, a);
//	auto log_it = logs_new.FindKey(0);
//	//while ( log_it != nullptr) {
//
//	//	logs_new.Remove(*log_it);
//	//    log_it = logs_new.FindKey(0);
//	//}
//	a.Reset();
//	a.AppendInt(logs_new.Num());
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, a);
//	for (auto& it : logs_new) {
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, it.Key.log_message);
//		it.Value-= secondsBetweenLogsUpdate;
//	}
//}

void AApplePickerGS::updateLogs()
{
	GEngine->ClearOnScreenDebugMessages();// crear logs
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Update Logs");
	
	TArray<FString> res;

	for (auto& it : logs) {					//	
		if (shouldLogBeDeleted(it.Value)) {	//delete logs which might expire
			logs.Remove(it.Key, it.Value);	//
		}
	}

	logs.ValueSort([](const LogRecord& A, const LogRecord& B) {
		return B.log_message.Compare(A.log_message, ESearchCase::IgnoreCase) < 0;
		});

	for (auto& it : logs) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, it.Value.log_message);
		res.Add(it.Value.log_message);
		it.Value.timeRemain-=secondsBetweenLogsUpdate;
	}

	RefreshLogs(res);

}

void AApplePickerGS::RefreshLogs_Implementation(const TArray<FString>& LogRecords)
{

}

void AApplePickerGS::addLog(LogTypes type, const LogRecord& log)
{
	logs.AddUnique(type, log);
}

bool AApplePickerGS::shouldLogBeDeleted(const LogRecord& log)
{
	return log.timeRemain <= 0;
}
