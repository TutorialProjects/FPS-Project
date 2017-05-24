// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"

UCLASS(Classgroup=(Custom),meta=(BlueprintSpawnableComponent))
class FPS_PROJECT_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPatrolRoute();
	UPROPERTY(EditAnywhere)
	TArray<AActor*> PatrolPoints;

	TArray<AActor*> GetActorList() const;


	
	
};
