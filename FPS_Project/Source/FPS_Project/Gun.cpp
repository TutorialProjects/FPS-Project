// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "Gun.h"
#include "FPS_ProjectProjectile.h"
#include "Animation/AnimInstance.h"



// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = true;
	FP_Gun->CastShadow = true;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
	//	FP_Gun->SetupAttachment(Mesh1P);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
//	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::OnFire()
{
	//UE_LOG(LogTemp,Warning,TEXT("Gun Actor Fire Called."))
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
				const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				auto GunProjectile = World->SpawnActor<AFPS_ProjectProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				if (GunProjectile) { GunProjectile->ProjectileDamage = Damage; }
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation3P != NULL && AnimInstance3P != NULL)
	{
		AnimInstance3P->Montage_Play(FireAnimation3P, 1.f);
	}
	if (FireAnimation1P != NULL && AnimInstance1P != NULL)
	{
		AnimInstance1P->Montage_Play(FireAnimation1P, 1.f);
	}
	
}