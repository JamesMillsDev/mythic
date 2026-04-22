// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/Values/MythicStatValue.h"

void FMythicStatValue::Initialize()
{
	if (!TypeDescriptor.IsValid())
	{
		return;
	}
	
	TypeDescriptor->FreeValue(Memory.GetData());
	Memory.SetNumZeroed(TypeDescriptor->GetValueSize());
	TypeDescriptor->InitializeValue(Memory.GetData());
}

bool FMythicStatValue::IsValid() const
{
	return TypeDescriptor.IsValid() && Memory.Num() > 0;
}

bool FMythicStatValue::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	if (!TypeDescriptor.IsValid())
	{
		bOutSuccess = false;
		return false;
	}

	const FProperty* Prop = TypeDescriptor->GetValueProperty();
	if (Prop == nullptr)
	{
		bOutSuccess = false;
		return false;
	}

	if (Ar.IsLoading())
	{
		// Receiving — make sure memory is ready before deserializing into it
		Memory.SetNumZeroed(TypeDescriptor->GetValueSize());
		TypeDescriptor->InitializeValue(Memory.GetData());
	}

	Prop->NetSerializeItem(Ar, Map, Memory.GetData());

	bOutSuccess = true;
	return true;
}
