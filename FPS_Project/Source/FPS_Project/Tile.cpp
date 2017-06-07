// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NavigationBoundsOffset = FVector(5000.f, 0.f, 0.f);
	MinBound = FVector(0.f, -5000.f, 0);
	MaxBound = FVector(10000.f, 5000.f, 0);
}

void ATile::SetNavPool(UActorPool* ActorPool) {
	NavPool = ActorPool;

	//PositionNavMeshBoundsVolume();
	NavMeshBoundsVolume = NavPool->Checkout();

	if (!NavMeshBoundsVolume) { UE_LOG(LogTemp, Error, TEXT("Not enough Actors in pool. Penis Cakes.")) return; }
	 UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: {%s}."),*GetName(), *NavMeshBoundsVolume->GetName())
	
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation()+ NavigationBoundsOffset);
	 GetWorld()->GetNavigationSystem()->Build();
	
}

void ATile::PlaceActors(TSubclassOf<AActor> SpawnTypeA, int32 MinSpawnAmount = 1, int32 MaxSpawnAmount = 20, float OverlapCheckRadius = 300, float MinScale = 1.f, float MaxScale = 1.f)
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(MinSpawnAmount, MaxSpawnAmount, OverlapCheckRadius, MinScale, MaxScale);
	for (FSpawnPosition SpawnPosition : SpawnPositions) 
	{
		PlaceActor(SpawnTypeA, SpawnPosition);
	
	}
}
void ATile::PlaceAIPawns(TSubclassOf<APawn> SpawnTypeA, FSpawnCustomizations SpawnParams, bool FreeForAllMode = false)
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(SpawnParams.MinSpawnAmount, SpawnParams.MaxSpawnAmount, SpawnParams.Radius, SpawnParams.MinScale, SpawnParams.MaxScale);
	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceAIPawn(SpawnTypeA, SpawnPosition, FreeForAllMode);
		

	}
}
void ATile::PlaceAIPawn(TSubclassOf<APawn> &SpawnTypeA, FSpawnPosition &SpawnPosition, bool FreeForAllMode)
{
	FRotator Rotation = FRotator(0, SpawnPosition.RotationYaw, 0);
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(SpawnTypeA, SpawnPosition.Location, Rotation);
	CleanupList.Add(Spawned);
	if (!Spawned) { return; }

	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
	Spawned->SpawnDefaultController();
	if (FreeForAllMode) { Spawned->Tags.Add(FName("PlayerTeam")); }
					else { Spawned->Tags.Add(FName("Enemy")); }
}

//void ATile::PlaceActor(TSubclassOf<AActor> SpawnTypeA, FVector SpawnPoint, float RotationYaw, float Scale) {
void ATile::PlaceActor(TSubclassOf<AActor> SpawnTypeA, FSpawnPosition SpawnPosition) {


	//	UE_LOG(LogTemp, Warning, TEXT("SpawnPoint: %s"), *SpawnPoint.ToString())
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(SpawnTypeA);
	CleanupList.Add(Spawned);
	if (!Spawned) { return; }
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.RotationYaw, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}
TArray<FSpawnPosition> ATile::RandomSpawnPositions(int32 MinSpawnAmount = 1, int32 MaxSpawnAmount = 20, float OverlapCheckRadius = 300, float MinScale = 1.f, float MaxScale = 1.f)
{
	TArray<FSpawnPosition> SpawnPositions;
	int32 SpawnAmount = FMath::RandRange(MinSpawnAmount, MaxSpawnAmount);
	for (int32 spawn = 0; spawn <= SpawnAmount; spawn++)
	{

		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool CanSpawn = FindEmptyLocation(SpawnPosition.Location, OverlapCheckRadius*SpawnPosition.Scale);
		SpawnPosition.RotationYaw = FMath::RandRange(-180.f, 180.f);
		if (CanSpawn)
		{
			SpawnPositions.Add(SpawnPosition);
		}
		//FVector SpawnPoint = FMath::RandPointInBox(Bounds);
	}
	return SpawnPositions;

}
bool ATile::FindEmptyLocation(FVector& OutLocation, float CheckRadius) {

	FBox Bounds(MinBound, MaxBound);
	const int32 MAX_ATTEMPTS = 20;
	for (int32 attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnSphereCheck(CandidatePoint, CheckRadius)){
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}



// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}
void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (NavPool && NavMeshBoundsVolume) {
		NavPool->Return(NavMeshBoundsVolume); 
	}
	for (int i = 0; i < CleanupList.Num(); i++) {
		if (CleanupList[i] != nullptr) {
			CleanupList[i]->Destroy();
		}
	}
	//for (AActor* ToBeDestroyed : CleanupList)
	//{
	//if (ToBeDestroyed != nullptr) {
		//	ToBeDestroyed->Destroy();
	//}
	//}
	

}
// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ATile::CanSpawnSphereCheck(FVector Location, float Radius = 300.f) {
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool hasHit =GetWorld()->SweepSingleByChannel(
				HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius)
				);
	FColor ResultColor = hasHit ? FColor::Red : FColor::Green;
//	DrawDebugSphere(GetWorld(), Location, Radius, 16, ResultColor, true, 100.f);
	if (bShouldDrawDebug == true) {
		DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, Radius);
	}
	return !hasHit;
}

void ATile::SetDrawDebugCapsule(bool shouldDrawDebug) {
	bShouldDrawDebug = shouldDrawDebug;
}


/*
void ATile::PositionNavMeshBoundsVolume(){

	// see bottom of ATile:SetNavPool(){}

*/