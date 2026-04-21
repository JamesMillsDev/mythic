// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MythicStat.h"
#include "MythicIntegerStat.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Stat (Integer)", EditInlineNew)
class MYTHIC_API UMythicIntegerStat : public UMythicStat, public TMythicStatValue<int32>
{
	GENERATED_BODY()

public:
	virtual int32 GetTypedValue() const override;
	virtual void SetTypedValue(int32 NewValue) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, SaveGame)
	int32 Value = 0;

};
