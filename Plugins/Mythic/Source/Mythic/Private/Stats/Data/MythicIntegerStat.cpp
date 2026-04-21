// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/MythicIntegerStat.h"

#include "Net/UnrealNetwork.h"

int32 UMythicIntegerStat::GetTypedValue() const
{
	return Value;
}

void UMythicIntegerStat::SetTypedValue(const int32 NewValue)
{
	Value = NewValue;
}

void UMythicIntegerStat::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMythicIntegerStat, Value);
}
