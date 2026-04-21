// Copyright Epic Games, Inc. All Rights Reserved.

#include "MythicEditor.h"

#define LOCTEXT_NAMESPACE "FMythicEditorModule"

void FMythicEditorModule::StartupModule()
{
	MythicCategory = FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory("mythic", FText::FromString("Mythic"));
	
	StatContainerAssetTypeActions = MakeShared<FStatContainerAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(StatContainerAssetTypeActions.ToSharedRef());
}

void FMythicEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		return;
	}

	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(StatContainerAssetTypeActions.ToSharedRef());
}

EAssetTypeCategories::Type FMythicEditorModule::GetMythicCategory() const
{
	return MythicCategory;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMythicEditorModule, MythicEditor)