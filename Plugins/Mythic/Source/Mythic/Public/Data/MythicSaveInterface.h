// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MythicSaveInterface.generated.h"

class UMythicStatContainer;

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UMythicSaveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYTHIC_API IMythicSaveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mythic|Save")
	void SerializeStatContainer(UMythicStatContainer* Container, FName ContainerTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mythic|Save")
	void DeserializeStatContainer(UMythicStatContainer* Container, FName ContainerTag);

};