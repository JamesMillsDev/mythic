// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MythicStatValueType.h"
#include "MythicStatValue.generated.h"

USTRUCT()
struct MYTHIC_API FMythicStatValue
{
	GENERATED_BODY()

public:
	TArray<uint8> Memory;
	TWeakObjectPtr<UMythicStatValueType> TypeDescriptor;

	// Called after TypeDescriptor is set to allocate and initialize memory
	void Initialize();

	bool IsValid() const;

	bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);
	
};

template<>
struct TStructOpsTypeTraits<FMythicStatValue> : public TStructOpsTypeTraitsBase2<FMythicStatValue>
{
	enum { WithNetSerializer = true };
};