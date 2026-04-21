// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/StatContainerFactory.h"

#include "Stats/Data/MythicStatContainer.h"

UStatContainerFactory::UStatContainerFactory()
{
	SupportedClass = UMythicStatContainer::StaticClass();
	bCreateNew = true;
}

UObject* UStatContainerFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UMythicStatContainer>(InParent, InClass, InName, Flags, Context);
}
