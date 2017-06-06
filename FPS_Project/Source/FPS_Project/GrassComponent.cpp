// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "GrassComponent.h"


UGrassComponent::UGrassComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UGrassComponent::BeginPlay() {

	Super::BeginPlay();
	SpawnGrass();
}

void UGrassComponent::SpawnGrass()
{
	if (SpawningExtent == NULL) { SpawningExtent = FBox(FVector(0.f, -5000.f, 0.f), FVector(10000.f, 5000.f, 0.f)); }
	for (int32 tile = 0; tile < SpawnCount; tile++)
	{
		FVector Location = FMath::RandPointInBox(SpawningExtent);
		float uniformScale = FMath::RandRange(MinScale, MaxScale);
		FVector Scale= FVector(uniformScale);

		AddInstance(FTransform(FQuat::Identity,Location, Scale));
	}
}