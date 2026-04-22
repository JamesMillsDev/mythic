// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MythicStatComponent.generated.h"

class IMythicSaveInterface;
class UMythicStatContainer;
class UMythicStat;

UCLASS(ClassGroup = ("Mythic"), meta = (BlueprintSpawnableComponent))
class MYTHIC_API UMythicStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMythicStatComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	/** Gets the current stat container and its information. */
	UFUNCTION(BlueprintPure, Category = "Mythic|Stats")
	UMythicStatContainer* GetStatContainer() const;

	/**
	 * Serialises the contents of the generated stat container into the passed interface.
	 * @param SaveObject The object this component is being serialised into.
	 */
	UFUNCTION(BlueprintCallable, Category = "Mythic|Save")
	void SerializeStats(TScriptInterface<IMythicSaveInterface> SaveObject) const;

	/**
	 * Deserializes the contents of the generated stat container from the passed interface.
	 * @param SaveObject The object this component is deserialising from.
	 */
	UFUNCTION(BlueprintCallable, Category = "Mythic|Save")
	void DeserializeStats(TScriptInterface<IMythicSaveInterface> SaveObject) const;

public:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	/** The template of stats that will be used to generate the runtime variants. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Mythic", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMythicStatContainer> StatsTemplate;

	/** Tag to identify this component's container in the save object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mythic|Save", meta = (AllowPrivateAccess = true))
	FName SaveTag = "Default";

	/** The runtime generated container of the template stats. This is the object that is being managed. */
	UPROPERTY()
	TObjectPtr<UMythicStatContainer> GeneratedStats;

};
