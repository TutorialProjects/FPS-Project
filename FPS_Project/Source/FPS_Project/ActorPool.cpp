// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Checkout()
{
	if (Pool.Num() == 0) { UE_LOG(LogTemp, Error, TEXT("did NOT pop")) return nullptr; }
	UE_LOG(LogTemp, Error, TEXT("popped"))
	return Pool.Pop();
}

void UActorPool::Return(AActor * ActorToReturn)
{
	if (!ActorToReturn) { return; }
	Add(ActorToReturn);
	
}

void UActorPool::Add(AActor * ActorToAdd)
{
	if (!ActorToAdd) { return; }
	Pool.Push(ActorToAdd);
}