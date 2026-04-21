// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MythicStatComponent.generated.h"

class UMythicStatContainer;
class UMythicStat;

UCLASS(ClassGroup = ("Mythic"), meta = (BlueprintSpawnableComponent))
class MYTHIC_API UMythicStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMythicStatComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintPure, Category = "Mythic|Stats")
	UMythicStatContainer* GetStatContainer() const;

public:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Mythic", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMythicStatContainer> Stats;
	
};
