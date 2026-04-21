// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MythicSaveInterface.h"

#include "GameFramework/SaveGame.h"
#include "MythicSaveGame.generated.h"

// Wrapper so UHT accepts TArray<uint8> as a TMap value
USTRUCT()
struct FMythicSerializedContainer
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<uint8> Bytes;
};

/**
 * 
 */
UCLASS()
class MYTHIC_API UMythicSaveGame : public USaveGame, public IMythicSaveInterface
{
	GENERATED_BODY()

public:
	// IStatSaveInterface — default implementation using byte serialization
	virtual void SerializeStatContainer_Implementation(
		UMythicStatContainer* Container, FName ContainerTag) override;

	virtual void DeserializeStatContainer_Implementation(
		UMythicStatContainer* Container, FName ContainerTag) override;

private:
	// Keyed by ContainerTag so multiple components can share one save object
	UPROPERTY()
	TMap<FName, FMythicSerializedContainer> SerializedContainers;

};
