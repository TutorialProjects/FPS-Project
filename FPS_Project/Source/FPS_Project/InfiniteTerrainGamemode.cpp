// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "InfiniteTerrainGamemode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"



AInfiniteTerrainGamemode::AInfiniteTerrainGamemode()
{
	NavMeshPool = CreateDefaultSubobject<UActorPool>(TEXT("NAV POOL"));
}

void AInfiniteTerrainGamemode::PopulateBoundsVolumePool() {
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		
		ANavMeshBoundsVolume* FoundActor = *VolumeIterator;
		NavMeshPool->Add(*VolumeIterator);
		//AddToPool(*VolumeIterator);
			++VolumeIterator;
	}

}
void AInfiniteTerrainGamemode::AddToPool(ANavMeshBoundsVolume * VolumeToAdd)
{
	NavMeshPool->Add(VolumeToAdd);
}
