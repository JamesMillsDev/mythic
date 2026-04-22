// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stats/Data/Values/MythicStatValueType.h"
#include "MythicStatTypeFloat.generated.h"

USTRUCT()
struct FMythicStatFloat
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float Value = 0.f;
};

/**
 * 
 */
UCLASS(DisplayName = "Float")
class MYTHIC_API UMythicStatTypeFloat : public UMythicStatValueType
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
	float DefaultValue = 0.f;

};
