// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Components/MythicStatComponent.h"

#include "Data/MythicSaveInterface.h"
#include "Stats/Data/MythicStat.h"
#include "Stats/Data/MythicStatContainer.h"

// Sets default values for this component's properties
UMythicStatComponent::UMythicStatComponent(const FObjectInitializer& ObjectInitializer) :
	Super{ObjectInitializer}
{
	SetIsReplicatedByDefault(true);
}

UMythicStatContainer* UMythicStatComponent::GetStatContainer() const
{
	return GeneratedStats;
}

void UMythicStatComponent::SerializeStats(const TScriptInterface<IMythicSaveInterface> SaveObject) const
{
	if (!IsValid(GeneratedStats) || !SaveObject)
	{
		return;
	}

	IMythicSaveInterface::Execute_SerializeStatContainer(
	                                                     SaveObject.GetObject(), GeneratedStats, SaveTag
	                                                    );
}

void UMythicStatComponent::DeserializeStats(const TScriptInterface<IMythicSaveInterface> SaveObject) const
{
	if (!IsValid(GeneratedStats) || !SaveObject)
	{
		return;
	}

	IMythicSaveInterface::Execute_DeserializeStatContainer(
	                                                       SaveObject.GetObject(), GeneratedStats, SaveTag
	                                                      );
}

// Called when the game starts
void UMythicStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// Only generate the replicated object when this is a server object.
	if (GetOwnerRole() == ROLE_Authority && IsValid(StatsTemplate))
	{
		GeneratedStats = DuplicateObject(StatsTemplate, StatsTemplate->GetOuter());

		// Register the container itself
		AddReplicatedSubObject(GeneratedStats);

		// Register each individual stat so their Values replicate
		for (TObjectPtr Stat : GeneratedStats->GetStats())
		{
			if (!IsValid(Stat))
			{
				continue;
			}

			AddReplicatedSubObject(Stat);
		}
	}
}

void UMythicStatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}