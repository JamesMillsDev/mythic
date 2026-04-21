// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/MythicSaveGame.h"

#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

#include "Stats/Data/MythicStatContainer.h"

void UMythicSaveGame::SerializeStatContainer_Implementation(UMythicStatContainer* Container, FName ContainerTag)
{
	if (!IsValid(Container))
	{
		return;
	}

	// Find / Add the generated binary data
	FMythicSerializedContainer& ByteContainer = SerializedContainers.FindOrAdd(ContainerTag);
	ByteContainer.Bytes.Reset();

	// Generate the memory writer and proxy archive from the bytes
	FMemoryWriter MemoryWriter(ByteContainer.Bytes, true);
	FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, false);

	// Serialize this object
	Archive.ArIsSaveGame = true;
	Container->Serialize(Archive);
}

void UMythicSaveGame::DeserializeStatContainer_Implementation(UMythicStatContainer* Container, FName ContainerTag)
{
	if (!IsValid(Container))
	{
		return;
	}

	// Find the binary data, if it doesn't exist, or is empty, exit
	FMythicSerializedContainer* ByteContainer = SerializedContainers.Find(ContainerTag);
	if (ByteContainer == nullptr || ByteContainer->Bytes.IsEmpty())
	{
		return;
	}

	// Generate the memory reader and proxy archive from the bytes
	FMemoryReader MemoryReader(ByteContainer->Bytes, true);
	FObjectAndNameAsStringProxyArchive Archive(MemoryReader, false);

	// Deserialize this object
	Archive.ArIsSaveGame = true;
	Container->Serialize(Archive);
}
