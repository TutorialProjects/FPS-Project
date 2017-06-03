// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "WaypointMan.generated.h"
class AGun;
UCLASS()
class FPS_PROJECT_API AWaypointMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWaypointMan();
	UPROPERTY(EditAnywhere)
	UChildActorComponent* ChildRef_Gun;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;
	UFUNCTION(BlueprintCallable)
		void PullTrigger();
	//UPROPERTY(EditAnywhere)
	 AGun* GunActor = nullptr ;
	// UInputComponent* GrabbedInputComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
