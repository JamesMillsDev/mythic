// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Components/MythicStatComponent.h"


#include "Stats/Data/MythicStat.h"
#include "Stats/Data/MythicStatContainer.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UMythicStatComponent::UMythicStatComponent(const FObjectInitializer& ObjectInitializer)
	: Super{ ObjectInitializer }
{
	SetIsReplicatedByDefault(true);
}

UMythicStatContainer* UMythicStatComponent::GetStatContainer() const
{
	return Stats;
}

// Called when the game starts
void UMythicStatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority && IsValid(Stats))
	{
		// Register the container itself
		AddReplicatedSubObject(Stats);

		// Register each individual stat so their Values replicate
		for (TObjectPtr Stat : Stats->GetStats())
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

	DOREPLIFETIME(UMythicStatComponent, Stats);
}