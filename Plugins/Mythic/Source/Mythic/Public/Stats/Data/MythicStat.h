// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MythicStatValue.h"
#include "UObject/Object.h"
#include "MythicStat.generated.h"

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, DisplayName = "Stat")
class MYTHIC_API UMythicStat : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default", meta = (MultiLine))
	FText Description;

	// Designer picks the type here — initializes memory when changed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Default")
	TObjectPtr<UMythicStatValueType> ValueType;

public:
	UFUNCTION(BlueprintPure, CustomThunk, Category = "Mythic|Stats",
		meta = (CustomStructureParam = "OutValue", DisplayName = "Get Value"))
	void GetValue(int32& OutValue) const;

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Mythic|Stats",
		meta = (CustomStructureParam = "InValue", DisplayName = "Set Value"))
	void SetValue(int32 InValue);

	DECLARE_FUNCTION(execGetValue);
	DECLARE_FUNCTION(execSetValue);

public:
	virtual void PostInitProperties() override;

	// Entry point for the CustomThunk GetValue / SetValue functions
	bool GetValueProperty(FProperty*& OutProp, void*& OutValuePtr);

	FString DescribeValue() const;

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

private:
	UPROPERTY(Replicated)
	FMythicStatValue Value;

};
