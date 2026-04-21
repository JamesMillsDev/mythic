// Fill out your copyright notice in the Description page of Project Settings.

#include "Stats/Data/StatContainerAssetTypeActions.h"

#include "MythicEditor.h"

#include "Stats/Data/MythicStatContainer.h"

UClass* FStatContainerAssetTypeActions::GetSupportedClass() const
{
	return UMythicStatContainer::StaticClass();
}

FText FStatContainerAssetTypeActions::GetName() const
{
	return INVTEXT("Stat Container");
}

FColor FStatContainerAssetTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

uint32 FStatContainerAssetTypeActions::GetCategories()
{
	return FMythicEditorModule::GetModule().GetMythicCategory();
}
