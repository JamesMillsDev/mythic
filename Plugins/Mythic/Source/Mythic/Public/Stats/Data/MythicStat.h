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
	template <typename T>
	bool TryGetValue(T& OutValue);

	template <typename T>
	bool TrySetValue(const T& InValue);

	virtual void PostInitProperties() override;

	// Entry point for the CustomThunk GetValue / SetValue functions
	bool GetValueProperty(FProperty*& OutProp, void*& OutValuePtr);

	FString DescribeValue() const;

	virtual bool IsSupportedForNetworking() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostLoad() override;

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

private:
	UPROPERTY(Replicated)
	FMythicStatValue Value;
};

// Detect any USTRUCT - they all have a static StaticStruct() method
template <typename T>
concept CUEStruct = requires { T::StaticStruct(); };

template <typename T>
bool UMythicStat::TryGetValue(T& OutValue)
{
	FProperty* Prop = nullptr;
	void* Memory = nullptr;

	if (!GetValueProperty(Prop, Memory))
	{
		return false;
	}

	using TDecayed = std::decay_t<T>;

	if constexpr (std::is_same_v<TDecayed, float>)
	{
		if (const FFloatProperty* P = CastField<FFloatProperty>(Prop))
		{
			OutValue = P->GetPropertyValue(Memory);
			return true;
		}
	}
	else if constexpr (std::is_same_v<TDecayed, int32>)
	{
		if (const FIntProperty* P = CastField<FIntProperty>(Prop))
		{
			OutValue = P->GetPropertyValue(Memory);
			return true;
		}
	}
	else if constexpr (TIsUEnumClass<TDecayed>::Value || std::is_enum_v<TDecayed>)
	{
		if (const FEnumProperty* P = CastField<FEnumProperty>(Prop))
		{
			OutValue = static_cast<TDecayed>(P->GetUnderlyingProperty()->GetSignedIntPropertyValue(Memory));
			return true;
		}
	}
	else if constexpr (CUEStruct<TDecayed>)
	{
		if (FStructProperty* P = CastField<FStructProperty>(Prop))
		{
			if (P->Struct == TDecayed::StaticStruct())
			{
				OutValue = *reinterpret_cast<const TDecayed*>(Memory);
				return true;
			}
		}
	}

	return false;
}

template <typename T>
bool UMythicStat::TrySetValue(const T& InValue)
{
	FProperty* Prop = nullptr;
	void* Memory = nullptr;

	if (!GetValueProperty(Prop, Memory))
	{
		return false;
	}

	using TDecayed = std::decay_t<T>;

	if constexpr (std::is_same_v<TDecayed, float>)
	{
		if (FFloatProperty* P = CastField<FFloatProperty>(Prop))
		{
			P->SetPropertyValue(Memory, InValue);
			return true;
		}
	}
	else if constexpr (std::is_same_v<TDecayed, int32>)
	{
		if (FIntProperty* P = CastField<FIntProperty>(Prop))
		{
			P->SetPropertyValue(Memory, InValue);
			return true;
		}
	}
	else if constexpr (TIsUEnumClass<TDecayed>::Value || std::is_enum_v<TDecayed>)
	{
		if (FEnumProperty* P = CastField<FEnumProperty>(Prop))
		{
			// Write through the underlying int property (usually uint8/int32)
			P->GetUnderlyingProperty()->SetIntPropertyValue(Memory, static_cast<int64>(InValue));
			return true;
		}
	}
	else if constexpr (CUEStruct<TDecayed>)
	{
		if (FStructProperty* P = CastField<FStructProperty>(Prop))
		{
			if (P->Struct == TDecayed::StaticStruct())
			{
				// CopySingleValue handles FString, TArray, etc. correctly
				// It calls the struct's copy assignment through the reflection layer
				P->CopySingleValue(Memory, &InValue);
				return true;
			}
		}
	}

	return false;
}
