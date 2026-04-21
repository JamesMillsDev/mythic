// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/MythicFloatStat.h"

#include "Net/UnrealNetwork.h"

float UMythicFloatStat::GetTypedValue() const
{
	return Value;
}

void UMythicFloatStat::SetTypedValue(const float NewValue)
{
	Value = NewValue;
}

void UMythicFloatStat::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMythicFloatStat, Value);
}
