// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/Values/Types/MythicStatTypeInt.h"

uint16 UMythicStatTypeInt::GetValueSize() const
{
	return sizeof(int32);
}

void UMythicStatTypeInt::InitializeValue(uint8* Memory) const
{
	*reinterpret_cast<int32*>(Memory) = DefaultValue;
}

void UMythicStatTypeInt::CopyValue(uint8* Dest, const uint8* Src) const
{
	*reinterpret_cast<int32*>(Dest) = *reinterpret_cast<const int32*>(Src);
}

FProperty* UMythicStatTypeInt::GetValueProperty() const
{
	return FindFProperty<FIntProperty>(FMythicStatInt::StaticStruct(),
									   GET_MEMBER_NAME_CHECKED(FMythicStatInt, Value));
}

FString UMythicStatTypeInt::DescribeValue(const uint8* Memory) const
{
	return FString::FromInt(*reinterpret_cast<const int32*>(Memory));
}
