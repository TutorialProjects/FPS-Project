// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> SpawnTypeA, int MinSpawnAmount, int MaxSpawnAmount, float ZSpawnOverride) {
	FVector Min(0.f, -5000.f, ZSpawnOverride);
	FVector Max(10000.f, 5000.f, ZSpawnOverride);
	FBox Bounds(Min, Max);
	int SpawnAmount = FMath::RandRange(MinSpawnAmount, MaxSpawnAmount);
	for (int spawn = 0; spawn <= SpawnAmount; spawn++) {
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		UE_LOG(LogTemp, Warning, TEXT("SpawnPoint: %s"), *SpawnPoint.ToString())
			AActor* Spawned = GetWorld()->SpawnActor<AActor>(SpawnTypeA);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	CastSphere(GetActorLocation()+FVector(0,0,1000.f),1000.f);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ATile::CastSphere(FVector Location, float Radius = 300.f) {
	FHitResult HitResult;
	bool hasHit =GetWorld()->SweepSingleByChannel(
				HitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius)
				);
	FColor ResultColor = hasHit ? FColor::Red : FColor::Green;
//	DrawDebugSphere(GetWorld(), Location, Radius, 16, ResultColor, true, 100.f);
	DrawDebugCapsule(GetWorld(), Location,0, Radius, FQuat::Identity, ResultColor, true, 100.f);
	return hasHit;
}


