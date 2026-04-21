// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Stats/Data/StatContainerAssetTypeActions.h"

class FMythicEditorModule : public IModuleInterface
{
public:
	FORCEINLINE static FMythicEditorModule& GetModule()
	{
		static const FName ModuleName = "MythicEditor";
		return FModuleManager::LoadModuleChecked<FMythicEditorModule>(ModuleName);
	}
	
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	EAssetTypeCategories::Type GetMythicCategory() const;

private:
	TSharedPtr<FStatContainerAssetTypeActions> StatContainerAssetTypeActions;

	EAssetTypeCategories::Type MythicCategory = EAssetTypeCategories::Type::None;
	
};
