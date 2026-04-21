// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "StatContainerFactory.generated.h"

/**
 * 
 */
UCLASS()
class MYTHICEDITOR_API UStatContainerFactory : public UFactory
{
	GENERATED_BODY()
public:
	UStatContainerFactory();

public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
