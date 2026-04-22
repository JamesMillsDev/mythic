// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/Values/Types/MythicStatTypeFloat.h"

uint16 UMythicStatTypeFloat::GetValueSize() const
{
	return sizeof(float);
}

void UMythicStatTypeFloat::InitializeValue(uint8* Memory) const
{
	*reinterpret_cast<float*>(Memory) = DefaultValue;
}

void UMythicStatTypeFloat::CopyValue(uint8* Dest, const uint8* Src) const
{
	*reinterpret_cast<float*>(Dest) = *reinterpret_cast<const float*>(Src);
}

FProperty* UMythicStatTypeFloat::GetValueProperty() const
{
	return FindFProperty<FFloatProperty>(FMythicStatFloat::StaticStruct(),
	                                     GET_MEMBER_NAME_CHECKED(FMythicStatFloat, Value));
}

FString UMythicStatTypeFloat::DescribeValue(const uint8* Memory) const
{
	return FString::SanitizeFloat(*reinterpret_cast<const float*>(Memory));
}
