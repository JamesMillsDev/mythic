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
	UFUNCTION(BlueprintPure, Category = "Mythic|Stats")
	UMythicStatContainer* GetStatContainer() const;

	UFUNCTION(BlueprintCallable, Category = "Mythic|Save")
	void SerializeStats(TScriptInterface<IMythicSaveInterface> SaveObject) const;
	
	UFUNCTION(BlueprintCallable, Category = "Mythic|Save")
	void DeserializeStats(TScriptInterface<IMythicSaveInterface> SaveObject) const;
	
public:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Mythic", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMythicStatContainer> Stats;

	// Tag to identify this component's container in the save object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mythic|Save", meta = (AllowPrivateAccess = true))
	FName SaveTag = "Default";
	
};
