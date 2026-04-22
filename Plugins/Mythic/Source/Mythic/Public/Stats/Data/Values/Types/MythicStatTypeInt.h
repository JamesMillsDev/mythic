// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Data/Values/MythicStatValueType.h"
#include "MythicStatTypeInt.generated.h"

USTRUCT()
struct FMythicStatInt
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Value = 0;
};

/**
 * 
 */
UCLASS(DisplayName = "Integer")
class MYTHIC_API UMythicStatTypeInt : public UMythicStatValueType
{
	GENERATED_BODY()

public:
	virtual uint16 GetValueSize() const override;

	virtual void InitializeValue(uint8* Memory) const override;

	virtual void CopyValue(uint8* Dest, const uint8* Src) const override;

	virtual FProperty* GetValueProperty() const override;

	virtual FString DescribeValue(const uint8* Memory) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	int32 DefaultValue = 0;

};
