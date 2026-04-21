// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MythicStat.generated.h"

template <typename T>
class TMythicStatValue
{
public:
	virtual ~TMythicStatValue() = default;
	
public:
	virtual T GetTypedValue() const = 0;
	virtual void SetTypedValue(T NewValue) = 0;

};

UCLASS(DisplayName = "Stat (Invalid)", BlueprintType, DefaultToInstanced, NotEditInlineNew)
class MYTHIC_API UMythicStat : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine))
	FText Description;

public:
	virtual bool IsSupportedForNetworking() const override;

};
