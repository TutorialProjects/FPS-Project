// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class FPS_PROJECT_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

		UGrassComponent();
	UPROPERTY(EditAnywhere, Category = SPAWNING)
		FBox SpawningExtent;
	UPROPERTY(EditAnywhere, Category = SPAWNING)
	float MinScale = 1;
	UPROPERTY(EditAnywhere, Category = SPAWNING)
	float MaxScale = 1;
	UPROPERTY(EditAnywhere, Category = SPAWNING)
		int32 SpawnCount = 200;
protected:
	virtual void BeginPlay() override;
	void SpawnGrass();
	
};
