// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MythicStatValueType.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories)
class MYTHIC_API UMythicStatValueType : public UObject
{
	GENERATED_BODY()

public:
	virtual uint16 GetValueSize() const
	{
		return 0;
	}

	virtual void InitializeValue(uint8* Memory) const
	{
	}

	virtual void FreeValue(uint8* Memory) const
	{
	}

	virtual void CopyValue(uint8* Dest, const uint8* Src) const
	{
	}

	virtual FProperty* GetValueProperty() const
	{
		return nullptr;
	}

	virtual FString DescribeValue(const uint8* Memory) const
	{
		return TEXT("");
	}

};
