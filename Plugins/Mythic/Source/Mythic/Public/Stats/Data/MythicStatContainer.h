// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "Utility/BranchResult.h"

#include "MythicStatContainer.generated.h"

class UMythicStat;

/**
 * 
 */
UCLASS(BlueprintType)
class MYTHIC_API UMythicStatContainer : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE const TArray<TObjectPtr<UMythicStat>>& GetStats() const
	{
		return Stats;
	}

public:
	UMythicStatContainer(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable, Category = "Mythic|Stats", meta = (ExpandEnumAsExecs = "OutBranches"))
	void FindStat(EBranchResult& OutBranches, FName ID, UMythicStat*& Stat);

public:
	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mythic", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UMythicStat>> Stats;

	UPROPERTY()
	TMap<FName, TObjectPtr<UMythicStat>> StatMap;

};
