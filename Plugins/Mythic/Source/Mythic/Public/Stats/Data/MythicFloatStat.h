// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MythicStat.h"
#include "MythicFloatStat.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Stat (Float)", EditInlineNew)
class MYTHIC_API UMythicFloatStat : public UMythicStat, public TMythicStatValue<float>
{
	GENERATED_BODY()

public:
	virtual float GetTypedValue() const override;
	virtual void SetTypedValue(float NewValue) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, SaveGame)
	float Value = 0.f;

};
