// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "PatrolRoute.h"


// Sets default values
UPatrolRoute::UPatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryComponentTick.bCanEverTick = true;

}

TArray<AActor*> UPatrolRoute::GetActorList() const {

	return PatrolPoints;
}


