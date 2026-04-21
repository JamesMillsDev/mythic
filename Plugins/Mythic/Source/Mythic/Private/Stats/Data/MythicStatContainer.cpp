// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/MythicStatContainer.h"

#include "Stats/Data/MythicStat.h"

UMythicStatContainer::UMythicStatContainer(const FObjectInitializer& ObjectInitializer)
	: Super{ ObjectInitializer }
{
}

void UMythicStatContainer::FindStat(EBranchResult& OutBranches, const FName ID, UMythicStat*& Stat)
{
	// Check if there is a state with this ID registered
	if (!StatMap.Contains(ID))
	{
		// There isn't, so return the failure branch and mark the stat as nullptr
		Stat = nullptr;
		OutBranches = EBranchResult::Failure;

		UE_LOG(LogBlueprint, Warning, TEXT("No Stat found for ID %s"), *ID.ToString());
		return;
	}

	// Return the success stat and set the stat to the correct one
	Stat = StatMap[ID];
	OutBranches = EBranchResult::Success;
}

bool UMythicStatContainer::IsSupportedForNetworking() const
{
	return true;
}

void UMythicStatContainer::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
}

#if WITH_EDITOR
void UMythicStatContainer::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);

	// Clear out the existing map
	StatMap.Empty();

	// Iterate over each Stat
	for (TObjectPtr Stat : Stats)
	{
		// Validate the stat, if it's not, skip it
		if (!IsValid(Stat))
		{
			continue;
		}

		// Construct a FName from the stat's name as a lower string
		const FName ID = FName(Stat->Name.ToString().ToLower());
		if (ID == NAME_None)
		{
			// The name is empty, so skip this
			continue;
		}

		// If a stat with the same name has already been registered, log an error and skip
		if (StatMap.Contains(ID))
		{
			UE_LOG(LogAssetData, Error, TEXT("Stat already exists"));
			continue;
		}

		StatMap.Add(ID, Stat);
	}
}
#endif
