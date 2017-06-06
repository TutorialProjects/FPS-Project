// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPS_ProjectGameMode.h"
#include "InfiniteTerrainGamemode.generated.h"

/**
 * 
 */

UCLASS()
class FPS_PROJECT_API AInfiniteTerrainGamemode : public AFPS_ProjectGameMode
{
	GENERATED_BODY()

		AInfiniteTerrainGamemode();
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = POOL)
	class UActorPool* NavMeshPool;

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
		void PopulateBoundsVolumePool();
	
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);
};
