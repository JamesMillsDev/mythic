// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/MythicStat.h"

#include "Net/UnrealNetwork.h"

DEFINE_FUNCTION(UMythicStat::execGetValue)
{
    Stack.StepCompiledIn<FProperty>(nullptr);
    void* OutValueAddr = Stack.MostRecentPropertyAddress;
    FProperty* OutValueProp = Stack.MostRecentProperty;
    P_FINISH;
    P_NATIVE_BEGIN;

    FProperty* StatProp = nullptr;
    void* StatValuePtr = nullptr;

    if (!P_THIS->GetValueProperty(StatProp, StatValuePtr))
    {
        UE_LOG(LogTemp, Warning, TEXT("GetValue: Stat has no value (%s)"), *P_THIS->GetName());
        return;
    }

    if (OutValueProp->SameType(StatProp))
    {
        // Types match — direct copy
        StatProp->CopyCompleteValue(OutValueAddr, StatValuePtr);
    }
    else if (CastField<FNumericProperty>(StatProp) && CastField<FNumericProperty>(OutValueProp))
    {
        // Numeric promotion — int <-> float etc.
        double Val = CastField<FNumericProperty>(StatProp)->GetFloatingPointPropertyValue(StatValuePtr);
        CastField<FNumericProperty>(OutValueProp)->SetFloatingPointPropertyValue(OutValueAddr, Val);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GetValue: Type mismatch on stat '%s' — pin type does not match stat type"), *P_THIS->GetName());
    }

    P_NATIVE_END;
}

DEFINE_FUNCTION(UMythicStat::execSetValue)
{
    Stack.StepCompiledIn<FProperty>(nullptr);
    void* InValueAddr = Stack.MostRecentPropertyAddress;
    FProperty* InValueProp = Stack.MostRecentProperty;
    P_FINISH;
    P_NATIVE_BEGIN;

    FProperty* StatProp = nullptr;
    void* StatValuePtr = nullptr;

    if (!P_THIS->GetValueProperty(StatProp, StatValuePtr))
    {
        UE_LOG(LogTemp, Warning, TEXT("SetValue: Stat has no value (%s)"), *P_THIS->GetName());
        return;
    }

    if (InValueProp->SameType(StatProp))
    {
        StatProp->CopyCompleteValue(StatValuePtr, InValueAddr);
    }
    else if (CastField<FNumericProperty>(StatProp) && CastField<FNumericProperty>(InValueProp))
    {
        double Val = CastField<FNumericProperty>(InValueProp)->GetFloatingPointPropertyValue(InValueAddr);
        CastField<FNumericProperty>(StatProp)->SetFloatingPointPropertyValue(StatValuePtr, Val);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetValue: Type mismatch on stat '%s'"), *P_THIS->GetName());
    }

    P_NATIVE_END;
}

void UMythicStat::PostInitProperties()
{
	Super::PostInitProperties();
	if (ValueType)
	{
		Value.TypeDescriptor = ValueType;
		Value.Initialize();
	}
}

bool UMythicStat::GetValueProperty(FProperty*& OutProp, void*& OutValuePtr)
{
	if (!Value.IsValid())
	{
		return false;
	}
	
	OutProp = ValueType->GetValueProperty();
	OutValuePtr = Value.Memory.GetData();
	return OutProp != nullptr;
}

FString UMythicStat::DescribeValue() const
{
	if (!Value.IsValid())
	{
		return TEXT("(no value)");
	}

	return ValueType->DescribeValue(Value.Memory.GetData());
}

bool UMythicStat::IsSupportedForNetworking() const
{
	return true;
}

void UMythicStat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UMythicStat, Value);
}

void UMythicStat::PostLoad()
{
	Super::PostLoad();
	if (ValueType)
	{
		Value.TypeDescriptor = ValueType;
		Value.Initialize();
	}
}

#if WITH_EDITOR
void UMythicStat::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UMythicStat, ValueType))
	{
		Value.TypeDescriptor = ValueType;
		Value.Initialize();
	}
}
#endif
