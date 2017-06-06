// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition 
{
	GENERATED_USTRUCT_BODY()
	FVector Location; 
	float RotationYaw = 0; 
	float Scale = 1;
};
USTRUCT(BlueprintType)
struct FSpawnCustomizations
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = SpawnParams)
	int32 MinSpawnAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	int32 MaxSpawnAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	float Radius = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	float MinScale = 1; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnParams)
	float MaxScale = 1;
};
class UActorPool;

UCLASS()
class FPS_PROJECT_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category = THINGY)
	void PlaceActors(TSubclassOf<AActor> SpawnTypeA, int32 MinSpawnAmount , int32 MaxSpawnAmount, float Radius, float MinScale, float MaxScale);
	UFUNCTION(BlueprintCallable, Category = THINGY)
	void PlaceAIPawns(TSubclassOf<APawn> SpawnTypeA, FSpawnCustomizations SpawnParams, bool FreeForAllMode);



	
	UFUNCTION(BlueprintCallable, Category = THINGY)
	void SetDrawDebugCapsule(bool shouldDrawDebug);

private:
	bool bShouldDrawDebug = false;
	bool CanSpawnSphereCheck(FVector Location, float Radius);
	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	//void PlaceActor(TSubclassOf<AActor> SpawnTypeA, FVector SpawnPoint, float RotationYaw, float Scale);

	void PlaceActor(TSubclassOf<AActor> SpawnTypeA, FSpawnPosition SpawnPosition);
	void PlaceAIPawn(TSubclassOf<APawn> &SpawnTypeA, FSpawnPosition &SpawnPosition, bool FreeForAllMode);

	AActor* NavMeshBoundsVolume;
	TArray<FSpawnPosition> RandomSpawnPositions(int32 MinSpawnAmount, int32 MaxSpawnAmount, float OverlapCheckRadius, float MinScale, float MaxScale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(EditAnywhere, Category = SPAWNING)
		FVector MinBound = FVector(0.f, -5000.f, 0);
	UPROPERTY(EditAnywhere, Category = SPAWNING)
	FVector MaxBound = FVector(10000.f, 5000.f, 0);
	UPROPERTY(EditAnywhere, Category = SPAWNING)
	FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UActorPool* NavPool;
	UFUNCTION(BlueprintCallable,Category = POOL)
		void SetNavPool(UActorPool* ActorPool);

};
