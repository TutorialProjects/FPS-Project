// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class FPS_PROJECT_API AGun : public AActor
{
	GENERATED_BODY()
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditAnywhere, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;
public:	
	// Sets default values for this actor's properties
	AGun();
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPS_ProjectProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation1P;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation3P;
	UPROPERTY()
	class UAnimInstance* AnimInstance1P;
	UPROPERTY()
	class UAnimInstance* AnimInstance3P;
public:
	UFUNCTION(BlueprintCallable, Category = "FIRING")
	void OnFire();
	UPROPERTY(EditAnywhere)
	float Damage = 100;
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// fires a fag


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
